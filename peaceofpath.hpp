#ifndef _POP_
#define _POP_
class Player;
#include <iostream>
class PeaceOfPath {
protected:
	float _yCoord, _xCoord;
	float _width, _height;
	virtual bool check_if_player_is_on_this_X(Player&);
	bool is_player_upper = false;
	int length = 10;
public:
	int getLength()const {std::cout << length << " poslo" << std::endl; return length;}
	virtual void init() = 0;
	virtual void advance() = 0;
	virtual void make()const = 0;
	virtual void check_if_player_is_on_this_and_update(Player& p);
};

#endif
