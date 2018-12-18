@extends('layouts/default')

@section('content')
    <div class="container">
        <div class="row mt-5">
            <div class="col-md-4">
                <div class="card text-white bg-dark">
                    <div class="card-body">
                        @if (!is_null($game->winner))
                        <h5 class="card-title">Game finished</h5>
                        <p class="card-text"><strong>{{ $game->winner }}</strong> won the game! (<strong>{{ $game->winner_score }}</strong> vs {{ $game->looser_score }})</p>
                        @elseif (!is_null($game->opponent_sid))
                        <h5 id="status-title" class="card-title">Game queued</h5>
                        <p id="status-desc" class="card-text">The game has been queued. It should start within few seconds.</p>
                        @else
                        <h5 id="status-title" class="card-title">Waiting for an opponent...</h5>
                        <p id="status-desc" class="card-text">In order to join the game, please give this link to your opponent:</p>
                        @endif
                        <input class="form-control" type="text" value="{{ route('game.view', ['id' => $game->id]) }}" disabled>
                    </div>
                </div>
            </div>
            <div class="col-md-8">
                <h5>Filler #{{ $game->id }}</h5>
                <div class="filler-color text-success float-left"><span class="font-weight-bold">O</span> - {{ $game->champion_name }}</div>
                <div class="filler-color text-danger float-right"><span class="font-weight-bold">X</span> - <span id="opponent-name">{{ $game->opponent_name ?: '???' }}</span></div>
                @if (isset($board))
                    @for ($y = 0; $y < $game->map_height; $y++)
                <div class="filler-map">
                    @for ($x = 0; $x < $game->map_width; $x++)
                        @if ($board[$y][$x] == 'O' || $board[$y][$x] == 'o')
                    <span class="text-success bg-success">.</span>
                        @elseif ($board[$y][$x] == 'X' || $board[$y][$x] == 'x')
                    <span class="text-danger bg-danger">.</span>
                        @else
                    <span>.</span>
                        @endif
                    @endfor
                </div>
                    @endfor
                @else
                    @for ($y = 0; $y < $game->map_height; $y++)
                <div class="filler-map">
                    @for ($x = 0; $x < $game->map_width; $x++)
                    <span id="filler-{{ $y }}-{{ $x }}">.</span>
                    @endfor
                </div>
                    @endfor
                @endif
            </div>
        </div>
    </div>
    @if (is_null($game->opponent_sid) && session()->getId() != $game->session_id)
    <div class="modal fade" id="joinModal" data-backdrop="static" data-keyboard="false" tabindex="-1" role="dialog" aria-labelledby="modalTitle" aria-hidden="true">
        <div class="modal-dialog" role="document">
            <div class="modal-content">
                <form method="post" action="{{ route('game.join', ['id' => $game->id]) }}" enctype="multipart/form-data">
                    @csrf
                    <div class="modal-header">
                        <h5 class="modal-title" id="modalTitle">Join the battle</h5>
                    </div>
                    <div class="modal-body">
                        <div class="form-group">
                            <label for="champ">Champion</label>
                            <div class="custom-file">
                                <input id="champ" name="champ" type="file" class="custom-file-input" required>
                                <label for="champ" class="custom-file-label">Choose your player</label>
                            </div>
                        </div>
                    </div>
                    <div class="modal-footer">
                        <button type="button" class="btn btn-secondary" data-dismiss="modal">Just watch</button>
                        <button type="submit" class="btn btn-success">FIGHT!</button>
                    </div>
                </div>
            </form>
        </div>
    </div>
        @push('scripts')
    <script>
        $(document).ready(function() {
            $('#joinModal').modal('show');
        });
    </script>
        @endpush
    @endif
@endsection

@push('scripts')
<script src="{{ asset('js/app.js') }}"></script>
<script>
    Echo.channel('state.{{ $game->id }}').listen('FillerStateUpdate', function(evt) {
        switch (evt.state)
        {
            case 1:
                $("#status-title").text("Opponent found!");
                $("#status-desc").text("Your game has been queued. It should starts within few seconds.");
                $("#opponent-name").text(evt.data.opponent);
                break;
            case 2:
                $("#status-title").text("Playing");
                $("#status-desc").text("Game is running.");
                break;
            case 3:
                $("#status-title").text("Game finished");
                $("#status-desc").html('<strong>' + evt.data.winner + '</strong> won the game! (<strong>' + evt.data.winner_score + '</strong> vs ' + evt.data.looser_score + ')');
                break;
        }
    });

    Echo.channel('board.{{ $game->id }}').listen('FillerBoardUpdate', function(evt) {
        for (var row = 0; row < evt.board.length; row++) {
            var cols = evt.board[row].length;
            for (var col = 0; col < cols; col++) {
                var char = evt.board[row].charAt(col).toUpperCase();
                if (char == 'O')
                    $('#filler-' + row + '-' + col).addClass('text-success bg-success');
                else if (char == 'X')
                    $('#filler-' + row + '-' + col).addClass('text-danger bg-danger');
            }
        }
    });
</script>
@endpush
