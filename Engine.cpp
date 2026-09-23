#include "Engine.h"

Engine &Engine::instance() {
    static Engine engine;
    return engine;
}

bool Engine::placeShip(int row, int col, int length, Orientation orientation, int id) {
    if (row<0 || col<0){return false;}
    for (int i=0; i<length; i++) {
        if (orientation == Orientation::Horizontal) {
            if (col+i>=10) {return false;}
            if (player_board[row][col+i].id!=-1){return false;}
        }
        else {
            if (row+i>=10) {return false;}
            if (player_board[row+i][col].id!=-1){return false;}
        }
    }
    for (int i=0; i<length; i++) {
        if (orientation == Orientation::Horizontal) {
            player_board[row][col+i].id = id;
            player_board[row][col+i].mastIndex = i;
        }
        else {
            player_board[row+i][col].id = id;
            player_board[row+i][col].mastIndex = i;
        }
    }
    player_ships[id].length = length;
    player_ships[id].orientation = orientation;
    player_ships[id].startRow = row;
    player_ships[id].startCol = col;
    emit boardUpdate();
    return true;
};

bool Engine::has_ship_at(BoardOwner owner,int row, int col) {
    return get_tile_internal(owner, row, col).id>=0;
};

ShipData Engine::get_ship_at(BoardOwner owner,int row, int col) {
    return get_ship_internal(owner)[get_tile_internal(owner, row, col).id];
};

void Engine::pickup_ship(int row, int col) {
    ShipData ship = player_ships[player_board[row][col].id];
    if (ship.orientation == Orientation::Horizontal) {
        for (int c = ship.startCol; c < ship.startCol + ship.length; c++) {
            player_board[ship.startRow][c].id = -1;
            player_board[ship.startRow][c].mastIndex = -1;
        }
    }
    else {
        for (int r = ship.startRow; r < ship.startRow + ship.length; r++) {
            player_board[r][ship.startCol].id = -1;
            player_board[r][ship.startCol].mastIndex = -1;
        }
    }
    emit boardUpdate();
};

void Engine::cancel_pickup(ShipData ship, int id) {
    if (ship.orientation == Orientation::Horizontal) {
        for (int i=0; i<ship.length; i++) {
            player_board[ship.startRow][ship.startCol+i].id = id;
            player_board[ship.startRow][ship.startCol+i].mastIndex = i;
        }
    }
    else {
        for (int i=0; i<ship.length; i++) {
            player_board[ship.startRow+i][ship.startCol].id = id;
            player_board[ship.startRow+i][ship.startCol].mastIndex = i;
        }
    }
    emit boardUpdate();
}

void Engine::setup_ships() {
    add_ship(BoardOwner::Player,0,0,5,Orientation::Vertical);
    add_ship(BoardOwner::Player,0,2,4,Orientation::Vertical);
    add_ship(BoardOwner::Player,0,4,3,Orientation::Vertical);
    add_ship(BoardOwner::Player,0,5,3,Orientation::Vertical);
    add_ship(BoardOwner::Player,0,6,2,Orientation::Vertical);
    emit boardUpdate();
};

void Engine::add_ship(BoardOwner owner,int startRow, int startCol, int length, Orientation orientation) {
    ShipData ship(length,orientation,startRow,startCol);
    get_ship_internal(owner).push_back(ship);
    if (orientation == Orientation::Horizontal) {
        for (int i=0; i<ship.length; i++) {
            get_tile_internal(owner, startRow, startCol+i).id = get_ship_internal(owner).size()-1;
            get_tile_internal(owner, startRow, startCol+i).mastIndex = i;
        }
    }
    else {
        for (int i=0; i<ship.length; i++) {
            get_tile_internal(owner, startRow+i, startCol).id = get_ship_internal(owner).size()-1;
            get_tile_internal(owner, startRow+i, startCol).mastIndex = i;
        }
    }
}

