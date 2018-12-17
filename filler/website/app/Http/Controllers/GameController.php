<?php

namespace App\Http\Controllers;

use App\Game;
use App\Jobs\FillerStart;
use App\Events\FillerStateUpdate;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\DB;

class GameController extends Controller
{

    public function view(int $id)
    {
        $game = Game::findOrFail($id);
        return view('game', ['game' => $game]);
    }

    public function store(Request $request)
    {
        $this->validate($request, [
            'map' => 'required|string|in:15,24,100',
            'champ' => 'required|file|max:50|mimetypes:application/octet-stream'
        ]);
        $game = new Game;
        $game->map_size = $request->input('map');
        $game->session_id = session()->getId();
        $game->champion_name = str_replace(".filler", "", $request->file('champ')->getClientOriginalName());
        $game->save();
        $request
            ->file('champ')
            ->storeAs("players/{$game->id}", $request->file('champ')->getClientOriginalName());
        return redirect()->route('game.view', ['id' => $game->id]);
    }

    public function join(int $id, Request $request)
    {
        $game = Game::findOrFail($id);
        if (!is_null($game->opponent_sid))
        {
            return redirect()
                ->route('home')
                ->with('error', 'The player is already fighting with someone else.');
        }
        else if (session()->getId() == $game->session_id)
        {
            return redirect()
                ->route('home')
                ->with('error', "You can't play with yourself.");
        }
        $this->validate($request, [
            'champ' => 'required|file|max:50|mimetypes:application/octet-stream'
        ]);
        $game->opponent_sid = session()->getId();
        $game->opponent_name = str_replace(".filler", "", $request->file('champ')->getClientOriginalName());
        $game->save();
        $request
            ->file('champ')
            ->storeAs("players/{$game->id}", $request->file('champ')->getClientOriginalName());
        event(new FillerStateUpdate($game, 1, ['opponent' => $game->opponent_name]));
        FillerStart::dispatch($game);
        return redirect()->route('game.view', ['id' => $game->id]);
    }
}
