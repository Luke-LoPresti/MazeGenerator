#pragma once
#include <SFML/Graphics.hpp>
#include <stack>

#include "MazeGrid.h"

class MazeGenerator
{
public:
	MazeGenerator(const MazeGrid& grid);
	MazeGenerator() = default;
	~MazeGenerator();

	void start();
	void togglePause();
	void reset();

	void update();

private:
	std::shared_ptr<MazeCell> getRandomUnvisitedNeighbour(std::shared_ptr<MazeCell> cell) const;

	std::shared_ptr<MazeCell> getActiveCell() const;
	void setActiveCell(std::shared_ptr<MazeCell> cell);
	void popActiveCell();

	void linkCells(std::shared_ptr<MazeCell> cell1, std::shared_ptr<MazeCell> cell2);

	bool mRunning;
	MazeGrid mGrid;
	std::stack<std::shared_ptr<MazeCell>> mCellStack;
};

