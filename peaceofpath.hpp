#ifndef _POP_
#define _POP_
class Player;
class PeaceOfPath {
protected:
	float _yCoord, _xCoord, _zCoord;
	float _dx, _dz, _dy;
	float _width, _height, _length;
	virtual bool check_if_player_is_on_this_X(Player&);
	virtual bool check_if_player_is_on_this_Z(Player&);
	bool is_player_upper = false;
	int length = 10;
public:
	int getLength()const { return length;}
	virtual void init() = 0;
	virtual void advance() = 0;
	virtual void make()const = 0;
	virtual void check_if_player_is_on_this_and_update(Player& p);
};

#endif
