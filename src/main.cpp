#include "main.h"
#include <cstring>

using namespace std;

#define WITHIN_BOX(x, dim) max(-(dim),min(dim,x))
#define W WITHIN_BOX

#define ON_OR_OFF(x) x ? "(On)" : "(Off)"

// viewport
struct Viewport {
    Viewport(): mousePos(0.0,0.0) { orientation = identity3D(); };
	int w, h; // width and height
	vec2 mousePos;
    mat4 orientation;
};


//****************************************************
// Global Variables
//****************************************************

Viewport viewport;
UCB::ImageSaver * imgSaver;
bool rightMouse;
int startTime;
int prevTime;
int timeRemaining;
bool zoom = false;
bool paused = false;
bool sound = true;

int startingBalls = 2;
int startingLives = 2;
int highScore = 0;
vec3 dimensions = vec3(2, 1, 1);
float ballColor[4] = { 1.0, 0.0, 0.0, 1.0}; // red
Settings * settings = new Settings(0.05, 0.03, 0.1, 0.05, 0.03, ballColor, 80);
int startingDirection[2] = { VY, VZ };

Game * game;

// setup the model view matrix
void setupView() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glTranslatef(0,0,-5);
    applyMat4(viewport.orientation);

	//Enable depth buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

    //Enable Anti-Aliasing
    glEnable (GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glLineWidth(1.5);
    glutPostRedisplay();
}

//-------------------------------------------------------------------------------
/// You will be calling all of your drawing-related code from this function.
/// Nowhere else in your code should you use glBegin(...) and glEnd() except code
/// called from this method.
///
/// To force a redraw of the screen (eg. after mouse events or the like) simply call
/// glutPostRedisplay();
void display() {

	// Clear Buffers

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Set text

	if (!paused) {
		timeRemaining = game->getTime();
	}

	char livesBuf[100] = {0}, scoreBuf[100] = {0}, timeBuf[100] = {0}, areaBuf[100] = {0}, highScoreBuf[100] = {0};
	char pauseBuf[100] = {0}, soundBuf[100] = {0}, zoomBuf[100] = {0};

	sprintf(livesBuf, "Lives: %d", game->getNumLives());
	sprintf(scoreBuf, "Score: %d", game->getScore());
	sprintf(highScoreBuf, "High Score: %d", highScore);
	sprintf(timeBuf, "Time Left: %d", timeRemaining);
	sprintf(areaBuf, "Volume Cleared: %d%%", game->getArea());

	sprintf(pauseBuf, "[P] Pause %s", ON_OR_OFF(paused));
	sprintf(soundBuf, "[S] Sound %s", ON_OR_OFF(sound));
	sprintf(zoomBuf, "[Z] Zoom Mode %s", ON_OR_OFF(zoom));

	// Draw text

	beforeDrawText();
	printString(GLUT_BITMAP_HELVETICA_18, livesBuf, 10, 440);
	printString(GLUT_BITMAP_HELVETICA_18, scoreBuf, 285, 450);
	printString(GLUT_BITMAP_HELVETICA_18, highScoreBuf, 262, 430);
	printString(GLUT_BITMAP_HELVETICA_18, timeBuf, 560, 440);
	printString(GLUT_BITMAP_HELVETICA_18, areaBuf, 260, 10);
	printString(GLUT_BITMAP_HELVETICA_18, game->getStatus(), 470, 10);

	printString(GLUT_BITMAP_HELVETICA_12, pauseBuf, 10, 45);
	printString(GLUT_BITMAP_HELVETICA_12, soundBuf, 10, 30);
	printString(GLUT_BITMAP_HELVETICA_12, zoomBuf, 10, 15);
	afterDrawText();

	// Draw game

	setupView();

	game->render();

	//Now that we've drawn on the buffer, swap the drawing buffer and the displaying buffer.
	glutSwapBuffers();
}

void animate(int value)
{
	// Set up the next timer tick (do this first)
    glutTimerFunc(TIMERMSECS, animate, 0);

	// Measure the elapsed time
	int currTime = glutGet(GLUT_ELAPSED_TIME);
	//int timeSincePrevFrame = currTime - prevTime;
	//int elapsedTime = currTime - startTime;

	if (!paused) {
		game->animate();

		// Set high score
		if (game->getScore() > highScore) {
			highScore = game->getScore();
		}
	}

	// Force a redisplay to render the new image
	glutPostRedisplay();

	prevTime = currTime;
}

