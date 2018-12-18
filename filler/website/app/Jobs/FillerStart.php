<?php

namespace App\Jobs;

use App\Game;
use App\Events\FillerBoardUpdate;
use App\Events\FillerStateUpdate;

use Illuminate\Bus\Queueable;
use Illuminate\Queue\SerializesModels;
use Illuminate\Queue\InteractsWithQueue;
use Illuminate\Contracts\Queue\ShouldQueue;
use Illuminate\Foundation\Bus\Dispatchable;
use Illuminate\Support\Facades\Storage;

class FillerStart implements ShouldQueue
{
    use Dispatchable, InteractsWithQueue, Queueable, SerializesModels;

    protected $game;

    /**
     * Create a new job instance.
     *
     * @return void
     */
    public function __construct(Game $game)
    {
        $this->game = $game;
    }

    protected function read_board($handle, int $rows)
    {
        fgets($handle); // Skip premiere ligne
        $board = [];
        for ($row = 0; $row < $rows; $row++)
        {
            $buffer = fgets($handle);
            array_push($board, substr($buffer, 4, strlen($buffer) - 5));
        }
        event(new FillerBoardUpdate($this->game, $board));
        return $board;
    }

    /**
     * Execute the job.
     *
     * @return void
     */
    public function handle()
    {
        event(new FillerStateUpdate($this->game, 2));
        $champion_path = storage_path("app") . "/players/{$this->game->id}/{$this->game->champion_name}.filler";
        $opponent_path = storage_path("app") . "/players/{$this->game->id}/{$this->game->opponent_name}.filler";
        chmod($champion_path, 740);
        chmod($opponent_path, 740);
        $handle = popen(storage_path("app") . "/filler_vm -f " . storage_path("app") . "/maps/{$this->game->map_width}x{$this->game->map_height} -p1 {$champion_path} -p2 {$opponent_path}", "r");
        $winner = "???";
        $winner_score = 0;
        $looser_score = 0;
        $board = [];
        while (($buffer = fgets($handle)) !== false)
        {
            if (substr($buffer, 0, 7) === "Plateau")
            {
                $parts = explode(" ", $buffer);
                $board = $this->read_board($handle, $parts[1]);
            }
            else if (substr($buffer, 0, 3) === "== ")
            {
                $winner_score = (int)explode(" ", $buffer)[3];
                $looser_score = (int)explode(" ", fgets($handle))[3];
                if ($winner_score > $looser_score)
                    $winner = $this->game->champion_name;
                else if ($winner_score == $looser_score)
                    $winner = "-";
                else
                {
                    $tmp = $winner_score;
                    $winner_score = $looser_score;
                    $looser_score = $tmp;
                    $winner = $this->game->opponent_name;
                }
            }
        }
        pclose($handle);
        event(new FillerStateUpdate($this->game, 3, [
            'winner' => $winner,
            'winner_score' => $winner_score,
            'looser_score' => $looser_score
        ]));
        $this->game->winner = $winner;
        $this->game->winner_score = $winner_score;
        $this->game->looser_score = $looser_score;
        $this->game->board = implode("|", $board);
        $this->game->save();
    }
}
