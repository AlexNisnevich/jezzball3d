/*
 * main.h
 *
 *  Created on: Feb 2, 2009
 *      Author: njoubert
 */

#ifndef MAIN_H_
#define MAIN_H_

#define VERSION 2

#include "global.h"

#include "game.h"
#include "box.h"
#include "ball.h"
#include "wall.h"

// The time in milliseconds between timer ticks
#define TIMERMSECS 30

void applyMat4(mat4 &m);
vec3 GetOGLPos(int x, int y);
void printString(void* font, const char* str, int x = 10, int y = 10);
void beforeDrawText();
void afterDrawText();

#endif /* MAIN_H_ */
