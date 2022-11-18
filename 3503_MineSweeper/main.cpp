
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
    Board myBoard("resources/boards/config.cfg", "resources/boards/testboard1.brd");
    Sprites mySprites;
    winWidth = myBoard.GetRows() * 32;
    std::cout << "Width: " << winWidth << std::endl;
    winHeight = (myBoard.GetColumns() * 32) + 100;
    std::cout << "Height: " << winHeight << std::endl;

    //PROGRAM LOOP

    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Gio's Minesweeper");
   
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        int countPos = 0;
        for (int i = 0; i < myBoard.GetRows(); i++)
        {
            for (int j = 0; j < myBoard.GetColumns(); j++)
            {
                if (myBoard.boardTiles.at(countPos)->isBomb)
                {
                    mySprites.tileHidden.setPosition(i * 32, j * 32);
                    window.draw(mySprites.tileHidden);
                    mySprites.mine.setPosition(i * 32, j * 32);
                    window.draw(mySprites.mine);
                }
                else
                {
                    mySprites.tileHidden.setPosition(i * 32, j * 32);
                    window.draw(mySprites.tileHidden);
                }
                countPos++;
            }
        }


        window.display();
    }

    return 0;
}
