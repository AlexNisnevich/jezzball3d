#include "wall.h"

Wall::Wall(vec3 pos, int pd, int sd, int state, Game * game)
	:startPosition(pos), primaryDirection(pd), secondaryDirection(sd), positiveSide(PROGRESS), negativeSide(PROGRESS), state(state), game(game) {
		float primaryWidth = game->getSettings()->wallPrimaryWidth;
		prisms = new Prisms();
		
		if (!game->isDrawing(1)) {
			positiveProgress = primaryWidth;
		} else {
			positiveProgress = 0;
			positiveSide = DEAD;
		}
		
		if (!game->isDrawing(0)) {
			negativeProgress = primaryWidth;
		} else {
			negativeProgress = 0;
			negativeSide = DEAD;
		}

		positiveFill = 0.02;
		negativeFill = 0.02;
};

Wall::~Wall() {
	delete prisms;
}

void Wall::getPrisms(bool expanding) {
	vec3 rect = startPosition;
	vec3 dim = game->getDimensions();
	float tertiaryWidth = game->getSettings()->wallTertiaryWidth;

	float positiveProgressDisplay, negativeProgressDisplay;
	float positiveFillDisplay, negativeFillDisplay;
	if (expanding) {
		tertiaryWidth *= 0.5;
		positiveProgressDisplay =  positiveProgress - tertiaryWidth;
		negativeProgressDisplay =  negativeProgress - tertiaryWidth;
		positiveFillDisplay = positiveFill - 0.001;
		negativeFillDisplay = negativeFill - 0.001;
	} else {
		positiveProgressDisplay =  positiveProgress;
		negativeProgressDisplay =  negativeProgress;
		positiveFillDisplay = positiveFill;
		negativeFillDisplay = negativeFill;
	}

	if (primaryDirection == VX) {
		if (secondaryDirection == VY) {
			prisms->prism_neg[0][0][0] = vec3(rect[VX] - negativeProgressDisplay, rect[VY] - negativeFillDisplay, rect[VZ] - tertiaryWidth);
			prisms->prism_neg[0][0][1] = vec3(rect[VX], rect[VY] - negativeFillDisplay, rect[VZ] - tertiaryWidth);
			prisms->prism_neg[0][1][1] = vec3(rect[VX], rect[VY] + positiveFillDisplay, rect[VZ] - tertiaryWidth);
			prisms->prism_neg[0][1][0] = vec3(rect[VX] - negativeProgressDisplay, rect[VY] + positiveFillDisplay, rect[VZ] - tertiaryWidth);

			prisms->prism_neg[1][0][0] = vec3(rect[VX] - negativeProgressDisplay, rect[VY] - negativeFillDisplay, rect[VZ] + tertiaryWidth);
			prisms->prism_neg[1][0][1] = vec3(rect[VX], rect[VY] - negativeFillDisplay, rect[VZ] + tertiaryWidth);
			prisms->prism_neg[1][1][1] = vec3(rect[VX], rect[VY] + positiveFillDisplay, rect[VZ] + tertiaryWidth);
			prisms->prism_neg[1][1][0] = vec3(rect[VX] - negativeProgressDisplay, rect[VY] + positiveFillDisplay, rect[VZ] + tertiaryWidth);

			prisms->prism_pos[0][0][0] = vec3(rect[VX], rect[VY] - negativeFillDisplay, rect[VZ] - tertiaryWidth);
			prisms->prism_pos[0][0][1] = vec3(rect[VX] + positiveProgressDisplay, rect[VY] - negativeFillDisplay, rect[VZ] - tertiaryWidth);
			prisms->prism_pos[0][1][1] = vec3(rect[VX] + positiveProgressDisplay, rect[VY] + positiveFillDisplay, rect[VZ] - tertiaryWidth);
			prisms->prism_pos[0][1][0] = vec3(rect[VX], rect[VY] + positiveFillDisplay, rect[VZ] - tertiaryWidth);

			prisms->prism_pos[1][0][0] = vec3(rect[VX], rect[VY] - negativeFillDisplay, rect[VZ] + tertiaryWidth);
			prisms->prism_pos[1][0][1] = vec3(rect[VX] + positiveProgressDisplay, rect[VY] - negativeFillDisplay, rect[VZ] + tertiaryWidth);
			prisms->prism_pos[1][1][1] = vec3(rect[VX] + positiveProgressDisplay, rect[VY] + positiveFillDisplay, rect[VZ] + tertiaryWidth);
			prisms->prism_pos[1][1][0] = vec3(rect[VX], rect[VY] + positiveFillDisplay, rect[VZ] + tertiaryWidth);

		} else { // VZ
			prisms->prism_neg[0][0][0] = vec3(rect[VX] - negativeProgressDisplay, rect[VY] - tertiaryWidth, rect[VZ] - negativeFillDisplay);
			prisms->prism_neg[0][0][1] = vec3(rect[VX], rect[VY] - tertiaryWidth, rect[VZ] - negativeFillDisplay);
			prisms->prism_neg[0][1][1] = vec3(rect[VX], rect[VY] - tertiaryWidth, rect[VZ] + positiveFillDisplay);
			prisms->prism_neg[0][1][0] = vec3(rect[VX] - negativeProgressDisplay, rect[VY] - tertiaryWidth, rect[VZ] + positiveFillDisplay);

			prisms->prism_neg[1][0][0] = vec3(rect[VX] - negativeProgressDisplay, rect[VY] + tertiaryWidth, rect[VZ] - negativeFillDisplay);
			prisms->prism_neg[1][0][1] = vec3(rect[VX], rect[VY] + tertiaryWidth, rect[VZ] - negativeFillDisplay);
			prisms->prism_neg[1][1][1] = vec3(rect[VX], rect[VY] + tertiaryWidth, rect[VZ] + positiveFillDisplay);
			prisms->prism_neg[1][1][0] = vec3(rect[VX] - negativeProgressDisplay, rect[VY] + tertiaryWidth, rect[VZ] + positiveFillDisplay);

			prisms->prism_pos[0][0][0] = vec3(rect[VX], rect[VY] - tertiaryWidth, rect[VZ] - negativeFillDisplay);
			prisms->prism_pos[0][0][1] = vec3(rect[VX] + positiveProgressDisplay, rect[VY] - tertiaryWidth, rect[VZ] - negativeFillDisplay);
			prisms->prism_pos[0][1][1] = vec3(rect[VX] + positiveProgressDisplay, rect[VY] - tertiaryWidth, rect[VZ] + positiveFillDisplay);
			prisms->prism_pos[0][1][0] = vec3(rect[VX], rect[VY] - tertiaryWidth, rect[VZ] + positiveFillDisplay);

			prisms->prism_pos[1][0][0] = vec3(rect[VX], rect[VY] + tertiaryWidth, rect[VZ] - negativeFillDisplay);
			prisms->prism_pos[1][0][1] = vec3(rect[VX] + positiveProgressDisplay, rect[VY] + tertiaryWidth, rect[VZ] - negativeFillDisplay);
			prisms->prism_pos[1][1][1] = vec3(rect[VX] + positiveProgressDisplay, rect[VY] + tertiaryWidth, rect[VZ] + positiveFillDisplay);
			prisms->prism_pos[1][1][0] = vec3(rect[VX], rect[VY] + tertiaryWidth, rect[VZ] + positiveFillDisplay);
		}

	} else if (primaryDirection == VY) {
		if (secondaryDirection == VX) {
			prisms->prism_neg[0][0][0] = vec3(rect[VX] - negativeFillDisplay, rect[VY] - negativeProgressDisplay, rect[VZ] - tertiaryWidth);
			prisms->prism_neg[0][0][1] = vec3(rect[VX] - negativeFillDisplay, rect[VY], rect[VZ] - tertiaryWidth);
			prisms->prism_neg[0][1][1] = vec3(rect[VX] + positiveFillDisplay, rect[VY], rect[VZ] - tertiaryWidth);
			prisms->prism_neg[0][1][0] = vec3(rect[VX] + positiveFillDisplay, rect[VY] - negativeProgressDisplay, rect[VZ] - tertiaryWidth);

			prisms->prism_neg[1][0][0] = vec3(rect[VX] - negativeFillDisplay, rect[VY] - negativeProgressDisplay, rect[VZ] + tertiaryWidth);
			prisms->prism_neg[1][0][1] = vec3(rect[VX] - negativeFillDisplay, rect[VY], rect[VZ] + tertiaryWidth);
			prisms->prism_neg[1][1][1] = vec3(rect[VX] + positiveFillDisplay, rect[VY], rect[VZ] + tertiaryWidth);
			prisms->prism_neg[1][1][0] = vec3(rect[VX] + positiveFillDisplay, rect[VY] - negativeProgressDisplay, rect[VZ] + tertiaryWidth);

			prisms->prism_pos[0][0][0] = vec3(rect[VX] - negativeFillDisplay, rect[VY], rect[VZ] - tertiaryWidth);
			prisms->prism_pos[0][0][1] = vec3(rect[VX] - negativeFillDisplay, rect[VY] + positiveProgressDisplay, rect[VZ] - tertiaryWidth);
			prisms->prism_pos[0][1][1] = vec3(rect[VX] + positiveFillDisplay, rect[VY] + positiveProgressDisplay, rect[VZ] - tertiaryWidth);
			prisms->prism_pos[0][1][0] = vec3(rect[VX] + positiveFillDisplay, rect[VY], rect[VZ] - tertiaryWidth);

			prisms->prism_pos[1][0][0] = vec3(rect[VX] - negativeFillDisplay, rect[VY], rect[VZ] + tertiaryWidth);
			prisms->prism_pos[1][0][1] = vec3(rect[VX] - negativeFillDisplay, rect[VY] + positiveProgressDisplay, rect[VZ] + tertiaryWidth);
			prisms->prism_pos[1][1][1] = vec3(rect[VX] + positiveFillDisplay, rect[VY] + positiveProgressDisplay, rect[VZ] + tertiaryWidth);
			prisms->prism_pos[1][1][0] = vec3(rect[VX] + positiveFillDisplay, rect[VY], rect[VZ] + tertiaryWidth);

		} else { // VY
			prisms->prism_neg[0][0][0] = vec3(rect[VX] - tertiaryWidth, rect[VY] - negativeProgressDisplay, rect[VZ] - negativeFillDisplay);
			prisms->prism_neg[0][0][1] = vec3(rect[VX] - tertiaryWidth, rect[VY], rect[VZ] - negativeFillDisplay);
			prisms->prism_neg[0][1][1] = vec3(rect[VX] - tertiaryWidth, rect[VY], rect[VZ] + positiveFillDisplay);
			prisms->prism_neg[0][1][0] = vec3(rect[VX] - tertiaryWidth, rect[VY] - negativeProgressDisplay, rect[VZ] + positiveFillDisplay);

			prisms->prism_neg[1][0][0] = vec3(rect[VX] + tertiaryWidth, rect[VY] - negativeProgressDisplay, rect[VZ] - negativeFillDisplay);
			prisms->prism_neg[1][0][1] = vec3(rect[VX] + tertiaryWidth, rect[VY], rect[VZ] - negativeFillDisplay);
			prisms->prism_neg[1][1][1] = vec3(rect[VX] + tertiaryWidth, rect[VY], rect[VZ] + positiveFillDisplay);
			prisms->prism_neg[1][1][0] = vec3(rect[VX] + tertiaryWidth, rect[VY] - negativeProgressDisplay, rect[VZ] + positiveFillDisplay);

			prisms->prism_pos[0][0][0] = vec3(rect[VX] - tertiaryWidth, rect[VY], rect[VZ] - negativeFillDisplay);
			prisms->prism_pos[0][0][1] = vec3(rect[VX] - tertiaryWidth, rect[VY] + positiveProgressDisplay, rect[VZ] - negativeFillDisplay);
			prisms->prism_pos[0][1][1] = vec3(rect[VX] - tertiaryWidth, rect[VY] + positiveProgressDisplay, rect[VZ] + positiveFillDisplay);
			prisms->prism_pos[0][1][0] = vec3(rect[VX] - tertiaryWidth, rect[VY], rect[VZ] + positiveFillDisplay);

			prisms->prism_pos[1][0][0] = vec3(rect[VX] + tertiaryWidth, rect[VY], rect[VZ] - negativeFillDisplay);
			prisms->prism_pos[1][0][1] = vec3(rect[VX] + tertiaryWidth, rect[VY] + positiveProgressDisplay, rect[VZ] - negativeFillDisplay);
			prisms->prism_pos[1][1][1] = vec3(rect[VX] + tertiaryWidth, rect[VY] + positiveProgressDisplay, rect[VZ] + positiveFillDisplay);
			prisms->prism_pos[1][1][0] = vec3(rect[VX] + tertiaryWidth, rect[VY], rect[VZ] + positiveFillDisplay);
		}

	} else { // VZ
		if (secondaryDirection == VY) {
			prisms->prism_neg[0][0][0] = vec3(rect[VX] - tertiaryWidth, rect[VY] - negativeFillDisplay, rect[VZ] - negativeProgressDisplay);
			prisms->prism_neg[0][0][1] = vec3(rect[VX] - tertiaryWidth, rect[VY] - negativeFillDisplay, rect[VZ]);
			prisms->prism_neg[0][1][1] = vec3(rect[VX] - tertiaryWidth, rect[VY] + positiveFillDisplay, rect[VZ]);
			prisms->prism_neg[0][1][0] = vec3(rect[VX] - tertiaryWidth, rect[VY] + positiveFillDisplay, rect[VZ] - negativeProgressDisplay);

			prisms->prism_neg[1][0][0] = vec3(rect[VX] + tertiaryWidth, rect[VY] - negativeFillDisplay, rect[VZ] - negativeProgressDisplay);
			prisms->prism_neg[1][0][1] = vec3(rect[VX] + tertiaryWidth, rect[VY] - negativeFillDisplay, rect[VZ]);
			prisms->prism_neg[1][1][1] = vec3(rect[VX] + tertiaryWidth, rect[VY] + positiveFillDisplay, rect[VZ]);
			prisms->prism_neg[1][1][0] = vec3(rect[VX] + tertiaryWidth, rect[VY] + positiveFillDisplay, rect[VZ] - negativeProgressDisplay);

			prisms->prism_pos[0][0][0] = vec3(rect[VX] - tertiaryWidth, rect[VY] - negativeFillDisplay, rect[VZ]);
			prisms->prism_pos[0][0][1] = vec3(rect[VX] - tertiaryWidth, rect[VY] - negativeFillDisplay, rect[VZ] + positiveProgressDisplay);
			prisms->prism_pos[0][1][1] = vec3(rect[VX] - tertiaryWidth, rect[VY] + positiveFillDisplay, rect[VZ] + positiveProgressDisplay);
			prisms->prism_pos[0][1][0] = vec3(rect[VX] - tertiaryWidth, rect[VY] + positiveFillDisplay, rect[VZ]);

			prisms->prism_pos[1][0][0] = vec3(rect[VX] + tertiaryWidth, rect[VY] - negativeFillDisplay, rect[VZ]);
			prisms->prism_pos[1][0][1] = vec3(rect[VX] + tertiaryWidth, rect[VY] - negativeFillDisplay, rect[VZ] + positiveProgressDisplay);
			prisms->prism_pos[1][1][1] = vec3(rect[VX] + tertiaryWidth, rect[VY] + positiveFillDisplay, rect[VZ] + positiveProgressDisplay);
			prisms->prism_pos[1][1][0] = vec3(rect[VX] + tertiaryWidth, rect[VY] + positiveFillDisplay, rect[VZ]);
		} else { // VZ
			prisms->prism_neg[0][0][0] = vec3(rect[VX] - negativeFillDisplay, rect[VY] - tertiaryWidth, rect[VZ] - negativeProgressDisplay);
			prisms->prism_neg[0][0][1] = vec3(rect[VX] - negativeFillDisplay, rect[VY] - tertiaryWidth, rect[VZ]);
			prisms->prism_neg[0][1][1] = vec3(rect[VX] + positiveFillDisplay, rect[VY] - tertiaryWidth, rect[VZ]);
			prisms->prism_neg[0][1][0] = vec3(rect[VX] + positiveFillDisplay, rect[VY] - tertiaryWidth, rect[VZ] - negativeProgressDisplay);

			prisms->prism_neg[1][0][0] = vec3(rect[VX] - negativeFillDisplay, rect[VY] + tertiaryWidth, rect[VZ] - negativeProgressDisplay);
			prisms->prism_neg[1][0][1] = vec3(rect[VX] - negativeFillDisplay, rect[VY] + tertiaryWidth, rect[VZ]);
			prisms->prism_neg[1][1][1] = vec3(rect[VX] + positiveFillDisplay, rect[VY] + tertiaryWidth, rect[VZ]);
			prisms->prism_neg[1][1][0] = vec3(rect[VX] + positiveFillDisplay, rect[VY] + tertiaryWidth, rect[VZ] - negativeProgressDisplay);

			prisms->prism_pos[0][0][0] = vec3(rect[VX] - negativeFillDisplay, rect[VY] - tertiaryWidth, rect[VZ]);
			prisms->prism_pos[0][0][1] = vec3(rect[VX] - negativeFillDisplay, rect[VY] - tertiaryWidth, rect[VZ] + positiveProgressDisplay);
			prisms->prism_pos[0][1][1] = vec3(rect[VX] + positiveFillDisplay, rect[VY] - tertiaryWidth, rect[VZ] + positiveProgressDisplay);
			prisms->prism_pos[0][1][0] = vec3(rect[VX] + positiveFillDisplay, rect[VY] - tertiaryWidth, rect[VZ]);

			prisms->prism_pos[1][0][0] = vec3(rect[VX] - negativeFillDisplay, rect[VY] + tertiaryWidth, rect[VZ]);
			prisms->prism_pos[1][0][1] = vec3(rect[VX] - negativeFillDisplay, rect[VY] + tertiaryWidth, rect[VZ] + positiveProgressDisplay);
			prisms->prism_pos[1][1][1] = vec3(rect[VX] + positiveFillDisplay, rect[VY] + tertiaryWidth, rect[VZ] + positiveProgressDisplay);
			prisms->prism_pos[1][1][0] = vec3(rect[VX] + positiveFillDisplay, rect[VY] + tertiaryWidth, rect[VZ]);
		}
	}
}

