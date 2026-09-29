#ifndef ENGINE_H
#define ENGINE_H
#include <QObject>

enum class Orientation { Horizontal, Vertical };

enum class BoardOwner {Player, Computer};

struct ShipData {
    int length;
    Orientation orientation;
    int startRow;
    int startCol;
    bool sunken = false;
};

struct TileData {
    int id = -1;
    int mastIndex = -1;
    bool hit = false;
};

enum class ShotResult {
    Miss,
    Hit,
    Sunk,
    Invalid
};

enum class Winner {
    Player,
    Computer,
    Unresolved
};

class Engine: public QObject {
    Q_OBJECT
    private:
    Engine() = default;
    ~Engine() = default;

    TileData playerBoard[10][10] = {};
    TileData computerBoard[10][10] = {};

    std::vector<ShipData> playerShips;
    std::vector<ShipData> computerShips;

    TileData& getTileInternal(BoardOwner owner, int row, int col);

    std::vector<ShipData>& getShipInternal(BoardOwner owner);

public:
    Engine(const Engine &) = delete;
    Engine &operator=(const Engine &) = delete;

    static Engine& instance();

    void placeShip(BoardOwner owner, int startRow, int startCol, int length, Orientation orientation, int id);

    void pickupShip(int row, int col);

    void cancelPickup(ShipData ship, int id);

    void setupPlayerShips();

    void addShip(BoardOwner owner, int startRow, int startCol, int length, Orientation orientation);

    bool canPlaceShip(BoardOwner owner, int startRow, int startCol, int length, Orientation orientation);

    void clearComputerBoard();

    bool hasShipAt(BoardOwner owner, int row, int col);

    ShipData getShipAt(BoardOwner owner, int row, int col);

    TileData getTileAt(BoardOwner owner, int row, int col);

    ShotResult fire(BoardOwner owner, int row, int col);

    bool isShipSunken(BoardOwner owner, int row, int col);

    bool isTileHit(BoardOwner owner, int row, int col);

    Winner isGameEnded();

    signals:
        void boardUpdate();
};

#endif //ENGINE_H
