//
// Created by Karol on 29.05.2026.
//

#include "Engine.h"

Engine::Engine() {

}


Engine &Engine::instance() {
    static Engine engine;
    return engine;
}

bool Engine::fire(int row, int col) {
    if (computer_board[row][col]!=0) {return false;}
    computer_board[row][col] = 1;
    return true;
}

bool Engine::ship_setup_correct() {
    return true;
}

int Engine::get_tile_state(int row, int col) {
    return player_board[row][col];
}

void Engine::add_ship(int row, int col, int ship_length) {
    player_board[row][col] = 1;
}

void Engine::remove_ship(int row, int col, int ship_length) {
    player_board[row][col] = 0;
}




