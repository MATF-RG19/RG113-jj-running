#include "runnning_enviroment.hpp"
#include <GL/glut.h>
#include <iostream>

#include "cube3.hpp"
#include "player.hpp"
#include "movingcube.hpp"
#include "switchcube.hpp"
RunningPath::RunningPath(Player* player)
{
	_player = player;
	stored_path = new PeaceOfPath*[NumOfStoredPath];
	currents = new int[NumOfVisiblePath];
	for(int i = 0; i < NumOfStoredPath-5; i++)
			  stored_path[i] = new Cube3;
	stored_path[NumOfStoredPath-5] = new SwitchCube; 
	stored_path[NumOfStoredPath-4] = new SwitchCube; 
	stored_path[NumOfStoredPath-3] = new SwitchCube; 
	stored_path[NumOfStoredPath-2] = new MovingCube; 
	stored_path[NumOfStoredPath-1] = new MovingCube; 

	paths = new PeaceOfPath*[NumOfVisiblePath];
	for(int i =0; i < NumOfVisiblePath; i++)
	{
			  paths[i] = stored_path[i];
			  currents[i] = i;
	}	
	player->set_current_cube3(paths[NumOfVisiblePath-2]);
}
void RunningPath::advance() {
	if(_player->getZ() >= paths[NumOfVisiblePath-2]->getLength()/2) {
		reorder_new_path();
		_player->set_current_cube3(paths[NumOfVisiblePath-2]);
	} 
	else 
			  for(int i =0; i < NumOfVisiblePath; i++)
						 paths[i]->advance();
}
void RunningPath::make_path() const {
	glPushMatrix();
	glTranslatef(0, 0, paths[NumOfVisiblePath-1]->getLength()/2 +
						 paths[NumOfVisiblePath-2]->getLength()/2
						 );
//	std::cout << "ispiso " <<  paths[NumOfVisiblePath-1]->getLength() << std::endl;
	for(int i = NumOfVisiblePath-1; i > 0; i--) {
		paths[i]->make();
		glTranslatef(0, 0, -paths[i]->getLength()/2 -paths[i-1]->getLength()/2);
	}
	paths[0]->make();
	glPopMatrix();
}
void RunningPath::reorder_new_path() {
	for(int i = NumOfVisiblePath-1; i >= 1; i--) {
			  paths[i] = paths[i-1];
			  currents[i] = currents[i-1];
	}

	srand(time(NULL));
	int r = rand()%NumOfStoredPath;
	for(int i = 0; i < NumOfVisiblePath; i++)
			  if(currents[i] == r){
					r = (r+1)%NumOfStoredPath;
	 				i = 0;
			  }

	currents[0] = r;
	paths[0] = stored_path[r];
	paths[0]->init();
}
