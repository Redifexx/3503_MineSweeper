#include "textures.h"
#include <iostream>

void Sprites::LoadSprites()
{
	if (!mineTex.loadFromFile("resources/images/mine.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	mine.setTexture(mineTex);

	if (!tileHiddenTex.loadFromFile("resources/images/tile_hidden.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	tileHidden.setTexture(tileHiddenTex);

	if (!tileRevealedTex.loadFromFile("resources/images/tile_revealed.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	tileRevealed.setTexture(tileRevealedTex);

	if (!numberOneTex.loadFromFile("resources/images/number_1.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	numberOne.setTexture(numberOneTex);

	if (!numberTwoTex.loadFromFile("resources/images/number_2.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	numberTwo.setTexture(numberTwoTex);

	if (!numberThreeTex.loadFromFile("resources/images/number_3.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	numberThree.setTexture(numberThreeTex);

	if (!numberFourTex.loadFromFile("resources/images/number_4.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	numberFour.setTexture(numberFourTex);

	if (!numberFiveTex.loadFromFile("resources/images/number_5.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	numberFive.setTexture(numberFiveTex);

	if (!numberSixTex.loadFromFile("resources/images/number_6.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	numberSix.setTexture(numberSixTex);

	if (!numberSevenTex.loadFromFile("resources/images/number_7.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	numberSeven.setTexture(numberSevenTex);

	if (!numberEightTex.loadFromFile("resources/images/number_8.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	numberEight.setTexture(numberEightTex);

	if (!flagTex.loadFromFile("resources/images/flag.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	flag.setTexture(flagTex);

	if (!faceHappyTex.loadFromFile("resources/images/face_happy.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	faceHappy.setTexture(faceHappyTex);

	if (!faceWinTex.loadFromFile("resources/images/face_win.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	faceWin.setTexture(faceWinTex);

	if (!faceLoseTex.loadFromFile("resources/images/face_lose.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	faceLose.setTexture(faceLoseTex);

	if (!digitsTex.loadFromFile("resources/images/digits.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	digitsZero.setTexture(digitsTex);
	digitsZero.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(21, 32)));

	if (!digitsTex.loadFromFile("resources/images/digits.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	digitsOne.setTexture(digitsTex);
	digitsOne.setTextureRect(sf::IntRect(sf::Vector2i(21, 0), sf::Vector2i(21, 32)));

	if (!digitsTex.loadFromFile("resources/images/digits.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	digitsTwo.setTexture(digitsTex);
	digitsTwo.setTextureRect(sf::IntRect(sf::Vector2i(42, 0), sf::Vector2i(21, 32)));

	if (!digitsTex.loadFromFile("resources/images/digits.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	digitsThree.setTexture(digitsTex);
	digitsThree.setTextureRect(sf::IntRect(sf::Vector2i(63, 0), sf::Vector2i(21, 32)));

	if (!digitsTex.loadFromFile("resources/images/digits.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	digitsFour.setTexture(digitsTex);
	digitsFour.setTextureRect(sf::IntRect(sf::Vector2i(84, 0), sf::Vector2i(21, 32)));

	if (!digitsTex.loadFromFile("resources/images/digits.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	digitsFive.setTexture(digitsTex);
	digitsFive.setTextureRect(sf::IntRect(sf::Vector2i(105, 0), sf::Vector2i(21, 32)));

	if (!digitsTex.loadFromFile("resources/images/digits.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	digitsSix.setTexture(digitsTex);
	digitsSix.setTextureRect(sf::IntRect(sf::Vector2i(126, 0), sf::Vector2i(21, 32)));

	if (!digitsTex.loadFromFile("resources/images/digits.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	digitsSeven.setTexture(digitsTex);
	digitsSeven.setTextureRect(sf::IntRect(sf::Vector2i(147, 0), sf::Vector2i(21, 32)));

	if (!digitsTex.loadFromFile("resources/images/digits.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	digitsEight.setTexture(digitsTex);
	digitsEight.setTextureRect(sf::IntRect(sf::Vector2i(168, 0), sf::Vector2i(21, 32)));

	if (!digitsTex.loadFromFile("resources/images/digits.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	digitsNine.setTexture(digitsTex);
	digitsNine.setTextureRect(sf::IntRect(sf::Vector2i(189, 0), sf::Vector2i(21, 32)));

	if (!digitsTex.loadFromFile("resources/images/digits.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	digitsMinus.setTexture(digitsTex);
	digitsMinus.setTextureRect(sf::IntRect(sf::Vector2i(210, 0), sf::Vector2i(21, 32)));

	if (!debugTex.loadFromFile("resources/images/debug.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	debug.setTexture(debugTex);

	if (!testOneTex.loadFromFile("resources/images/test_1.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	testOne.setTexture(testOneTex);

	if (!testTwoTex.loadFromFile("resources/images/test_2.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	testTwo.setTexture(testTwoTex);

	if (!testThreeTex.loadFromFile("resources/images/test_3.png"))
	{
		std::cout << "Texture Failed To Load!" << std::endl;
	}
	testThree.setTexture(testThreeTex);
}

Sprites::Sprites()
{
	LoadSprites();
}