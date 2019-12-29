#include "player.hpp"
#include "peaceofpath.hpp"
/*treba dodati.....*/
bool PeaceOfPath::check_if_player_is_on_this_X(Player& p) {
	auto x_feets = p.getXfeet();
	 return !(x_feets.second < _xCoord - _width || x_feets.first > _xCoord + _width);
}

bool PeaceOfPath::check_if_player_is_on_this_Z(Player& p) {
	auto z_feets = p.getZfeet();
	 return !(z_feets.second < _zCoord - _length|| z_feets.first > _zCoord + _length);
}
/*Proverava dali je igrac na postolju tako
 *ako jeste onda ne radi nista ako nije 
 *stavi ga da pada*/
void PeaceOfPath::check_if_player_is_on_this_and_update(Player& p) {
		  std::cout << "uso" << std::endl;
	float y = p.getYfeet();
	if(p._falling) {
		  std::cout << "1" << std::endl;
		/*ako igrac vec pada proverava dali je po y koord.
		 *veci od trenutnog postolja*/ 
		if(y - 0.05 > _yCoord + _height){
		  std::cout << "2" << std::endl;
			is_player_upper = true;			  
			return;
		}
		bool pom  = check_if_player_is_on_this_X(p) && check_if_player_is_on_this_Z(p);
		if(pom && is_player_upper){
		  std::cout << "3" << std::endl;
		/*ako je manji od trenutnog postolja
		 * provera dali je po x koord. na postolju
		 * i ako je u prethodnoj iteraciji bio
		 * iznad postolja vraca se na postolje*/
			p.set_y_position(_yCoord + _height);
			p.set_on_ground();
			p._dx = _dx;
		}
		is_player_upper = false;
		  std::cout << "4" << std::endl;
	}
	else if(!p._jumping){
			  /*igrac ne pada ni ne skace, znaci u prethodnoj
				* iteraciji je bio na postolju
				* treba proveriti dali je izgubio postolje*/
		  std::cout << "5" << std::endl;
		bool pom  = check_if_player_is_on_this_X(p) && check_if_player_is_on_this_Z(p);
		if(y - 0.05 > _yCoord + _height){
		  std::cout << "6" << std::endl;
			is_player_upper = true;			  
			p.set_falling();	
		}
		else if(y + 0.05 < _yCoord + _height || !pom) {
		  std::cout << "7" << std::endl;
			is_player_upper = false;
			p.set_falling();
		}
		else {
		  std::cout << "8" << std::endl;
			p._dx = _dx;

		}
	}
}
