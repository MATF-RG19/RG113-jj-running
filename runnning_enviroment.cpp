#include "runnning_enviroment.hpp"
#include <GL/glut.h>
#include <iostream>

#include "cube3.hpp"
#include "player.hpp"
#include "skor.hpp"
#include "movingcube.hpp"
#include "switchcube.hpp"
/* Konstruktor koji pravi celo 
 * okruzenje oko igraca*/
RunningPath::RunningPath(Player* player, Skor* sk)
{
	int num_of_switch = 7;
	int num_of_move = 4;
	_player = player;
	skor = sk;
	stored_path = new PeaceOfPath*[NumOfStoredPath];
	currents = new int[NumOfVisiblePath];
	for(int i = 0; i < NumOfStoredPath-num_of_switch-num_of_move; i++)
			  stored_path[i] = new Cube3;

	for(int i = NumOfStoredPath-num_of_move-num_of_switch; 
			  i < NumOfStoredPath-num_of_move	
						 ;i++)
		stored_path[i] = new SwitchCube; 

	for(int i = NumOfStoredPath-num_of_move; i < NumOfStoredPath; i++)
		stored_path[i] = new MovingCube; 

	paths = new PeaceOfPath*[NumOfVisiblePath];
	for(int i =0; i < NumOfVisiblePath; i++)
	{
			  paths[i] = stored_path[i];
			  currents[i] = i;
	}	
	player->set_current_peace_of_path(paths[NumOfVisiblePath-2]);
}
/* Promena celog puta u 
 * zavisnosti od vremena*/
void RunningPath::advance() {
	if(_player->getZ() >= paths[NumOfVisiblePath-2]->getLength()/2) {
		reorder_new_path();
		/* Ako je igrac preso trenutni deo puta
	 	* stavlja mu se novi deo puta kao 
	 	* trenutni*/
		_player->set_current_peace_of_path(paths[NumOfVisiblePath-2]);
	} 
	else 
			  for(int i =0; i < NumOfVisiblePath; i++)
						 paths[i]->advance();
}
/* Metod crta delove puta*/
void RunningPath::make_path() const {
	glPushMatrix();
	glTranslatef(0, 0, paths[NumOfVisiblePath-1]->getLength()/2 +
						 paths[NumOfVisiblePath-2]->getLength()/2
						 );

	for(int i = NumOfVisiblePath-1; i > 0; i--) {
		paths[i]->make();
		glTranslatef(0, 0, -paths[i]->getLength()/2 -paths[i-1]->getLength()/2);
	}
	paths[0]->make();
	glPopMatrix();
}
/* Metod vraca dee puta koji
 * je igrac presao iz promenljive
 * paths u promenljivu 
 * stored_paths, i ubacuje random deo 
 * puta iz stored_paths u paths*/
void RunningPath::reorder_new_path() {
	++*skor;
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
