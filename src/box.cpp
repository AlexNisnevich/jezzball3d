#include "box.h"
#include "ball.h"

Box::~Box() {
	for (vector<Ball *>::iterator it = getBallsBegin(); it != getBallsEnd(); it++) {				
		Ball * ball = *it;
		delete ball;
	}
}

void Box::addBall(float radius, float velocity, float color[4]) {
	Ball * ball = new Ball(numBalls, radius, VEC3(RAND), VEC3(RAND_SIGN*velocity), this, color, 0.0);
	balls.push_back(ball);
	numBalls++;
}

void Box::animate() {
	for (vector<Ball *>::iterator it = getBallsBegin(); it != getBallsEnd(); it++) {				
		Ball * ball = *it;
		ball->move();
	}
}

void Box::render() {
	renderBalls();
	renderBox();
	renderGrids();
}

// Private

void Box::renderBox() {
	float colorInvisible[4] = { 0.0, 0.0, 0.0, 0.0 };
	
	glBegin(GL_LINE_LOOP);
		glVertex3f(corner1[0], corner1[1], corner1[2]);
		glVertex3f(corner1[0], corner2[1], corner1[2]);
		glVertex3f(corner2[0], corner2[1], corner1[2]);
		glVertex3f(corner2[0], corner1[1], corner1[2]);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glVertex3f(corner1[0], corner1[1], corner2[2]);
		glVertex3f(corner1[0], corner2[1], corner2[2]);
		glVertex3f(corner2[0], corner2[1], corner2[2]);
		glVertex3f(corner2[0], corner1[1], corner2[2]);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(corner1[0], corner1[1], corner1[2]);
		glVertex3f(corner1[0], corner1[1], corner2[2]);

		glVertex3f(corner1[0], corner2[1], corner1[2]);
		glVertex3f(corner1[0], corner2[1], corner2[2]);

		glVertex3f(corner2[0], corner2[1], corner1[2]);
		glVertex3f(corner2[0], corner2[1], corner2[2]);

		glVertex3f(corner2[0], corner1[1], corner1[2]);
		glVertex3f(corner2[0], corner1[1], corner2[2]);
	glEnd();

	glColor4fv(colorInvisible);
	glBegin(GL_QUADS);
		glVertex3f(0.99 * corner1[0], 0.99 * corner1[1], 0.99 * corner1[2]);
		glVertex3f(0.99 * corner1[0], 0.99 * corner2[1], 0.99 * corner1[2]);
		glVertex3f(0.99 * corner1[0], 0.99 * corner2[1], 0.99 * corner2[2]);
		glVertex3f(0.99 * corner1[0], 0.99 * corner1[1], 0.99 * corner2[2]);

		glVertex3f(0.99 * corner2[0], 0.99 * corner1[1], 0.99 * corner1[2]);
		glVertex3f(0.99 * corner2[0], 0.99 * corner2[1], 0.99 * corner1[2]);
		glVertex3f(0.99 * corner2[0], 0.99 * corner2[1], 0.99 * corner2[2]);
		glVertex3f(0.99 * corner2[0], 0.99 * corner1[1], 0.99 * corner2[2]);

		glVertex3f(0.99 * corner1[0], 0.99 * corner1[1], 0.99 * corner1[2]);
		glVertex3f(0.99 * corner2[0], 0.99 * corner1[1], 0.99 * corner1[2]);
		glVertex3f(0.99 * corner2[0], 0.99 * corner1[1], 0.99 * corner2[2]);
		glVertex3f(0.99 * corner1[0], 0.99 * corner1[1], 0.99 * corner2[2]);

		glVertex3f(0.99 * corner1[0], 0.99 * corner2[1], 0.99 * corner1[2]);
		glVertex3f(0.99 * corner2[0], 0.99 * corner2[1], 0.99 * corner1[2]);
		glVertex3f(0.99 * corner2[0], 0.99 * corner2[1], 0.99 * corner2[2]);
		glVertex3f(0.99 * corner1[0], 0.99 * corner2[1], 0.99 * corner2[2]);

		glVertex3f(0.99 * corner1[0], 0.99 * corner1[1], 0.99 * corner1[2]);
		glVertex3f(0.99 * corner2[0], 0.99 * corner1[1], 0.99 * corner1[2]);
		glVertex3f(0.99 * corner2[0], 0.99 * corner2[1], 0.99 * corner1[2]);
		glVertex3f(0.99 * corner1[0], 0.99 * corner2[1], 0.99 * corner1[2]);

		glVertex3f(0.99 * corner1[0], 0.99 * corner1[1], 0.99 * corner2[2]);
		glVertex3f(0.99 * corner2[0], 0.99 * corner1[1], 0.99 * corner2[2]);
		glVertex3f(0.99 * corner2[0], 0.99 * corner2[1], 0.99 * corner2[2]);
		glVertex3f(0.99 * corner1[0], 0.99 * corner2[1], 0.99 * corner2[2]);
	glEnd();
}