void Wall::render() {
	if (state == NONEXISTENT) {
		return;
	}

	getPrisms();

	float colorLightRed[4] = { 1.0, 0.3, 0.3, 0.5 };
	float colorLightGreen[4] = { 0.3, 1.0, 0.3, 0.5 };
	float colorLightBlue[4] = { 0.3, 0.3, 1.0, 0.5 };
	float colorWhite[4] = { 1.0, 1.0, 1.0, 1.0 };
	float colorGrey[4] = { 1.0, 1.0, 1.0, 0.3 };
	glColor4fv(colorWhite);

	if (positiveSide == COMPLETED && negativeSide == COMPLETED) {
		glBegin(GL_LINE_LOOP);
			glVertex3f((prisms->prism_neg[0][0][0])[VX], (prisms->prism_neg[0][0][0])[VY], (prisms->prism_neg[0][0][0])[VZ]);
			glVertex3f((prisms->prism_pos[0][0][1])[VX], (prisms->prism_pos[0][0][1])[VY], (prisms->prism_pos[0][0][1])[VZ]);
			glVertex3f((prisms->prism_pos[0][1][1])[VX], (prisms->prism_pos[0][1][1])[VY], (prisms->prism_pos[0][1][1])[VZ]);
			glVertex3f((prisms->prism_neg[0][1][0])[VX], (prisms->prism_neg[0][1][0])[VY], (prisms->prism_neg[0][1][0])[VZ]);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f((prisms->prism_neg[1][0][0])[VX], (prisms->prism_neg[1][0][0])[VY], (prisms->prism_neg[1][0][0])[VZ]);
			glVertex3f((prisms->prism_pos[1][0][1])[VX], (prisms->prism_pos[1][0][1])[VY], (prisms->prism_pos[1][0][1])[VZ]);
			glVertex3f((prisms->prism_pos[1][1][1])[VX], (prisms->prism_pos[1][1][1])[VY], (prisms->prism_pos[1][1][1])[VZ]);
			glVertex3f((prisms->prism_neg[1][1][0])[VX], (prisms->prism_neg[1][1][0])[VY], (prisms->prism_neg[1][1][0])[VZ]);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f((prisms->prism_neg[0][0][0])[VX], (prisms->prism_neg[0][0][0])[VY], (prisms->prism_neg[0][0][0])[VZ]);
			glVertex3f((prisms->prism_pos[0][0][1])[VX], (prisms->prism_pos[0][0][1])[VY], (prisms->prism_pos[0][0][1])[VZ]);
			glVertex3f((prisms->prism_pos[1][0][1])[VX], (prisms->prism_pos[1][0][1])[VY], (prisms->prism_pos[1][0][1])[VZ]);
			glVertex3f((prisms->prism_neg[1][0][0])[VX], (prisms->prism_neg[1][0][0])[VY], (prisms->prism_neg[1][0][0])[VZ]);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f((prisms->prism_neg[0][1][0])[VX], (prisms->prism_neg[0][1][0])[VY], (prisms->prism_neg[0][1][0])[VZ]);
			glVertex3f((prisms->prism_pos[0][1][1])[VX], (prisms->prism_pos[0][1][1])[VY], (prisms->prism_pos[0][1][1])[VZ]);
			glVertex3f((prisms->prism_pos[1][1][1])[VX], (prisms->prism_pos[1][1][1])[VY], (prisms->prism_pos[1][1][1])[VZ]);
			glVertex3f((prisms->prism_neg[1][1][0])[VX], (prisms->prism_neg[1][1][0])[VY], (prisms->prism_neg[1][1][0])[VZ]);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f((prisms->prism_neg[0][0][0])[VX], (prisms->prism_neg[0][0][0])[VY], (prisms->prism_neg[0][0][0])[VZ]);
			glVertex3f((prisms->prism_neg[1][0][0])[VX], (prisms->prism_neg[1][0][0])[VY], (prisms->prism_neg[1][0][0])[VZ]);
			glVertex3f((prisms->prism_neg[1][1][0])[VX], (prisms->prism_neg[1][1][0])[VY], (prisms->prism_neg[1][1][0])[VZ]);
			glVertex3f((prisms->prism_neg[0][1][0])[VX], (prisms->prism_neg[0][1][0])[VY], (prisms->prism_neg[0][1][0])[VZ]);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f((prisms->prism_pos[0][0][1])[VX], (prisms->prism_pos[0][0][1])[VY], (prisms->prism_pos[0][0][1])[VZ]);
			glVertex3f((prisms->prism_pos[1][0][1])[VX], (prisms->prism_pos[1][0][1])[VY], (prisms->prism_pos[1][0][1])[VZ]);
			glVertex3f((prisms->prism_pos[1][1][1])[VX], (prisms->prism_pos[1][1][1])[VY], (prisms->prism_pos[1][1][1])[VZ]);
			glVertex3f((prisms->prism_pos[0][1][1])[VX], (prisms->prism_pos[0][1][1])[VY], (prisms->prism_pos[0][1][1])[VZ]);
		glEnd();
	} else {
		if (negativeSide != DEAD) {
			glBegin(GL_LINE_LOOP);
				glVertex3f((prisms->prism_neg[0][0][0])[VX], (prisms->prism_neg[0][0][0])[VY], (prisms->prism_neg[0][0][0])[VZ]);
				glVertex3f((prisms->prism_neg[0][0][1])[VX], (prisms->prism_neg[0][0][1])[VY], (prisms->prism_neg[0][0][1])[VZ]);
				glVertex3f((prisms->prism_neg[0][1][1])[VX], (prisms->prism_neg[0][1][1])[VY], (prisms->prism_neg[0][1][1])[VZ]);
				glVertex3f((prisms->prism_neg[0][1][0])[VX], (prisms->prism_neg[0][1][0])[VY], (prisms->prism_neg[0][1][0])[VZ]);
			glEnd();
			glBegin(GL_LINE_LOOP);
				glVertex3f((prisms->prism_neg[1][0][0])[VX], (prisms->prism_neg[1][0][0])[VY], (prisms->prism_neg[1][0][0])[VZ]);
				glVertex3f((prisms->prism_neg[1][0][1])[VX], (prisms->prism_neg[1][0][1])[VY], (prisms->prism_neg[1][0][1])[VZ]);
				glVertex3f((prisms->prism_neg[1][1][1])[VX], (prisms->prism_neg[1][1][1])[VY], (prisms->prism_neg[1][1][1])[VZ]);
				glVertex3f((prisms->prism_neg[1][1][0])[VX], (prisms->prism_neg[1][1][0])[VY], (prisms->prism_neg[1][1][0])[VZ]);
			glEnd();
			glBegin(GL_LINE_LOOP);
				glVertex3f((prisms->prism_neg[0][0][0])[VX], (prisms->prism_neg[0][0][0])[VY], (prisms->prism_neg[0][0][0])[VZ]);
				glVertex3f((prisms->prism_neg[0][0][1])[VX], (prisms->prism_neg[0][0][1])[VY], (prisms->prism_neg[0][0][1])[VZ]);
				glVertex3f((prisms->prism_neg[1][0][1])[VX], (prisms->prism_neg[1][0][1])[VY], (prisms->prism_neg[1][0][1])[VZ]);
				glVertex3f((prisms->prism_neg[1][0][0])[VX], (prisms->prism_neg[1][0][0])[VY], (prisms->prism_neg[1][0][0])[VZ]);
			glEnd();
			glBegin(GL_LINE_LOOP);
				glVertex3f((prisms->prism_neg[0][1][0])[VX], (prisms->prism_neg[0][1][0])[VY], (prisms->prism_neg[0][1][0])[VZ]);
				glVertex3f((prisms->prism_neg[0][1][1])[VX], (prisms->prism_neg[0][1][1])[VY], (prisms->prism_neg[0][1][1])[VZ]);
				glVertex3f((prisms->prism_neg[1][1][1])[VX], (prisms->prism_neg[1][1][1])[VY], (prisms->prism_neg[1][1][1])[VZ]);
				glVertex3f((prisms->prism_neg[1][1][0])[VX], (prisms->prism_neg[1][1][0])[VY], (prisms->prism_neg[1][1][0])[VZ]);
			glEnd();
			glBegin(GL_LINE_LOOP);
				glVertex3f((prisms->prism_neg[0][0][0])[VX], (prisms->prism_neg[0][0][0])[VY], (prisms->prism_neg[0][0][0])[VZ]);
				glVertex3f((prisms->prism_neg[1][0][0])[VX], (prisms->prism_neg[1][0][0])[VY], (prisms->prism_neg[1][0][0])[VZ]);
				glVertex3f((prisms->prism_neg[1][1][0])[VX], (prisms->prism_neg[1][1][0])[VY], (prisms->prism_neg[1][1][0])[VZ]);
				glVertex3f((prisms->prism_neg[0][1][0])[VX], (prisms->prism_neg[0][1][0])[VY], (prisms->prism_neg[0][1][0])[VZ]);
			glEnd();
			glBegin(GL_LINE_LOOP);
				glVertex3f((prisms->prism_neg[0][0][1])[VX], (prisms->prism_neg[0][0][1])[VY], (prisms->prism_neg[0][0][1])[VZ]);
				glVertex3f((prisms->prism_neg[1][0][1])[VX], (prisms->prism_neg[1][0][1])[VY], (prisms->prism_neg[1][0][1])[VZ]);
				glVertex3f((prisms->prism_neg[1][1][1])[VX], (prisms->prism_neg[1][1][1])[VY], (prisms->prism_neg[1][1][1])[VZ]);
				glVertex3f((prisms->prism_neg[0][1][1])[VX], (prisms->prism_neg[0][1][1])[VY], (prisms->prism_neg[0][1][1])[VZ]);
			glEnd();
		}

		glColor4fv(colorWhite);
		if (positiveSide != DEAD) {
			glBegin(GL_LINE_LOOP);
				glVertex3f((prisms->prism_pos[0][0][0])[VX], (prisms->prism_pos[0][0][0])[VY], (prisms->prism_pos[0][0][0])[VZ]);
				glVertex3f((prisms->prism_pos[0][0][1])[VX], (prisms->prism_pos[0][0][1])[VY], (prisms->prism_pos[0][0][1])[VZ]);
				glVertex3f((prisms->prism_pos[0][1][1])[VX], (prisms->prism_pos[0][1][1])[VY], (prisms->prism_pos[0][1][1])[VZ]);
				glVertex3f((prisms->prism_pos[0][1][0])[VX], (prisms->prism_pos[0][1][0])[VY], (prisms->prism_pos[0][1][0])[VZ]);
			glEnd();
			glBegin(GL_LINE_LOOP);
				glVertex3f((prisms->prism_pos[1][0][0])[VX], (prisms->prism_pos[1][0][0])[VY], (prisms->prism_pos[1][0][0])[VZ]);
				glVertex3f((prisms->prism_pos[1][0][1])[VX], (prisms->prism_pos[1][0][1])[VY], (prisms->prism_pos[1][0][1])[VZ]);
				glVertex3f((prisms->prism_pos[1][1][1])[VX], (prisms->prism_pos[1][1][1])[VY], (prisms->prism_pos[1][1][1])[VZ]);
				glVertex3f((prisms->prism_pos[1][1][0])[VX], (prisms->prism_pos[1][1][0])[VY], (prisms->prism_pos[1][1][0])[VZ]);
			glEnd();
			glBegin(GL_LINE_LOOP);
				glVertex3f((prisms->prism_pos[0][0][0])[VX], (prisms->prism_pos[0][0][0])[VY], (prisms->prism_pos[0][0][0])[VZ]);
				glVertex3f((prisms->prism_pos[0][0][1])[VX], (prisms->prism_pos[0][0][1])[VY], (prisms->prism_pos[0][0][1])[VZ]);
				glVertex3f((prisms->prism_pos[1][0][1])[VX], (prisms->prism_pos[1][0][1])[VY], (prisms->prism_pos[1][0][1])[VZ]);
				glVertex3f((prisms->prism_pos[1][0][0])[VX], (prisms->prism_pos[1][0][0])[VY], (prisms->prism_pos[1][0][0])[VZ]);
			glEnd();
			glBegin(GL_LINE_LOOP);
				glVertex3f((prisms->prism_pos[0][1][0])[VX], (prisms->prism_pos[0][1][0])[VY], (prisms->prism_pos[0][1][0])[VZ]);
				glVertex3f((prisms->prism_pos[0][1][1])[VX], (prisms->prism_pos[0][1][1])[VY], (prisms->prism_pos[0][1][1])[VZ]);
				glVertex3f((prisms->prism_pos[1][1][1])[VX], (prisms->prism_pos[1][1][1])[VY], (prisms->prism_pos[1][1][1])[VZ]);
				glVertex3f((prisms->prism_pos[1][1][0])[VX], (prisms->prism_pos[1][1][0])[VY], (prisms->prism_pos[1][1][0])[VZ]);
			glEnd();
			glBegin(GL_LINE_LOOP);
				glVertex3f((prisms->prism_pos[0][0][0])[VX], (prisms->prism_pos[0][0][0])[VY], (prisms->prism_pos[0][0][0])[VZ]);
				glVertex3f((prisms->prism_pos[1][0][0])[VX], (prisms->prism_pos[1][0][0])[VY], (prisms->prism_pos[1][0][0])[VZ]);
				glVertex3f((prisms->prism_pos[1][1][0])[VX], (prisms->prism_pos[1][1][0])[VY], (prisms->prism_pos[1][1][0])[VZ]);
				glVertex3f((prisms->prism_pos[0][1][0])[VX], (prisms->prism_pos[0][1][0])[VY], (prisms->prism_pos[0][1][0])[VZ]);
			glEnd();
			glBegin(GL_LINE_LOOP);
				glVertex3f((prisms->prism_pos[0][0][1])[VX], (prisms->prism_pos[0][0][1])[VY], (prisms->prism_pos[0][0][1])[VZ]);
				glVertex3f((prisms->prism_pos[1][0][1])[VX], (prisms->prism_pos[1][0][1])[VY], (prisms->prism_pos[1][0][1])[VZ]);
				glVertex3f((prisms->prism_pos[1][1][1])[VX], (prisms->prism_pos[1][1][1])[VY], (prisms->prism_pos[1][1][1])[VZ]);
				glVertex3f((prisms->prism_pos[0][1][1])[VX], (prisms->prism_pos[0][1][1])[VY], (prisms->prism_pos[0][1][1])[VZ]);
			glEnd();
		}
	}


	if (positiveSide == COMPLETED && negativeSide == COMPLETED) {
		glColor4fv(colorGrey);
		glBegin(GL_QUADS);
			glVertex3f((prisms->prism_neg[0][0][0])[VX], (prisms->prism_neg[0][0][0])[VY], (prisms->prism_neg[0][0][0])[VZ]);
			glVertex3f((prisms->prism_pos[0][0][1])[VX], (prisms->prism_pos[0][0][1])[VY], (prisms->prism_pos[0][0][1])[VZ]);
			glVertex3f((prisms->prism_pos[0][1][1])[VX], (prisms->prism_pos[0][1][1])[VY], (prisms->prism_pos[0][1][1])[VZ]);
			glVertex3f((prisms->prism_neg[0][1][0])[VX], (prisms->prism_neg[0][1][0])[VY], (prisms->prism_neg[0][1][0])[VZ]);

			glVertex3f((prisms->prism_neg[1][0][0])[VX], (prisms->prism_neg[1][0][0])[VY], (prisms->prism_neg[1][0][0])[VZ]);
			glVertex3f((prisms->prism_pos[1][0][1])[VX], (prisms->prism_pos[1][0][1])[VY], (prisms->prism_pos[1][0][1])[VZ]);
			glVertex3f((prisms->prism_pos[1][1][1])[VX], (prisms->prism_pos[1][1][1])[VY], (prisms->prism_pos[1][1][1])[VZ]);
			glVertex3f((prisms->prism_neg[1][1][0])[VX], (prisms->prism_neg[1][1][0])[VY], (prisms->prism_neg[1][1][0])[VZ]);

			glVertex3f((prisms->prism_neg[0][0][0])[VX], (prisms->prism_neg[0][0][0])[VY], (prisms->prism_neg[0][0][0])[VZ]);
			glVertex3f((prisms->prism_pos[0][0][1])[VX], (prisms->prism_pos[0][0][1])[VY], (prisms->prism_pos[0][0][1])[VZ]);
			glVertex3f((prisms->prism_pos[1][0][1])[VX], (prisms->prism_pos[1][0][1])[VY], (prisms->prism_pos[1][0][1])[VZ]);
			glVertex3f((prisms->prism_neg[1][0][0])[VX], (prisms->prism_neg[1][0][0])[VY], (prisms->prism_neg[1][0][0])[VZ]);

			glVertex3f((prisms->prism_neg[0][1][0])[VX], (prisms->prism_neg[0][1][0])[VY], (prisms->prism_neg[0][1][0])[VZ]);
			glVertex3f((prisms->prism_pos[0][1][1])[VX], (prisms->prism_pos[0][1][1])[VY], (prisms->prism_pos[0][1][1])[VZ]);
			glVertex3f((prisms->prism_pos[1][1][1])[VX], (prisms->prism_pos[1][1][1])[VY], (prisms->prism_pos[1][1][1])[VZ]);
			glVertex3f((prisms->prism_neg[1][1][0])[VX], (prisms->prism_neg[1][1][0])[VY], (prisms->prism_neg[1][1][0])[VZ]);

			glVertex3f((prisms->prism_neg[0][0][0])[VX], (prisms->prism_neg[0][0][0])[VY], (prisms->prism_neg[0][0][0])[VZ]);
			glVertex3f((prisms->prism_neg[1][0][0])[VX], (prisms->prism_neg[1][0][0])[VY], (prisms->prism_neg[1][0][0])[VZ]);
			glVertex3f((prisms->prism_neg[1][1][0])[VX], (prisms->prism_neg[1][1][0])[VY], (prisms->prism_neg[1][1][0])[VZ]);
			glVertex3f((prisms->prism_neg[0][1][0])[VX], (prisms->prism_neg[0][1][0])[VY], (prisms->prism_neg[0][1][0])[VZ]);

			glVertex3f((prisms->prism_pos[0][0][1])[VX], (prisms->prism_pos[0][0][1])[VY], (prisms->prism_pos[0][0][1])[VZ]);
			glVertex3f((prisms->prism_pos[1][0][1])[VX], (prisms->prism_pos[1][0][1])[VY], (prisms->prism_pos[1][0][1])[VZ]);
			glVertex3f((prisms->prism_pos[1][1][1])[VX], (prisms->prism_pos[1][1][1])[VY], (prisms->prism_pos[1][1][1])[VZ]);
			glVertex3f((prisms->prism_pos[0][1][1])[VX], (prisms->prism_pos[0][1][1])[VY], (prisms->prism_pos[0][1][1])[VZ]);
		glEnd();

	} else {
		glBegin(GL_QUADS);
		if (state == TEMP) {
			glColor4fv(colorLightGreen);
		} else {
			glColor4fv(colorLightBlue);
		}
		if (negativeSide == COMPLETED) {
			glColor4fv(colorGrey);
		}
		if (negativeSide != DEAD) {
			glVertex3f((prisms->prism_neg[0][0][0])[VX], (prisms->prism_neg[0][0][0])[VY], (prisms->prism_neg[0][0][0])[VZ]);
			glVertex3f((prisms->prism_neg[0][0][1])[VX], (prisms->prism_neg[0][0][1])[VY], (prisms->prism_neg[0][0][1])[VZ]);
			glVertex3f((prisms->prism_neg[0][1][1])[VX], (prisms->prism_neg[0][1][1])[VY], (prisms->prism_neg[0][1][1])[VZ]);
			glVertex3f((prisms->prism_neg[0][1][0])[VX], (prisms->prism_neg[0][1][0])[VY], (prisms->prism_neg[0][1][0])[VZ]);

			glVertex3f((prisms->prism_neg[1][0][0])[VX], (prisms->prism_neg[1][0][0])[VY], (prisms->prism_neg[1][0][0])[VZ]);
			glVertex3f((prisms->prism_neg[1][0][1])[VX], (prisms->prism_neg[1][0][1])[VY], (prisms->prism_neg[1][0][1])[VZ]);
			glVertex3f((prisms->prism_neg[1][1][1])[VX], (prisms->prism_neg[1][1][1])[VY], (prisms->prism_neg[1][1][1])[VZ]);
			glVertex3f((prisms->prism_neg[1][1][0])[VX], (prisms->prism_neg[1][1][0])[VY], (prisms->prism_neg[1][1][0])[VZ]);

			glVertex3f((prisms->prism_neg[0][0][0])[VX], (prisms->prism_neg[0][0][0])[VY], (prisms->prism_neg[0][0][0])[VZ]);
			glVertex3f((prisms->prism_neg[0][0][1])[VX], (prisms->prism_neg[0][0][1])[VY], (prisms->prism_neg[0][0][1])[VZ]);
			glVertex3f((prisms->prism_neg[1][0][1])[VX], (prisms->prism_neg[1][0][1])[VY], (prisms->prism_neg[1][0][1])[VZ]);
			glVertex3f((prisms->prism_neg[1][0][0])[VX], (prisms->prism_neg[1][0][0])[VY], (prisms->prism_neg[1][0][0])[VZ]);

			glVertex3f((prisms->prism_neg[0][1][0])[VX], (prisms->prism_neg[0][1][0])[VY], (prisms->prism_neg[0][1][0])[VZ]);
			glVertex3f((prisms->prism_neg[0][1][1])[VX], (prisms->prism_neg[0][1][1])[VY], (prisms->prism_neg[0][1][1])[VZ]);
			glVertex3f((prisms->prism_neg[1][1][1])[VX], (prisms->prism_neg[1][1][1])[VY], (prisms->prism_neg[1][1][1])[VZ]);
			glVertex3f((prisms->prism_neg[1][1][0])[VX], (prisms->prism_neg[1][1][0])[VY], (prisms->prism_neg[1][1][0])[VZ]);

			glVertex3f((prisms->prism_neg[0][0][0])[VX], (prisms->prism_neg[0][0][0])[VY], (prisms->prism_neg[0][0][0])[VZ]);
			glVertex3f((prisms->prism_neg[1][0][0])[VX], (prisms->prism_neg[1][0][0])[VY], (prisms->prism_neg[1][0][0])[VZ]);
			glVertex3f((prisms->prism_neg[1][1][0])[VX], (prisms->prism_neg[1][1][0])[VY], (prisms->prism_neg[1][1][0])[VZ]);
			glVertex3f((prisms->prism_neg[0][1][0])[VX], (prisms->prism_neg[0][1][0])[VY], (prisms->prism_neg[0][1][0])[VZ]);

			glVertex3f((prisms->prism_neg[0][0][1])[VX], (prisms->prism_neg[0][0][1])[VY], (prisms->prism_neg[0][0][1])[VZ]);
			glVertex3f((prisms->prism_neg[1][0][1])[VX], (prisms->prism_neg[1][0][1])[VY], (prisms->prism_neg[1][0][1])[VZ]);
			glVertex3f((prisms->prism_neg[1][1][1])[VX], (prisms->prism_neg[1][1][1])[VY], (prisms->prism_neg[1][1][1])[VZ]);
			glVertex3f((prisms->prism_neg[0][1][1])[VX], (prisms->prism_neg[0][1][1])[VY], (prisms->prism_neg[0][1][1])[VZ]);
		}
		glEnd();

		glBegin(GL_QUADS);
		if (state == TEMP) {
			glColor4fv(colorLightGreen);
		} else {
			glColor4fv(colorLightRed);
		}
		if (positiveSide == COMPLETED) {
			glColor4fv(colorGrey);
		}
		if (positiveSide != DEAD) {
			glVertex3f((prisms->prism_pos[0][0][0])[VX], (prisms->prism_pos[0][0][0])[VY], (prisms->prism_pos[0][0][0])[VZ]);
			glVertex3f((prisms->prism_pos[0][0][1])[VX], (prisms->prism_pos[0][0][1])[VY], (prisms->prism_pos[0][0][1])[VZ]);
			glVertex3f((prisms->prism_pos[0][1][1])[VX], (prisms->prism_pos[0][1][1])[VY], (prisms->prism_pos[0][1][1])[VZ]);
			glVertex3f((prisms->prism_pos[0][1][0])[VX], (prisms->prism_pos[0][1][0])[VY], (prisms->prism_pos[0][1][0])[VZ]);

			glVertex3f((prisms->prism_pos[1][0][0])[VX], (prisms->prism_pos[1][0][0])[VY], (prisms->prism_pos[1][0][0])[VZ]);
			glVertex3f((prisms->prism_pos[1][0][1])[VX], (prisms->prism_pos[1][0][1])[VY], (prisms->prism_pos[1][0][1])[VZ]);
			glVertex3f((prisms->prism_pos[1][1][1])[VX], (prisms->prism_pos[1][1][1])[VY], (prisms->prism_pos[1][1][1])[VZ]);
			glVertex3f((prisms->prism_pos[1][1][0])[VX], (prisms->prism_pos[1][1][0])[VY], (prisms->prism_pos[1][1][0])[VZ]);

			glVertex3f((prisms->prism_pos[0][0][0])[VX], (prisms->prism_pos[0][0][0])[VY], (prisms->prism_pos[0][0][0])[VZ]);
			glVertex3f((prisms->prism_pos[0][0][1])[VX], (prisms->prism_pos[0][0][1])[VY], (prisms->prism_pos[0][0][1])[VZ]);
			glVertex3f((prisms->prism_pos[1][0][1])[VX], (prisms->prism_pos[1][0][1])[VY], (prisms->prism_pos[1][0][1])[VZ]);
			glVertex3f((prisms->prism_pos[1][0][0])[VX], (prisms->prism_pos[1][0][0])[VY], (prisms->prism_pos[1][0][0])[VZ]);

			glVertex3f((prisms->prism_pos[0][1][0])[VX], (prisms->prism_pos[0][1][0])[VY], (prisms->prism_pos[0][1][0])[VZ]);
			glVertex3f((prisms->prism_pos[0][1][1])[VX], (prisms->prism_pos[0][1][1])[VY], (prisms->prism_pos[0][1][1])[VZ]);
			glVertex3f((prisms->prism_pos[1][1][1])[VX], (prisms->prism_pos[1][1][1])[VY], (prisms->prism_pos[1][1][1])[VZ]);
			glVertex3f((prisms->prism_pos[1][1][0])[VX], (prisms->prism_pos[1][1][0])[VY], (prisms->prism_pos[1][1][0])[VZ]);

			glVertex3f((prisms->prism_pos[0][0][0])[VX], (prisms->prism_pos[0][0][0])[VY], (prisms->prism_pos[0][0][0])[VZ]);
			glVertex3f((prisms->prism_pos[1][0][0])[VX], (prisms->prism_pos[1][0][0])[VY], (prisms->prism_pos[1][0][0])[VZ]);
			glVertex3f((prisms->prism_pos[1][1][0])[VX], (prisms->prism_pos[1][1][0])[VY], (prisms->prism_pos[1][1][0])[VZ]);
			glVertex3f((prisms->prism_pos[0][1][0])[VX], (prisms->prism_pos[0][1][0])[VY], (prisms->prism_pos[0][1][0])[VZ]);

			glVertex3f((prisms->prism_pos[0][0][1])[VX], (prisms->prism_pos[0][0][1])[VY], (prisms->prism_pos[0][0][1])[VZ]);
			glVertex3f((prisms->prism_pos[1][0][1])[VX], (prisms->prism_pos[1][0][1])[VY], (prisms->prism_pos[1][0][1])[VZ]);
			glVertex3f((prisms->prism_pos[1][1][1])[VX], (prisms->prism_pos[1][1][1])[VY], (prisms->prism_pos[1][1][1])[VZ]);
			glVertex3f((prisms->prism_pos[0][1][1])[VX], (prisms->prism_pos[0][1][1])[VY], (prisms->prism_pos[0][1][1])[VZ]);
		}
	}
	glEnd();


}

