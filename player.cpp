#include "player.hpp"
#include <GL/glut.h>
#include "cube3.hpp"
void Player::draw_legs() const { 
	glPushMatrix();
	if(!_slow_falling)
	{
		glTranslatef(-.2, -.9, 0);
		glRotatef(_rotating, 1, 0, 0);
	}
	else
	{
		glTranslatef(0, -.6, 0);
		glRotatef(3*_rotate_hends_when_falling, 0, 1, 0);
		glTranslatef(-0.248, -0.248, 0);
		glRotatef(-45, 0, 0, 1);
	}
	glScalef(.2, .7, .4);
	glutWireCube(1);glColor3f(0, 1, 0);glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	if(!_slow_falling)
	{
		glTranslatef(.2, -.9, 0);
		glRotatef(-_rotating, 1, 0, 0);
	}
	else
	{
		glTranslatef(0, -.6, 0);
		glRotatef(3*_rotate_hends_when_falling, 0, 1, 0);
		glTranslatef(0.248, -0.248, 0);
		glRotatef(45, 0, 0, 1);
	}
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
	if(_falling)
			  glRotatef(_rotate_hends_when_falling, 0, 0, 1);
	else
		glRotatef(-_rotating, 1, 0, 0);
	glScalef(0.14, .6, 0.4);
	glColor3f(0, 1, 0);glutSolidCube(1);
	
	glColor3f(0, 0, 0);
	glutWireCube(1);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-0.4, 0, 0);

	if(_falling) {
			  glRotatef(-_rotate_hends_when_falling, 0, 0, 1);
	}
	else
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
	glutSolidSphere(0.3, 20, 20);
}

void Player::draw_player() const {
//	glTranslatef(0, _position_in_y_direction, 0);
	glTranslatef(_position_in_x_direction, _position_in_y_direction, 0);
	float ambient_diffuse[] = {1, 1, 0, 1};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambient_diffuse);
	draw_body();
	draw_arms();
	draw_legs();
	draw_head();
	ambient_diffuse[0] = ambient_diffuse[1] = ambient_diffuse[2] = .2;
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_diffuse);
	glTranslatef(-_position_in_x_direction, -_position_in_y_direction, 0);
//	glTranslatef(0, -_position_in_y_direction, 0);
}

void Player::run() {
	_rotating += 3*_add;	
	if(_rotating >= 45 || _rotating <= -45)
		_add *= -1;
}
#include <iostream>
void Player::calculate_move_in_Ydir() {
	_sec_in_air += 0.05;
	float pom = _position_in_y_direction 
			  +_initial_velocity_in_y_dirr*_dh-9.8*(_sec_in_air-0.05)*_dh-4.9*_dh*_dh;

	if(_jumping && _position_in_y_direction >= pom)
			  set_falling();

	_position_in_y_direction = pom;

}

void Player::advance() {
	if(_jumping || _falling)
			  calculate_move_in_Ydir();

	if(_falling)_rotate_hends_when_falling+=4;
	run();
	_current_cube3->check_if_player_is_on_this_and_update(*this);
}
void Player::set_jumping() {
	_jumping = true;
	_initial_velocity_in_y_dirr = 8;
}
#include <iostream>
void Player::move_on_keyboard(int c) {
	if(c == GLUT_KEY_LEFT)
		  _position_in_x_direction-=.1;
	else if(c == GLUT_KEY_RIGHT)
		  _position_in_x_direction+=.1;	  
	else if(c == ' ' && !_jumping && !_falling)
			  set_jumping();
	else if(c == GLUT_KEY_UP){
		if(_falling)
				  _dh = (_slow_falling = !_slow_falling) ? 0.02 : 0.05;

	}
}

void Player::set_current_cube3(PeaceOfPath* c3) {
	_current_cube3 = c3;
	_current_cube3->check_if_player_is_on_this_and_update(*this);
}

void Player::set_falling(){
	_falling = true;
	if(!_jumping)
		_initial_velocity_in_y_dirr = 0;
	else 
	{
		_initial_velocity_in_y_dirr = 8;
	}
		_jumping = false;
	_dh = 0.05;
}

void Player::set_on_ground(){_falling = _jumping = false;
	_sec_in_air = 0;
	_rotate_hends_when_falling = 0;
	_initial_velocity_in_y_dirr = 0;
	_dh = 0.05;
	_slow_falling = false;
}
