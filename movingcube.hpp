#include "peaceofpath.hpp"
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>

class MovingCube : public PeaceOfPath {
public:
	MovingCube(){init();}
	void init() override {
		_xCoord = 0;
		_width = 1;
		_height = 0.45;
		is_player_upper = false;
		srand(time(NULL));
		_dx = 0.05;
		_yCoord = rand()%7 - 3;
		_yCoord = 0;
		_zCoord = 0;
		_length = 2;
	}
	void advance() override{
		_xCoord += _dx;
		if(_xCoord >= 2 || _xCoord <= -2)_dx*=-1;
	}
	void make()const override{
//			std::cout << "_wit " << _width << std::endl;
		float diffuse[4] = {1, 0, 0, 1};	
		float old_diffuse[4];
		float old_ambient[4];
		glGetMaterialfv(GL_FRONT, GL_DIFFUSE, old_diffuse);
		glGetMaterialfv(GL_FRONT,GL_AMBIENT, old_ambient);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse);


		glPushMatrix();
		glTranslatef(_xCoord, _yCoord, 0);	
		glScalef(2*_width, 1, 2*_length);
		glutSolidCube(1);
		glPopMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, old_diffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, old_ambient);
	}

};
