#include "runnning_enviroment.hpp"
#include <GL/glut.h>
#include <iostream>

#include "cube3.hpp"
#include "player.hpp"
RunningPath::RunningPath(Player* player) {
	_player = player;
	paths = new PeaceOfPath*[NumOfVisiblePath];
	for(int i =0; i < NumOfVisiblePath; i++)
			  paths[i] = new Cube3;
	for(int i = 0; i < NumOfVisiblePath; i++)
			  paths[i] = new Cube3();
	player->set_current_cube3(paths[NumOfVisiblePath-2]);
}
void RunningPath::advance() {
	position += 0.2;
	if(position >= RunningPath::granica)
			  reorder_new_path();
	else if(position >= 20.7 && _should_change) {
		_should_change = false;
		_player->set_current_cube3(paths[NumOfVisiblePath-3]);
		Cube3* c = (Cube3*)paths[NumOfVisiblePath-3];
	} 
	else 
			  for(int i =0; i < NumOfVisiblePath; i++)
						 paths[i]->advance();
}
void RunningPath::make_path() const {
	glPushMatrix();
	glTranslatef(0, 0, position);
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
// eksperimentalno odredjena kosntanta
float RunningPath::granica = 22.5;
