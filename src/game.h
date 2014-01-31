#ifndef GAME_H_
#define GAME_H_

#include "main.h"

using namespace std;

#include "box.h"
class Box; // forward declaration
#include "wall.h"
class Wall; // forward declaration

struct Mouse {
	vec3 position;
	int primaryDirection;
	int secondaryDirection;

	Mouse(int direction[]);

	void changeDirection();
};

struct Settings {
	float ballRadius;
	float ballVelocity;
	float wallPrimaryWidth;
	float wallTertiaryWidth;
	float wallVelocity;
	float ballColor[4];
	int goal;

	Settings(float br, float bv, float wsw, float wtw, float wv, float bc[4], int goal)
		: ballRadius(br), ballVelocity(bv), wallPrimaryWidth(wsw), wallTertiaryWidth(wtw), wallVelocity(wv), goal(goal) {
			for (int i=0; i<4; i++)
				ballColor[i] = bc[i];
	};
};

class Game {

private:
	Settings * settings;
	vec3 dimension;

	int numBalls;
	int numLives;
	int score;
	int startTime;
	int finishTime;
	int area;

	bool gameOver;
	bool win;

	Box * playField;
	Mouse * mouse;
	Wall * tempWall;
	
	vector<Wall *> walls;
	
	void renderWalls();

public:
	Game(Settings * settings, int startingBalls, int startingLives, vec3 dimension, int startingDirection[]);
	~Game();

	int getNumBalls() {return numBalls;}
	int getNumLives();
	int getScore();
	Box * getPlayField() {return playField;}
	Mouse * getMouse() {return mouse;}
	Wall * getTempWall() {return tempWall;}
	vec3 getDimensions() {return dimension;}
	Settings * getSettings() {return settings;}
	int getTime();
	char* getStatus();

	inline vector<Wall *>::iterator getWallsBeginIterator() {return walls.begin();}
    inline vector<Wall *>::iterator getWallsEndIterator() {return walls.end();}
	
	void setNumBalls(int nb) {numBalls = nb;}
	void setNumLives(int nl) {numLives = nl;}
	void setScore(int s) {score = s;}
	void setTempWall(Wall * w);

	void clearTempWall();
	void finalizeTempWall();

	bool isDrawing(int side);
	int getArea();

	void render();
	void animate();
	void createBalls();

	void loseLife();
	void nextLevel();
	void calcArea();
	void unpause();

	bool occupied[40][20][20]; // occupied by wall?
};

#endif
