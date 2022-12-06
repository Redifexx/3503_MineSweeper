#include "board.h"
#include "textures.h"
#include <random>

std::mt19937 random_mt;

int Random(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}

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
		CFGmineCount = std::stoi(curLine);
	}
	else
	{
		std::cout << "Error opening CFG!" << std::endl;
	}

	tileCount = rows * columns;
	flagCount = 0;
	hiddenCount = 0;
	debugMode = false;
	mineCount = CFGmineCount;
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
		CFGmineCount = std::stoi(curLine);
	}
	else
	{
		std::cout << "Error opening CFG!" << std::endl;
	}

	tileCount = rows * columns;
	flagCount = 0;
	debugMode = false;
	mineCount = 0;
	hiddenCount = 0;
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

void Board::AddFlag()
{
	flagCount++;
}

void Board::RemoveFlag()
{
	flagCount--;
}

int Board::GetFlagCount()
{
	return flagCount;
}

void Board::SetTiles()
{
	//Tiles
	mineCount = CFGmineCount;
	for (int i = 0; i < columns; i++)
	{
		std::vector<Tile*>* curRow = new std::vector<Tile*>;
		for (int j = 0; j < rows; j++)
		{
			Tile* currentTile = new Tile;
			sf::Vector2i curCord(j, i);
			currentTile->tileCords = curCord;
			currentTile->isHidden = true;
			currentTile->isFlagged = false;
			currentTile->isBomb = false;
			curRow->push_back(currentTile);
			hiddenCount++;
		}
		boardTiles.push_back(*curRow);
	}
	
	//Bomb Pass
	int seed = Random(1, 10);
	int bombPlacementCount = 0;
	while (bombPlacementCount < mineCount) 
	{
		std::cout << bombPlacementCount << std::endl;
		for (int i = 0; i < columns; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				if (boardTiles.at(i).at(j)->isBomb == false && bombPlacementCount < mineCount)
				{
					seed = Random(1, 10);
					if (seed == 1)
					{
						boardTiles.at(i).at(j)->isBomb = true;
						bombPlacementCount++;
						std::cout << bombPlacementCount << std::endl;
					}
				}
			}
		}
	} 
	

	//Clean Array
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				boardTiles.at(i).at(j)->adjacentTiles[k] = nullptr;
			}
		}
	}

	//Adjacent Bombs
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			boardTiles.at(i).at(j)->adjacentBombCt = 0;
			if ((j - 1) >= 0)
			{
				if ((i - 1) >= 0)
				{
					boardTiles.at(i).at(j)->adjacentTiles[0] = boardTiles.at(i - 1).at(j - 1);
					if (boardTiles.at(i - 1).at(j - 1)->isBomb)
					{
						boardTiles.at(i).at(j)->adjacentBombCt++;
					}
				}
				if ((i + 1) < columns)
				{
					boardTiles.at(i).at(j)->adjacentTiles[6] = boardTiles.at(i + 1).at(j - 1);
					if (boardTiles.at(i + 1).at(j - 1)->isBomb)
					{
						boardTiles.at(i).at(j)->adjacentBombCt++;
					}
				}
				boardTiles.at(i).at(j)->adjacentTiles[3] = boardTiles.at(i).at(j - 1);
				if (boardTiles.at(i).at(j - 1)->isBomb)
				{
					boardTiles.at(i).at(j)->adjacentBombCt++;
				}
			}
			if ((i - 1) >= 0)
			{
				boardTiles.at(i).at(j)->adjacentTiles[1] = boardTiles.at(i - 1).at(j);
				if (boardTiles.at(i - 1).at(j)->isBomb)
				{
					boardTiles.at(i).at(j)->adjacentBombCt++;
				}
			}
			if ((i + 1) < columns)
			{
				boardTiles.at(i).at(j)->adjacentTiles[6] = boardTiles.at(i + 1).at(j);
				if (boardTiles.at(i + 1).at(j)->isBomb)
				{
					boardTiles.at(i).at(j)->adjacentBombCt++;
				}
			}
			if (((j + 1) < rows))
			{
				if ((i - 1) >= 0)
				{
					boardTiles.at(i).at(j)->adjacentTiles[2] = boardTiles.at(i - 1).at(j + 1);
					if (boardTiles.at(i - 1).at(j + 1)->isBomb)
					{
						boardTiles.at(i).at(j)->adjacentBombCt++;
					}
				}
				if ((i + 1) < columns)
				{
					boardTiles.at(i).at(j)->adjacentTiles[7] = boardTiles.at(i + 1).at(j + 1);
					if (boardTiles.at(i + 1).at(j + 1)->isBomb)
					{
						boardTiles.at(i).at(j)->adjacentBombCt++;
					}
				}
				boardTiles.at(i).at(j)->adjacentTiles[4] = boardTiles.at(i).at(j + 1);
				if (boardTiles.at(i).at(j + 1)->isBomb)
				{
					boardTiles.at(i).at(j)->adjacentBombCt++;
				}
			}
		}
	}

}

