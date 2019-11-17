#include "runnning_enviroment.hpp"
#include <GL/glut.h>
#include <iostream>

#include "cube3.hpp"
RunningPath::RunningPath() {
	paths = new Cube3*[NumOfVisiblePath];
	for(int i = 0; i < NumOfVisiblePath; i++)
			  paths[i] = new Cube3();
}
void RunningPath::advance() {
	position += 0.2;
	if(position >= RunningPath::granica)
			  reorder_new_path();
}
void RunningPath::make_path() const {
	glPushMatrix();
	glTranslatef(0, 0, position);
	for(int i = NumOfVisiblePath-1; i >= 0; i--) {
		paths[i]->make_cube3();
		glTranslatef(0, 0, -10);
	}
	glPopMatrix();
}
void RunningPath::reorder_new_path() {
	position = 12.5;

	Cube3* pom = paths[NumOfVisiblePath-1];
	for(int i = NumOfVisiblePath-1; i >= 1; i--)
			  paths[i] = paths[i-1];
	paths[0] = pom;
	paths[0]->reorder_cube3();
}
// eksperimentalno odredjena kosntanta
float RunningPath::granica = 22.5;