void Wall::setDirection(int pd, int sd) {
	primaryDirection = pd;
	secondaryDirection = sd;
}


void Wall::animate() {
	float wallVelocity = game->getSettings()->wallVelocity;

	if (positiveSide == PROGRESS) {
		if (positiveProgress < positiveMaxExtentPrimary - startPosition[primaryDirection] - wallVelocity) {
			positiveProgress += wallVelocity;
		} else {
			positiveProgress = positiveMaxExtentPrimary - startPosition[primaryDirection];
			positiveSide = COMPLETED;
		}
	}

	if (negativeSide == PROGRESS) {
		if (negativeProgress < startPosition[primaryDirection] - negativeMaxExtentPrimary - wallVelocity) {
			negativeProgress += wallVelocity;
		} else {
			negativeProgress = startPosition[primaryDirection] - negativeMaxExtentPrimary;
			negativeSide = COMPLETED;
		}
	}

	if (positiveSide == COMPLETED && negativeSide == COMPLETED) {
		completeWall();
	}

	// nonexistence needs to be consistent (this fixes several bugs)

	if (positiveSide == NONEXISTENT) {
		positiveProgress = 0;
	}

	if (negativeSide == NONEXISTENT) {
		negativeProgress = 0;
	}

	if (positiveProgress == 0 && negativeProgress == 0) {
		positiveSide = NONEXISTENT;
		negativeSide = NONEXISTENT;
	}
}

