<?php

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', ['as' => 'home', 'uses' => 'PageController@home']);
Route::post('game/store', ['as' => 'game.store', 'uses' => 'GameController@store']);
Route::get('game/{id}', ['as' => 'game.view', 'uses' => 'GameController@view'])->where('id', '[0-9]+');
Route::post('game/{id}/join', ['as' => 'game.join', 'uses' => 'GameController@join'])->where('id', '[0-9]+');
