#include "Rectangle.h"

void rect_init(SqBox *rect, float posx, float posy, float wid, float hgt) {
	rect->x = posx;
	rect->y = posy;
	rect->width = wid;
	rect->height = hgt;
}

void rect_translate(SqBox *rect, float dx, float dy) {
	rect->x += dx;
	rect->y += dy;
}

bool rect_intersects(SqBox *src, SqBox *tgt) {
	float tlx = tgt->x;
	float tly = tgt->x;
	float brx = tlx + tgt->width;
	float bry = tly + tgt->height;
	if (src->x > brx) return false;
	if (src->y > bry) return false;
	if (src->x + src->width < tlx) return false;
	if (src->y + src->height < tly) return false;
	return true;
}