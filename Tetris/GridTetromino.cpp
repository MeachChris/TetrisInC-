

#include "GridTetromino.h"
#include "Tetromino.h"
#include "Point.h"



	GridTetromino::GridTetromino() {
		gridLoc = Point(0, 0);
	};

	// return the tetromino's grid/gameboard loc (x,y)
	Point GridTetromino::getGridLoc() const {
		return gridLoc;
	};
	// sets the tetromino's grid/gameboard loc using x,y
	void GridTetromino::setGridLoc(int x, int y) {
		gridLoc = Point(x, y);

	};

	void GridTetromino::setGridLoc(const Point& pt) {
		gridLoc = pt;
	};


	void GridTetromino::move(int xOffset, int yOffset) {
		int x = gridLoc.getX() + xOffset;
		int y = gridLoc.getY() + yOffset;
		//x = x + xOffset;
		//y = y + yOffset;
		setGridLoc(x, y);
	};



	std::vector<Point> GridTetromino::getBlockLocsMappedToGrid() const {
		std::vector<Point> newBlockLocs;
		int x = gridLoc.getX();
		int y = gridLoc.getY();

		for (auto& point : blockLocs) {
			int internalX = point.getX();
			int internalY = point.getY();
			Point newpoint = Point(internalX + x, internalY + y);
			newBlockLocs.push_back(newpoint);

		}
		return newBlockLocs;
	}

