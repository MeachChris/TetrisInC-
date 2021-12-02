

#include "Gameboard.h"
#include "TetrisGame.h"
#include "GridTetromino.h"
#include <SFML/Graphics.hpp>



TetrisGame::TetrisGame(sf::RenderWindow& window, sf::Sprite& blockSprite, Point gameboardOffset, Point nextShapeOffset) 
	: window(window), blockSprite(blockSprite), gameboardOffset(gameboardOffset), nextShapeOffset(nextShapeOffset){
	//TetrisGame::blockSprite = blockSprite;
	//TetrisGame::window = window;
	//currentShape.move(board.getSpawnLoc().getX(), 0);
	if (!scoreFont.loadFromFile("fonts/RedOctober.ttf")) { 
		assert(false && "Missing font: RedOctober.ttf"); 
	};
	scoreText.setFont(scoreFont);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(435, 325);
	//currentShape.setShape(Tetromino::getRandomShape());
	reset();
	//board.setContent(Gameboard::MAX_X / 2, Gameboard::MAX_Y / 2, 3);
}

// Draw anything to do with the game,
void TetrisGame::draw() {
	//drawBlock(TetrisGame::gameboardOffset, 0, 0, TetColor::GREEN);
	//int x = gameboardOffset.getX();
	//Point spawnloc = board.getSpawnLoc();
	//int addX = spawnloc.getX();
	//int newx = x + addX;
	//int newy = gameboardOffset.getY();
	//Point newPoint = Point(newx, newy);
	// 
	// 
	//board.setContent(Point(1,1), 1);
	drawGameboard();
	drawTetromino(currentShape, gameboardOffset);
	drawTetromino(nextShape, nextShapeOffset);

	window.draw(scoreText);
}

// Event and game loop processing
// handles keypress events (up, left, right, down, space)
void TetrisGame::onKeyPressed(sf::Event event) {
	//window.setKeyRepeatEnabled(false);
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Up) {
			attemptRotate(currentShape);
		}
		if (event.key.code == sf::Keyboard::Left) {
			attemptMove(currentShape, -1, 0);
		}
		if (event.key.code == sf::Keyboard::Right) {
			attemptMove(currentShape, 1, 0);
		}
		if (event.key.code == sf::Keyboard::Down) {
			if (!attemptMove(currentShape, 0, 1)) {
				lock(currentShape);
			}
		}
		if (event.key.code == sf::Keyboard::Space) {
			drop(currentShape);
			lock(currentShape);
			
		}
	}
}

// called every game loop to handle ticks & tetromino placement (locking)
void TetrisGame::processGameLoop(float secondsSinceLastLoop) {
	secondsSinceLastTick = secondsSinceLastTick + secondsSinceLastLoop;
	if (secondsSinceLastTick > secondsPerTick) {
		tick();
		secondsSinceLastTick = secondsSinceLastTick - secondsPerTick;
	}
	if (shapePlacedSinceLastGameLoop) {
		if (!spawnNextShape()) {
			reset();
		}
		pickNextShape();
		score = score + board.removeCompletedRows();
		updateScoreDisplay();
		determineSecondsPerTick();
		shapePlacedSinceLastGameLoop = false;
	}
} 


// A tick() forces the currentShape to move 

void TetrisGame::tick() {
	if (!attemptMove(currentShape, 0, 1)) {
		lock(currentShape);
		shapePlacedSinceLastGameLoop = true;
	}

}

// reset everything for a new game 
void TetrisGame::reset() {
	score = 0;
	updateScoreDisplay();
	determineSecondsPerTick();
	board.empty();
	pickNextShape();
	spawnNextShape();
	pickNextShape();

}

// assign nextShape.setShape a new random shape  
void TetrisGame::pickNextShape() {
	nextShape.setShape(Tetromino::getRandomShape());
	//nextShape.rotateClockwise();
	//nextShape.rotateClockwise();
}

// copy the nextShape into the currentShape (through assignment)

bool TetrisGame::spawnNextShape() {
	currentShape = nextShape;
	currentShape.setGridLoc(board.getSpawnLoc());
	//currentShape.move(0, 1);
	return isPositionLegal(currentShape);
	/*
	testGTShape = currentShape;
	//bool legalPosition = false;
	std::vector<Point> testVec = testGTShape.getBlockLocsMappedToGrid();
	for (auto& points : testVec) {
		points.setX(points.getX() + 5);
	}
	//legalPosition = board.areLocsEmpty(testVec);
	bool validity = isPositionLegal(testGTShape);
	currentShape.move(board.getSpawnLoc().getX(), 0);
	std::cout << validity;
	*/

	
}

