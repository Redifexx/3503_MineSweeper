#include "board.h"
#include "textures.h"

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
	/*
	for (int i = 0; i < tileCount; i++)
	{
		Tile* currentTile = new Tile;
		boardTiles.push_back(currentTile);
	}*/
	std::cout << "check" << std::endl;
	for (int i = 0; i < columns; i++)
	{
		std::vector<Tile*>* curRow = new std::vector<Tile*>;
		for (int j = 0; j < rows; j++)
		{
			Tile* currentTile = new Tile;
			curRow->push_back(currentTile);
			currentTile->isHidden = true;
			currentTile->isFlagged = false;
		}
		boardTiles.push_back(*curRow);
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
		std::vector<Tile*>* curRow = new std::vector<Tile*>;
		for (int j = 0; j < rows; j++)
		{
			Tile* currentTile = new Tile;
			if (curLine[j] == '1')
			{
				currentTile->isBomb = true;
				//std::cout << "BOMB" << std::endl;
			}
			else
			{
				currentTile->isBomb = false;
			}
			sf::Vector2i curCord(j + 1, i + 1);
			currentTile->tileCords = curCord;
			currentTile->isHidden = true;
			currentTile->isFlagged = false;
			curRow->push_back(currentTile);
			//std::cout << j << ", " << i << std::endl;
			//std::cout << i << " check " << j << std::endl;
			//boardTiles.at(i).push_back(currentTile);
			//std::cout << "check " << j << std::endl;
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
		// 27 -> 1, 2, 3, 26, 28, 51, 52, 53
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
			//std::cout << "test2 " << i << " " << j << std::endl;
		}// 27 -> 1, 2, 3, 26, 28, 51, 52, 53
	}
	//std::cout << "check" << std::endl;
	/*
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			int curCount = 0;
			if (boardTiles.at(i).at(j)->isBomb)
			{
				//std::cout << "check" << std::endl;
				curCount++;
			}
			boardTiles.at(i).at(j)->adjacentBombCt = curCount;
			std::cout << "bombcount " << boardTiles.at(i).at(j)->adjacentBombCt << std::endl;
		}
		// 27 -> 1, 2, 3, 26, 28, 51, 52, 53
	}*/

	std::cout << "Board Tiles: " << boardTiles.size() << " TileCOUNT: " << tileCount << std::endl;
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
}