#include "MazeGenerator.h"

#include <random>

MazeGenerator::MazeGenerator(const MazeGrid& grid)
	: mRunning(false),
	  mGrid(grid)
{
}

MazeGenerator::~MazeGenerator()
{
}

void MazeGenerator::start()
{
	if (mCellStack.empty() && !mGrid.getCellAt(0, 0)->isVisited())
	{
		// if no cells have been touched, start the generation
		setActiveCell(mGrid.getCellAt(0, 0));
	}

	// flag the generator as running
	mRunning = true;
}

void MazeGenerator::togglePause()
{
	// toggle the running state
	mRunning = !mRunning;
}

void MazeGenerator::reset()
{
	// reset every cell in the gird back to unvisited
	mGrid.reset();

	// clear the stack
	mCellStack = std::stack<std::shared_ptr<MazeCell>>();

	// flag the generator as not running
	mRunning = false;
}

void MazeGenerator::update()
{
	if (!mRunning)
	{
		// not running, don't update
		return;
	}

	if (mCellStack.empty())
	{
		// no more cells to processed, all done, stop running
		mRunning = false;
		return;
	}

	const auto firstCell = mGrid.getCellAt(0, 0);
	if (getActiveCell() == firstCell)
	{
		// if the current cell is the first cell, open the entry path
		firstCell->openPath(MazeCell::Path::kEastPath);
	}
	
	const auto lastCell = mGrid.getCellAt(mGrid.getRows() - 1, mGrid.getColumns() - 1);
	if (getActiveCell() == lastCell)
	{
		// if the current cell is the last cell, open the exit path
		lastCell->openPath(MazeCell::Path::kWestPath);
	}

	// get a random unvisited neighbour for the cell at the top of the stack
	auto randomNeighbour = getRandomUnvisitedNeighbour(mCellStack.top());

	if (randomNeighbour)
	{
		// if we successfully got a neighbour, link the cells
		linkCells(getActiveCell(), randomNeighbour);

		// add the neighbot to the top of the stack
		setActiveCell(randomNeighbour);
	}
	else
	{
		// no neighbours pop the active cell off the stack
		popActiveCell();
	}

}

std::shared_ptr<MazeCell> MazeGenerator::getRandomUnvisitedNeighbour(std::shared_ptr<MazeCell> cell) const
{
	int row = cell->getRow();
	int col = cell->getColumn();

	std::vector<std::shared_ptr<MazeCell>> neighbours;

	// if we're not at the top row
	if (row > 0)
	{
		// get the north neighbour
		auto cell = mGrid.getCellAt(row - 1, col);

		if (!cell->isVisited())
		{
			neighbours.push_back(cell);
		}
	}

	// if we're not at the first column
	if (col > 0)
	{
		// get the east neighbour
		auto cell = mGrid.getCellAt(row, col - 1);

		if (!cell->isVisited())
		{
			neighbours.push_back(cell);
		}
	}

	// if we're not at the last column
	if (col < mGrid.getColumns() - 1)
	{
		// get the west neighbour
		auto cell = mGrid.getCellAt(row, col + 1);

		if (!cell->isVisited())
		{
			neighbours.push_back(cell);
		}
	}

	// if we're not at the bottom row
	if (row < mGrid.getRows() - 1)
	{
		// get the south neighbour
		auto cell = mGrid.getCellAt(row + 1, col);

		if (!cell->isVisited())
		{
			neighbours.push_back(cell);
		}
	}

	if (neighbours.empty())
	{
		// no unvisted neighbours
		return nullptr;
	}
	
	if (neighbours.size() == 1)
	{
		// only 1 neighbour, return it
		return neighbours.front();
	}


	// otherwise, shuffle all unvisited neighbours
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(neighbours.begin(), neighbours.end(), g);

	// return the first neighbour after the shuffle
	return neighbours.front();
}

std::shared_ptr<MazeCell> MazeGenerator::getActiveCell() const
{
	return mCellStack.top();
}

void MazeGenerator::setActiveCell(std::shared_ptr<MazeCell> cell)
{
	if (!mCellStack.empty())
	{
		// set the current active cell to inactive and mark the cell as visited
		mCellStack.top()->setActive(false);
		mCellStack.top()->setVisited(true);
	}

	// set the new cell to active and add it to the stack
	cell->setActive(true);
	mCellStack.push(cell);
}

void MazeGenerator::popActiveCell()
{
	// set the current active cell to inactive and mark the cell as visited
	mCellStack.top()->setActive(false);
	mCellStack.top()->setVisited(true);

	// pop the old active cell off the stack
	mCellStack.pop();

	if (!mCellStack.empty())
	{
		// set the new cell top to active
		mCellStack.top()->setActive(true);
	}
}

void MazeGenerator::linkCells(std::shared_ptr<MazeCell> cell1, std::shared_ptr<MazeCell> cell2)
{
	if (cell1 == cell2)
	{
		// can't link a cell to itself
		return;
	}

	if (cell1->getRow() == cell2->getRow())
	{
		// rows are equal, linking left/right
		if (cell1->getColumn() < cell2->getColumn())
		{
			// link left to right - path cell1 west to cell2 east
			cell1->openPath(MazeCell::Path::kWestPath);
			cell2->openPath(MazeCell::Path::kEastPath);
		}
		else
		{
			// link left to right - path cell1 east to cell2 west
			cell1->openPath(MazeCell::Path::kEastPath);
			cell2->openPath(MazeCell::Path::kWestPath);
		}
	}
	else if (cell1->getColumn() == cell2->getColumn())
	{
		// columns are equal, linking up/down
		if (cell1->getRow() < cell2->getRow())
		{
			// link up to dowm - path cell1 south to cell2 north
			cell1->openPath(MazeCell::Path::kSouthPath);
			cell2->openPath(MazeCell::Path::kNorthPath);
		}
		else
		{
			// link down to up - path cell1 north to cell2 south
			cell1->openPath(MazeCell::Path::kNorthPath);
			cell2->openPath(MazeCell::Path::kSouthPath);
		}
	}
}
