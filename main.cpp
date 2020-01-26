#include <GL/glut.h>
#include <iostream>
#include "runnning_enviroment.hpp"
#include "player.hpp"
#include "skor.hpp"
Skor* skor = new Skor(640, 480);
Player* player = new Player(skor);
RunningPath* RE = new RunningPath(player, skor);
bool started = false;;
static void display();
static void reshape(int, int);
static void keyboard(unsigned char, int, int);
static void ky(int , int, int);
static void timer(int);
void init();
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("igra");
	init();
	glutMainLoop();
	return 0;
}
/*vrsi se inicijalizacija*/
void init() {
	glClearColor(0, 0, 0, 0);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(ky);
}

static void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, .1, 100);
}
static void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	skor->draw();

	/* gluLookat je postavljen tako da 
	 * kamera prati igraca*/
	gluLookAt(0, 3+player->getYfeet(), 6 - player->getZ(),
				  0, player->getYfeet(), -player->getZ(),
				  0, 1, 0);
	/*crta se put*/
	RE->make_path();
	/*crta se igrac*/
	player->draw_player();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(0, 1, 0);
	glPointSize(10);
	glBegin(GL_POINTS);

	glVertex3f(-0.5, -3.5, -10);

	glEnd();
	glutSwapBuffers();
}
/* prosledjuju se pritisci tastature
 * igracu */ 
static void keyboard(unsigned char c, int, int) {
		  if(c == ' ')
				player->move_on_keyboard(c);
		  else if (c == '1')
				player->addY();
		  else if(c == 27)
					 exit(0);
		  else if(c == 'r')
		  {
				if(skor->is_game_over){
					/* ako je doslo do game overa
					 * resetuje se i igrac se vraca
					 * na pocetak*/
					skor->is_game_over = false;
					delete RE;
					delete player;
					delete skor;
					skor = new Skor(640, 480);
					player = new Player(skor);
					RE = new RunningPath(player, skor);
					glutPostRedisplay();
					started = false;
				}
				else if(!started){			  
					/*zapocinje se igra*/
					started = true;
					glutTimerFunc(45, timer, 1);
				}
			}
}
static void ky(int c, int, int) {
	player->move_on_keyboard(c);
}
static void timer(int value) {
	if(skor->is_game_over)
		return;
	RE->advance();
	player->advance();
	glutTimerFunc(45, timer, 1);
	glutPostRedisplay();
}
