#include "runnning_enviroment.hpp"
#include <GL/glut.h>
#include <iostream>

#include "cube3.hpp"
#include "player.hpp"
#include "movingcube.hpp"
RunningPath::RunningPath(Player* player) {
	_player = player;
	paths = new PeaceOfPath*[NumOfVisiblePath];
	for(int i =1; i < NumOfVisiblePath; i++)
			  paths[i] = new Cube3;
	paths[0] = new MovingCube;
	player->set_current_cube3(paths[NumOfVisiblePath-2]);
}
void RunningPath::advance() {
		  
	if(_player->getZ() >= paths[NumOfVisiblePath-1]->getLength()/2) {
		reorder_new_path();
		_player->set_current_cube3(paths[NumOfVisiblePath-2]);
	} 
	else 
			  for(int i =0; i < NumOfVisiblePath; i++)
						 paths[i]->advance();
}
void RunningPath::make_path() const {
	glPushMatrix();
	glTranslatef(0, 0, paths[NumOfVisiblePath-1]->getLength());
	for(int i = NumOfVisiblePath-1; i >= 0; i--) {
		paths[i]->make();
		glTranslatef(0, 0, -10);
	}
	glPopMatrix();
}
void RunningPath::reorder_new_path() {
	position = 12.5;
	_should_change = true;
	PeaceOfPath* pom = paths[NumOfVisiblePath-1];
	for(int i = NumOfVisiblePath-1; i >= 1; i--)
			  paths[i] = paths[i-1];
	paths[0] = pom;
	paths[0]->init();
}
