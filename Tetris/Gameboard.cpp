#include <vector>
#include "Point.h"
#include "Gameboard.h"
#include <assert.h>



	// MEMBER FUNCTIONS

Gameboard::Gameboard() {


	empty();



}

Point Gameboard::getSpawnLoc() {
	return spawnLoc;
}

// return the content at a given point (assert the point is valid)
int Gameboard::getContent(const Point& pt) const {

	assert(isValidPoint(pt));
	//int x = pt.getX();
	//int y = pt.getY();
	return grid[pt.getY()][pt.getX()];

}
// return the content at an x,y grid loc (assert the point is valid)
int Gameboard::getContent(int x, int y) const {
	assert(isValidPoint(x, y));
	return grid[y][x];

}

// set the content at a given point (only if the point is valid)
void Gameboard::setContent(const Point& pt, int content) {
	assert(isValidPoint(pt));
	//int x = pt.getX();
	//int y = pt.getY();
	grid[pt.getY()][pt.getX()] = content;


}
// set the content at an x,y position (only if the point is valid)
void Gameboard::setContent(int x, int y, int content) {

	assert(isValidPoint(x, y));
	grid[y][x] = content;


}
// set the content for a set of points (only if the points are valid)
void Gameboard::setContent(const std::vector<Point>& locs, int content) {

	for (auto& point : locs) {
		setContent(point.getX(), point.getY(), content);
	}
}

// return true if the content at ALL (valid) points is empty
bool Gameboard::areLocsEmpty(std::vector<Point> locs) const {
	for (auto& point : locs) {
		if (isValidPoint(point)) {
			if (getContent(point) != EMPTY_BLOCK) {
				return false;
			}
		}
	}
	return true;
}

// removes all completed rows from the board
int Gameboard::removeCompletedRows() {
	std::vector<int> finRows = getCompletedRowIndices();
	removeRows(finRows);
	return finRows.size();
}

// fill the board with EMPTY_BLOCK 
void Gameboard::empty() {
	for (int y = 0; y < MAX_Y; y++) {

		fillRow(y, EMPTY_BLOCK);
	}
}


// print the grid contents to the console 
void Gameboard::printToConsole() const {
	std::cout << "-------------GAMEBOARD--------------\n";
	for (int y = 0; y < MAX_Y; y++) {
		for (int x = 0; x < MAX_X; x++) {
			if (getContent(x, y) == EMPTY_BLOCK) {
				std::cout << getContent(x, y);
			}
			else {
				std::cout << " " << getContent(x, y);
			}

		}
		std::cout << "\n";
	}
	std::cout << "-------------END BOARD--------------\n";

}


// return a bool indicating if a given row is full (no EMPTY_BLOCK in the row)
bool Gameboard::isRowCompleted(int rowIndex) const {

	for (int x = 0; x < MAX_X; x++) {
		if (getContent(x, rowIndex) == EMPTY_BLOCK) {
			return false;
		}
	}
	return true;

}

// scan the board for completed rows.
std::vector<int> Gameboard::getCompletedRowIndices() const {
	std::vector<int> finRows;
	for (int y = 0; y < MAX_Y; y++) {
		if (isRowCompleted(y)) {
			finRows.push_back(y);
		}
	}
	return finRows;
}

// In gameplay, when a full row is completed (filled with content)
// it gets "removed".  To be exact, the row itself is not removed
// but the content from the row above it is copied into it.
void Gameboard::removeRow(int rowIndex) {
	for (int y = rowIndex; y > 0; y--) {
		copyRowIntoRow(y - 1, y);
	}
	fillRow(0, EMPTY_BLOCK);
}

// given a vector of row indices, remove them 
//   (iterate through the vector and and call removeRow()
//   on each row index). 
void Gameboard::removeRows(const std::vector<int>& rowIndices) {
	for (auto& row : rowIndices) {
		removeRow(row);
	}
}

// fill a given grid row with specified content
void Gameboard::fillRow(int rowIndex, int content) {
	for (int x = 0; x < MAX_X; x++) {
		setContent(x, rowIndex, content);
	}
}

// copy a source row's contents into a target row.
void Gameboard::copyRowIntoRow(int sourceRowIndex, int targetRowIndex) {
	for (int x = 0; x < MAX_X; x++) {
		setContent(x, targetRowIndex, getContent(x, sourceRowIndex));
	} 
}

// return true if the point is on the grid, false otherwise
bool Gameboard::isValidPoint(const Point& p) const {
	int x = p.getX();
	int y = p.getY();
	return (x >= 0 && x < MAX_X && y < MAX_Y && y >= 0);
}

// return true if the x,y location is on the grid, false otherwise
bool Gameboard::isValidPoint(int x, int y) const {
	return (x >= 0 && x < MAX_X && y < MAX_Y && y >= 0);
}



