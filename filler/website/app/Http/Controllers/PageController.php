<?php

namespace App\Http\Controllers;

use App\Game;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\DB;

class PageController extends Controller
{

    public function home()
    {
        return view('home');
    }
}
