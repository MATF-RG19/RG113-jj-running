#include <GL/glut.h>
#include <cstdlib>
#include <time.h>
#include "cube3.hpp"
#include "player.hpp"

Cube3::Cube3() {
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

		glPopMatrix();
	}
}
#include <iostream>
bool Cube3::is_player_on_this() const {
		
	if(!(_index_of_current_cube != -1 && _visibles[_index_of_current_cube]))
		  std::cout << (_index_of_current_cube != -1) <<  " " <<  _visibles[_index_of_current_cube] <<  " razmak " << _index_of_current_cube << std::endl;;
	return _index_of_current_cube != -1 && _visibles[_index_of_current_cube];
}

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
		if(_visibles[1])index = 1;
		else if(_visibles[2])index = 2;
	}
	else if(x > -1.3 && x < -0.7)
	{
		if(_visibles[1])index = 1;
		else if(_visibles[0])index = 0;
	}

	_index_of_current_cube = index;
}
