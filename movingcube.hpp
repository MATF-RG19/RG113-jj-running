#include "peaceofpath.hpp"
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
class MovingCube : public PeaceOfPath {
public:
	MovingCube(){
			  _dx = 0.05;
			  _width = 1;
			  _height = 0.5;
			  _length = 2;
			  make_cubes(1);
			  init();}
	void init() override {
			  is_player_uppers[0] = false;
	}
	void advance() override{
		_xCoords[0] += _dx;
			  std::cout << "pozvan" << _xCoords[0] << std::endl;
		if(_xCoords[0] >= 2 || _xCoords[0] <= -2)_dx*=-1;
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
		glTranslatef(_xCoords[0], _yCoords[0], _zCoords[0]);	
		glScalef(2*_width, 2*_height, 2*_length);
		glutSolidCube(1);
		glPopMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, old_diffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, old_ambient);
	}

};
