#ifndef BOX_H_
#define BOX_H_

#include "main.h"

#include "ball.h"
class Ball; // forward declaration

using namespace std;

class Box {

private:
	vec3 corner1;
	vec3 corner2;
	vector<Ball *> balls;
	int numBalls;

	void renderBox();
	void renderGrids(); //draws the grid lines for the box, this method also work for rectangular boxes
	void renderBalls();

public:

	Box(vec3 corner1, vec3 corner2) 
		: corner1(corner1), corner2(corner2), numBalls(0) {}
	~Box();

	vec3 getCorner1() {return corner1;}
	vec3 getCorner2() {return corner2;}
	vector<Ball *>::iterator getBallsBegin() {return balls.begin();}
	vector<Ball *>::iterator getBallsEnd() {return balls.end();}

	void addBall(float radius, float velocity, float color[4]);

	void animate();

	void render();
};

#endif
