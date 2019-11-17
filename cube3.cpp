#include <GL/glut.h>
#include <cstdlib>
#include <time.h>
#include "cube.hpp"
#include "cube3.hpp"

Cube3::Cube3() : cubes(new Cube[3]) {
}

void Cube3::make_cube3() const {
	for(int i = 0; i < 3; i++) {
		if(!cubes[i].is_visible())
			  continue;
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(-2+i*2, 0, 0);
		glScalef(2, 1, 10);

		cubes[i].make_cube();

		glPopMatrix();
	}
}

void Cube3::set_visible(bool visible[3]) {
	for(int i =0; i < 3; i++)
			  cubes[i].set_visible(visible[i]);
}
bool Cube3::is_visible(int n) {
	return cubes[n].is_visible();
	return true;
}

void Cube3::reorder_cube3() {
	bool visibles[3];
	srand(time(NULL));
	switch(rand()%7) {
		case 0: 
			visibles[2] = visibles[1] = !(visibles[0] = true);
			break;
		case 1:
			visibles[2] = visibles[0] = !(visibles[1] = true);
			break;
		case 2:
			visibles[1] = visibles[0] = !(visibles[2] = true);
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
	set_visible(visibles);
}
