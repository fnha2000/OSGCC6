#ifndef COLL_CIRC
#define COLL_CIRC

typedef struct Circle {
	float x, y, radius;
} Circle;

void circ_init(Circle *circle, float posx, float posy, float rad);
void circ_translate(Circle *circle, float dx, float dy);
bool circ_intersects(Circle *src, Circle *tgt);

#endif