void Wall::expand() {
	int pDir = primaryDirection;
	int sDir = secondaryDirection;

	positiveMaxExtentPrimary = game->getDimensions()[pDir];
	negativeMaxExtentPrimary = - game->getDimensions()[pDir];

	float positiveMaxExtentSecondary = game->getDimensions()[sDir];
	float negativeMaxExtentSecondary = - game->getDimensions()[sDir];

	positiveFill = positiveMaxExtentSecondary - startPosition[sDir];
	negativeFill = startPosition[sDir] - negativeMaxExtentSecondary;

	getPrisms(true);

	for (vector<Wall *>::iterator it = game->getWallsBeginIterator(); it != game->getWallsEndIterator(); ++it) {
		Wall * w = *it;

		if (w == this) {
			continue;
		}

		vec3 wppos1 = w->prisms->prism_pos[0][0][0];
		vec3 wppos2 = w->prisms->prism_pos[1][1][1];
		vec3 wpneg1 = w->prisms->prism_neg[0][0][0];
		vec3 wpneg2 = w->prisms->prism_neg[1][1][1];

		if ((w->positiveSide != DEAD &&
				(lineWithinPrism(prisms->prism_neg[0][0][0], prisms->prism_neg[0][1][0], wppos1, wppos2) ||
				 lineWithinPrism(prisms->prism_neg[0][0][1], prisms->prism_neg[0][1][1], wppos1, wppos2) ||
				 lineWithinPrism(prisms->prism_pos[1][0][0], prisms->prism_pos[1][1][0], wppos1, wppos2) ||
				 lineWithinPrism(prisms->prism_pos[1][0][1], prisms->prism_pos[1][1][1], wppos1, wppos2))) ||
			(w->negativeSide != DEAD &&
				(lineWithinPrism(prisms->prism_neg[0][0][0], prisms->prism_neg[0][1][0], wpneg1, wpneg2) ||
				 lineWithinPrism(prisms->prism_neg[0][0][1], prisms->prism_neg[0][1][1], wpneg1, wpneg2) ||
				 lineWithinPrism(prisms->prism_pos[1][0][0], prisms->prism_pos[1][1][0], wpneg1, wpneg2) ||
				 lineWithinPrism(prisms->prism_pos[1][0][1], prisms->prism_pos[1][1][1], wpneg1, wpneg2)))) {
					if (wppos1[sDir] < positiveMaxExtentSecondary && wppos1[sDir] >= startPosition[sDir]) 
						positiveMaxExtentSecondary = wppos1[sDir];
					if (wppos2[sDir] < positiveMaxExtentSecondary && wppos2[sDir] >= startPosition[sDir]) 
						positiveMaxExtentSecondary = wppos2[sDir];
					if (wpneg1[sDir] < positiveMaxExtentSecondary && wpneg1[sDir] >= startPosition[sDir]) 
						positiveMaxExtentSecondary = wpneg1[sDir];
					if (wpneg2[sDir] < positiveMaxExtentSecondary && wpneg2[sDir] >= startPosition[sDir]) 
						positiveMaxExtentSecondary = wpneg2[sDir];

					if (wppos1[sDir] > negativeMaxExtentSecondary && wppos1[sDir] <= startPosition[sDir]) 
						negativeMaxExtentSecondary = wppos1[sDir];
					if (wppos2[sDir] > negativeMaxExtentSecondary && wppos2[sDir] <= startPosition[sDir]) 
						negativeMaxExtentSecondary = wppos2[sDir];
					if (wpneg1[sDir] > negativeMaxExtentSecondary && wpneg1[sDir] <= startPosition[sDir]) 
						negativeMaxExtentSecondary = wpneg1[sDir];
					if (wpneg2[sDir] > negativeMaxExtentSecondary && wpneg2[sDir] <= startPosition[sDir]) 
						negativeMaxExtentSecondary = wpneg2[sDir];
		} 
	}

	positiveFill = positiveMaxExtentSecondary - startPosition[sDir] - 2 * game->getSettings()->wallPrimaryWidth;
	negativeFill = startPosition[sDir] - negativeMaxExtentSecondary - 2 * game->getSettings()->wallPrimaryWidth;

	positiveProgress = positiveMaxExtentPrimary - startPosition[pDir];
	negativeProgress = startPosition[pDir] - negativeMaxExtentPrimary;

	getPrisms(true);

	for (vector<Wall *>::iterator it = game->getWallsBeginIterator(); it != game->getWallsEndIterator(); ++it) {
		Wall * w = *it;

		if (w == this) {
			continue;
		}

		vec3 wppos1 = w->prisms->prism_pos[0][0][0];
		vec3 wppos2 = w->prisms->prism_pos[1][1][1];
		vec3 wpneg1 = w->prisms->prism_neg[0][0][0];
		vec3 wpneg2 = w->prisms->prism_neg[1][1][1];

		if ((w->positiveSide != DEAD &&
				(lineWithinPrism(prisms->prism_neg[0][0][0], prisms->prism_pos[1][0][0], wppos1, wppos2) ||
				 lineWithinPrism(prisms->prism_neg[0][0][1], prisms->prism_pos[1][0][1], wppos1, wppos2) ||
				 lineWithinPrism(prisms->prism_neg[0][1][0], prisms->prism_pos[1][1][0], wppos1, wppos2) ||
				 lineWithinPrism(prisms->prism_neg[0][1][1], prisms->prism_pos[1][1][1], wppos1, wppos2))) ||
			(w->negativeSide != DEAD && 
				 (lineWithinPrism(prisms->prism_neg[0][0][0], prisms->prism_pos[1][0][0], wppos1, wppos2) ||
				  lineWithinPrism(prisms->prism_neg[0][0][1], prisms->prism_pos[1][0][1], wppos1, wppos2) ||
				  lineWithinPrism(prisms->prism_neg[0][1][0], prisms->prism_pos[1][1][0], wppos1, wppos2) ||
				  lineWithinPrism(prisms->prism_neg[0][1][1], prisms->prism_pos[1][1][1], wppos1, wppos2)))) {

					if (wppos1[pDir] < positiveMaxExtentPrimary && wppos1[pDir] > startPosition[pDir])
						positiveMaxExtentPrimary = wppos1[pDir];
					if (wppos2[pDir] < positiveMaxExtentPrimary && wppos2[pDir] > startPosition[pDir])
						positiveMaxExtentPrimary = wppos2[pDir];
					if (wpneg1[pDir] < positiveMaxExtentPrimary && wpneg1[pDir] > startPosition[pDir])
						positiveMaxExtentPrimary = wpneg1[pDir];
					if (wpneg2[pDir] < positiveMaxExtentPrimary && wpneg2[pDir] > startPosition[pDir])
						positiveMaxExtentPrimary = wpneg2[pDir];

					if (wppos1[pDir] > negativeMaxExtentPrimary && wppos1[pDir] < startPosition[pDir])
						negativeMaxExtentPrimary = wppos1[pDir];
					if (wppos2[pDir] > negativeMaxExtentPrimary && wppos2[pDir] < startPosition[pDir])
						negativeMaxExtentPrimary = wppos2[pDir];
					if (wpneg1[pDir] > negativeMaxExtentPrimary && wpneg1[pDir] < startPosition[pDir])
						negativeMaxExtentPrimary = wpneg1[pDir];
					if (wpneg2[pDir] > negativeMaxExtentPrimary && wpneg2[pDir] < startPosition[pDir])
						negativeMaxExtentPrimary = wpneg2[pDir];
		}
	}

	positiveFill = positiveMaxExtentSecondary - startPosition[sDir];
	negativeFill = startPosition[sDir] - negativeMaxExtentSecondary;

	getPrisms(true);

	for (vector<Wall *>::iterator it = game->getWallsBeginIterator(); it != game->getWallsEndIterator(); ++it) {
		Wall * w = *it;

		if (w == this) {
			continue;
		}

		vec3 wppos1 = w->prisms->prism_pos[0][0][0];
		vec3 wppos2 = w->prisms->prism_pos[1][1][1];
		vec3 wpneg1 = w->prisms->prism_neg[0][0][0];
		vec3 wpneg2 = w->prisms->prism_neg[1][1][1];

		if ((w->positiveSide != DEAD &&
			(lineWithinPrism(prisms->prism_neg[0][0][0], prisms->prism_pos[1][0][0], wppos1, wppos2) ||
			lineWithinPrism(prisms->prism_neg[0][0][1], prisms->prism_pos[1][0][1], wppos1, wppos2) ||
			lineWithinPrism(prisms->prism_neg[0][1][0], prisms->prism_pos[1][1][0], wppos1, wppos2) ||
			lineWithinPrism(prisms->prism_neg[0][1][1], prisms->prism_pos[1][1][1], wppos1, wppos2))) ||
			(w->negativeSide != DEAD && 
			(lineWithinPrism(prisms->prism_neg[0][0][0], prisms->prism_pos[1][0][0], wppos1, wppos2) ||
			lineWithinPrism(prisms->prism_neg[0][0][1], prisms->prism_pos[1][0][1], wppos1, wppos2) ||
			lineWithinPrism(prisms->prism_neg[0][1][0], prisms->prism_pos[1][1][0], wppos1, wppos2) ||
			lineWithinPrism(prisms->prism_neg[0][1][1], prisms->prism_pos[1][1][1], wppos1, wppos2)))) {

				if (wppos1[pDir] < positiveMaxExtentPrimary && wppos1[pDir] > startPosition[pDir])
					positiveMaxExtentPrimary = wppos1[pDir];
				if (wppos2[pDir] < positiveMaxExtentPrimary && wppos2[pDir] > startPosition[pDir])
					positiveMaxExtentPrimary = wppos2[pDir];
				if (wpneg1[pDir] < positiveMaxExtentPrimary && wpneg1[pDir] > startPosition[pDir])
					positiveMaxExtentPrimary = wpneg1[pDir];
				if (wpneg2[pDir] < positiveMaxExtentPrimary && wpneg2[pDir] > startPosition[pDir])
					positiveMaxExtentPrimary = wpneg2[pDir];

				if (wppos1[pDir] > negativeMaxExtentPrimary && wppos1[pDir] < startPosition[pDir])
					negativeMaxExtentPrimary = wppos1[pDir];
				if (wppos2[pDir] > negativeMaxExtentPrimary && wppos2[pDir] < startPosition[pDir])
					negativeMaxExtentPrimary = wppos2[pDir];
				if (wpneg1[pDir] > negativeMaxExtentPrimary && wpneg1[pDir] < startPosition[pDir])
					negativeMaxExtentPrimary = wpneg1[pDir];
				if (wpneg2[pDir] > negativeMaxExtentPrimary && wpneg2[pDir] < startPosition[pDir])
					negativeMaxExtentPrimary = wpneg2[pDir];
		}
	}

	positiveProgress = game->getSettings()->wallPrimaryWidth;
	negativeProgress = positiveProgress;
}