void Box::renderGrids() {
	float colorlightGreen[4] = { 0.0, 0.3, 0.2, 0.75 };
	float colorWhite[4] = { 1.0, 1.0, 1.0, 1.0 };
	float gridSpacing = 0.2;

	glColor4fv(colorlightGreen);
	for (float i = gridSpacing; i < (corner2[2]-corner1[2])/2; i+=gridSpacing) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(corner2[0], corner1[1], corner1[2]+i);
		glVertex3f(corner1[0], corner1[1], corner1[2]+i);
		glVertex3f(corner1[0], corner2[1], corner1[2]+i);
		glVertex3f(corner2[0], corner2[1], corner1[2]+i);
		glEnd();
	}
	for (float i = gridSpacing; i < (corner2[2]-corner1[2])/2+gridSpacing; i+=gridSpacing) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(corner2[0], corner1[1], corner2[2]-i);
		glVertex3f(corner1[0], corner1[1], corner2[2]-i);
		glVertex3f(corner1[0], corner2[1], corner2[2]-i);
		glVertex3f(corner2[0], corner2[1], corner2[2]-i);
		glEnd();
	}
	for (float i = gridSpacing; i < (corner2[1]-corner1[0])/2+gridSpacing; i+=gridSpacing) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(corner2[0], corner1[1]+i, corner1[2]);
		glVertex3f(corner1[0], corner1[1]+i, corner1[2]);
		glVertex3f(corner1[0], corner1[1]+i, corner2[2]);
		glVertex3f(corner2[0], corner1[1]+i, corner2[2]);
		glEnd();
	}
	for (float i = gridSpacing; i < (corner2[1]-corner1[0])/2+gridSpacing; i+=gridSpacing) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(corner2[0], corner2[1]-i, corner1[2]);
		glVertex3f(corner1[0], corner2[1]-i, corner1[2]);
		glVertex3f(corner1[0], corner2[1]-i, corner2[2]);
		glVertex3f(corner2[0], corner2[1]-i, corner2[2]);
		glEnd();
	}
	for (float i = gridSpacing; i < (corner2[0]-corner1[0])/2; i+=gridSpacing) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(corner1[0]+i, corner1[1], corner2[2]);
		glVertex3f(corner1[0]+i, corner1[1], corner1[2]);
		glVertex3f(corner1[0]+i, corner2[1], corner1[2]);
		glVertex3f(corner1[0]+i, corner2[1], corner2[2]);
		glEnd();
	}
	for (float i = gridSpacing; i < (corner2[0]-corner1[0])/2+gridSpacing; i+=gridSpacing) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(corner2[0]-i, corner1[1], corner2[2]);
		glVertex3f(corner2[0]-i, corner1[1], corner1[2]);
		glVertex3f(corner2[0]-i, corner2[1], corner1[2]);
		glVertex3f(corner2[0]-i, corner2[1], corner2[2]);
		glEnd();
	}
	glColor4fv(colorWhite);
}

void Box::renderBalls() {
	for (vector<Ball *>::iterator it = getBallsBegin(); it != getBallsEnd(); it++) {
		Ball * ball = *it;
		ball->render();
	}
}
