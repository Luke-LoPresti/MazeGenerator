#include "MazeGrid.h"

#include <random>

MazeGrid::MazeGrid(int numRows, int numCols, float cellSize, float wallSize)
	: mNumRows(numRows),
	  mNumCols(numCols),
	  mCellSize(cellSize),
	  mWallSize(wallSize),
	  mPosition(sf::Vector2f(0.f, 0.f))
{
	// generate the grid
	for (int row = 0; row < numRows; ++row)
	{
		for (int col = 0; col < numCols; ++col)
		{
			auto mazeCell = std::make_shared<MazeCell>(row, col, cellSize, wallSize);
			mCells.emplace_back(mazeCell);
		}
	}
}

MazeGrid::~MazeGrid()
{
}

std::shared_ptr<MazeCell> MazeGrid::getCellAt(int row, int column) const
{
	// return a pointer to the cell at a row and column
	return mCells[column + (row * mNumCols)];
}

void MazeGrid::setPosition(const sf::Vector2f& position)
{
	mPosition = position;
	for (const auto& cell : mCells)
	{
		cell->setMazeOffset(position);
	}
}

void MazeGrid::reset()
{
	for (const auto& cell : mCells)
	{
		cell->reset();
	}
}

void MazeGrid::draw(sf::RenderWindow* window) const
{
	for (const auto& cell : mCells)
	{
		cell->draw(window);
	}
}