bool Wall::collision() {

	getPrisms();

	for (vector<Ball *>::iterator it = game->getPlayField()->getBallsBegin(); it != game->getPlayField()->getBallsEnd(); it++) {
		collideWithBall(it);
	}

	float primaryWidth = game->getSettings()->wallPrimaryWidth;
	if ((positiveProgress < primaryWidth && negativeProgress < primaryWidth) ||
		(positiveFill < primaryWidth && negativeFill < primaryWidth)) {
		positiveSide = DEAD;
		negativeSide = DEAD;
		state = NONEXISTENT;
	}

	return false;
}

void Wall::collideWithBall( vector<Ball *>::iterator it )
{
	Ball * b = *it;
	vec3 posFuture = b->pos + b->direction;

	vec3 ppos1 = prisms->prism_pos[0][0][0];
	vec3 ppos2 = prisms->prism_pos[1][1][1];
	vec3 pneg1 = prisms->prism_neg[0][0][0];
	vec3 pneg2 = prisms->prism_neg[1][1][1];

	//check the entire wall if the wall is complete
	if (positiveSide == COMPLETED && negativeSide == COMPLETED) {
		vec3 temp = ppos1;
		ppos1 = pneg1;
		pneg2 = temp;
	}

	if ((posFuture[VX]+b->radius > ppos1[VX]) && (posFuture[VX]-b->radius < ppos2[VX])) {
		if ((posFuture[VY]+b->radius > ppos1[VY]) && (posFuture[VY]-b->radius < ppos2[VY])) {
			if ((posFuture[VZ]+b->radius > ppos1[VZ]) && (posFuture[VZ]-b->radius < ppos2[VZ])) {
				if (positiveSide != DEAD) {
					if (((posFuture[VX]+b->radius > ppos1[VX]) && (posFuture[VX]-b->radius < ppos1[VX])) ||
						((posFuture[VX]+b->radius > ppos2[VX]) && (posFuture[VX]-b->radius < ppos2[VX]))) {
							b->direction[VX] *= -1;
					}
					if (((posFuture[VY]+b->radius > ppos1[VY]) && (posFuture[VY]-b->radius < ppos1[VY])) ||
						((posFuture[VY]+b->radius > ppos2[VY]) && (posFuture[VY]-b->radius < ppos2[VY]))) {
							b->direction[VY] *= -1;
					}
					if (((posFuture[VZ]+b->radius > ppos1[VZ]) && (posFuture[VZ]-b->radius < ppos1[VZ])) ||
						((posFuture[VZ]+b->radius > ppos2[VZ]) && (posFuture[VZ]-b->radius < ppos2[VZ]))) {
							b->direction[VZ] *= -1;
					}
				}
				if (positiveSide == PROGRESS) {
					positiveProgress = 0;
					positiveSide = COMPLETED;
					game->loseLife();
					PLAYSOUND("jezzdead.wav");
				} else {
					PLAYSOUND("bounce.wav");
				}
			}
		}
	}

	if ((posFuture[VX]+b->radius > pneg1[VX]) && (posFuture[VX]-b->radius < pneg2[VX])) {
		if ((posFuture[VY]+b->radius > pneg1[VY]) && (posFuture[VY]-b->radius < pneg2[VY])) {
			if ((posFuture[VZ]+b->radius > pneg1[VZ]) && (posFuture[VZ]-b->radius < pneg2[VZ])) {
				if (negativeSide != DEAD) {
					if (((posFuture[VX]+b->radius > pneg1[VX]) && (posFuture[VX]-b->radius < pneg1[VX])) ||
						((posFuture[VX]+b->radius > pneg2[VX]) && (posFuture[VX]-b->radius < pneg2[VX]))) {
							b->direction[VX] *= -1;
					}
					if (((posFuture[VY]+b->radius > pneg1[VY]) && (posFuture[VY]-b->radius < pneg1[VY])) ||
						((posFuture[VY]+b->radius > pneg2[VY]) && (posFuture[VY]-b->radius < pneg2[VY]))) {
							b->direction[VY] *= -1;
					}
					if (((posFuture[VZ]+b->radius > pneg1[VZ]) && (posFuture[VZ]-b->radius < pneg1[VZ])) ||
						((posFuture[VZ]+b->radius > pneg2[VZ]) && (posFuture[VZ]-b->radius < pneg2[VZ]))) {
							b->direction[VZ] *= -1;
					}
				}
				if (negativeSide == PROGRESS) {
					negativeProgress = 0;
					negativeSide = COMPLETED;
					game->loseLife();
					PLAYSOUND("jezzdead.wav");
				} else {
					PLAYSOUND("bounce.wav");
				}
			}
		}
	}
}

