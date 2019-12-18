#ifndef __CUBE3__
#define __CUBE3__
#include "peaceofpath.hpp"
class Player;
class Cube3 : public PeaceOfPath{
	enum TypeOfCube3 {ORDINARY, SWITCHING, MOVING};
	TypeOfCube3 _type = ORDINARY;
		  public:
	bool _visibles[3] = {true, true, true};
	float _num = 1.;
	float diffuse[4] = {1, 0, 0, 1};
	float _mv = 0;
	/*index kocke na kojoj je igrac*/
	int _index_of_current_cube = 1;
	bool check_if_player_is_on_this_X(Player&) override;
public:
	void init() override;
	Cube3();
	void make() const override;
	void advance() override;
};

#endif
