
#include "Point.h"
#include "Tetromino.h"
#include <vector>


Tetromino::Tetromino() {
	//color = TetColor::RED;
	//shape = TetShape::I;
	//blockLocs;
	setShape(shape);

}

//gets the color, cannot reassign variables.
TetColor Tetromino::getColor() const {
	return TetColor{ this->color };
};

//gets the shape, cannot reassign variables.
TetShape Tetromino::getShape() const {
	return TetShape{ this->shape };
};

// set the shape
void Tetromino::setShape(TetShape shape) {
	blockLocs.empty();
	this->shape = shape;
	if (shape == TetShape::S) {
		blockLocs = { Point(0,0), Point(-1, 0), Point(0, 1), Point(1,1) };
		color = TetColor::RED;
	}
	else if (shape == TetShape::Z) {
		blockLocs = { Point(0,0), Point(1, 0), Point(0,1), Point(-1, 1) };
		color = TetColor::ORANGE;
	}
	else if (shape == TetShape::L) {
		blockLocs = { Point(0,0), Point(0,1), Point(0,-1), Point(1,-1) };
		color = TetColor::YELLOW;
	}
	else if (shape == TetShape::J) {
		blockLocs = { Point(0,0), Point(0,1), Point(0, -1), Point(-1,-1) };
		color = TetColor::GREEN;
	}
	else if (shape == TetShape::O) {
		blockLocs = { Point(0,0), Point(0,1), Point(1,1), Point(1,0) };
		color = TetColor::BLUE_LIGHT;
	}
	else if (shape == TetShape::I) {
		blockLocs = { Point(0,0), Point(0,-1), Point(0, 1), Point(0,2) };
		color = TetColor::BLUE_DARK;
	}
	else if (shape == TetShape::T) {
		blockLocs = { Point(0,0), Point(-1,0), Point(0,-1), Point(1,0) };
		color = TetColor::PURPLE;
	}

};

//rotates the tetromino clockwise
void Tetromino::rotateClockwise() {
	for (auto& point : blockLocs) {
		point.multiplyX(-1);
		point.swapXY();
	}
};




//prints to console; the tetromino what it looks like.
void Tetromino::printToConsole() {
	std::cout << "\n" << "Printing Tetromino piece:\n";
	// print grid to display current shape
	for (int y = 6; y > 0; y--) {
		bool same = false;
		for (int x = 0; x < 6; x++) {

			for (auto& point : blockLocs) {
				if ((x - 3) == point.getX() && (y - 3) == point.getY()) {
					same = true;
				}
			}
			if (same == false) {
				std::cout << ".";
			}
			else {
				std::cout << "X";
			}
			same = false;
		}
		std::cout << "\n";
	}

};

TetShape Tetromino::getRandomShape() {

	TetShape randomShape = static_cast<TetShape>(rand() % static_cast<int>(TetShape::COUNT));
	return randomShape;
}


