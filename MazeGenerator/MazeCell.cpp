#include "MazeCell.h"

static const sf::Color kUnvisitedColour = sf::Color(255, 255, 255);	// white
static const sf::Color kWallColour = sf::Color(0, 0, 0);			// black

static const sf::Color kVisitedColour = sf::Color(63, 124, 172), kPathColour = sf::Color(63, 124, 172);		// light blue
static const sf::Color kActiveColor = sf::Color(78, 255, 50);			// green
static const sf::Color kActiveVisitedColor = sf::Color(107, 50, 168);	// purple

MazeCell::MazeCell(int row, int column, float cellSize, float wallSize)
	: mRow(row),
	  mColumn(column),
	  mCellSize(cellSize),
	  mWallSize(wallSize),
	  mMazeOffset(sf::Vector2f(0.f, 0.f)),
	  mPaths(Path::kNoPaths),
	  mActive(false),
	  mVisited(false)
{
}

MazeCell::~MazeCell()
{
}

void MazeCell::openPath(Path path)
{
	// set the path bit for the path to open
	mPaths = static_cast<Path>(mPaths | path);
}

void MazeCell::reset()
{
	mPaths = kNoPaths;
	mActive = false;
	mVisited = false;
}

void MazeCell::draw(sf::RenderWindow* window) const
{
	sf::Color colour = sf::Color::White;

	if (mActive)
	{
		// if active, draw as active colour
		// if the cell is active and has been visitied, we are backtracking, draw as a diffrent colour (active visited colour)
		colour = mVisited ? kActiveVisitedColor : kActiveColor;
	}
	else if (mVisited)
	{
		// if not active and visited, draw as the visited colour
		colour = kVisitedColour;
	}

	sf::RectangleShape mazeCellRect(sf::Vector2f(mCellSize, mCellSize));
	mazeCellRect.setPosition(mMazeOffset + sf::Vector2f((float)mColumn, (float)mRow) * mCellSize);
	mazeCellRect.setFillColor(colour);

	mazeCellRect.setOutlineThickness(-1.f * mWallSize);
	mazeCellRect.setOutlineColor(kWallColour);

	window->draw(mazeCellRect);

	// draw the path for each open path
	if (mPaths & Path::kNorthPath)
	{
		// remove 2 * mWallSize from each shape so we don't draw the path in the corner of each cell
		sf::RectangleShape wall(sf::Vector2f(mCellSize - 2 * mWallSize, mWallSize));
		wall.setPosition(mMazeOffset + sf::Vector2f((float)mColumn, (float)mRow) * mCellSize + sf::Vector2f(mWallSize, 0));	
		wall.setFillColor(kPathColour);
		window->draw(wall);
	}

	if (mPaths & Path::kEastPath)
	{
		sf::RectangleShape wall(sf::Vector2f(mWallSize, mCellSize - 2 * mWallSize));
		wall.setPosition(mMazeOffset + sf::Vector2f((float)mColumn, (float)mRow) * (mCellSize) + sf::Vector2f(0, mWallSize));
		wall.setFillColor(kPathColour);
		window->draw(wall);
	}

	if (mPaths & Path::kSouthPath)
	{
		sf::RectangleShape wall(sf::Vector2f(mCellSize - 2 * mWallSize, mWallSize));
		wall.setPosition(mMazeOffset + sf::Vector2f((float)mColumn, (float)mRow) * mCellSize + sf::Vector2f(mWallSize, mCellSize - mWallSize));
		wall.setFillColor(kPathColour);
		window->draw(wall);
	}

	if (mPaths & Path::kWestPath)
	{
		sf::RectangleShape wall(sf::Vector2f(mWallSize, mCellSize - 2 * mWallSize));
		wall.setPosition(mMazeOffset + sf::Vector2f((float)mColumn, (float)mRow) * (mCellSize)+sf::Vector2f(mCellSize - mWallSize, mWallSize));
		wall.setFillColor(kPathColour);
		window->draw(wall);
	}
}
