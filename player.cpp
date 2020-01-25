#include "player.hpp"
#include <GL/glut.h>
#include "cube3.hpp"
/* Metod koji crta noge igraca*/
void Player::draw_legs() const { 
	glPushMatrix();
	/* ako je ukljuceno sporo padanje
	 * treba igracu zavrteti noge*/
	if(_movement != SLOW_FALLING)
	{
		glTranslatef(-.2, -.9, 0);
		glRotatef(_rotating, 1, 0, 0);
	}
	else
	{
		glTranslatef(0, -.6, 0);
		glRotatef(4*_rotate_hends_when_falling, 0, 1, 0);
		glTranslatef(-0.25, -0.25, 0);
		glRotatef(-45, 0, 0, 1);
	}
	glScalef(.2, .7, .4);
	glutWireCube(1);glColor3f(0, 1, 0);glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	/* ako je ukljuceno sporo padanje
	 * treba igracu zavrteti noge*/
	if(_movement != SLOW_FALLING)
	{
		glTranslatef(.2, -.9, 0);
		glRotatef(-_rotating, 1, 0, 0);
	}
	else
	{
		glTranslatef(0, -.6, 0);
		glRotatef(4*_rotate_hends_when_falling, 0, 1, 0);
		glTranslatef(0.25, -0.25, 0);
		glRotatef(45, 0, 0, 1);
	}
	glScalef(.2, .7, .4);
	glutWireCube(1);glColor3f(0, 1, 0);glutSolidCube(1);
	glPopMatrix();
}
/* Metod koji crta telo igraca*/
void Player::draw_body() const {
	glPushMatrix();
	glScalef(0.5, .7, 0.6);
	glColor3f(0, 1, 0);glutSolidCube(1);glColor3f(0, 0, 0);glutWireCube(1);
	glPopMatrix();
}
/*Metod koji crta ruke igraca*/
void Player::draw_arms() const {
	glPushMatrix();
	glTranslatef(0.4, 0, 0);
	/* Ako igrac pada trebaju 
	 * ruke da mu malo zaostaju */
	if(_movement == FALLING || _movement == SLOW_FALLING)
			  glRotatef(_rotate_hends_when_falling > 100 ? 100 : _rotate_hends_when_falling, 0, 0, 1);
	else
		glRotatef(-_rotating, 1, 0, 0);
	glScalef(0.14, .6, 0.4);
	glColor3f(0, 1, 0);glutSolidCube(1);
	
	glColor3f(0, 0, 0);
	glutWireCube(1);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-0.4, 0, 0);

	/* Ako igrac pada trebaju 
	 * ruke da mu malo zaostaju */
	if(_movement == FALLING || _movement == SLOW_FALLING)
			  glRotatef(-_rotate_hends_when_falling < -100 ? -100 : -_rotate_hends_when_falling, 0, 0, 1);
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
/* Metod koji crta celog igraca*/
void Player::draw_player() const {
	glTranslatef(_position_in_x_direction, _position_in_y_direction, -_position_in_z_direction);
	float ambient_diffuse[] = {1, 1, 0, 1};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambient_diffuse);
	draw_body();
	draw_arms();
	draw_legs();
	draw_head();
	ambient_diffuse[0] = ambient_diffuse[1] = ambient_diffuse[2] = .2;
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_diffuse);
	glTranslatef(-_position_in_x_direction, -_position_in_y_direction, _position_in_z_direction);
}
/* Metod koji dok igrac trci pomera
 * mu ruke i noge */
void Player::run() {
	_rotating += 3*_add;	
	if(_rotating >= 45 || _rotating <= -45)
		_add *= -1;
}
/* Ako se igrac pomera po y koordinatu 
 * ovaj metod mu odredjuje narednu
 * y koordinatu*/
void Player::calculate_move_in_Ydir() {
	/* Broj sekundi u vazduhu se povecava */
	_sec_in_air += 0.05;
	float pom = _position_in_y_direction 
			  +_initial_velocity_in_y_dirr*_dh-9.8*(_sec_in_air-0.05)*_dh-4.9*_dh*_dh;

	if(_movement == JUMPING&& _position_in_y_direction >= pom)
			  set_falling();

	_position_in_y_direction = pom;

}
/* Metod koji pomera igraca
 * u zavisnosti od vremena*/
void Player::advance() {
	_position_in_z_direction += 0.2;
	_position_in_x_direction += _dx;
	if(_movement == JUMPING || _movement == FALLING || _movement == SLOW_FALLING)
			  calculate_move_in_Ydir();

	if(_movement == FALLING || _movement == SLOW_FALLING)_rotate_hends_when_falling+=4;
	run();
	current_peace_of_path->check_if_player_is_on_this_and_update(*this);
}
/* Metod koji postavlja igraca da skace
 * sa pocetnim ubrzanjem*/
void Player::set_jumping(float velocity) {
	_movement = JUMPING;
	_initial_velocity_in_y_dirr = velocity;
	_dx = 0;
}
/* Metod koji menja stanje igraca
 * u zavisnosti od kliknutog dugmeta*/
void Player::move_on_keyboard(int c) {
	if(c == GLUT_KEY_LEFT)
		  _position_in_x_direction-=.1;
	else if(c == GLUT_KEY_RIGHT)
		  _position_in_x_direction+=.1;	  
	else if(c == ' ' && _movement == ON_GROUND)
			  set_jumping();
	else if(c == ' ' && _movement == FALLING){
			  _dh = 0.02;
			  _movement = SLOW_FALLING;
	}
	else if(c == ' ' && _movement == SLOW_FALLING){
			  _dh = 0.03;
			  _movement = FALLING;
	}
}

/* Metod koji postavlaj novo
 * poostolje za igraca*/ 
void Player::set_current_peace_of_path(PeaceOfPath* c3) {
	_position_in_z_direction = -(c3->getLength()) / 2;
	current_peace_of_path = c3;
	current_peace_of_path->check_if_player_is_on_this_and_update(*this);
}

/* Metod koji stavlja igraca da pada*/
void Player::set_falling(){
	if(_movement == ON_GROUND)
		_initial_velocity_in_y_dirr = 0;
	else 
		_initial_velocity_in_y_dirr = 8;
	_movement = FALLING;
	_dh = 0.05;
	_dx = 0;
}
/*Metod koji stavlja giraca na zemlju*/
void Player::set_on_ground(){
	_sec_in_air = 0;
	_rotate_hends_when_falling = 0;
	_initial_velocity_in_y_dirr = 0;
	_dh = 0.05;
	_movement = ON_GROUND;
}
