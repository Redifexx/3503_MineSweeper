
#include <SFML/Graphics.hpp>
#include "board.h"
#include "textures.h"
#include <fstream>
#include <iostream>
#include <string>


int main()
{
    //SETUP
    int winWidth, winHeight;
    Board myBoard("resources/boards/config.cfg", "resources/boards/testboard2.brd");
    Sprites mySprites;
    winWidth = myBoard.GetRows() * 32;
    std::cout << "Width: " << winWidth << std::endl;
    winHeight = (myBoard.GetColumns() * 32) + 100;
    std::cout << "Height: " << winHeight << std::endl;

    //PROGRAM LOOP

    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Gio's Minesweeper");
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        bool leftMouseDown = true;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (int i = 0; i < myBoard.GetColumns(); i++)
        {
            for (int j = 0; j < myBoard.GetRows(); j++)
            {
                myBoard.DrawTile(j, i, &window, &mySprites);
            }
        }
        mySprites.testOne.setPosition((myBoard.GetRows() - 6) * 32, (myBoard.GetColumns()) * 32);
        mySprites.testTwo.setPosition((myBoard.GetRows() - 4) * 32, (myBoard.GetColumns()) * 32);
        mySprites.testThree.setPosition((myBoard.GetRows() - 2) * 32, (myBoard.GetColumns()) * 32);
        window.draw(mySprites.testOne);
        window.draw(mySprites.testTwo);
        window.draw(mySprites.testThree);
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        std::cout << mousePosition.x / 32 << " " << mousePosition.y / 32 << std::endl;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {

            if (!myBoard.boardTiles.at(mousePosition.y / 32).at(mousePosition.x / 32)->isFlagged)
            {
                myBoard.boardTiles.at(mousePosition.y / 32).at(mousePosition.x / 32)->isFlagged = true;
            }
            else
            {
                myBoard.boardTiles.at(mousePosition.y / 32).at(mousePosition.x / 32)->isFlagged = false;
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {

            if (myBoard.boardTiles.at(mousePosition.y / 32).at(mousePosition.x / 32)->isHidden)
            {
                myBoard.boardTiles.at(mousePosition.y / 32).at(mousePosition.x / 32)->isHidden = false;
            }
        }
        window.display();
    }

    return 0;
}
