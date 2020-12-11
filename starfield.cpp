#include "stdafx.h"
#include "starfield.h"

/* #define SCREEN_SAVER_MODE */




star* stars = NULL;
int num_stars = 150;

void __reshapestar(int cx,int cy)
{

	int i;
for (i = 0; i < num_stars; i++) 
	{
        stars[i].x = rand() % cx;
        stars[i].y = rand() % cy;
        stars[i].vx = rand() / (float)RAND_MAX * 5 + 2;
        stars[i].vy = 0;
    }
}

void __starsfield()
{
	int i;
for (i = 0; i < num_stars; i++) {
        stars[i].x += stars[i].vx;
        if (stars[i].x < glutGet(GLUT_WINDOW_WIDTH)) {
            glBegin(GL_LINE_STRIP);
            glColor3ub(0, 0, 0);
            glVertex2i(stars[i].x-stars[i].vx*4, stars[i].y);
            glColor3ub(255, 255, 255);
            glVertex2i(stars[i].x, stars[i].y);
            glEnd();
        } else {
            stars[i].x = 0;
        }
    }

}