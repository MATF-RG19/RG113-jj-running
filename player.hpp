#ifndef _PLAYER_
#define _PLAYER_


class Player {
	int _size = 1;
	float _position_in_x_direction = 0;
	int _rotating = 0;
	float _in_air = 0;
	float _sec_in_air = 0;
	bool _on_ground = true;
	int _add= 1;
	void draw_legs() const;
	void draw_body() const;
	void draw_arms() const;
	void draw_head() const;
	void jump();
	void run();
public:
	void set_jumping();
	void draw_player() const;
	void move_on_keyboard(int);
	void advance();
};

#endif