//-------------------------------------------------------------------------------
/// \brief	Called when the screen gets resized.
/// This gives you the opportunity to set up all the relevant transforms.
///
void reshape(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, ((double)w / MAX(h, 1)), 1.0, 100.0);
	//glOrtho(-10,10,-10,10,1,100);

    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//-------------------------------------------------------------------------------
/// Called to handle keyboard events.
void myKeyboardFunc (unsigned char key, int x, int y) {
	switch (key) {
		case 27:			// Escape key
			exit(0);
			break;
		case ' ':
			if (paused)
				break;
			// Change direction
			game->getMouse()->changeDirection();
			// change direction of temp wall
			int primary, secondary;
			primary = game->getMouse()->primaryDirection;
			secondary = game->getMouse()->secondaryDirection;
			game->getTempWall()->setDirection(primary, secondary);
			game->getTempWall()->expand();
			// cout << game->getMouse()->primaryDirection << "," << game->getMouse()->secondaryDirection << "\n";
			break;
		case 'N':
		case 'n':
			// next level
			game->nextLevel();
			break;
		case 'P':
		case 'p':
			// pause
			paused = !paused;
			if (!paused) {
				game->unpause();
			}
			break;
		case 'R':
		case 'r':
			// restart game
			delete game;
			game = new Game(settings, startingBalls, startingLives, dimensions, startingDirection);
			break;
		case 'S':
		case 's':
			// toggle sound
			sound = !sound;
			break;
		case 'Z':
		case 'z':
			// zoom mode
			zoom = !zoom;
			break;
	}
}

void myMouseFunc(int button, int state, int x, int y) {
	if (!paused) {
		if (button==GLUT_LEFT_BUTTON) {
			game->finalizeTempWall();	
		} else if (button==GLUT_MIDDLE_BUTTON) {
			if (state==GLUT_DOWN) {
				// Change direction
				game->getMouse()->changeDirection();
				// change direction of temp wall
				int primary, secondary;
				primary = game->getMouse()->primaryDirection;
				secondary = game->getMouse()->secondaryDirection;
				game->getTempWall()->setDirection(primary, secondary);
				game->getTempWall()->expand();	
			}
		} else {
			if (state==GLUT_DOWN) {
				rightMouse = true;
			} else {
				rightMouse = false;
			}
		}
	}
}

//-------------------------------------------------------------------------------
/// Called whenever the mouse moves while a button is pressed
void myActiveMotionFunc(int x, int y) {
	if (!paused) {

		vec2 newMouse = vec2((double)x / glutGet(GLUT_WINDOW_WIDTH),(double)y / glutGet(GLUT_WINDOW_HEIGHT));

		if (rightMouse) {
			vec2 diff = (newMouse - viewport.mousePos);
			double len = diff.length();
				
			if (!zoom) {
				// Rotate viewport orientation proportional to mouse motion
				if (len > .001) {
					vec3 axis = vec3(diff[1]/len, diff[0]/len, 0);
					viewport.orientation = rotation3D(axis, 180 * len) * viewport.orientation;
				}
			} else {
				// scale
				double scale = diff[VY];
				if (abs(scale) > .001) {
					scale += 1.0;
					mat4 scaleMat = mat4(vec4(scale, 0, 0, 0),
						vec4(0, scale, 0, 0),
						vec4(0, 0, scale, 0),
						vec4(0, 0, 0, 1));
					viewport.orientation = scaleMat * viewport.orientation;
				}
			}
		}
		

		//Record the mouse location for drawing crosshairs
		viewport.mousePos = newMouse;
		//Force a redraw of the window.
		//glutPostRedisplay();
	}
}


