#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "MazeCell.h"

class MazeGrid
{
public:
	MazeGrid(int numCols, int numRows, float cellSize, float wallSize);
	MazeGrid() = default;
	~MazeGrid();

	int getRows() const { return mNumRows; }
	int getColumns() const { return mNumCols; }

	std::shared_ptr<MazeCell> getCellAt(int row, int column) const;

	void setPosition(const sf::Vector2f& position);

	void reset();

	void draw(sf::RenderWindow* window) const;

private:
	int mNumRows;
	int mNumCols;
	float mCellSize;
	float mWallSize;
	sf::Vector2f mPosition;

	std::vector<std::shared_ptr<MazeCell>> mCells;
};

