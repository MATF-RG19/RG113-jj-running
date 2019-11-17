#include <GL/glut.h>
#include <iostream>
#include "runnning_enviroment.hpp"
float curr = -3.5;
float murr = -5;
int rotate = 0;
RunningPath RE;
static void display();
static void reshape(int, int);
static void keyboard(unsigned char, int, int);
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
	glutTimerFunc(50, timer, 1);

	glutMainLoop();
	return 0;
}

static void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.*w/h, .1, 100);
}

static void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 4, 10,
				  0, 0, 0,
				  0, 1, 0);

	RE.make_path();

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
}
static void timer(int value) {
	RE.advance();
	glutTimerFunc(50, timer, 1);
	glutPostRedisplay();
}
