
#include <SFML/Graphics.hpp>
#include "board.h"
#include "textures.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>


int main()
{
    //SETUP
    int winWidth, winHeight;
    Board myBoard("resources/boards/config.cfg");
    Sprites mySprites;
    winWidth = myBoard.GetRows() * 32;
    std::cout << "Width: " << winWidth << std::endl;
    winHeight = (myBoard.GetColumns() * 32) + 100;
    std::cout << "Height: " << winHeight << std::endl;

    //PROGRAM LOOP

    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Gio's Minesweeper", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    int mineFlagCount = myBoard.GetMineCount();
    int mineFlagArr[4];
    bool gameOver = false;
    bool gameWon = false;
    sf::RectangleShape bkGround;
    bkGround.setSize(sf::Vector2f(winWidth, winHeight));
    bkGround.setFillColor(sf::Color::Cyan);
    bkGround.setPosition(0, 0);
    while (window.isOpen())
    {
        sf::Event event;
        bool leftMouseDown = true;
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::RectangleShape bkGround;
        bkGround.setSize(sf::Vector2f(winWidth, winHeight));
        bkGround.setFillColor(sf::Color::Cyan);
        bkGround.setPosition(0, 0);

        mySprites.testOne.setPosition((myBoard.GetRows() - 7) * 32, (myBoard.GetColumns() + 0.5) * 32);
        sf::Vector2f testOneTop = (mySprites.testOne.getPosition());
        sf::Vector2f testOneBottom;
        testOneBottom.x = testOneTop.x + 64;
        testOneBottom.y = testOneTop.y + 64;

        mySprites.testTwo.setPosition((myBoard.GetRows() - 5) * 32, (myBoard.GetColumns() + 0.5) * 32);
        sf::Vector2f testTwoTop = (mySprites.testTwo.getPosition());
        sf::Vector2f testTwoBottom;
        testTwoBottom.x = testTwoTop.x + 64;
        testTwoBottom.y = testTwoTop.y + 64;

        mySprites.testThree.setPosition((myBoard.GetRows() - 3) * 32, (myBoard.GetColumns() + 0.5) * 32);
        sf::Vector2f testThreeTop = (mySprites.testThree.getPosition());
        sf::Vector2f testThreeBottom;
        testThreeBottom.x = testThreeTop.x + 64;
        testThreeBottom.y = testThreeTop.y + 64;

        mySprites.faceHappy.setPosition((myBoard.GetRows() / 2) * 32, (myBoard.GetColumns() + 0.5) * 32);
        sf::Vector2f faceTop = (mySprites.faceHappy.getPosition());
        sf::Vector2f faceBottom;
        faceBottom.x = faceTop.x + 64;
        faceBottom.y = faceTop.y + 64;

        mySprites.faceLose.setPosition((myBoard.GetRows() / 2) * 32, (myBoard.GetColumns() + 0.5) * 32);
        mySprites.faceWin.setPosition((myBoard.GetRows() / 2) * 32, (myBoard.GetColumns() + 0.5) * 32);

        mySprites.debug.setPosition((myBoard.GetRows() - 9) * 32, (myBoard.GetColumns() + 0.5) * 32);
        sf::Vector2f debugTop = (mySprites.debug.getPosition());
        sf::Vector2f debugBottom;
        debugBottom.x = debugTop.x + 64;
        debugBottom.y = debugTop.y + 64;

        window.clear();
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Right) 
                    {
                        if (((mousePosition.x >= 0) && (mousePosition.y >= 0)) && ((mousePosition.x <= myBoard.GetRows() * 32) && (mousePosition.y <= myBoard.GetColumns() * 32)) && (!gameOver && !gameWon))
                        {
                            if (myBoard.boardTiles.at(mousePosition.y / 32).at(mousePosition.x / 32)->isHidden)
                            {
                                if (!myBoard.boardTiles.at(mousePosition.y / 32).at(mousePosition.x / 32)->isFlagged)
                                {
                                    myBoard.boardTiles.at(mousePosition.y / 32).at(mousePosition.x / 32)->isFlagged = true;
                                    myBoard.AddFlag();
                                }
                                else
                                {
                                    myBoard.boardTiles.at(mousePosition.y / 32).at(mousePosition.x / 32)->isFlagged = false;
                                    myBoard.RemoveFlag();
                                }
                            }
                            mineFlagCount = myBoard.GetMineCount() - myBoard.GetFlagCount();
                        }
                    }
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (((mousePosition.x >= 0) && (mousePosition.y >= 0)) && ((mousePosition.x <= myBoard.GetRows() * 32) && (mousePosition.y <= myBoard.GetColumns() * 32)) && (!gameOver && !gameWon))
                        {
                            if (myBoard.boardTiles.at(mousePosition.y / 32).at(mousePosition.x / 32)->isHidden && !myBoard.boardTiles.at(mousePosition.y / 32).at(mousePosition.x / 32)->isFlagged)
                            {
                                if (myBoard.boardTiles.at(mousePosition.y / 32).at(mousePosition.x / 32)->isBomb)
                                {
                                    gameOver = true;
                                    myBoard.boardTiles.at(mousePosition.y / 32).at(mousePosition.x / 32)->isHidden = false;
                                    break;
                                }
                                else
                                {
                                    myBoard.RevealEmpty(mousePosition.y / 32, mousePosition.x / 32);
                                    std::cout << "hIDDEN: " << myBoard.GetHidden() << std::endl;
                                    if (myBoard.GetHidden() == myBoard.GetMineCount())
                                    {
                                        gameWon = true;
                                        break;
                                    }
                                }
                            }
                        }
                        if (((mousePosition.x >= faceTop.x) && (mousePosition.y >= faceTop.y)) && ((mousePosition.x <= faceBottom.x) && (mousePosition.y <= faceBottom.y)))
                        {
                            std::cout << "FACE" << std::endl;
                            myBoard.Reset();
                            myBoard.SetTiles();
                            gameOver = false;
                            gameWon = false;
                            mineFlagCount = myBoard.GetMineCount();
                        }
                        if ((mousePosition.x >= debugTop.x) && (mousePosition.y >= debugTop.y) && (mousePosition.x <= debugBottom.x) && (mousePosition.y <= debugBottom.y))
                        {
                            std::cout << "DEBUG" << std::endl;
                            if (myBoard.debugMode == false)
                            {
                                myBoard.debugMode = true;
                            }
                            else
                            {
                                myBoard.debugMode = false;
                            }
                        }
                        if ((mousePosition.x >= testOneTop.x) && (mousePosition.y >= testOneTop.y) && (mousePosition.x <= testOneBottom.x) && (mousePosition.y <= testOneBottom.y))
                        {
                            std::cout << "TEST ONE" << std::endl; 
                            myBoard.Reset();
                            myBoard.SetTiles("resources/boards/testboard1.brd");
                            gameOver = false;
                            gameWon = false;
                            mineFlagCount = myBoard.GetMineCount();
                        }
                        if ((mousePosition.x >= testTwoTop.x) && (mousePosition.y >= testTwoTop.y) && (mousePosition.x <= testTwoBottom.x) && (mousePosition.y <= testTwoBottom.y))
                        {
                            std::cout << "TEST TWO" << std::endl;
                            myBoard.Reset();
                            myBoard.SetTiles("resources/boards/testboard2.brd");
                            gameOver = false;
                            gameWon = false;
                            mineFlagCount = myBoard.GetMineCount();
                        }
                        if ((mousePosition.x >= testThreeTop.x) && (mousePosition.y >= testThreeTop.y) && (mousePosition.x <= testThreeBottom.x) && (mousePosition.y <= testThreeBottom.y))
                        {
                            std::cout << "TEST THREE" << std::endl;
                            myBoard.Reset();
                            myBoard.SetTiles("resources/boards/testboard3.brd");
                            gameOver = false;
                            gameWon = false;
                            mineFlagCount = myBoard.GetMineCount();
                        }
                    }
                    break;

                default:
                    break;
            }
        
        }
        window.clear();
        window.draw(bkGround);
        for (int i = 0; i < myBoard.GetColumns(); i++)
        {
            for (int j = 0; j < myBoard.GetRows(); j++)
            {
                myBoard.DrawTile(j, i, &window, &mySprites);
            }
        }

        if (mineFlagCount < 0)
        {
            mineFlagArr[0] = -1;
        }
        else
        {
            mineFlagArr[0] = 0;
        }

        int tempNum = 100;
        int tempMineFlagCount = std::abs(mineFlagCount);
        for (int i = 1; i < 4; i++)
        {
            if (tempMineFlagCount / tempNum == 0)
            {
                mineFlagArr[i] = 0;
            }
            else
            {
                mineFlagArr[i] = tempMineFlagCount / tempNum;
                tempMineFlagCount -= tempNum * mineFlagArr[i];
            }
            tempNum /= 10;
        }

        for (int i = 0; i < 4; i++)
        {
            if (i == 0)
            {
                if ((mineFlagArr[i] == -1))
                {
                    mySprites.digitsMinus.setPosition((myBoard.GetRows() - (20 - i)) * 21, (myBoard.GetColumns() + 0.5) * 32);
                    window.draw(mySprites.digitsMinus);
                }
            }
            else
            {
                switch (mineFlagArr[i])
                {
                case 0:
                    mySprites.digitsZero.setPosition((myBoard.GetRows() - (20 - i)) * 21, (myBoard.GetColumns() + 0.5) * 32);
                    window.draw(mySprites.digitsZero);
                    break;
                case 1:
                    mySprites.digitsOne.setPosition((myBoard.GetRows() - (20 - i)) * 21, (myBoard.GetColumns() + 0.5) * 32);
                    window.draw(mySprites.digitsOne);
                    break;
                case 2:
                    mySprites.digitsTwo.setPosition((myBoard.GetRows() - (20 - i)) * 21, (myBoard.GetColumns() + 0.5) * 32);
                    window.draw(mySprites.digitsTwo);
                    break;
                case 3:
                    mySprites.digitsThree.setPosition((myBoard.GetRows() - (20 - i)) * 21, (myBoard.GetColumns() + 0.5) * 32);
                    window.draw(mySprites.digitsThree);
                    break;
                case 4:
                    mySprites.digitsFour.setPosition((myBoard.GetRows() - (20 - i)) * 21, (myBoard.GetColumns() + 0.5) * 32);
                    window.draw(mySprites.digitsFour);
                    break;
                case 5:
                    mySprites.digitsFive.setPosition((myBoard.GetRows() - (20 - i)) * 21, (myBoard.GetColumns() + 0.5) * 32);
                    window.draw(mySprites.digitsFive);
                    break;
                case 6:
                    mySprites.digitsSix.setPosition((myBoard.GetRows() - (20 - i)) * 21, (myBoard.GetColumns() + 0.5) * 32);
                    window.draw(mySprites.digitsSix);
                    break;
                case 7:
                    mySprites.digitsSeven.setPosition((myBoard.GetRows() - (20 - i)) * 21, (myBoard.GetColumns() + 0.5) * 32);
                    window.draw(mySprites.digitsSeven);
                    break;
                case 8:
                    mySprites.digitsEight.setPosition((myBoard.GetRows() - (20 - i)) * 21, (myBoard.GetColumns() + 0.5) * 32);
                    window.draw(mySprites.digitsEight);
                    break;
                case 9:
                    mySprites.digitsNine.setPosition((myBoard.GetRows() - (20 - i)) * 21, (myBoard.GetColumns() + 0.5) * 32);
                    window.draw(mySprites.digitsNine);
                    break;
                }
            }
        }

        window.draw(mySprites.testOne);
        window.draw(mySprites.testTwo);
        window.draw(mySprites.testThree);
        window.draw(mySprites.debug);

        if (gameOver)
        {
            window.draw(mySprites.faceLose);
        }
        else if (gameWon)
        {
            window.draw(mySprites.faceWin);
        }
        else
        {
            window.draw(mySprites.faceHappy);
        }

        window.display();
    }

    return 0;
}
