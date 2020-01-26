#ifndef _SKOR_
#define _SKOR_
#include <GL/glut.h>
#include <iostream>
class Skor {
	int potencijalni_skor = 0;
	int skor = 0;
	int w, h;
public:
	Skor(int ww, int hh) : w(ww), h(hh){}
	Skor& operator++(){
		potencijalni_skor++;
		return *this;
	}
	void make_potential_real() {
		skor = potencijalni_skor;
	}
	/*Iscrtava se skor na ekranu*/
	void draw() const {
		int pom = 1;

		while( pom <= skor)pom*=10;
		if(skor >= 10)
			pom /= 10;

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, w, 0, h, -1, 1); 
		glDisable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glRasterPos2i(w-50, h-20);

		do{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0' + (skor/pom)%10);
			pom/=10;
		}
		while(pom);

		glEnable(GL_LIGHTING);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
};
#endif
