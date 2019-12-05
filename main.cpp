#include <GL/glut.h>
#include <iostream>
#include "runnning_enviroment.hpp"
#include "player.hpp"
float curr = -3.5;
float murr = -5;
int rotate = 0;
Player player;
RunningPath RE(&player);
static void display();
static void reshape(int, int);
static void keyboard(unsigned char, int, int);
static void ky(int , int, int);
static void timer(int);
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	
	glutInitWindowSize(640, 480);

	glutCreateWindow("djole");

	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(ky);
	glutTimerFunc(50, timer, 1);

	glutMainLoop();
	return 0;
}

static void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65, 1.*w/h, .1, 100);
}
float s = 1.7;
static void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 4, 10,
				  0, 0, 0,
				  0, 1, 0);

	RE.make_path();
	glTranslatef(0, s, 
						 6);
	player.draw_player();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(0, 1, 0);
	glPointSize(10);
	glBegin(GL_POINTS);

	glVertex3f(-0.5, curr, -10);

	glEnd();
	glutSwapBuffers();
}

static void keyboard(unsigned char c, int, int) {
		  if(c == '+')s+=.1;
		  else if(c == ' ')
				player.set_jumping();
		  else s-=.1;
		  player.move_on_keyboard(c);
		  std::cout << s << std::endl;
}
static void ky(int c, int, int) {
	player.move_on_keyboard(c);
}
static void timer(int value) {
	RE.advance();
	player.advance();
	glutTimerFunc(50, timer, 1);
	glutPostRedisplay();
}
