// SFML-2.4.2-windows-gcc-6.1.0-mingw-64-bit

#include <SFML/Graphics.hpp>
#include <iostream>
#include <iostream>
using namespace std;

#include "SudokuBoard.h"


const sf::Color tile_color = sf::Color::White;
const sf::Color grid_color = sf::Color::Green;
const sf::Color number_color = sf::Color::Black;
const sf::Color input_color = sf::Color::Blue;
const int tile_size = 128;
const int border_size = 4;
const int height = 9;
const int width = 9;
const int SIZE = 3;

int main() {
    srand(time(nullptr));
    SudokuBoard* game = new SudokuBoard(SIZE);
    game->loadBoardFromFile("cleanSudoku.txt");
    game->updateSet();
    game->lasVegasAlgorithm();
    int answer;
    int holes;

    cout << "Welcome to Sudoku!" << endl;
    cout << "Right click on a tile to place number and left click to remove number" << endl;
    cout << "Press ESC or Q to exit, or the R to restart" << endl;
    cout << "Press A, S or Z to solve Sudoku" << endl;
    cout << "Press N to get new board" << endl;
    cout << "Press L to save board to file" << endl;
    cout << "Choose difficulty:" << endl;
    cout << "(1) Simple " << endl;
    cout << "(2) Easy   " << endl;
    cout << "(3) Medium " << endl;
    cout << "(4) Hard   " << endl;
    cout << "Input: ";
    for(;;){
        cin >> answer;
        if (answer == 1){
            holes = 30;
            break;
        } else if (answer == 2){
            holes = 40;
            break;
        } else if (answer == 3){
            holes = 50;
            break;
        } else if (answer == 4) {
            holes = 55;
            break;
        } else{
            cout << "Incorrect answer! Try again!" << endl;
        }
    }

    cout << "\nGenerating Sudoku board..." << endl;
    game->diggingHole(holes);
    cout << "Sudoku board generated!\n" << endl;

    sf::Font font;
    if (!font.loadFromFile("sansation.ttf")){
        cout << "Did not fine the file 'sansation.ttf'" << endl;
        exit(0);
    }

    sf::RenderWindow window(sf::VideoMode(width * tile_size, (height) * tile_size), "Sudoku", sf::Style::Close);
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Escape:
                        case sf::Keyboard::Q:
                            window.close();
                            break;
                        case sf::Keyboard::S:
                            game->solveGame();
                            break;
                        case sf::Keyboard::R:
                            game->resetGame();
                            break;
                        case sf::Keyboard::A:
                            game->depthFirstSearch(0,0);
                            break;
                        case sf::Keyboard::Z:
                            game->depthFirstSearchReversed(0,0);
                            break;
                        case sf::Keyboard::N:
                            delete game;
                            game = new SudokuBoard(SIZE);
                            game->loadBoardFromFile("cleanSudoku.txt");
                            game->updateSet();
                            game->lasVegasAlgorithm();
                            cout << "Generating Sudoku board..." << endl;
                            game->diggingHole(holes);
                            cout << "Sudoku board generated!\n" << endl;
                            break;
                        case sf::Keyboard::L:
                            game->saveBoardToFile("savedSudokuBoard.txt");
                            cout << "Sudoku Board saved to file\n" << endl;
                            break;
                    }
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        unsigned int row = event.mouseButton.y / tile_size;
                        unsigned int col = event.mouseButton.x / tile_size;
                        sf::Event inputNumberEvent;
                        bool input = false;

                        if(!game->numberAlreadyInPosition(row, col)){
                            const int tile_x = col * tile_size, tile_y = row * tile_size;
                            sf::RectangleShape tile;
                            tile.setSize(sf::Vector2f(tile_size - border_size, tile_size - border_size));
                            tile.setFillColor(input_color);
                            tile.setPosition(tile_x + int(border_size / 2.0), tile_y + int(border_size / 2.0));
                            window.draw(tile);
                            window.display();
                            while (!input) {
                                while (window.pollEvent(inputNumberEvent)) {
                                    switch (inputNumberEvent.type) {
                                        case sf::Event::KeyPressed:
                                            switch (inputNumberEvent.key.code) {
                                                case sf::Keyboard::Num1:
                                                    game->setSudokuNumber(row, col, 1);
                                                    input = true;
                                                    continue;
                                                case sf::Keyboard::Num2:
                                                    game->setSudokuNumber(row, col, 2);
                                                    input = true;
                                                    continue;
                                                case sf::Keyboard::Num3:
                                                    game->setSudokuNumber(row, col, 3);
                                                    input = true;
                                                    continue;
                                                case sf::Keyboard::Num4:
                                                    game->setSudokuNumber(row, col, 4);
                                                    input = true;
                                                    continue;
                                                case sf::Keyboard::Num5:
                                                    game->setSudokuNumber(row, col, 5);
                                                    input = true;
                                                    continue;
                                                case sf::Keyboard::Num6:
                                                    game->setSudokuNumber(row, col, 6);
                                                    input = true;
                                                    continue;
                                                case sf::Keyboard::Num7:
                                                    game->setSudokuNumber(row, col, 7);
                                                    input = true;
                                                    continue;
                                                case sf::Keyboard::Num8:
                                                    game->setSudokuNumber(row, col, 8);
                                                    input = true;
                                                    continue;
                                                case sf::Keyboard::Num9:
                                                    game->setSudokuNumber(row, col, 9);
                                                    input = true;
                                                    continue;
                                                default:
                                                    continue;
                                            }

                                    }
                                }
                            }
                        }
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right){
                        unsigned int row = event.mouseButton.y / tile_size;
                        unsigned int col = event.mouseButton.x / tile_size;
                        if(!game->isTileOriginal(row, col)){
                            game->removeMove(row, col);
                        }
                    }
            }
        }

        window.clear();
        for(int row = 0; row < height; ++row) {
            for(int col = 0; col < width; ++col) {
                const int tile_x = col * tile_size, tile_y = row * tile_size;
                sf::RectangleShape tile;
                tile.setSize(sf::Vector2f(tile_size - border_size, tile_size - border_size));
                tile.setFillColor(tile_color);
                tile.setPosition(tile_x + int(border_size / 2.0), tile_y + int(border_size / 2.0));
                window.draw(tile);
            }
        }

        sf::RectangleShape grid1;
        grid1.setSize(sf::Vector2f(border_size*2, tile_size*height));
        grid1.setFillColor(grid_color);
        grid1.setPosition(tile_size*3-border_size,0);
        window.draw(grid1);

        sf::RectangleShape grid2;
        grid2.setSize(sf::Vector2f(border_size*2, tile_size*height));
        grid2.setFillColor(grid_color);
        grid2.setPosition(tile_size*6-border_size,0);
        window.draw(grid2);

        sf::RectangleShape grid3;
        grid3.setSize(sf::Vector2f(tile_size*width, border_size*2));
        grid3.setFillColor(grid_color);
        grid3.setPosition(0, tile_size*3-border_size);
        window.draw(grid3);

        sf::RectangleShape grid4;
        grid4.setSize(sf::Vector2f(tile_size*width, border_size*2));
        grid4.setFillColor(grid_color);
        grid4.setPosition(0, tile_size*6-border_size);
        window.draw(grid4);

        for(unsigned  int row = 0; row < height; ++row) {
            for(unsigned  int col = 0; col < width; ++col) {
                const int tile_x = col * tile_size, tile_y = row * tile_size;
                if(game->get(row, col)){
                    sf::Text text;
                    text.setStyle(sf::Text::Bold);
                    text.setCharacterSize(tile_size / 2.0);
                    text.setString(to_string(game->get(row, col)));
                    if(game->isTileOriginal(row, col)){
                        text.setColor(number_color);
                    }
                    else{
                        text.setColor(input_color);
                    }
                    text.setFont(font);
                    sf::FloatRect text_rect = text.getLocalBounds();
                    text.setOrigin(text_rect.left + text_rect.width  / 2.0, text_rect.top  + text_rect.height / 2.0);
                    text.setPosition(tile_x + tile_size / 2.0, tile_y + tile_size / 2.0);
                    window.draw(text);
                }
            }
        }

        window.display();
    }
    return 0;
}
