#include "board.h"

Board::Board(std::string fileCFG)
{
	std::ifstream myCFG(fileCFG);
	if (myCFG.is_open())
	{
		std::string curLine;

		getline(myCFG, curLine);
		rows = std::stoi(curLine);

		getline(myCFG, curLine);
		columns = std::stoi(curLine);

		getline(myCFG, curLine);
		mineCount = std::stoi(curLine);
	}
	else
	{
		std::cout << "Error opening CFG!" << std::endl;
	}

	tileCount = rows * columns;
	SetTiles();
}

Board::Board(std::string fileCFG, std::string fileBRD)
{
	std::ifstream myCFG(fileCFG);
	if (myCFG.is_open())
	{
		std::string curLine;

		getline(myCFG, curLine);
		rows = std::stoi(curLine);

		getline(myCFG, curLine);
		columns = std::stoi(curLine);

		getline(myCFG, curLine);
		mineCount = std::stoi(curLine);
	}
	else
	{
		std::cout << "Error opening CFG!" << std::endl;
	}

	tileCount = rows * columns;
	SetTiles(fileBRD);
}

void Board::SetRows(int rows_)
{
	rows = rows_;
	tileCount = rows * columns;
}

int Board::GetRows()
{
	return rows;
}

void Board::SetColumns(int columns_)
{
	columns = columns_;
	tileCount = rows * columns;
}

int Board::GetColumns()
{
	return columns;
}

void Board::SetMineCount(int mineCount_)
{
	mineCount = mineCount_;
}

int Board::GetMineCount()
{
	return mineCount;
}

void Board::SetTiles()
{
	for (int i = 0; i < tileCount; i++)
	{
		Tile* currentTile = new Tile;
		boardTiles.push_back(currentTile);
	}
}

void Board::SetTiles(std::string fileBRD)
{
	std::ifstream myBRD(fileBRD);
	std::string curLine;
	for (int i = 0; i < columns; i++)
	{
		getline(myBRD, curLine);
		std::cout << curLine << std::endl;
		for (int j = 0; j < curLine.length(); j++)
		{
			Tile* currentTile = new Tile;
			if (curLine[j] == '1')
			{
				currentTile->isBomb = true;
				std::cout << "BOMB" << std::endl;
			}
			else
			{
				currentTile->isBomb = false;
			}
			boardTiles.push_back(currentTile);
		}
	}
	std::cout << "Board Tiles: " << boardTiles.size() << " TileCOUNT: " << tileCount << std::endl;
}


