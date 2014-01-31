/*
 * global.h
 *
 *  Created on: Feb 2, 2009
 *      Author: njoubert
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#define IMPLEMENT_ME(file,line)    cout << "METHOD NEEDS TO BE IMPLEMENTED AT " << file << ":" << line << endl; exit(1);

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <vector>
#include <cmath>

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#define PLAYSOUND(snd) ;
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <windows.h>
#include <mmsystem.h>
#define PLAYSOUND(SND) extern bool sound; if (sound && SND != "bounce.wav") PlaySound(SND, NULL, SND_FILENAME | SND_ASYNC)
#endif

//Include our math library
#include <algebra3.h>
//Include our Image Saving library.
#include "UCB/ImageSaver.h"

#include <cstdlib> 
#include <ctime> 
#include <iostream>

#define RAND (2*((double) rand()/RAND_MAX) - 1)
#define RAND_POS ((double) rand()/RAND_MAX)
#define RAND_SIGN (2*((double)(rand()%2) - 0.5))
#define RAND_COLOR { RAND_POS, RAND_POS, RAND_POS, 1.0 }

#define VEC3(x) vec3(x,x,x)

// wall sides
#define PROGRESS 0
#define COMPLETED 1
#define DEAD 2

// wall state
#define NORMAL 0
#define TEMP 1
#define NONEXISTENT 2

#endif /* GLOBAL_H_ */
