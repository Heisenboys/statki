#include "Engine.h"

Engine &Engine::instance() {
    static Engine engine;
    return engine;
}

void Engine::placeShip(BoardOwner owner, int startRow, int startCol, int length, Orientation orientation, int id) {
    const int dRow = (orientation == Orientation::Horizontal) ? 0:1;
    const int dCol = (orientation == Orientation::Horizontal) ? 1:0;

    for (int i=0; i<length; i++) {
        getTileInternal(owner, startRow+i*dRow, startCol+i*dCol).id = id;
        getTileInternal(owner, startRow+i*dRow, startCol+i*dCol).mastIndex = i;
    }
    getShipInternal(owner)[id].length = length;
    getShipInternal(owner)[id].orientation = orientation;
    getShipInternal(owner)[id].startRow = startRow;
    getShipInternal(owner)[id].startCol = startCol;
    emit boardUpdate();
};

bool Engine::hasShipAt(BoardOwner owner,int row, int col) {
    return getTileInternal(owner, row, col).id>=0;
};

ShipData Engine::getShipAt(BoardOwner owner,int row, int col) {
    return getShipInternal(owner)[getTileInternal(owner, row, col).id];
};

void Engine::pickupShip(int row, int col) {
    ShipData ship = playerShips[playerBoard[row][col].id];

    const int dRow = (ship.orientation == Orientation::Horizontal) ? 0:1;
    const int dCol = (ship.orientation == Orientation::Horizontal) ? 1:0;

    for (int i=0; i<ship.length; i++) {
        playerBoard[ship.startRow+i*dRow][ship.startCol+i*dCol].id = -1;
        playerBoard[ship.startRow+i*dRow][ship.startCol+i*dCol].mastIndex = -1;
    }
    emit boardUpdate();
};

void Engine::cancelPickup(ShipData ship, int id) {
    const int dRow = (ship.orientation == Orientation::Horizontal) ? 0:1;
    const int dCol = (ship.orientation == Orientation::Horizontal) ? 1:0;

    for (int i=0; i<ship.length; i++) {
        playerBoard[ship.startRow+i*dRow][ship.startCol+i*dCol].id = id;
        playerBoard[ship.startRow+i*dRow][ship.startCol+i*dCol].mastIndex = i;
    }
    emit boardUpdate();
}

void Engine::setupPlayerShips() {
    addShip(BoardOwner::Player,0,0,5,Orientation::Vertical);
    addShip(BoardOwner::Player,0,2,4,Orientation::Vertical);
    addShip(BoardOwner::Player,0,4,3,Orientation::Vertical);
    addShip(BoardOwner::Player,0,6,3,Orientation::Vertical);
    addShip(BoardOwner::Player,0,8,2,Orientation::Vertical);
    emit boardUpdate();
};

void Engine::addShip(BoardOwner owner,int startRow, int startCol, int length, Orientation orientation) {
    ShipData ship(length,orientation,startRow,startCol);
    getShipInternal(owner).push_back(ship);
    placeShip(owner, startRow, startCol, length, orientation, getShipInternal(owner).size()-1);
}

bool Engine::canPlaceShip(BoardOwner owner, int startRow, int startCol, int lenght, Orientation orientation) {
    if (startRow<0 || startRow>=10 || startCol<0 || startCol>=10) {return false;}

    const int dRow = (orientation == Orientation::Horizontal) ? 0:1;
    const int dCol = (orientation == Orientation::Horizontal) ? 1:0;

    if (startRow+(lenght-1)*dRow>=10 || startCol+(lenght-1)*dCol>=10){return false;}

    const int minRow = std::max(0, startRow-1);
    const int maxRow = std::min(9, startRow+(lenght-1)*dRow+1);
    const int minCol = std::max(0, startCol-1);
    const int maxCol = std::min(9, startCol+(lenght-1)*dCol+1);

    for (int r=minRow;r<=maxRow;r++) {
        for (int c=minCol;c<=maxCol;c++) {
            if (getTileInternal(owner,r,c).id!=-1) {return false;}
        }
    }
    return true;
}

void Engine::clearComputerBoard() {
    for (int i=0;i<10;i++) {
        for (int j=0;j<10;j++) {
            computerBoard[i][j] = TileData{};
        }
    }
    computerShips.clear();
}

TileData Engine::getTileAt(BoardOwner owner,int row, int col) {
    return getTileInternal(owner, row, col);
}

ShotResult Engine::fire(BoardOwner owner, int row, int col) {
    if (row<0 || row>=10 || col<0 || col>=10) {return ShotResult::Invalid;}
    if (getTileInternal(owner, row, col).hit == true){return ShotResult::Invalid;}
    getTileInternal(owner, row, col).hit = true;
    emit boardUpdate();
    if (getTileInternal(owner, row, col).id == -1){return ShotResult::Miss;}
    if (isShipSunken(owner, row, col)){return ShotResult::Sunk;}
    return ShotResult::Hit;
}

bool Engine::isShipSunken(BoardOwner owner, int row, int col) {
    const TileData& tile = getTileInternal(owner, row, col);
    if (tile.id == -1){return false;}
    ShipData& ship = getShipInternal(owner)[tile.id];
    if (ship.sunken){return true;}

    const int dRow = (ship.orientation == Orientation::Horizontal) ? 0:1;
    const int dCol = (ship.orientation == Orientation::Horizontal) ? 1:0;

    for (int i=0; i<ship.length; i++) {
        if (!getTileInternal(owner,ship.startRow+i*dRow, ship.startCol+i*dCol).hit) {
            return false;
        }
    }
    ship.sunken = true;
    return true;
}

Winner Engine::isGameEnded() {
    bool player_won = true;
    bool computer_won = true;
    for (const auto& ship : playerShips) {
        if (!ship.sunken) {
            computer_won = false;
            break;
        }
    }
    for (const auto& ship : computerShips) {
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

bool Engine::isTileHit(BoardOwner owner, int row, int col) {
    return getTileInternal(owner, row, col).hit;
}

TileData& Engine::getTileInternal(BoardOwner owner,int row, int col){
    return (owner == BoardOwner::Player) ? playerBoard[row][col] : computerBoard[row][col];
}

std::vector<ShipData>& Engine::getShipInternal(BoardOwner owner) {
    return (owner == BoardOwner::Player) ? playerShips : computerShips;
}







