#include <GL/glut.h>
#include <cstdlib>
#include <time.h>
#include "cube.hpp"
#include "cube3.hpp"
#include "player.hpp"

Cube3::Cube3() : cubes(new Cube[3]) {
}

void Cube3::make() const {
	float diffuse[4] = {0, 0, 0, 1};
	if(_type == ORDINARY)
			  diffuse[0] = 1;
	else if(_type == SWITCHING)
			  diffuse[2] = _num;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	for(int i = 0; i < 3; i++) {
		if(!cubes[i].is_visible())
			  continue;
		glPushMatrix();
		glTranslatef(-2+i*2, 0, 0);
		glScalef(2, 1, 10);

		cubes[i].make_cube();

		glPopMatrix();
	}
}
#include <iostream>
bool Cube3::is_player_on_this() const {
		
	if(!(_index_of_current_cube != -1 && cubes[_index_of_current_cube].is_visible()))
		  std::cout << (_index_of_current_cube != -1) <<  " " <<  cubes[_index_of_current_cube].is_visible() <<  " razmak " << _index_of_current_cube << std::endl;;
	return _index_of_current_cube != -1 && cubes[_index_of_current_cube].is_visible();
}

void Cube3::init() {
	bool visibles[3];
	srand(time(NULL));
	_type = ORDINARY;
	switch(rand()%7) {
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
void Cube3::check_if_player_is_on_this_and_update(Player &p) {
	float x = p.getX();
	int index = -1;
	if(x <= 0.7 && x >= -0.7)
	{			  
		//	std::cout << "skroz na srednjem" << std::endl;
			index = 1;	
	}
	else if(x >= 1.3 && x <= 2.7) 
	{
		//	std::cout << "skroz na desnom" << std::endl;
			index = 2;
									
	}
	else if(x <= -1.3 && x >=  -2.7) 
	{
		//	std::cout << "skroz na levom" << std::endl;
			index = 0;
	}
	else if(x >= 3.3)
			  index = -1;
	else if(x <= -3.3)
			  index = -1;
	else if(x > .7 && x <1.3)
	{
		if(cubes[1].is_visible())index = 1;
		else if(cubes[2].is_visible())index = 2;
	}
	else if(x > -1.3 && x < -0.7)
	{
		if(cubes[1].is_visible())index = 1;
		else if(cubes[0].is_visible())index = 0;
	}

	_index_of_current_cube = index;
}
