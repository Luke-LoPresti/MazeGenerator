#pragma once
#include <SFML/Graphics.hpp>

class MazeCell
{
public:
	enum Path
	{
		kNoPaths	= 0,
		kNorthPath	= 1,
		kEastPath	= 2,
		kSouthPath  = 4,
		kWestPath	= 8
	};

	MazeCell(int row, int column, float cellSize, float wallSize);
	~MazeCell();

	int getRow() const { return mRow; }
	int getColumn() const { return mColumn; }
	bool isVisited() const { return mVisited; }

	void setMazeOffset(const sf::Vector2f& offset) { mMazeOffset = offset; }
	void setActive(bool active) { mActive = active; }
	void setVisited(bool visited) { mVisited = visited; }

	void openPath(Path path);

	void reset();

	void draw(sf::RenderWindow* window) const;

	bool operator==(const MazeCell& mazeCell) const
	{
		return mRow == mazeCell.mRow && mColumn == mazeCell.mColumn;
	}

private:
	int mRow;
	int mColumn;
	float mCellSize;
	float mWallSize;

	sf::Vector2f mMazeOffset;

	Path mPaths;
	bool mActive;
	bool mVisited;
};