// Test if a rotation is legal on the tetromino and if so, rotate it. 
bool TetrisGame::attemptRotate(GridTetromino& shape) {
	GridTetromino tempShape = shape;
	tempShape.rotateClockwise();
	if (isPositionLegal(tempShape)) {
		shape.rotateClockwise();
		return true;
	}
	//Gameboard::isValidMove(tempShape.rotateClockwise());
	return false;
}

// test if a move is legal on the tetromino, if so, move it.
bool TetrisGame::attemptMove(GridTetromino& shape, int x, int y) {
	GridTetromino tempShape = shape;
	tempShape.move(x, y);

	if (isPositionLegal(tempShape)) {
		shape.move(x, y);
		return true;
	}
	return false;
}

// drops the tetromino vertically as far as it can 
void TetrisGame::drop(GridTetromino& shape) {
	while (attemptMove(shape, 0, 1)) {};
}

// copy the contents (color) of the tetromino's mapped block locs to the grid.
void TetrisGame::lock(const GridTetromino& shape) {
	std::vector<Point> locklocs = shape.getBlockLocsMappedToGrid();
	for (auto& points : locklocs) {
		if (board.isValidPoint(points)) {
			board.setContent(points, static_cast<int>(currentShape.getColor()));
		}
	}
}

// Graphics methods ==============================================

// Draw a tetris block sprite on the canvas		
void TetrisGame::drawBlock(const Point& topLeft, int xOffset, int yOffset, TetColor color) {
	int x = topLeft.getX() + (xOffset * BLOCK_WIDTH);
	int y = topLeft.getY() + (yOffset * BLOCK_HEIGHT);

	sf::IntRect rect = sf::IntRect(BLOCK_WIDTH * static_cast<int>(color), 0, BLOCK_WIDTH, BLOCK_HEIGHT);

	blockSprite.setTextureRect(rect);
	blockSprite.setPosition(x, y);
	window.draw(blockSprite);


};

// Draw the gameboard blocks on the window
void TetrisGame::drawGameboard() {

	for (int y = 0; y < Gameboard::MAX_Y; y++) {
		for (int x = 0; x < Gameboard::MAX_X; x++) {
			if (board.getContent(x, y) != Gameboard::EMPTY_BLOCK) {
				TetColor color = static_cast<TetColor>(board.getContent(x, y));
				drawBlock(TetrisGame::gameboardOffset, x, y, color);
				//g.setContent(x, y, static_cast<int>(TetColor::GREEN));

			}
		};

	};

};

// Draw a tetromino on the window
void TetrisGame::drawTetromino(const GridTetromino& tetromino, const Point& topLeft) {
	std::vector<Point> tetblocks = tetromino.getBlockLocsMappedToGrid();
	for (auto& points : tetblocks) {
		drawBlock(topLeft, points.getX() , points.getY(), tetromino.getColor());
	}
}



// update the score display
void TetrisGame::updateScoreDisplay() {
	std::string scoreString = "score: " + std::to_string(score);
	scoreText.setString(scoreString);
}

// State & gameplay/logic methods ================================

// return true if shape is within borders (isShapeWithinBorders())
bool TetrisGame::isPositionLegal(const GridTetromino& shape) const {

	std::vector<Point> tetblocks = shape.getBlockLocsMappedToGrid();
	
	return isShapeWithinBorders(shape) && board.areLocsEmpty(tetblocks);
}

// return true if the shape is within the left, right, and lower border of
bool TetrisGame::isShapeWithinBorders(const GridTetromino& shape) const {
	std::vector<Point> tetblocks = shape.getBlockLocsMappedToGrid();
	//Point spawnloc { Gameboard::MAX_X / 2, 0 };
	for (auto& points : tetblocks) {
		int x = points.getX();
		int y = points.getY();
		//x = x - (Gameboard::MAX_X / 2);
		//x >= 0 && x < MAX_X && y < MAX_Y
		if (x < 0 || x >= Gameboard::MAX_X || y >= Gameboard::MAX_Y) {
		return false;
		}
		//if (!board.isValidPoint(points.getX(), points.getY())) {
			//return false;
		//}
	}
	return true;
}


// set secsPerTick 
void TetrisGame::determineSecondsPerTick() {
	if (secondsPerTick > 0) {
		secondsPerTick = secondsPerTick - (score / 50);
	}
}