void Board::SetTiles(std::string fileBRD)
{
	std::ifstream myBRD(fileBRD);
	std::string curLine;
	mineCount = 0;
	for (int i = 0; i < columns; i++)
	{
		getline(myBRD, curLine);
		std::cout << curLine << std::endl;
		std::vector<Tile*>* curRow = new std::vector<Tile*>;
		for (int j = 0; j < rows; j++)
		{
			Tile* currentTile = new Tile;
			if (curLine[j] == '1')
			{
				currentTile->isBomb = true;
				mineCount++;
			}
			else
			{
				currentTile->isBomb = false;
			}
			sf::Vector2i curCord(j, i);
			currentTile->tileCords = curCord;
			currentTile->isHidden = true;
			currentTile->isFlagged = false;
			curRow->push_back(currentTile);
			hiddenCount++;
		}
		boardTiles.push_back(*curRow);
	}
	

	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				boardTiles.at(i).at(j)->adjacentTiles[k] = nullptr;
			}
		}
	}


	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			boardTiles.at(i).at(j)->adjacentBombCt = 0;
			if ((j - 1) >= 0)
			{
				if ((i - 1) >= 0)
				{
					boardTiles.at(i).at(j)->adjacentTiles[0] = boardTiles.at(i - 1).at(j - 1);
					if (boardTiles.at(i - 1).at(j - 1)->isBomb)
					{
						boardTiles.at(i).at(j)->adjacentBombCt++;
					}
				}
				if ((i + 1) < columns)
				{
					boardTiles.at(i).at(j)->adjacentTiles[6] = boardTiles.at(i + 1).at(j - 1);
					if (boardTiles.at(i + 1).at(j - 1)->isBomb)
					{
						boardTiles.at(i).at(j)->adjacentBombCt++;
					}
				}
				boardTiles.at(i).at(j)->adjacentTiles[3] = boardTiles.at(i).at(j - 1);
				if (boardTiles.at(i).at(j - 1)->isBomb)
				{
					boardTiles.at(i).at(j)->adjacentBombCt++;
				}
			}
			if ((i - 1) >= 0)
			{
				boardTiles.at(i).at(j)->adjacentTiles[1] = boardTiles.at(i - 1).at(j);
				if (boardTiles.at(i - 1).at(j)->isBomb)
				{
					boardTiles.at(i).at(j)->adjacentBombCt++;
				}
			}
			if ((i + 1) < columns)
			{
				boardTiles.at(i).at(j)->adjacentTiles[6] = boardTiles.at(i + 1).at(j);
				if (boardTiles.at(i + 1).at(j)->isBomb)
				{
					boardTiles.at(i).at(j)->adjacentBombCt++;
				}
			}
			if (((j + 1) < rows))
			{
				if ((i - 1) >= 0)
				{
					boardTiles.at(i).at(j)->adjacentTiles[2] = boardTiles.at(i - 1).at(j + 1);
					if (boardTiles.at(i - 1).at(j + 1)->isBomb)
					{
						boardTiles.at(i).at(j)->adjacentBombCt++;
					}
				}
				if ((i + 1) < columns)
				{
					boardTiles.at(i).at(j)->adjacentTiles[7] = boardTiles.at(i + 1).at(j + 1);
					if (boardTiles.at(i + 1).at(j + 1)->isBomb)
					{
						boardTiles.at(i).at(j)->adjacentBombCt++;
					}
				}
				boardTiles.at(i).at(j)->adjacentTiles[4] = boardTiles.at(i).at(j + 1);
				if (boardTiles.at(i).at(j + 1)->isBomb)
				{
					boardTiles.at(i).at(j)->adjacentBombCt++;
				}
			}
		}
	}

	std::cout << "Board Tiles: " << boardTiles.size() << " TileCOUNT: " << tileCount << " minecount: " << mineCount << std::endl;
}

