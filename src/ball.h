#ifndef BALL_H_
#define BALL_H_

#include "main.h"

#include "box.h"
class Box; // forward declaration

using namespace std;

class Ball {

private:
	Box * box;
	float color[4];

	float distance(Ball * ball);
	void collision3D(double R, double m1, double m2, double r1, double r2,
		double& x1, double& y1,double& z1,
		double& x2, double& y2, double& z2,
		double& vx1, double& vy1, double& vz1,
		double& vx2, double& vy2, double& vz2,
		int& error);

public:
	int num;
	float radius;
	vec3 pos;
	vec3 direction;
	float progress;


	Ball(int num, float radius, vec3 pos, vec3 direction, Box * box, float col[4], float progress) 
		: num(num), radius(radius), pos(pos), direction(direction), box(box), progress(progress){
		for (int i = 0; i < 4; i++)
			color[i] = col[i];
			
	}
	void render();

	void move();
};

#endif
