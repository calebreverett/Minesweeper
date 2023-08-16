#include <vector>
#pragma once

class Tile {
    bool isMine;
    bool isRevealed;
    bool hasFlag;
    bool isChecked = false;
    short neighborMines = 0;
    std::vector<Tile*> neighborTiles;

public:
    Tile();
    Tile(bool _isMine, bool _isRevealed);
    void RevealTile();
    bool GetRevealed();
    bool GetFlag();
    bool GetBomb();
    void PlaceBomb();
    void HasFlag();
    void IsFlag();
    void SetNumber(short number);
    short GetNeighborMines();
    void AddNeighborTiles(Tile* tile);
    void RevealNeighborTiles();
};


