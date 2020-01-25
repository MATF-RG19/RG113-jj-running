#include <GL/glut.h>
#include <cstdlib>
#include <time.h>
#include "cube3.hpp"
#include "player.hpp"

/* Konsturktor pravi maksimalni 
 * broj potrebnih kocki.*/
Cube3::Cube3() {
		  _length = 5;
		  _height = .45;
		  _width = 1;
		  n = 2;
		  _xCoords = new float[2];
		  _zCoords = new float[2];
		  _yCoords = new float[2];
		  is_player_uppers = new bool[2];
		  init();
}
/* Metod make crta put*/ 
void Cube3::make() const {
	/*Stavlja se zeljena boja*/
	float diffuse[4] = {1, 0, 0, 1};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	/*Zove se metod iz nasledjene klase
	 *da nacrta kocke sa prethodno
	 *postavljenom bojom*/
	PeaceOfPath::make();
}

void Cube3::init() {
	srand(time(NULL));
	/*Random se generise broj kocki
	 *i njihov raspored*/
	switch(rand()%6) {
		case 0: 
			_xCoords[0] = -2;
			n = 1;
			break;
		case 1:
			_xCoords[0] = 0;
			n = 1;
			break;
		case 2:
			_xCoords[0] = 2;
			n = 1;
			break;
		case 3:
			_xCoords[0] = -2;
			_xCoords[1] = 2;
			n = 2;
			break;
		case 4:
			_xCoords[0] = -2;
			_xCoords[1] = 0;
			n = 2;
			break;
		case 5:
			_xCoords[0] = 2;
			_xCoords[1] = 0;
			n = 2;
			break;
	}
	PeaceOfPath::init();
}
