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

    Engine(const Engine &) = delete;
    Engine &operator=(const Engine &) = delete;

    TileData player_board[10][10] = {};
    TileData computer_board[10][10] = {};

    std::vector<ShipData> player_ships;
    std::vector<ShipData> computer_ships;

    TileData& get_tile_internal(BoardOwner owner, int row, int col);

    std::vector<ShipData>& get_ship_internal(BoardOwner owner);

public:
    static Engine& instance();

    bool placeShip(int row, int col, int length, Orientation orientation, int id);

    void pickup_ship(int row, int col);

    void cancel_pickup(ShipData ship, int id);

    void setup_ships();

    void add_ship(BoardOwner owner, int row, int col, int length, Orientation orientation);

    bool can_add_ship(int startRow, int startCol, int length, Orientation orientation);

    void clear_computer_board();

    bool ship_setup_correct();

    bool has_ship_at(BoardOwner owner, int row, int col);

    ShipData get_ship_at(BoardOwner owner, int row, int col);

    TileData get_tile_at(BoardOwner owner, int row, int col);

    ShotResult fire(BoardOwner owner, int row, int col);

    bool ship_sunken(BoardOwner owner, int row, int col);

    bool is_tile_hit(BoardOwner owner, int row, int col);

    Winner is_game_ended();

    signals:
        void boardUpdate();
};



#endif //ENGINE_H
