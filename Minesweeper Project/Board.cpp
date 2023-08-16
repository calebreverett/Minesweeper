#include "Board.h"
#include "Support.h"

Board::Board() {
    mineCount = 0;
    columns = 0;
    rows = 0;
    tileCount = 0;
}

Board::Board(int _columns, int _rows, int _mineCount) {
    columns = _columns;
    rows = _rows;
    mineCount = _mineCount;
    tileCount = columns * rows;

    for(int i = 0; i < tileCount; i++){
        Tile tile;
        tiles.push_back(tile);
    }

    int mineCountLoop = mineCount;
    for(int i = 0; i < mineCountLoop; i++){
        int tempNum = Random::Int(0, tileCount - 1);
        if(tiles.at(tempNum).GetBomb()){
            mineCountLoop++;
        }
        else{
            tiles.at(tempNum).PlaceBomb();
        }
    }


    TileChecker();
}

Board::Board(std::string filename) {
    std::ifstream inFile(filename);
    mineCount = 0;
    rows = 0;
    tileCount = 0;

    string binaryLine;
    while(getline(inFile, binaryLine)){
        columns = binaryLine.size();
        rows++;
        for(int i = 0; i < binaryLine.size(); i++){
            if(binaryLine.at(i) == '0'){
                Tile tile;
                tiles.push_back(tile);
            }
            else{
                Tile tile(true, false);
                tiles.push_back(tile);
                mineCount++;
            }
            tileCount++;
        }
    }

    TileChecker();
}

int Board::GetTileCount() {
    return tileCount;
}

int Board::GetColumns() {
    return columns;
}

int Board::GetRows() {
    return rows;
}

void Board::TileChecker(){
    for(int i = 0; i < tileCount; i++){
        short bombNumber = 0;
        if(i - columns - 1 >= 0 && i % columns != 0){
            if(tiles.at(i - columns - 1).GetBomb()){
                bombNumber++;
            }
            tiles.at(i).AddNeighborTiles(&tiles.at(i - columns - 1));
        }
        if(i - columns >= 0){
            if(tiles.at(i - columns).GetBomb()){
                bombNumber++;
            }
            tiles.at(i).AddNeighborTiles(&tiles.at(i - columns));
        }
        if(i - columns + 1 >= 0 && (i + 1) % columns != 0){
            if(tiles.at(i - columns + 1).GetBomb()){
                bombNumber++;
            }
            tiles.at(i).AddNeighborTiles(&tiles.at(i - columns + 1));
        }

        if(i % columns != 0){
            if(tiles.at(i - 1).GetBomb()){
                bombNumber++;
            }
            tiles.at(i).AddNeighborTiles(&tiles.at(i - 1));
        }

        if((i + 1) % columns != 0){
            if(tiles.at(i + 1).GetBomb()){
                bombNumber++;
            }
            tiles.at(i).AddNeighborTiles(&tiles.at(i + 1));
        }

        if(i + columns - 1 < tileCount && i % columns != 0){
            if(tiles.at(i + columns - 1).GetBomb()){
                bombNumber++;
            }
            tiles.at(i).AddNeighborTiles(&tiles.at(i + columns - 1));
        }
        if(i + (columns) < tileCount){
            if(tiles.at(i + columns).GetBomb()){
                bombNumber++;
            }
            tiles.at(i).AddNeighborTiles(&tiles.at(i + columns));
        }
        if(i + columns + 1 < tileCount && (i + 1) % columns != 0){
            if(tiles.at(i + columns + 1).GetBomb()){
                bombNumber++;
            }
            tiles.at(i).AddNeighborTiles(&tiles.at(i + columns + 1));
        }
        tiles.at(i).SetNumber(bombNumber);
    }
}

void Board::Win() {
    isWin = true;
}

void Board::Loss() {
    isLoss = true;
}

bool Board::GetisLoss() {
    return isLoss;
}

bool Board::GetisWin() {
    return isWin;
}

int Board::GetFlagCount(){
    flagCount = 0;
    for(int i = 0; i < tiles.size(); i++){
        if(tiles.at(i).GetFlag() && !tiles.at(i).GetRevealed()){
            flagCount++;
        }
    }
    return flagCount;
}

int Board::GetMineCount(){
    return mineCount;
}

void Board::CheckIfWin() {
    int winCounter = 0;
    for(int i = 0; i < tiles.size(); i++){
        if(tiles.at(i).GetRevealed() || tiles.at(i).GetBomb()){
            winCounter++;
        }
    }
    if(winCounter == tiles.size()){
        isWin = true;
        for(int i = 0; i < tiles.size(); i++){
            if(tiles.at(i).GetBomb()){
                tiles.at(i).IsFlag();
            }
        }
    }
}

void Board::operator=(Board rhs) {
    tiles.clear();
    columns = rhs.columns;
    rows = rhs.rows;
    mineCount = rhs.mineCount;
    tileCount = rhs.tileCount;
    isLoss = rhs.isLoss;
    isWin = rhs.isWin;
    flagCount = rhs.flagCount;
    for(int i = 0; i < tileCount; i++){
        tiles.push_back(rhs.tiles.at(i));
    }

    TileChecker();
}