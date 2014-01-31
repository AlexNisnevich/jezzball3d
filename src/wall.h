#ifndef WALL_H_
#define WALL_H_

#include "main.h"

using namespace std;

#include "game.h"
class Game;

#include "ball.h"
class Ball;

struct Prisms {
	vec3 prism_neg[2][2][2];
	vec3 prism_pos[2][2][2];

	Prisms () {
		vec3 p[2][2][2] = { vec3(0), vec3(0), vec3(0), vec3(0), vec3(0), vec3(0), vec3(0), vec3(0)};
		vec3 n[2][2][2] = { vec3(0), vec3(0), vec3(0), vec3(0), vec3(0), vec3(0), vec3(0), vec3(0)};
		Prisms(p, n);
	}

	Prisms (vec3 n[][2][2], vec3 p[][2][2]) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					prism_neg[i][j][k] = n[i][j][k];
					prism_pos[i][j][k] = p[i][j][k];
				}
			}
		}
	}
};

class Wall {

private:
	vec3 startPosition;
	int primaryDirection;
	int secondaryDirection;
	int positiveSide; // "red"
	int negativeSide; // "blue"
	int state;
	float positiveProgress ,negativeProgress, positiveFill, negativeFill, positiveMaxExtentPrimary, negativeMaxExtentPrimary;
	Prisms * prisms;

	Game * game;

	void collideWithBall( vector<Ball *>::iterator it );

public:
	Wall(vec3 pos, int pd, int sd, int state, Game * game);
	~Wall();

	int getState() {return state;}
	int getNegativeSide() { return negativeSide; }
	int getPositiveSide() { return positiveSide; }

	void setDirection(int pd, int sd);
	void setState(int s) {state = s;}

	void getPrisms(bool expanding = false);
	bool collision();
	void render();
	void animate();
	void completeWall();
	void expand();
};

static bool lineWithinPrism(vec3 L1, vec3 L2, vec3 p1, vec3 p2);

#endif
