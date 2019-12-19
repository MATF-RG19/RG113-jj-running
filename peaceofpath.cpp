#include "player.hpp"
#include "peaceofpath.hpp"
/*treba dodati.....*/
bool PeaceOfPath::check_if_player_is_on_this_X(Player& p) {
	return true;
}
/*Proverava dali je igrac na postolju tako
 *ako jeste onda ne radi nista ako nije 
 *stavi ga da pada*/
void PeaceOfPath::check_if_player_is_on_this_and_update(Player& p) {
	float y = p.getYfeet();
	/* ako je pozicija igraca iznad postolja 
	 * igrac treba i dalje da se ponasa kao i do sada
	 * tj. da nastavi da pada i ne treba da se proverava
	 * dali je po x i z koord. na postlju*/
	if(y - 0.05 > _yCoord){
		is_player_upper = true;			  
		return;
	}
	/* ako je program doso ovde igrac je ispod postolja.
	 * prvi put kad je igrac ispod postolja po y kordinati
	 * proverava se dali je on na njemu po x kordinati
	 * i ako jeste vraca se na postolje, ovo vracanje se radi
	 * samo prvi put kad je igrac ispod postolja*/
	bool pom  = !check_if_player_is_on_this_X(p);
	bool pom1 = p.isFalling();
	if(pom && !pom1)
	{
			  /*igrac nije na postolju po x kordinati ali pre
				* toga nije padao*/
	  		  p.set_falling();
			  is_player_upper = false;
	}
	else if(pom && pom1)
	{
			  /*igrac nije na postolju po x kordinati i pre
				* toga je padao*/
			  is_player_upper = false;
	}
	else  if(is_player_upper)
	{
			  /*igrac je na postolju po x koord., vraca se na postolje*/
						 p.set_y_position(_yCoord);
			  			 p.set_on_ground();
	}
}
