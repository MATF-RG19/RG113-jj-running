#include "player.hpp"
#include "peaceofpath.hpp"
#include <GL/glut.h>
/* Metod provera dali je igrac
 * na postolju po x kordinati.
 */
bool PeaceOfPath::check_if_player_is_on_this_X(Player& p, int i) {
	auto x_feets = p.getXfeet();
	 return !(x_feets.second < _xCoords[i] - _width || x_feets.first > _xCoords[i] + _width);
}
/* Metod provera dali je igrac
 * na postolju po z kordinati.
 */
bool PeaceOfPath::check_if_player_is_on_this_Z(Player& p, int i) {
	auto z_feets = p.getZfeet();
	 return !(z_feets.second < _zCoords[i] - _length|| z_feets.first > _zCoords[i] + _length);
}
/* Proverava dali je igrac na kocki sa 
 * indeksom i i ako jeste stavi ga na 
 * tu kocku, ako nije ne radi nista*/ 
void PeaceOfPath::check_if_player_is_on_this_and_update(Player& p, int i) {
	float y = p.getYfeet();
	if(p._movement == Player::TypeOfMovement::FALLING 
	|| p._movement == Player::TypeOfMovement::SLOW_FALLING) {
		/*ako igrac vec pada proverava dali je po y koord.
		 *veci od trenutnog postolja*/ 
		if(y - 0.05 > _yCoords[i] + _height){
			is_player_uppers[i] = true;			  
			return;
		}
			  bool pom1, pom2;
		bool pom  = (pom1 =check_if_player_is_on_this_X(p, i)) && (pom2 = check_if_player_is_on_this_Z(p, i));
		if(pom && is_player_uppers[i]){
		/*ako je manji od trenutnog postolja
		 * provera dali je po x koord. na postolju
		 * i ako je u prethodnoj iteraciji bio
		 * iznad postolja vraca se na postolje*/
			p.set_y_position(_yCoords[i] + _height);
			p.set_on_ground();
			action_when_player_colide(p, i);
			is_player_on_ground = true;
		}
		is_player_uppers[i] = false;
	}
	else if(p._movement != Player::TypeOfMovement::JUMPING){
			  /*igrac ne pada ni ne skace, znaci u prethodnoj
				* iteraciji je bio na postolju
				* treba proveriti dali je izgubio postolje*/
		bool pom  = check_if_player_is_on_this_X(p, i) && check_if_player_is_on_this_Z(p, i);
		if(y - 0.05 > _yCoords[i] + _height){
			is_player_uppers[i] = true;			  
		}
		else if(y + 0.05 < _yCoords[i] + _height || !pom) {
			is_player_uppers[i] = false;
		}
		else {
			p.set_on_ground();
			action_when_player_colide(p, i);
			is_player_on_ground = true;
			is_player_uppers[i] = false;
		}
	}
}
/* Proverava dali je igrac na postolju(niz kocki)
 * ako jeste stavlja ga na to postolje,
 * a ako nije ne radi nista*/
void PeaceOfPath::check_if_player_is_on_this_and_update(Player &p) {
	is_player_on_ground = false;
	/* prolazi se kroz sve kocke
	 * da se vidi dali je igrac 
	 * na nekoj*/
	for(int i = 0; i < n; i++) {
		check_if_player_is_on_this_and_update(p, i);
	}
	if(!is_player_on_ground && p._movement != Player::TypeOfMovement::FALLING && p._movement != Player::TypeOfMovement::SLOW_FALLING 
  && p._movement != Player::TypeOfMovement::JUMPING
						 )
			  p.set_falling();
}
/*vrsi se inicijalizacija, koliko je potrebno kocki*/
void PeaceOfPath::make_cubes(int num) {
	_xCoords = new float[num];
	_yCoords = new float[num];
	_zCoords = new float[num];
	is_player_uppers = new bool[num];
	for(int i =0;i  < num; i++)
		_xCoords[i] = _yCoords[i] = _zCoords[i] = 0;
	n = num;
}
/* Kad igrac stane na kocku, 
 * kako ce kocka uticati na 
 * njegovo kretanje.*/
void PeaceOfPath::action_when_player_colide(Player &p, int i) {
		 p.get_skor()->make_potential_real();
}
/*Metod crta kocke*/
void PeaceOfPath::make() const {
		for(int i = 0; i < n; i++) {
		glPushMatrix();
		glTranslatef(_xCoords[i], _yCoords[i], _zCoords[i]);
		glScalef(2*_width, 2*_height, 2*_length);
		glutSolidCube(1);
		glutWireCube(1);
		glDisable(GL_LIGHTING);

		if(is_player_uppers[i])
				  glColor3f(0, 1, 0);
		else 
				  glColor3f(0, 0, 0);
		glBegin(GL_POINTS);
		glVertex3f(0,.5, 0);
		glEnd();
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}
}
/*Metod inicijalizuje deo puta*/
void PeaceOfPath::init() {
	/* Inicijalno se stavlja
	 * da je igrac ispod svake 
	 * kocke*/
	for(int i = 0; i < n; i++)
			  is_player_uppers[i] = false;

}