void Wall::completeWall()
{
	float oldPositiveProgress = positiveProgress;
	float oldNegativeProgress = negativeProgress;

	float totalProgress = positiveProgress + negativeProgress;
	startPosition[primaryDirection] -= negativeProgress;
	positiveProgress = totalProgress;
	negativeProgress = 0;
	negativeSide = DEAD;

	getPrisms();

	// Mark on occupied chart
	float width = game->getSettings()->wallPrimaryWidth;
	vec3 start = (1/width) * (prisms->prism_pos[0][0][0] + game->getDimensions()) + vec3(0.01);
	vec3 end = (1/width) * (prisms->prism_pos[1][1][1] + game->getDimensions()) + vec3(0.01);
	for (int i = start[VX]; i < floor(end[VX]); i++) {
		for (int j = start[VY]; j < floor(end[VY]); j++) {
			for (int k = start[VZ]; k < floor(end[VZ]); k++) {
				game->occupied[i][j][k] = true;
			}
		}
	}

	game->calcArea();
	if (game->getArea() >= game->getSettings()->goal) {
		PLAYSOUND("tada.wav");
	} else if (oldPositiveProgress > 0 && oldNegativeProgress) {
		PLAYSOUND("wipe.wav");
	}
}

// http://www.3dkingdoms.com/weekly/weekly.php?a=21
static bool lineWithinPrism(vec3 L1, vec3 L2, vec3 p1, vec3 p2) {

	// Get box center and extent
	vec3 boxCenter = (p2 + p1) / 2;
	vec3 boxExtent = (p2 - p1) / 2;

	// Put line in box space
	L1 -= boxCenter;
	L2 -= boxCenter;

	// Get line midpoint and extent
	vec3 LMid = (L1 + L2) * 0.5f; 
	vec3 L = (L1 - LMid);
	vec3 LExt = vec3( fabs(L[VX]), fabs(L[VY]), fabs(L[VZ]) );

	// Use Separating Axis Test
	// Separation vector from box center to line center is LMid, since the line is in box space
	if ( fabs( LMid[VX] ) > boxExtent[VX] + LExt[VX] ) return false;
	if ( fabs( LMid[VY] ) > boxExtent[VY] + LExt[VY] ) return false;
	if ( fabs( LMid[VZ] ) > boxExtent[VZ] + LExt[VZ] ) return false;
	// Crossproducts of line and each axis
	if ( fabs( LMid[VY] * L[VZ] - LMid[VZ] * L[VY])  >  (boxExtent[VY] * LExt[VZ] + boxExtent[VZ] * LExt[VY]) ) return false;
	if ( fabs( LMid[VX] * L[VZ] - LMid[VZ] * L[VX])  >  (boxExtent[VX] * LExt[VZ] + boxExtent[VZ] * LExt[VX]) ) return false;
	if ( fabs( LMid[VX] * L[VY] - LMid[VY] * L[VX])  >  (boxExtent[VX] * LExt[VY] + boxExtent[VY] * LExt[VX]) ) return false;
	// No separating axis, the line intersects
	return true;

}
