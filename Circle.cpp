#include "Circle.h"

void circ_init(Circle *circle, float posx, float posy, float rad) {
	circle->x = posx;
	circle->y = posy;
	circle->radius = rad;
}

void circ_translate(Circle *circle, float dx, float dy) {
	circle->x += dx;
	circle->y += dy;
}

bool circ_intersects(Circle *src, Circle *tgt) {
	float tworad = tgt->radius + src->radius;
	float tgx = tgt->x;
	float tgy = tgt->y;
	float distx = src->x - tgx;
	float disty = src->y - tgy;
	if ((distx*distx) + (disty*disty) < (tworad * tworad)) return true;
	else return false;
}