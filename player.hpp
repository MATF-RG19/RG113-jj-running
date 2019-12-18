#ifndef _PLAYER_
#define _PLAYER_
#include "peaceofpath.hpp"
#include <iostream>
class Player {
	PeaceOfPath* _current_cube3;
	float _position_in_x_direction = 0;
	float _position_in_y_direction = 1.7;
	int _rotating = 0;
	float _in_air = 1.7;
	float _sec_in_air = 0;
	bool _jumping = false;
	bool _falling = false;
	bool _falling_to_game_over = false;
	int _add= 1;
	int _initial_velocity_in_y_dirr = 0;
	int _rotate_hends_when_falling = 0;
	void draw_legs() const;
	void draw_body() const;
	void draw_arms() const;
	void draw_head() const;
	void jump();
	void run();
	void falling_to_game_over();
	void calculate_move_in_Ydir();
public:
	void set_y_position(float y) { _position_in_y_direction = y + 1.25;}
	bool isFalling() {return _falling;}
	void set_falling();
	void set_on_ground();
	bool isInTheAir() const {return _falling || _jumping;}
	void set_current_cube3(PeaceOfPath* c3);
	float getX()const { return _position_in_x_direction;}
	float getYfeet()const { return _position_in_y_direction - 1.25;}
	void set_jumping();
	void draw_player() const;
	void move_on_keyboard(int);
	void advance();
};

#endif
