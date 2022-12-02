#pragma once
#include <SFML/Graphics.hpp>
#include "textures.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class Board
{
	int rows;
	int columns;
	int mineCount;
	struct Tile
	{
		bool isBomb;
		sf::Vector2i tileCords;
		Tile* adjacentTiles[8];
		int adjacentBombCt;
		bool isHidden;
		bool isFlagged;
	};


public:
	unsigned int tileCount;
	std::vector<std::vector<Tile*>> boardTiles;

	Board(std::string fileCFG);
	Board(std::string fileCFG, std::string fileBRD);

	void DrawTile(int row, int column, sf::RenderWindow *window_, Sprites *sprites_);

	void SetRows(int rows_);
	int GetRows();

	void SetColumns(int columns_);
	int GetColumns();

	void SetMineCount(int mineCount_);
	int GetMineCount();

	void SetTiles();
	void SetTiles(std::string fileBRD);

};
