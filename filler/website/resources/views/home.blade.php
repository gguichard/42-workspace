@extends('layouts/default')

@section('content')
    <div class="container filler-container">
        <div class="row align-items-center justify-content-center">
            <div class="col-md-7">
                @include('parts/error')
                <div class="jumbotron text-center">
                    <h1 class="jumbotron-heading">Filler</h1>
                    <p class="lead text-muted">Create games, fight against your friends and watch who is the best!</p>
                    <button type="button" class="btn btn-primary btn-lg btn-block" data-toggle="modal" data-target="#createModal">Create a private game</button>
                </div>
            </div>
        </div>
    </div>
    <div class="modal fade" id="createModal" tabindex="-1" role="dialog" aria-labelledby="modalTitle" aria-hidden="true">
        <div class="modal-dialog" role="document">
            <div class="modal-content">
                <form method="post" action="{{ route('game.store') }}" enctype="multipart/form-data">
                    @csrf
                    <div class="modal-header">
                        <h5 class="modal-title" id="modalTitle">Create game</h5>
                        <button type="button" class="close" data-dismiss="modal" aria-label="Fermer">
                            <span aria-hidden="true">&times;</span>
                        </button>
                    </div>
                    <div class="modal-body">
                        <div class="form-group">
                            <label for="map">Map size</label>
                            <select id="map" name="map" class="form-control" required>
                                <option value="15">15x15</option>
                                <option value="24">24x24</option>
                                <option value="100">100x100</option>
                            </select>
                        </div>
                        <div class="form-group">
                            <label for="champ">Champion</label>
                            <div class="custom-file">
                                <input id="champ" name="champ" type="file" class="custom-file-input" required>
                                <label for="champ" class="custom-file-label">Choose your player</label>
                            </div>
                        </div>
                    </div>
                    <div class="modal-footer">
                        <button type="button" class="btn btn-secondary" data-dismiss="modal">Cancel</button>
                        <button type="submit" class="btn btn-success">Create</button>
                    </div>
                </div>
            </form>
        </div>
    </div>
@endsection