void Board::DrawTile(int row, int column, sf::RenderWindow *window_, Sprites *sprites_)
{
	sprites_->tileRevealed.setPosition(row * 32, column * 32);
	window_->draw(sprites_->tileRevealed);
	if (boardTiles.at(column).at(row)->isBomb)
	{
		sprites_->mine.setPosition(row * 32, column * 32);
		window_->draw(sprites_->mine);
	}
	else if (boardTiles.at(column).at(row)->adjacentBombCt == 1)
	{
		sprites_->numberOne.setPosition(row * 32, column * 32);
		window_->draw(sprites_->numberOne);
	}
	else if (boardTiles.at(column).at(row)->adjacentBombCt == 2)
	{
		sprites_->numberTwo.setPosition(row * 32, column * 32);
		window_->draw(sprites_->numberTwo);
	}
	else if (boardTiles.at(column).at(row)->adjacentBombCt == 3)
	{
		sprites_->numberThree.setPosition(row * 32, column * 32);
		window_->draw(sprites_->numberThree);
	}
	else if (boardTiles.at(column).at(row)->adjacentBombCt == 4)
	{
		sprites_->numberFour.setPosition(row * 32, column * 32);
		window_->draw(sprites_->numberFour);
	}
	else if (boardTiles.at(column).at(row)->adjacentBombCt == 5)
	{
		sprites_->numberFive.setPosition(row * 32, column * 32);
		window_->draw(sprites_->numberFive);
	}
	else if (boardTiles.at(column).at(row)->adjacentBombCt == 6)
	{
		sprites_->numberSix.setPosition(row * 32, column * 32);
		window_->draw(sprites_->numberSix);
	}
	else if (boardTiles.at(column).at(row)->adjacentBombCt == 7)
	{
		sprites_->numberSeven.setPosition(row * 32, column * 32);
		window_->draw(sprites_->numberSeven);
	}
	else if (boardTiles.at(column).at(row)->adjacentBombCt == 8)
	{
		sprites_->numberEight.setPosition(row * 32, column * 32);
		window_->draw(sprites_->numberEight);
	}
	if (boardTiles.at(column).at(row)->isHidden)
	{
		sprites_->tileHidden.setPosition(row * 32, column * 32);
		window_->draw(sprites_->tileHidden);
		if (boardTiles.at(column).at(row)->isFlagged)
		{
			sprites_->flag.setPosition(row * 32, column * 32);
			window_->draw(sprites_->flag);
		}
	}
	if (boardTiles.at(column).at(row)->isFlagged && !boardTiles.at(column).at(row)->isHidden)
	{
		sprites_->tileHidden.setPosition(row * 32, column * 32);
		window_->draw(sprites_->tileHidden);
		sprites_->flag.setPosition(row * 32, column * 32);
		window_->draw(sprites_->flag);
	}
	if (debugMode)
	{
		window_->draw(sprites_->mine);
	}
}

void Board::Reset()
{
	flagCount = 0;
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			delete boardTiles.at(i).at(j);
		}
		boardTiles.at(i).clear();
	}
	boardTiles.clear();
	debugMode = false;
	hiddenCount = 0;
}

void Board::RevealEmpty(int i, int j)
{
	if ((!boardTiles.at(i).at(j)->isBomb))
	{
		if (boardTiles.at(i).at(j)->isHidden)
		{
			boardTiles.at(i).at(j)->isHidden = false;
			hiddenCount--;
		}
		if (boardTiles.at(i).at(j)->adjacentBombCt == 0)
		{
			for (int k = 0; k < 8; k++)
			{
				if (boardTiles.at(i).at(j)->adjacentTiles[k] != nullptr)
				{
					if (boardTiles.at(i).at(j)->adjacentTiles[k]->isHidden)
					{
						boardTiles.at(i).at(j)->adjacentTiles[k]->isHidden = false;
						hiddenCount--;
						if (boardTiles.at(i).at(j)->adjacentTiles[k]->adjacentBombCt == 0)
						{
							RevealEmpty(boardTiles.at(i).at(j)->adjacentTiles[k]->tileCords.y, boardTiles.at(i).at(j)->adjacentTiles[k]->tileCords.x);
						}
					}
				}
			}
		}
	}
}

void Board::RemoveHidden() 
{
	hiddenCount--;
}

int Board::GetHidden() 
{
	return hiddenCount;
}