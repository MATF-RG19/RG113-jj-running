#include <GL/glut.h>
#include <cstdlib>
#include <time.h>
#include "cube3.hpp"
#include "player.hpp"

Cube3::Cube3() {
		  _yCoord = .45;
}
void Cube3::make() const {
	float diffuse[4] = {0, 0, 0, 1};
	if(_type == ORDINARY)
			  diffuse[0] = 1;
	else if(_type == SWITCHING)
			  diffuse[2] = _num;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	for(int i = 0; i < 3; i++) {
		if(!_visibles[i])
			  continue;
		glPushMatrix();
		glTranslatef(-2+i*2, 0, 0);
		glScalef(2, 1, 10);

		glutSolidCube(1);
		glutWireCube(1);
		glDisable(GL_LIGHTING);

		if(is_player_upper)
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
#include <iostream>

void Cube3::init() {
	srand(time(NULL));
	_type = ORDINARY;
	switch(rand()%7) {
		case 0: 
			_visibles[2] = _visibles[1] = !(_visibles[0] = true);
			_type = SWITCHING;
			break;
		case 1:
			_visibles[2] = _visibles[0] = !(_visibles[1] = true);
			_type = SWITCHING;
			break;
		case 2:
			_visibles[1] = _visibles[0] = !(_visibles[2] = true);
			_type = SWITCHING;
			break;
		case 3: 
			_visibles[2] = _visibles[1] = !(_visibles[0] = false);
			break;
		case 4:
			_visibles[2] = _visibles[0] = !(_visibles[1] = false);
			break;
		case 5:
			_visibles[1] = _visibles[0] = !(_visibles[2] = false);
			break;
		case 6:
			_visibles[1] = _visibles[0] = _visibles[2] = true;
			break;
	}
	is_player_upper = false;
	_num = 1.;
}
void Cube3::advance() {
	if(_type == ORDINARY)
			  return;
	else if (_type == SWITCHING) {
		_num -= .03;	
		if(_num <= 0){
			 _num = 1;
			for(int i =0 ;i < 3; i++)
				if(_visibles[i]) {
					_visibles[(i+1)%3] = (true);
					_visibles[i] = (false);
					break;
				}
		}
	}
	else if(_type == MOVING) {
	}
}

bool Cube3::check_if_player_is_on_this_X(Player& p) {
	float x = p.getX();

	int index = -1;
	if(x <= 0.7 && x >= -0.7)
	{			  
			index = 1;	
	}
	else if(x >= 1.3 && x < 3.3) 
	{
			index = 2;
	}
	else if(x <= -1.3 && x > -3.2) 
	{
			index = 0;
	}
	else if(x >= 3.2)
			  index = -1;
	else if(x <= -3.2)
			  index = -1;
	else if(x > .7 && x <1.3)
	{
		if(_visibles[1])index = 1;
		else if(_visibles[2])index = 2;
	}
	else if(x > -1.3 && x < -0.7)
	{
		if(_visibles[1])index = 1;
		else if(_visibles[0])index = 0;
	}
	return !(index == -1 || !_visibles[index]);
}

