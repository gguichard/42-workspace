@if (session()->has('error'))
<div class="alert alert-danger" role="alert">
    <strong>Error!</strong> {{ session()->get('error') }}
    <button type="button" class="close" data-dismiss="alert" aria-label="Fermer">
        <span aria-hidden="true">&times;</span>
    </button>
</div>
@endif