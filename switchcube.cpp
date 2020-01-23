#include "switchcube.hpp"
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
SwitchCube::SwitchCube() {
	_dx = 0;
	_width = 1;
	_height = 0.5;
	_length = 5;
	make_cubes(1);
	speed_of_moving = .03;
	_xCoords[0] = 2*(rand()%3 - 1);
}

void SwitchCube::advance() {
	moving -= speed_of_moving;
	if(moving <= 0) {
		_xCoords[0] /= 2;
		moving = 1;
		_xCoords[0]++;
		_xCoords[0] = (int(_xCoords[0])+1)%3-1;
		_xCoords[0]*=2;
	}
}
void SwitchCube::init() {
	srand(time(NULL));
	switch(rand()%3){
		case 1:
			speed_of_moving = .03;
			break;
		case 2:
			speed_of_moving = .06;
			break;
		case 0:
			speed_of_moving = .09;
	}
	is_player_uppers[0] = false;
}
void SwitchCube::make() const {
	float diffuse[4] = {0, 0, moving, 1};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	PeaceOfPath::make();
}
