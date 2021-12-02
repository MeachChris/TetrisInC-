#pragma once
#include "Point.h"
#include <vector>


enum class TetColor { RED, ORANGE, YELLOW, GREEN, BLUE_LIGHT, BLUE_DARK, PURPLE };

enum class TetShape { S, Z, L, J, O, I, T, COUNT };



class Tetromino {
	friend class TestSuite;
	friend class GridTetromino;
	friend class TetrisGame;
private:

	TetColor color;
	TetShape shape;
	std::vector<Point> blockLocs;

public:

	Tetromino();


	//gets the color, cannot reassign variables.
	TetColor getColor() const;

	//gets the shape, cannot reassign variables.
	TetShape getShape() const;

	//sets the shape.
	void setShape(TetShape shape);

	//rotates the tetromino clockwise
	void rotateClockwise();

	//prints to console; the tetromino what it looks like.
	void printToConsole();

	static TetShape getRandomShape();
	


};