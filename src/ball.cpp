#include "ball.h"

void Ball::render() {
	//float colorRed[4] = { 1.0, 0.0, 0.0, 1.0 };
	float colorWhite[4] = { 1.0, 1.0, 1.0, 1.0 };	
	vec3 rotationPosition = pos + 0.01*cos(progress)*vec3(0.0,0.0,1.0).normalize() + 
	0.01*sin(progress)*vec3(1.0,0.0,0.0).normalize();
	
	
	if (progress == 1.0)
		progress = 0.0;
	else
		progress = progress + 0.01;
	
	glPushMatrix();
		glTranslatef(pos[VX], pos[VY], pos[VZ]);
		glColor4fv(color);
		glutSolidSphere(radius,20,20);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(rotationPosition[VX], rotationPosition[VY], rotationPosition[VZ]);
		glColor4fv(colorWhite);
		glutSolidSphere(radius,19,19);
	glPopMatrix();
	
	glPopMatrix();
	
	
}

void Ball::move() {
	
	pos += direction;

	// ball collision
	for (vector<Ball *>::iterator it = box->getBallsBegin(); it != box->getBallsEnd(); it++) {	
		Ball * ball = *it;

		if (ball != this && distance(ball) <= (radius + ball->radius)) {
			double x1, y1, z1, x2, y2, z2, vx1, vy1, vz1, vx2, vy2, vz2;
			int error;

			x1 = pos[VX]; y1 = pos[VY]; z1 = pos[VZ];
			x2 = ball->pos[VX]; y2 = ball->pos[VX]; z2 = ball->pos[VX];
			vx1 = direction[VX]; vy1 = direction[VY]; vz1 = direction[VZ];
			vx2 = ball->direction[VX]; vy2 = ball->direction[VX]; vz2 = ball->direction[VX];

			collision3D(1.0, 1.0, 1.0, radius, ball->radius,
				x1, y1, z1,
				x2, y2, z2,
				vx1, vy1, vz1,
				vx2, vy2, vz2,
				error);

			if (error == 0) {
				// Collision occurred - modify velocity (not position)

				//pos = vec3(x1, y1, z1);
				//ball->pos = vec3(x2, y2, z2);

				// We normalize directions to maintain constant velocity (for better gameplay)

				float velocity = direction.length();
				direction = vec3(vx1, vy1, vz1);
				direction.normalize();
				direction *= velocity;

				velocity = ball->direction.length();
				ball->direction = vec3(vx2, vy2, vz2);
				ball->direction.normalize();
				ball->direction *= velocity;

				// Debugging things
				//cout << distance(ball) << "\n";
				//direction = vec3(0);
				//ball->direction = vec3(0);

				PLAYSOUND("bounce.wav");
			}
		}
	}

	// wall collision
	if ((pos[VX]-radius < box->getCorner1()[VX] && direction[VX] < 0) || 
		(pos[VX]+radius > box->getCorner2()[VX] && direction[VX] > 0)) {
			direction[VX] *= -1;
			PLAYSOUND("bounce.wav");
	}

	if ((pos[VY]-radius < box->getCorner1()[VY] && direction[VY] < 0) || 
		(pos[VY]+radius > box->getCorner2()[VY] && direction[VY] > 0)) {
			direction[VY] *= -1;
			PLAYSOUND("bounce.wav");
	}

	if ((pos[VZ]-radius < box->getCorner1()[VZ] && direction[VZ] < 0) || 
		(pos[VZ]+radius > box->getCorner2()[VZ] && direction[VZ] > 0)) {
			direction[VZ] *= -1;
			PLAYSOUND("bounce.wav");
	}

}

// private


float Ball::distance(Ball * ball) {
	return sqrt(pow(pos[VX] - ball->pos[VX], 2) +
			    pow(pos[VY] - ball->pos[VY], 2) +
				pow(pos[VZ] - ball->pos[VZ], 2));
}

