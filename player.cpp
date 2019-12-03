#include "player.hpp"
#include <GL/glut.h>

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
	_in_air = 7*_sec_in_air - 4.9*_sec_in_air*_sec_in_air;
	if(_in_air <= 0)
			 _on_ground = !(_sec_in_air = _in_air = 0);
}

void Player::advance() {
	if(!_on_ground)
			  jump();

	run();
}
void Player::set_jumping() {
	_on_ground = false;
}

void Player::move_on_keyboard(int c) {
	if(c == GLUT_KEY_LEFT)
		  _position_in_x_direction-=.1;
	else if(c == GLUT_KEY_RIGHT)
		  _position_in_x_direction+=.1;	  
}
