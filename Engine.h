//
// Created by Karol on 29.05.2026.
//

#ifndef ENGINE_H
#define ENGINE_H
#include "SetupTile.h"


class Engine {
private:
    Engine();
    ~Engine() = default;

    Engine(const Engine &) = delete;
    Engine &operator=(const Engine &) = delete;

    int player_board[10][10] = {};
    int computer_board[10][10] = {};
public:
    static Engine& instance();

    bool fire(int row, int col);
    bool ship_setup_correct();

    void add_ship(int row, int col, int ship_length);

    void remove_ship(int row, int col, int ship_length);

    int get_tile_state(int row, int col);
};



#endif //ENGINE_H
