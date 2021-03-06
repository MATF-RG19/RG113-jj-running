#ifndef _PLAYER_
#define _PLAYER_
#include "peaceofpath.hpp"
#include <iostream>
#include <utility>
#include "skor.hpp"
class Player {
	friend class PeaceOfPath;
	friend class MovingCube;
	enum TypeOfMovement {UNKNOWN, ON_GROUND, JUMPING, FALLING, SLOW_FALLING};
	/*Igrac je postavljen da u pocetku pada*/
	TypeOfMovement _movement = FALLING;
	PeaceOfPath* current_peace_of_path;
	Skor* skor;
	float _position_in_x_direction = 0;
	float _position_in_y_direction = 20;
	float _position_in_z_direction = 0;
	float _dx = 0, _dy = 0, _dz = 0;
	int _rotating = 0;
	float _in_air = 1.7;
	float _sec_in_air = 0;
	float _dh = 0.05;
	int _add= 1;
	int _initial_velocity_in_y_dirr = 0;
	int _rotate_hends_when_falling = 0;
	void draw_legs() const;
	void draw_body() const;
	void draw_arms() const;
	void draw_head() const;
	void run();
	void calculate_move_in_Ydir();
	void set_jumping(float velocity = 8);
	void set_y_position(float y) { _position_in_y_direction = y + 1.25;}
	void set_falling();
	std::pair<float, float> getXfeet() const{
		return {_position_in_x_direction - 0.35, _position_in_x_direction + 0.35};
	}
	std::pair<float, float> getZfeet() const{
		return {_position_in_z_direction - 0.2, _position_in_z_direction + 0.2};
	}
	void set_on_ground();
public:
	Player(Skor* s) : skor(s){}
	void addY(){_position_in_y_direction += 10;}
	void set_current_peace_of_path(PeaceOfPath* c3);
	float getX()const { return _position_in_x_direction;}
	float getYfeet()const { return _position_in_y_direction - 1.25;}
	float getZ()const {return _position_in_z_direction;}
	Skor* get_skor() const {
		return skor;
	}
	void draw_player() const;
	void move_on_keyboard(int);
	void advance();
};

#endif
