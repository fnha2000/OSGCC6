#ifndef COLL_RECT
#define COLL_RECT

typedef struct Rectangle {
	float x, y, width, height;
} SqBox;

void rect_init(SqBox *rect, float posx, float posy, float wid, float hgt);
void rect_translate(SqBox *rect, float dx, float dy);
bool rect_intersects(SqBox *src, SqBox *tgt);

#endif