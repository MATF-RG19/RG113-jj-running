#include "peaceofpath.hpp"
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>

class MovingCube : public PeaceOfPath {
		  float add = 0.05;
public:
	MovingCube(){init();}
	void init() override {
		_xCoord = 0;
		_width = 1;
		_height = 0.45;
		is_player_upper = false;
		srand(time(NULL));

		_yCoord = rand()%7 - 3;
	}
	void advance() override{
		_xCoord += add;
		if(_xCoord >= 2 || _xCoord <= -2)add*=-1;
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
		glScalef(2*_width, 1, 10);
		glutSolidCube(1);
		glPopMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, old_diffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, old_ambient);
	}

};
