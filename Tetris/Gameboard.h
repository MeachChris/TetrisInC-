#pragma once



#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include "Point.h"

class Gameboard

{
	friend class TestSuite;
	friend class TetrisGame;
public:
	// CONSTANTS
	static const int MAX_X = 10;		// gameboard x dimension
	static const int MAX_Y = 19;		// gameboard y dimension
	static const int EMPTY_BLOCK = -1;	// contents of an empty block

private:
	// MEMBER VARIABLES -------------------------------------------------

	// the gameboard - a grid of X and Y offsets.  
	//  ([0][0] is top left, [MAX_Y-1][MAX_X-1] is bottom right) 
	int grid[MAX_Y][MAX_X];
	// the gameboard offset to spawn a new tetromino at.
	const Point spawnLoc{ MAX_X / 2, 0 };

public:
	// MEMBER FUNCTIONS

	// constructor 
	Gameboard();

	Point getSpawnLoc();

	
	int getContent(const Point& pt) const;

	int getContent(int x, int y) const;

	// set the content at an point
	void setContent(const Point& pt, int content);
	// set the content at an x,y position (only if the point is valid)
	void setContent(int x, int y, int content);
	// set the content for a set of points (only if the points are valid)
	void setContent(const std::vector<Point>& locs, int content);


	bool areLocsEmpty(std::vector<Point> locs) const;

	// removes all completed rows from the board
	int removeCompletedRows();

	// fill the board with EMPTY_BLOCK 
	void empty();

	void printToConsole() const;

public:
	bool isRowCompleted(int rowIndex) const;

	// scan the board for completed rows.
	std::vector<int> getCompletedRowIndices() const;
	//remove a row
	void removeRow(int rowIndex);

	// given a vector of row indices, remove them 
	void removeRows(const std::vector<int>& rowIndices);

	// fill a given grid row with specified content
	void fillRow(int rowIndex, int content);

	// copy a source row's contents into a target row.
	void copyRowIntoRow(int sourceRowIndex, int targetRowIndex);

	// return true if the point is on the grid, false otherwise
	bool isValidPoint(const Point& p) const;

	// return true if the x,y location is on the grid, false otherwise
	bool isValidPoint(int x, int y) const;

};

#endif /* GAMEBOARD_H */

