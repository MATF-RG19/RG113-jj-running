#ifndef _POP_
#define _POP_
class Player;
class PeaceOfPath {
public:
	virtual void init() = 0;
	virtual void advance() = 0;
	virtual void make()const = 0;
	virtual void check_if_player_is_on_this_and_update(Player& p) = 0;
	virtual bool is_player_on_this()const = 0;
};

#endif
