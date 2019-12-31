#include <GL/glut.h>
#include <cstdlib>
#include <time.h>
#include "cube3.hpp"
#include "player.hpp"

Cube3::Cube3() {
		  _yCoord = .45;
		  _zCoord = 0;
		  _length = 5;
		  _height = .45;
		  _width = 1;
		  n = 2;
		  _xCoords = new float[2];
		  _zCoords = new float[2];
		  _yCoords = new float[2];
		  is_player_uppers = new bool[2];
		  init();
}
void Cube3::make() const {
	float diffuse[4] = {1, 0, 0, 1};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	for(int i = 0; i < n; i++) {
		glPushMatrix();
		glTranslatef(_xCoords[i], _yCoords[i], _zCoords[i]);
		glScalef(2*_width, 2*_height, 2*_length);

		glutSolidCube(1);
		glutWireCube(1);
		glDisable(GL_LIGHTING);

		if(is_player_uppers[i])
				  glColor3f(0, 1, 0);
		else 
				  glColor3f(0, 0, 0);
		glBegin(GL_POINTS);
		glVertex3f(0,.5, 0);
		glEnd();
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}
}

void Cube3::init() {
	srand(time(NULL));
	switch(rand()%6) {
		case 0: 
			_xCoords[0] = -2;
			n = 1;
			break;
		case 1:
			_xCoords[0] = 0;
			n = 1;
			break;
		case 2:
			_xCoords[0] = 2;
			n = 1;
			break;
		case 3:
			_xCoords[0] = -2;
			_xCoords[1] = 2;
			n = 2;
			break;
		case 4:
			_xCoords[0] = -2;
			_xCoords[1] = 0;
			n = 2;
			break;
		case 5:
			_xCoords[0] = 2;
			_xCoords[1] = 0;
			n = 2;
			break;
	}
	is_player_uppers[0] = false;
	is_player_uppers[1] = false;
}
