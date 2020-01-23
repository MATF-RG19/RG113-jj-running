#ifndef _POP_
#define _POP_
class Player;
class PeaceOfPath {
protected:
	int n;
	bool *is_player_uppers;
	float *_xCoords, *_yCoords, *_zCoords;
	float _dx = 0, _dz = 0, _dy = 0;
	float _width, _height, _length;
	float length_of_path = 10;
	bool check_if_player_is_on_this_X(Player&, int i);
	bool check_if_player_is_on_this_Z(Player&, int i);
	virtual void action_when_player_colide(Player& p, int i);
	void make_cubes(int n);
	bool is_player_on_ground = false;
public:
	int getLength()const { return length_of_path;}
	virtual void init() = 0;
	virtual void advance(){}
	virtual void make()const;
	void check_if_player_is_on_this_and_update(Player& p, int i);
	void check_if_player_is_on_this_and_update(Player &p);
};
#endif
