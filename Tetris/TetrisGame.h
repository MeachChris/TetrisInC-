// This class encapsulates the tetris game and its drawing routines, gameplay, & control logic.
// This class was designed so with the idea of potentially instantiating 2 of them
// and have them run side by side (player vs player).
// So, anything you would need for an individual tetris game has been included here.
// Anything you might use between games (like the background, or the sprite used for 
// rendering a tetromino block) was left in main.cpp
// 
// This class is responsible for:
//   - setting up the board,
//	 - drawing game elements to the screen
//   - spawning tetrominoes,
//   - handling user input,
//   - moving and placing tetrominoes 
//
//  [expected .cpp size: ~ 275 lines]

#ifndef TETRISGAME_H
#define TETRISGAME_H

#include "Gameboard.h"
#include "GridTetromino.h"
#include <SFML/Graphics.hpp>
#include <assert.h>

class TetrisGame
{
private:
	// MEMBER VARIABLES

// State members ---------------------------------------------
	//const int xGameboardOffset = 54;      //gameboard pixel offset to top left
	//const int yGameboardOffset = 125;		//as above but top right.
	int score;					// the current game score.
	Gameboard board;			// the gameboard (grid) to represent where all the blocks are.
	GridTetromino nextShape;	// the tetromino shape that is "on deck".
	GridTetromino currentShape;	// the tetromino that is currently falling.
	GridTetromino testGTShape;	//to test movement for currentShape

	// Graphics members ------------------------------------------
	const Point gameboardOffset;// { xGameboardOffset, yGameboardOffset };	// pixel XY offset of the gameboard on the screen

	const Point nextShapeOffset; // = Point(480, 200);
	// pixel XY offset to the nextShape
	sf::Sprite& blockSprite;		// the sprite used for all the blocks.
	sf::RenderWindow& window;		// the window that we are drawing on.

	sf::Font scoreFont;				// SFML font for displaying the score.
	sf::Text scoreText;				// SFML text object for displaying the score

	// Time members ----------------------------------------------
	// Note: a "tick" is the amount of time it takes a block to fall one line.

	const double MAX_SECONDS_PER_TICK = 0.75;		// start off with a slow (max) tick rate. (seconds per game tick)
	const double MIN_SECONDS_PER_TICK = 0.20;		// this is the fastest tick pace (seconds per game tick).
	double secondsPerTick = MAX_SECONDS_PER_TICK;	// the number of seconds per tick (changes depending on score)

	double secondsSinceLastTick = 0.0;			// update this every game loop until it is >= secsPerTick,
												// we then know to trigger a tick.  Reduce this var (by a tick) & repeat.
	bool shapePlacedSinceLastGameLoop = false;	// Tracks whether we have placed (locked) a shape on
												// the gameboard in the current gameloop

public:
	// STATIC CONSTANTS
	static const int BLOCK_WIDTH = 32;			// pixel width of a tetris block
	static const int BLOCK_HEIGHT = 32;			// pixel height of a tetris block

	// MEMBER FUNCTIONS

	// constructor
	//   initialize/assign variables
	//   reset() the game
	//   load font from file: fonts/RedOctober.ttf
	//   setup scoreText
	TetrisGame(sf::RenderWindow& window, sf::Sprite& blockSprite, Point gameboardOffset, Point nextShapeOffset);

	// Draw anything to do with the game,
	//   includes the board, currentShape, nextShape, score
	//   called every game loop
	void draw();

	// Event and game loop processing
	// handles keypress events (up, left, right, down, space)
	void onKeyPressed(sf::Event event);

	// called every game loop to handle ticks & tetromino placement (locking)
	void processGameLoop(float secondsSinceLastLoop);

	// A tick() forces the currentShape to move 
	void tick();

private:
	// reset everything for a new game (use existing functions) 
	void reset();

	// assign nextShape.setShape a new random shape  
	void pickNextShape();

	// copy the nextShape into the currentShape (through assignment)
	bool spawnNextShape();

	// Test if a rotation is legal on the tetromino and if so, rotate it. 
	bool attemptRotate(GridTetromino& shape);

	// test if a move is legal on the tetromino, if so, move it.
	bool attemptMove(GridTetromino& shape, int x, int y);

	// drops the tetromino vertically as far as it can 
	//   legally go. 
	void drop(GridTetromino& shape);

	// copy the contents (color) of the tetromino's mapped block locs to the grid.
	void lock(const GridTetromino& shape);

	// Graphics methods ==============================================

	// Draw a tetris block sprite on the canvas		
	void drawBlock(const Point& topLeft, int xOffset, int yOffset, TetColor color);

	// Draw the gameboard blocks on the window
	void drawGameboard();

	// Draw a tetromino on the window
	void drawTetromino(const GridTetromino& tetromino, const Point& topLeft);

	// update the score display
	void updateScoreDisplay();

	// State & gameplay/logic methods ================================

	// return true if shape is within borders (isShapeWithinBorders())

	bool isPositionLegal(const GridTetromino& shape) const;

	// return true if the shape is within the left, right, and lower border of
	//	 the grid, but *NOT* the top border. 
	bool isShapeWithinBorders(const GridTetromino& shape) const;


	// set secsPerTick 
	void determineSecondsPerTick();


};

#endif /* TETRISGAME_H */

