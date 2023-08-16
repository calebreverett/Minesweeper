#include "Tile.h"

Tile::Tile() {
    isMine = false;
    isRevealed = false;
    hasFlag = false;

}

Tile::Tile(bool _isMine, bool _isRevealed) {
    isMine = _isMine;
    isRevealed = _isRevealed;
    hasFlag = false;
}

void Tile::RevealTile() {
    isRevealed = true;
}

bool Tile::GetRevealed() {
    return isRevealed;
}

bool Tile::GetFlag(){
    return hasFlag;
}
void Tile::HasFlag(){
    hasFlag = !hasFlag;
}
void Tile::IsFlag(){
    hasFlag = true;
}

bool Tile::GetBomb() {
    return isMine;
}

void Tile::PlaceBomb() {
    isMine = true;
}

void Tile::SetNumber(short number){
    neighborMines = number;
}

short Tile::GetNeighborMines(){
    return neighborMines;
}

void Tile::AddNeighborTiles(Tile* tile) {
    neighborTiles.push_back(tile);
}

void Tile::RevealNeighborTiles() {
    if(!isChecked && !isMine) {
        for (int i = 0; i < neighborTiles.size(); i++) {
            if (!neighborTiles.at(i)->GetBomb()) {
                isChecked = true;
                if(!neighborTiles.at(i)->GetFlag()) {
                    neighborTiles.at(i)->RevealTile();
                }
                if (neighborTiles.at(i)->GetNeighborMines() == 0) {
                    neighborTiles.at(i)->RevealNeighborTiles();
                }
            }
        }
    }
}