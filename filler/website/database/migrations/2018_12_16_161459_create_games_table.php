<?php

use Illuminate\Support\Facades\Schema;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateGamesTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('games', function (Blueprint $table) {
            $table->increments('id');
            $table->integer('map_size');
            $table->string('session_id');
            $table->string('champion_name');
            $table->string('opponent_sid')->nullable();
            $table->string('opponent_name')->nullable();
            $table->string('winner')->nullable();
            $table->integer('winner_score')->nullable();
            $table->integer('looser_score')->nullable();
            $table->longText('board')->nullable();
            $table->timestamps();
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('games');
    }
}
