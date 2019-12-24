#include "player.hpp"
#include "peaceofpath.hpp"
/*treba dodati.....*/
bool PeaceOfPath::check_if_player_is_on_this_X(Player& p) {
	auto x_feets = p.getXfeet();
	 return !(x_feets.second < _xCoord - _width || x_feets.first > _xCoord + _width);
}
/*Proverava dali je igrac na postolju tako
 *ako jeste onda ne radi nista ako nije 
 *stavi ga da pada*/
void PeaceOfPath::check_if_player_is_on_this_and_update(Player& p) {
	float y = p.getYfeet();
	if(p.isFalling()) {
		/*ako igrac vec pada proverava dali je po y koord.
		 *veci od trenutnog postolja*/ 
		if(y - 0.05 > _yCoord + _height){
			is_player_upper = true;			  
			return;
		}
		bool pom  = check_if_player_is_on_this_X(p);
		if(pom && is_player_upper){
		/*ako je manji od trenutnog postolja
		 * provera dali je po x koord. na postolju
		 * i ako je u prethodnoj iteraciji bio
		 * iznad postolja vraca se na postolje*/
			p.set_y_position(_yCoord + _height);
			p.set_on_ground();
			is_player_upper = false;
		}
	}
	else if(!p.isJumping()) {
			  /*igrac ne pada ni ne skace, znaci u prethodnoj
				* iteraciji je bio na postolju
				* treba proveriti dali je izgubio postolje*/
		if(y - 0.05 > _yCoord + _height){
			is_player_upper = true;			  
			p.set_falling();	
		}
		else if(y + 0.05 < _yCoord + _height || !check_if_player_is_on_this_X(p)) {
			is_player_upper = false;
			p.set_falling();
		}

	}
}
