#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include "Board.h"
#include "Support.h"
#include "Tile.h"

int main(){
    std::ifstream inFile("boards/config.cfg");
    int columns;
    int rows;
    int mineCount;
    inFile >> columns;
    inFile >> rows;
    inFile >> mineCount;
    Board gameBoard(columns, rows, mineCount);

    sf::Sprite hiddenTile(Textures::GetTexture("tile_hidden"));
    sf::Sprite revealedTile(Textures::GetTexture("tile_revealed"));
    sf::Sprite happyFace(Textures::GetTexture("face_happy"));
    sf::Sprite debug(Textures::GetTexture("debug"));
    sf::Sprite loseFace(Textures::GetTexture("face_lose"));
    sf::Sprite winFace(Textures::GetTexture("face_win"));
    sf::Sprite flag(Textures::GetTexture("flag"));
    sf::Sprite mine(Textures::GetTexture("mine"));
    sf::Sprite digits(Textures::GetTexture("digits"));
    sf::Sprite number1(Textures::GetTexture("number_1"));
    sf::Sprite number2(Textures::GetTexture("number_2"));
    sf::Sprite number3(Textures::GetTexture("number_3"));
    sf::Sprite number4(Textures::GetTexture("number_4"));
    sf::Sprite number5(Textures::GetTexture("number_5"));
    sf::Sprite number6(Textures::GetTexture("number_6"));
    sf::Sprite number7(Textures::GetTexture("number_7"));
    sf::Sprite number8(Textures::GetTexture("number_8"));
    sf::Sprite test1(Textures::GetTexture("test_1"));
    sf::Sprite test2(Textures::GetTexture("test_2"));
    sf::Sprite test3(Textures::GetTexture("test_3"));

    bool debugMode = false;
    bool lock_click = false;
    sf::RenderWindow window(sf::VideoMode(columns * 32, (rows * 32) + 100), "Minesweeper");
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        auto mousePosition = sf::Mouse::getPosition(window);
        auto mouseXY = window.mapPixelToCoords(mousePosition);
        window.clear(sf::Color::White);

        happyFace.setPosition(columns * 16 - 32, rows * 32);
        window.draw(happyFace);

        debug.setPosition(columns * 16 + 96, rows * 32);
        window.draw(debug);

        test1.setPosition(columns * 16 + 160, rows * 32);
        window.draw(test1);

        test2.setPosition(columns * 16 + 224, rows * 32);
        window.draw(test2);

        test3.setPosition(columns * 16 + 288, rows * 32);
        window.draw(test3);

        loseFace.setPosition(columns * 16 - 32, rows * 32);

        winFace.setPosition(columns * 16 - 32, rows * 32);

        if(gameBoard.GetMineCount() - gameBoard.GetFlagCount() < 0) {
            digits.setTextureRect(sf::IntRect(210, 0, 21, 32));
            digits.setPosition(0, rows * 32);
            window.draw(digits);
        }
        int digitTracker = abs(gameBoard.GetMineCount() - gameBoard.GetFlagCount());
        gameBoard.CheckIfWin();
        if(gameBoard.GetisWin()){
            debugMode = false;
        }
        digits.setTextureRect(sf::IntRect(0 + (digitTracker % 10)* 21, 0, 21, 32));
        digits.setPosition(63, rows * 32);
        window.draw(digits);
        digitTracker = digitTracker / 10;
        digits.setTextureRect(sf::IntRect(0 + (digitTracker % 10) * 21, 0, 21, 32));
        digits.setPosition(42, rows * 32);
        window.draw(digits);
        digitTracker = digitTracker / 10;
        digits.setTextureRect(sf::IntRect(0 + (digitTracker % 10) * 21, 0, 21, 32));
        digits.setPosition(21, rows * 32);
        window.draw(digits);

        for(int i = 0; i < gameBoard.GetColumns(); i++) {
            for (int j = 0; j < gameBoard.GetRows(); j++) {
                hiddenTile.setPosition(0 + 32.0f * i, 0 + j * 32.0f);
                revealedTile.setPosition(hiddenTile.getPosition());
                flag.setPosition(hiddenTile.getPosition());
                mine.setPosition(hiddenTile.getPosition());
                number1.setPosition(hiddenTile.getPosition());
                number2.setPosition(hiddenTile.getPosition());
                number3.setPosition(hiddenTile.getPosition());
                number4.setPosition(hiddenTile.getPosition());
                number5.setPosition(hiddenTile.getPosition());
                number6.setPosition(hiddenTile.getPosition());
                number7.setPosition(hiddenTile.getPosition());
                number8.setPosition(hiddenTile.getPosition());

                short neighborMines = gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetNeighborMines();

                if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && hiddenTile.getGlobalBounds().contains(mouseXY)
                && !lock_click && !gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetFlag() && !gameBoard.GetisLoss()
                && !gameBoard.GetisWin()) {
                    if (neighborMines == 0) {
                        gameBoard.tiles.at(i + j * gameBoard.GetColumns()).RevealNeighborTiles();
                    }
                    gameBoard.tiles.at(i + j * gameBoard.GetColumns()).RevealTile();
                    lock_click = true;
                }
                if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && hiddenTile.getGlobalBounds().contains(mouseXY)
                && !lock_click && !gameBoard.GetisLoss() && !gameBoard.GetisWin()){
                    gameBoard.tiles.at(i + j * gameBoard.GetColumns()).HasFlag();
                    lock_click = true;
                }
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && debug.getGlobalBounds().contains(mouseXY)
                && !lock_click && !gameBoard.GetisLoss() && !gameBoard.GetisWin()){
                    debugMode = !debugMode;
                    lock_click = true;
                }
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && test1.getGlobalBounds().contains(mouseXY)
                   && !lock_click){
                    Board testBoard("boards/testboard1.brd");
                    gameBoard = testBoard;
                    lock_click = true;
                }
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && test2.getGlobalBounds().contains(mouseXY)
                   && !lock_click){
                    Board testBoard("boards/testboard2.brd");
                    gameBoard = testBoard;
                    lock_click = true;
                }
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && test3.getGlobalBounds().contains(mouseXY)
                   && !lock_click){
                    Board testBoard("boards/testboard3.brd");
                    gameBoard = testBoard;
                    lock_click = true;
                }
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && happyFace.getGlobalBounds().contains(mouseXY)
                   && !lock_click){
                    Board board(columns, rows, mineCount);
                    gameBoard = board;
                    lock_click = true;
                }
                if(event.type == sf::Event::MouseButtonReleased){
                    lock_click = false;
                }

                if(gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetRevealed()
                && gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetBomb() ||
                gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetBomb() && gameBoard.GetisLoss()){
                    window.draw(revealedTile);
                    window.draw(mine);
                }
                else if(gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetRevealed()
                && neighborMines == 0){
                    window.draw(revealedTile);
                }
                else if(gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetRevealed()
                && neighborMines == 1){
                    window.draw(revealedTile);
                    window.draw(number1);
                }
                else if(gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetRevealed()
                && neighborMines == 2){
                    window.draw(revealedTile);
                    window.draw(number2);
                }
                else if(gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetRevealed()
                && neighborMines == 3){
                    window.draw(revealedTile);
                    window.draw(number3);
                }
                else if(gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetRevealed()
                && neighborMines == 4){
                    window.draw(revealedTile);
                    window.draw(number4);
                }
                else if(gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetRevealed()
                && neighborMines == 5){
                    window.draw(revealedTile);
                    window.draw(number5);
                }
                else if(gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetRevealed()
                && neighborMines == 6){
                    window.draw(revealedTile);
                    window.draw(number6);
                }
                else if(gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetRevealed()
                && neighborMines == 7){
                    window.draw(revealedTile);
                    window.draw(number7);
                }
                else if(gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetRevealed()
                && neighborMines == 8){
                    window.draw(revealedTile);
                    window.draw(number8);
                }
                else if(gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetFlag() && !debugMode){
                    window.draw(hiddenTile);
                    window.draw(flag);
                }
                else if(debugMode && gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetBomb()
                        && gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetFlag()){
                    window.draw(hiddenTile);
                    window.draw(flag);
                    window.draw(mine);
                }
                else if(debugMode && gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetBomb()){
                    window.draw(hiddenTile);
                    window.draw(mine);
                }
                else{
                    window.draw(hiddenTile);
                }

                if(gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetBomb() && gameBoard.tiles.at(i + j * gameBoard.GetColumns()).GetRevealed()){
                    window.draw(loseFace);
                    gameBoard.Loss();
                }

                if(gameBoard.GetisWin()){
                    window.draw(winFace);
                }
            }
        }

        window.display();
    }

    Textures::Clear();
    return 0;
}
