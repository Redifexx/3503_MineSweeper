#pragma once
#include <SFML/Graphics.hpp>

class Sprites
{
	sf::Texture mineTex;
	sf::Texture tileHiddenTex;
	sf::Texture tileRevealedTex;
	sf::Texture numberOneTex;
	sf::Texture numberTwoTex;
	sf::Texture numberThreeTex;
	sf::Texture numberFourTex;
	sf::Texture numberFiveTex;
	sf::Texture numberSixTex;
	sf::Texture numberSevenTex;
	sf::Texture numberEightTex;
	sf::Texture flagTex;
	sf::Texture faceHappyTex;
	sf::Texture faceWinTex;
	sf::Texture faceLoseTex;
	sf::Texture digitsTex;
	sf::Texture debugTex;
	sf::Texture testOneTex;
	sf::Texture testTwoTex;
	sf::Texture testThreeTex;
	void LoadSprites();
public:
	sf::Sprite mine;
	sf::Sprite tileHidden;
	sf::Sprite tileRevealed;
	sf::Sprite numberOne;
	sf::Sprite numberTwo;
	sf::Sprite numberThree;
	sf::Sprite numberFour;
	sf::Sprite numberFive;
	sf::Sprite numberSix;
	sf::Sprite numberSeven;
	sf::Sprite numberEight;
	sf::Sprite flag;
	sf::Sprite faceHappy;
	sf::Sprite faceWin;
	sf::Sprite faceLose;
	sf::Sprite digitsZero;
	sf::Sprite digitsOne;
	sf::Sprite digitsTwo;
	sf::Sprite digitsThree;
	sf::Sprite digitsFour;
	sf::Sprite digitsFive;
	sf::Sprite digitsSix;
	sf::Sprite digitsSeven;
	sf::Sprite digitsEight;
	sf::Sprite digitsNine;
	sf::Sprite digitsMinus;
	sf::Sprite debug;
	sf::Sprite testOne;
	sf::Sprite testTwo;
	sf::Sprite testThree;
	Sprites();

};