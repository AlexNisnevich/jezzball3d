#include "game.h"

Mouse::Mouse(int direction[]): primaryDirection(direction[0]), secondaryDirection(direction[1]) {}

void Mouse::changeDirection() {
	primaryDirection++;
	if (primaryDirection > VZ) {
		primaryDirection = VX;
		secondaryDirection++;
	}
	if (secondaryDirection > VZ) {
		secondaryDirection = VX;
	}
	if (primaryDirection == secondaryDirection) {
		changeDirection();
	}
}

void Mouse::changeDirectionBack() {
	for (int i = 0; i < 5; i++) {
		changeDirection();
	}
}

Game::Game(Settings * settings, int startingBalls, int startingLives, vec3 dimension, int startingDirection[]):
numBalls(startingBalls), numLives(startingLives), score(0), settings(settings), dimension(dimension), gameOver(false), win(false) {
	vec3 corner2 = dimension;
	vec3 corner1 = - dimension;
	playField = new Box(corner1, corner2);
	mouse = new Mouse(startingDirection);
	bool isDrawing[2] = { false, false };
	clearTempWall();
	startTime = glutGet(GLUT_ELAPSED_TIME);
	createBalls();
	area = 0;
	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 20; j++)
			for (int k = 0; k < 20; k++)
				occupied[i][j][k] = false;
	PLAYSOUND("tada.wav");
}

Game::~Game() {
	for (vector<Wall *>::iterator it = getWallsBeginIterator(); it != getWallsEndIterator(); ++it) {
		Wall * w = *it;
		delete w;
	}
	delete playField;
	delete mouse;
}

void Game::renderWalls() {
	for (vector<Wall *>::iterator it = getWallsBeginIterator(); it != getWallsEndIterator(); ++it) {
		Wall * w = *it;
		w->render();
	}
}

void Game::render() {
	tempWall->render();
	renderWalls();
	playField->render();

	// check if win condition satisfied for this level
	if (getArea() >= getSettings()->goal && !win) {
		win = true;
		finishTime = glutGet(GLUT_ELAPSED_TIME);
	}
}

void Game::animate() {
	if (gameOver || win) {
		return;
	}

	// animate box
	playField->animate();

	// animate walls
	for (vector<Wall *>::iterator it = getWallsBeginIterator(); it != getWallsEndIterator(); ++it) {
		Wall * w = *it;
		w->collision();
		w->animate();
	}
}

void Game::createBalls() {
	for (int i = 0; i < numBalls; i++) {
		playField->addBall(getSettings()->ballRadius, getSettings()->ballVelocity, getSettings()->ballColor);
	}
}

void Game::setTempWall(Wall * w) {
	if (!gameOver && !win) {
		tempWall = w;
	} else {
		clearTempWall();
	}
}

void Game::finalizeTempWall() {
	if (gameOver || win) {
		return;
	}

	if (tempWall->getState() != NONEXISTENT) {
		tempWall->setState(NORMAL);
		walls.push_back(tempWall);
		clearTempWall();
		PLAYSOUND("gap.wav");
	}
}

void Game::clearTempWall() {
	tempWall = new Wall(vec3(0), -1, -1, NONEXISTENT, this);
}

bool Game::isDrawing(int side) {
	for (vector<Wall *>::iterator it = getWallsBeginIterator(); it != getWallsEndIterator(); ++it) {
		Wall * w = *it;
		if ((side == 1 && w->getPositiveSide() == PROGRESS) ||
			(side == 0 && w->getNegativeSide() == PROGRESS)) {
				return true;
		}
	}
	return false;
}

int Game::getTime() {
	if (gameOver) {
		return 0;
	}
	int elapsedTime;
	if (win) {
		elapsedTime = (finishTime - startTime) / 300;
	} else {
		elapsedTime = (glutGet(GLUT_ELAPSED_TIME) - startTime) / 300;
	}

	int timeRemaining = 1500 - elapsedTime;
	if (timeRemaining < 0) {
		gameOver = true;
	}
	return timeRemaining;
}

void Game::unpause() {
	extern int timeRemaining;
	int elapsedTime = 1500 - timeRemaining;

	if (win) {
		startTime = finishTime - 300 * elapsedTime;
	} else {
		startTime = glutGet(GLUT_ELAPSED_TIME) - 300 * elapsedTime;
	}
}

int Game::getNumLives() {
	if (gameOver) {
		return 0;
	} else {
		return numLives;
	}
}

int Game::getScore() {
	int prevScore = score;
	int currentScore = prevScore + (46.67 * getArea());
	return currentScore;
}

void Game::nextLevel() {
	if (!win) {
		return;
	}

	score = getScore() + getTime();
	numBalls ++;
	numLives = numBalls;
	int startingDirection[2] = { VX, VZ };

	delete playField;
	playField = new Box(- dimension, dimension);
	delete mouse;
	mouse = new Mouse(startingDirection);

	walls.clear();
	clearTempWall();
	startTime = glutGet(GLUT_ELAPSED_TIME);
	createBalls();
	area = 0;
	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 20; j++)
			for (int k = 0; k < 20; k++)
				occupied[i][j][k] = false;
	win = false;
}

void Game::loseLife() {
	numLives--;
	if (numLives == 0) {
		gameOver = true;
	}
}

int Game::getArea() {
	int maxArea = 16000;
	// return area;
	return (area * 100 / maxArea);
}

void Game::calcArea() {
	bool balls[40][20][20] = { false };

	float width = getSettings()->wallPrimaryWidth;

	for (vector<Ball *>::iterator it = playField->getBallsBegin(); it != playField->getBallsEnd(); ++it) {
		Ball * b = *it;
		vec3 location = (1/width) * (b->pos + getDimensions());
		int x = floor(location[VX]);
		int y = floor(location[VY]);
		int z = floor(location[VZ]);
		balls[x][y][z] = true;
	}

	for (int n = 0; n < 80; n++) {
		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 20; j++) {
				for (int k = 0; k < 20; k++) {
					if (!balls[i][j][k] && !occupied[i][j][k] &&
							((i<39 && balls[i+1][j][k]) || (i>0 && balls[i-1][j][k]) ||
							 (j<19 && balls[i][j+1][k]) || (j>0 && balls[i][j-1][k]) ||
							 (k<19 && balls[i][j][k+1]) || (k>0 && balls[i][j][k-1]))) {
								balls[i][j][k] = true;
					}
				}
			}
		}
	}

	area = 0;
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 20; j++) {
			for (int k = 0; k < 20; k++) {
				if (!balls[i][j][k]) {
					area++;
				}
			}
		}
	}
}

char* Game::getStatus() {
	if (win) {
		return "Press N to advance to the next level.";
	} else if (gameOver) {
		return "Game over. Press R to restart.";
	} else {
		return "";
	}
}
