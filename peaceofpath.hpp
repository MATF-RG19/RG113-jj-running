#ifndef _POP_
#define _POP_
class Player;
class PeaceOfPath {
protected:
	int n;
	bool *is_player_uppers;
	float *_xCoords, *_yCoords, *_zCoords;
	float _yCoord, _xCoord, _zCoord;
	float _dx, _dz, _dy;
	float _width, _height, _length;
	virtual bool check_if_player_is_on_this_X(Player&, int i);
	virtual bool check_if_player_is_on_this_Z(Player&, int i);
	bool is_player_on_ground = false;
	int length = 10;
public:
	int getLength()const { return length;}
	virtual void init() = 0;
	virtual void advance(){}
	virtual void make()const = 0;
	void check_if_player_is_on_this_and_update(Player& p, int i);
	void check_if_player_is_on_this_and_update(Player &p);
};

#endif
