#ifndef sgl_h
#define sgl_h

#include "sgl_enum.h"

void sglBegin(SGL_PRIMITIVE_TYPE type);
void sglEnd();
void sglVertex2f(float x, float y);
void sglVertex3f(float x, float y, float z);
void sglColor3f(float r, float g, float b);
void sglFlush();

#endif