//-------------------------------------------------------------------------------
/// Called whenever the mouse moves without any buttons pressed.
void myPassiveMotionFunc(int x, int y) {
	if (!paused) {

		Wall * tempWall;
		//Record the mouse location for drawing crosshairs
		viewport.mousePos = vec2((double)x / glutGet(GLUT_WINDOW_WIDTH),(double)y / glutGet(GLUT_WINDOW_HEIGHT));
		//Force a redraw of the window.
		//glutPostRedisplay();

		float width = game->getSettings()->wallPrimaryWidth;

		vec3 mouse = GetOGLPos(x, y);
		for (int i = VX; i <= VZ; i++) {
			mouse[i] = floor(mouse[i] / width) * width;

			// position along grid
			if (mouse[i] >= game->getDimensions()[i] && mouse[i] <= game->getDimensions()[i] + 2 * width) {
				mouse[i] = game->getDimensions()[i] - width;
			} else if (mouse[i] <= - game->getDimensions()[i] && mouse[i] >= - game->getDimensions()[i] - 2 * width) {
				mouse[i] = - game->getDimensions()[i] + 0.000001;
			}
		}
		//cout << mouse << "\n";

		vec3 dim = game->getDimensions();
		if (mouse[VX] < dim[VX] && mouse[VX] > -dim[VX] &&
			mouse[VY] < dim[VY] && mouse[VY] > -dim[VY] &&
			mouse[VZ] < dim[VZ] && mouse[VZ] > -dim[VZ]) {
				// Mouse in bounds - make a wall
				vec3 rect = vec3(W(mouse[VX], dim[VX]), W(mouse[VY], dim[VY]), W(mouse[VZ], dim[VZ]));

				int primary = game->getMouse()->primaryDirection;
				int secondary = game->getMouse()->secondaryDirection;
				int tertiary = VX; while (primary == tertiary || secondary == tertiary) tertiary++;

				float primaryWidth = game->getSettings()->wallPrimaryWidth;
				float tertiaryWidth = game->getSettings()->wallTertiaryWidth;

				rect[primary] = W(rect[primary] + 2*primaryWidth, dim[primary]) - primaryWidth;
				rect[tertiary] = W(rect[tertiary] + 2*tertiaryWidth, dim[tertiary]) - tertiaryWidth;
				
				// set tempWall
				tempWall = new Wall(rect, primary, secondary, TEMP, game);
				tempWall->expand();

				game->setTempWall(tempWall);
		} else {
			// Mouse out of bounds - no temp wall
			game->clearTempWall();
		}
	}
}

//-------------------------------------------------------------------------------
/// Called to update the screen at 30 fps.
void frameTimer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000/30, frameTimer, 1);
}

//-------------------------------------------------------------------------------
/// Initialize the environment
int main(int argc,char** argv) {
	// Print stuff
	cout << "Welcome to 3D Jezzball!\n";
	cout << "A re-imagining of the classic Windows game Jezzball\n";
	cout << "By Alex Nisnevich and Erik Gui\n";
	cout << "\n";
	cout << "Controls:\n";
	cout << "Left-click to place a wall\n";
	cout << "Middle-click or spacebar to change wall orientation\n";
	cout << "Right-click and drag to rotate (or zoom, in zoom mode)\n";
	cout << "\n";
	cout << "Goal:\n";
	cout << "Clear 80% of the volume to complete each level.\n";
	cout << "\n";
	cout << "Good luck! :-)\n";
	cout << "\n";

	// Seed the random number generator
	srand((unsigned)time(0));

	//Initialize OpenGL
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);

	//Set up global variables
	viewport.w = 1200;
	viewport.h = 600;

	//Create OpenGL Window
	glutInitWindowSize(viewport.w,viewport.h);
	glutInitWindowPosition(0,0);
	glutCreateWindow("JezzBall 3D");

	//Register event handlers with OpenGL.
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(myKeyboardFunc);
	glutMotionFunc(myActiveMotionFunc);
	glutPassiveMotionFunc(myPassiveMotionFunc);
    glutMouseFunc(myMouseFunc);
    frameTimer(0);

	// Start the timer
    glutTimerFunc(TIMERMSECS, animate, 0);

	// Initialize the time variables
	startTime = glutGet(GLUT_ELAPSED_TIME);
	prevTime = startTime;

	//Initialize objects
	game = new Game(settings, startingBalls, startingLives, dimensions, startingDirection);

	//And Go!
	glutMainLoop();

	return 0;
}


// A simple helper function to load a mat4 into opengl
void applyMat4(mat4 &m) {
	double glmat[16];
	int idx = 0;
	for (int j = 0; j < 4; j++) 
		for (int i = 0; i < 4; i++)
			glmat[idx++] = m[i][j];
	glMultMatrixd(glmat);
}

// Unprojects 2d mouse coordinates to 3d
vec3 GetOGLPos(int x, int y) {
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	return vec3(posX, posY, posZ);
}

void printString(void* font, const char* str, int x, int y) {

	glRasterPos2i(x, y);
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(font, str[i]);
	}
}

void beforeDrawText() {
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_FOG);
	//glShadeModel(GL_FLAT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-0.5, 639.5, -0.5, 479.5, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0f, 1.0f, 1.0f);
}

void afterDrawText() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

	glShadeModel(GL_SMOOTH);
}
