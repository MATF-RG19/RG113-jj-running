#ifndef _PLAYER_
#define _PLAYER_
class Cube3;
class Player {
	Cube3* _current_cube3;
	int _index_of_current_cube = 1;
	int _size = 1;
	float _position_in_x_direction = 0;
	int _rotating = 0;
	float _in_air = 0;
	float _sec_in_air = 0;
	bool _on_ground = true;
	bool _falling = false;
	bool _falling_to_game_over = false;
	int _add= 1;
	int _initial_velocity_to_game_over = 0;
	void draw_legs() const;
	void draw_body() const;
	void draw_arms() const;
	void draw_head() const;
	void check_and_set_current_cube();
	void jump();
	void going_up();
	void run();
	void falling_to_game_over();
public:
	void set_current_cube3(Cube3* c3);
	void set_jumping();
	void draw_player() const;
	void move_on_keyboard(int);
	void advance();
};

#endif
