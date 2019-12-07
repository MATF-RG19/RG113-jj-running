#include <GL/glut.h>
#include <cstdlib>
#include <time.h>
#include "cube.hpp"
#include "cube3.hpp"
#include "player.hpp"

Cube3::Cube3() : cubes(new Cube[3]) {
}

void Cube3::make_cube3() const {
	for(int i = 0; i < 3; i++) {
		if(!cubes[i].is_visible())
			  continue;
		glPushMatrix();
		glColor3f(_num, 0, 0);
		glTranslatef(-2+i*2, 0, 0);
		glScalef(2, 1, 10);

		cubes[i].make_cube();

		glPopMatrix();
	}
}

bool Cube3::is_visible(int n) {
	return cubes[n].is_visible();
	return true;
}

void Cube3::reorder_cube3() {
	bool visibles[3];
	srand(time(NULL));
	_type = ORDINARY;
	switch(rand()%8) {
		case 0: 
			visibles[2] = visibles[1] = !(visibles[0] = true);
			_type = SWITCHING;
			break;
		case 1:
			visibles[2] = visibles[0] = !(visibles[1] = true);
			_type = SWITCHING;
			break;
		case 2:
			visibles[1] = visibles[0] = !(visibles[2] = true);
			_type = SWITCHING;
			break;
		case 3: 
			visibles[2] = visibles[1] = !(visibles[0] = false);
			break;
		case 4:
			visibles[2] = visibles[0] = !(visibles[1] = false);
			break;
		case 5:
			visibles[1] = visibles[0] = !(visibles[2] = false);
			break;
		case 6:
			visibles[1] = visibles[0] = visibles[2] = true;
			break;
		case 7:
			visibles[2] = visibles[1] = !(visibles[0] = true);
			_type = MOVING;
	}

	for(int i =0; i < 3; i++)
			  cubes[i].set_visible(visibles[i]);
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
				if(cubes[i].is_visible()) {
					cubes[(i+1)%3].set_visible(true);
					cubes[i].set_visible(false);
					break;
				}
		}
	}
	else if(_type == MOVING) {
	}
}
#include <iostream>
void Cube3::check_on_what_cube_is_player(Player &p) const{
	float x = p.getX();
	int index = -1;
	if(x <= 0.7 && x >= -0.7)
	{			  
			std::cout << "skroz na srednjem" << std::endl;
			index = 1;	
	}
	else if(x >= 1.3 && x <= 2.7) 
	{
			std::cout << "skroz na desnom" << std::endl;
			index = 2;
									
	}
	else if(x <= -1.3 && x >=  -2.7) 
	{
			std::cout << "skroz na levom" << std::endl;
			index = 0;
	}
	else if(x >= 3) 
			std::cout << "krece da pada desno" << std::endl;
	else if(x >= 3.3)
			std::cout << "ispo desno " << std::endl;
	else if(x <= -3) 
			std::cout << "krece da pada levo" << std::endl;
	else if(x <= -3.3)
			std::cout << "ispo levo" << std::endl;
	else if(x > .7 && x <1.3)
			std::cout << "izmedj srednjeg i desnog" << std::endl;
	else if(x > -1.3 && x < 0.7)
			std::cout << "izmedj srednjeg i levog" << std::endl;
	if(index != -1)
		p.set_current_cube(index);
}
