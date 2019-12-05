#include "player.hpp"
#include <GL/glut.h>
#include "cube3.hpp"
void Player::draw_legs() const { 
	glPushMatrix();
	glTranslatef(-.2, -.9, 0);
	glRotatef(_rotating, 1, 0, 0);
	glScalef(.2, .7, .4);
	glutWireCube(1);glColor3f(0, 1, 0);glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(.2, -.9, 0);
	glRotatef(-_rotating, 1, 0, 0);
	glScalef(.2, .7, .4);
	glutWireCube(1);glColor3f(0, 1, 0);glutSolidCube(1);
	glPopMatrix();
}

void Player::draw_body() const {
	glPushMatrix();
	glScalef(0.5, .7, 0.6);
	glColor3f(0, 1, 0);glutSolidCube(1);glColor3f(0, 0, 0);glutWireCube(1);
	glPopMatrix();
}
void Player::draw_arms() const {
	glPushMatrix();
	glTranslatef(0.4, 0, 0);
	glRotatef(-_rotating, 1, 0, 0);
	glScalef(0.14, .6, 0.4);
	glColor3f(0, 1, 0);glutSolidCube(1);
	
	glColor3f(0, 0, 0);
	glutWireCube(1);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-0.4, 0, 0);
	glRotatef(_rotating, 1, 0, 0);
	glScalef(0.14, .6, 0.4);
	
	glColor3f(0, 1, 0);
	glutSolidCube(1);
	
	glColor3f(0, 0, 0);
	glutWireCube(1);
	
	glPopMatrix();
}

void Player::draw_head() const { 
	glTranslatef(0, .8, 0);
	glutWireSphere(0.3, 20, 20);
}

void Player::draw_player() const {
	glTranslatef(_position_in_x_direction, _in_air, 0);
	draw_body();
	draw_arms();
	draw_legs();
	draw_head();
	glTranslatef(-_position_in_x_direction, -_in_air, 0);
}

void Player::run() {
	_rotating += 3*_add;	
	if(_rotating >= 45 || _rotating <= -45)
		_add *= -1;
}
#include <iostream>
void Player::jump() {
	_sec_in_air += 0.05;
	float pom = 7*_sec_in_air - 4.9*_sec_in_air*_sec_in_air;
	if(_in_air >= pom)
			  _falling = true;
	_in_air = pom;
	if(_in_air <= 0) {
		_on_ground = !(_sec_in_air = _in_air = _falling = 0);
		if(!_current_cube3->is_visible(_index_of_current_cube)) {
			_falling_to_game_over = true;
			_initial_velocity_to_game_over = -7;
		}
	}
}

void Player::advance() {
	if(_falling_to_game_over)
			 return falling_to_game_over();
	if(!_on_ground)
			  jump();
	else if(!_current_cube3->is_visible(_index_of_current_cube)){
			_falling_to_game_over = true;
			_initial_velocity_to_game_over = 0;
	}
	run();
}
void Player::set_jumping() {
	_on_ground = false;
}

void Player::move_on_keyboard(int c) {
	if(_falling_to_game_over)
			  return;
	if(c == GLUT_KEY_LEFT)
		  _position_in_x_direction-=.1;
	else if(c == GLUT_KEY_RIGHT)
		  _position_in_x_direction+=.1;	  
	check_and_set_current_cube();
}

void Player::set_current_cube3(Cube3* c3) {
		  _current_cube3 = c3;
		  std::cout << _current_cube3->is_visible(0) <<  _current_cube3->is_visible(1) << _current_cube3->is_visible(2) << std::endl;;
}

void Player::check_and_set_current_cube() {
	if(_position_in_x_direction <= 0.7 && _position_in_x_direction >= -0.7)
	{			  std::cout << "skroz na srednjem" << std::endl;
			_index_of_current_cube = 1;	
	}
	else if(_position_in_x_direction >= 1.3 && _position_in_x_direction <= 2.7) {
		std::cout << "skroz na desnom" << std::endl;
		_index_of_current_cube = 2;
	}
	else if(_position_in_x_direction <= -1.3 && _position_in_x_direction >=  -2.7) {
			std::cout << "skroz na levom" << std::endl;
			_index_of_current_cube = 0;
	}
	else if(_position_in_x_direction >= 3) 
			  std::cout << "krece da pada desno" << std::endl;
	else if(_position_in_x_direction >= 3.3)
			  std::cout << "ispo desno " << std::endl;
	else if(_position_in_x_direction <= -3) 
			  std::cout << "krece da pada levo" << std::endl;
	else if(_position_in_x_direction <= -3.3)
			  std::cout << "ispo levo" << std::endl;
	else if(_position_in_x_direction > .7 && _position_in_x_direction <1.3)
			  std::cout << "izmedj srednjeg i desnog" << std::endl;
	else if(_position_in_x_direction > -1.3 && _position_in_x_direction < 0.7)
			  std::cout << "izmedj srednjeg i levog" << std::endl;
}

void Player::falling_to_game_over() {
	_sec_in_air += .05;
	_in_air = _initial_velocity_to_game_over*_sec_in_air - 4.9*_sec_in_air*_sec_in_air;
}
