#include "peaceofpath.hpp"
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
int k = 5;
class MovingCube : public PeaceOfPath {
public:
	MovingCube(){
			  _dx = 0.05;
			  _width = 1;
			  _height = 0.5;
			  _length = 2;
			  make_cubes(k);
			  length_of_path = 9*k+1;
			  float start = -(length_of_path)/2 + 5;
			  for(int i = 0; i < k; i++) {
					_zCoords[i] = start;
					std::cout << start << "st " << std::endl;
					start += 9; 
			  }
			  init();}
	void init() override {
			  for(int i = 0; i < k; i++)
			  		is_player_uppers[i] = false;
	}
	void advance() override{
		for(int i =0, sign = 1;i  < k; i++, sign*=-1)
			_xCoords[i] += sign*_dx;

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

		for(int i= 0;i < k; i++){
		glPushMatrix();
		glTranslatef(_xCoords[i], _yCoords[i], _zCoords[i]);	
		glScalef(2*_width, 2*_height, 2*_length);
		glutSolidCube(1);
		glPopMatrix();
		}
		glMaterialfv(GL_FRONT, GL_DIFFUSE, old_diffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, old_ambient);
	}

};
