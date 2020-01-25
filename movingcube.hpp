#include "peaceofpath.hpp"
#include "player.hpp"
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
int k = 11;
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
					_yCoords[i] = -50;
					start += 9; 
			  }
			  init();
	}
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
		float diffuse[4] = {1, 0, 0, 1};	
		float old_diffuse[4];
		float old_ambient[4];
		glGetMaterialfv(GL_FRONT, GL_DIFFUSE, old_diffuse);
		glGetMaterialfv(GL_FRONT,GL_AMBIENT, old_ambient);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse);

		PeaceOfPath::make();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, old_diffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, old_ambient);
	}
	void action_when_player_colide(Player& p, int i) override{
		PeaceOfPath::action_when_player_colide(p, i);
		if(i == n-1)
			p.set_jumping(50);
	}
};
