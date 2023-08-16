#include <vector>
#include <fstream>
#include "Tile.h"

class Board {
    int columns;
    int rows;
    int mineCount;
    int tileCount;
    int flagCount;
    bool isWin = false;
    bool isLoss = false;
public:
    std::vector<Tile> tiles;

    Board();
    Board(int _columns, int _rows, int _mineCount);
    Board(std::string filename);
    int GetColumns();
    int GetTileCount();
    int GetRows();
    void TileChecker();
    void Win();
    void Loss();
    bool GetisLoss();
    bool GetisWin();
    int GetFlagCount();
    int GetMineCount();
    void CheckIfWin();
    void operator=(Board gameBoard);
};

