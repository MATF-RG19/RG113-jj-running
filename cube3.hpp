#ifndef __CUBE3__
#define __CUBE3__
#include "peaceofpath.hpp"
#include "cube.hpp"
class Player;
class Cube3 : public PeaceOfPath{
	enum TypeOfCube3 {ORDINARY, SWITCHING, MOVING};
	TypeOfCube3 _type = ORDINARY;
		  public:
	Cube *cubes;
	float _num = 1.;
	float diffuse[4] = {1, 0, 0, 1};
	float _mv = 0;
	/*index kocke na kojoj je igrac*/
	int _index_of_current_cube = 1;
public:
	void init() override;
	Cube3();
	void make() const override;
	void advance() override;
	void check_if_player_is_on_this_and_update(Player&) override;
	bool is_player_on_this() const override;
};

#endif
