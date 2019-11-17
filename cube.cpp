#include <GL/glut.h>
#include "cube.hpp"


void Cube::make_cube() const {
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1);
}

void Cube::set_visible(bool visible) {
	_is_visible = visible;
}

bool Cube::is_visible() const {
	return _is_visible;
}
