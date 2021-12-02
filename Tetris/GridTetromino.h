

#ifndef GRIDTETROMINO_H
#define GRIDTETROMINO_H

#include "Tetromino.h"

class GridTetromino : public Tetromino
{
	// MEMBER VARIABLES
private:
	Point gridLoc;	// the [x,y] location of this tetromino on the grid/gameboard. 
					// This loc changes each time the tetromino moves.

public:
	// constructor, initialize gridLoc to 0,0
	GridTetromino();

	// return the tetromino's grid/gameboard loc (x,y)
	Point getGridLoc() const;
	// sets the tetromino's grid/gameboard loc using x,y
	void setGridLoc(int x, int y);
	// sets the tetromino's grid/gameboard loc using a Point
	void setGridLoc(const Point& pt);

	// transpose the gridLoc of this shape
	//	(1,0) represents a move to the right (x+1)
	//	(-1,0) represents a move to the left (x-1)
	//	(0,1) represents a move down (y+1)
	void move(int xOffset, int yOffset);

	// build and return a vector of Points to represent our inherited vector
	std::vector<Point> getBlockLocsMappedToGrid() const;

};

#endif /* GRIDTETROMINO_H */