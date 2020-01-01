#include "player.hpp"
#include "peaceofpath.hpp"
/*treba dodati.....*/
bool PeaceOfPath::check_if_player_is_on_this_X(Player& p, int i) {
	auto x_feets = p.getXfeet();
	 return !(x_feets.second < _xCoords[i] - _width || x_feets.first > _xCoords[i] + _width);
}

bool PeaceOfPath::check_if_player_is_on_this_Z(Player& p, int i) {
	auto z_feets = p.getZfeet();
	 return !(z_feets.second < _zCoords[i] - _length|| z_feets.first > _zCoords[i] + _length);
}
/*Proverava dali je igrac na postolju tako
 *ako jeste onda ne radi nista ako nije 
 *stavi ga da pada*/
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
			p._dx = _dx;
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
			p._dx = _dx;
			is_player_on_ground = true;
			is_player_uppers[i] = false;
		}
	}
}
void PeaceOfPath::check_if_player_is_on_this_and_update(Player &p) {
	is_player_on_ground = false;
	for(int i = 0; i < n; i++) {
		check_if_player_is_on_this_and_update(p, i);
	}
	if(!is_player_on_ground && p._movement != Player::TypeOfMovement::FALLING && p._movement != Player::TypeOfMovement::SLOW_FALLING)
			  p.set_falling();
}
void PeaceOfPath::make_cubes(int num) {
	_xCoords = new float[num];
	_yCoords = new float[num];
	_zCoords = new float[num];
	is_player_uppers = new bool[num];
	for(int i =0;i  < num; i++)
		_xCoords[i] = _yCoords[i] = _zCoords[i] = 0;
	n = num;
}
