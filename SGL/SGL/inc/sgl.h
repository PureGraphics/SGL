#ifndef sgl_h
#define sgl_h

#include "sgl_enum.h"

void sglBegin(SGL_PRIMITIVE_TYPE type);
void sglEnd();
void sglVertex2f(float x, float y);
void sglVertex3f(float x, float y, float z);
void sglColor3f(float r, float g, float b);
void sglFlush();

void sglMatrixMode(SGL_MATRIX_MODE mode);
void sglLoadIdentity();
void sglScalef(float x, float y, float z);
void sglRotatef(float angle, float x, float y, float z);
void sglTranslatef(float x, float y, float z);

#endif