bool Engine::can_add_ship(int startRow, int startCol, int lenght, Orientation orientation) {
    if (orientation == Orientation::Horizontal) {
        if (startCol+lenght>10){return false;}
        for (int i=-1;i<=lenght;i++) {
            if (startCol+i<0 || startCol+i>=10){continue;}
            for (int j=-1; j<2;j++) {
                if (startRow+j<0 || startRow+j>=10){continue;}
                if (computer_board[startRow+j][startCol+i].id!=-1) {return false;}
            }
        }
    }
    if (orientation == Orientation::Vertical) {
        if (startRow+lenght>10){return false;}
        for (int i=-1;i<=lenght;i++) {
            if (startRow+i<0 || startRow+i>=10){continue;}
            for (int j=-1; j<2;j++) {
                if (startCol+j<0 || startCol+j>=10){continue;}
                if (computer_board[startRow+i][startCol+j].id!=-1){return false;}
            }
        }
    }
    return true;
}

void Engine::clear_computer_board() {
    for (int i=0;i<10;i++) {
        for (int j=0;j<10;j++) {
            computer_board[i][j] = TileData{};
        }
    }
    computer_ships.clear();
}

TileData Engine::get_tile_at(BoardOwner owner,int row, int col) {
    return get_tile_internal(owner, row, col);
}

ShotResult Engine::fire(BoardOwner owner, int row, int col) {
    if (row<0 || row>=10 || col<0 || col>=10) {return ShotResult::Invalid;}
    if (get_tile_internal(owner, row, col).hit == true){return ShotResult::Invalid;}
    get_tile_internal(owner, row, col).hit = true;
    emit boardUpdate();
    if (get_tile_internal(owner, row, col).id == -1){return ShotResult::Miss;}
    if (ship_sunken(owner, row, col)){return ShotResult::Sunk;}
    return ShotResult::Hit;
}

bool Engine::ship_sunken(BoardOwner owner, int row, int col) {
    if (get_tile_internal(owner, row, col).id == -1){return false;}
    ShipData& ship = get_ship_internal(owner)[get_tile_internal(owner, row, col).id];
    bool sunken = true;
    if (ship.orientation == Orientation::Horizontal) {
        for (int i=0; i<ship.length; i++) {
            if (!get_tile_internal(owner, ship.startRow, ship.startCol+i).hit) {
                sunken = false;
                return sunken;
            }
        }
    }
    else {
        for (int i=0; i<ship.length; i++) {
            if (!get_tile_internal(owner, ship.startRow+i, ship.startCol).hit) {
                sunken = false;
                return sunken;
            }
        }
    }
    ship.sunken = true;
    return sunken;
}

bool Engine::ship_setup_correct() {
    int id = 0;
    for (const auto& ship:player_ships) {
        for (int i=-1; i<=ship.length; i++) {
            for (int j=-1; j<=1; j++) {
                if (ship.orientation == Orientation::Horizontal) {
                    if (ship.startRow+j<0 || ship.startRow+j>=10 || ship.startCol+i<0 || ship.startCol+i>=10) {continue;}
                    if (player_board[ship.startRow+j][ship.startCol+i].id == id){continue;}
                    if (player_board[ship.startRow+j][ship.startCol+i].id!=-1) {return false;}
                }
                else {
                    if (ship.startRow+i<0 || ship.startRow+i>=10 || ship.startCol+j<0 || ship.startCol+j>=10) {continue;}
                    if (player_board[ship.startRow+i][ship.startCol+j].id == id){continue;}
                    if (player_board[ship.startRow+i][ship.startCol+j].id!=-1) {return false;}
                }
            }
        }
        id++;
    }
    return true;
}

Winner Engine::is_game_ended() {
    bool player_won = true;
    bool computer_won = true;
    for (const auto& ship : player_ships) {
        if (!ship.sunken) {
            computer_won = false;
            break;
        }
    }
    for (const auto& ship : computer_ships) {
        if (!ship.sunken) {
            player_won = false;
            break;
        }
    }
    if (player_won || computer_won) {
        return (player_won)?Winner::Player:Winner::Computer;
    }
    return Winner::Unresolved;
}

bool Engine::is_tile_hit(BoardOwner owner, int row, int col) {
    return get_tile_internal(owner, row, col).hit;
}

TileData& Engine::get_tile_internal(BoardOwner owner,int row, int col){
    return (owner == BoardOwner::Player) ? player_board[row][col] : computer_board[row][col];
}

std::vector<ShipData>& Engine::get_ship_internal(BoardOwner owner) {
    return (owner == BoardOwner::Player) ? player_ships : computer_ships;
}







