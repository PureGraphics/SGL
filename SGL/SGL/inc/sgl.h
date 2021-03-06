#ifndef sgl_h
#define sgl_h

#include "sgl_enum.h"
#include "sgl_math.h"

void sglClear();
void sglBegin(SGL_PRIMITIVE_TYPE type);
void sglEnd();
void sglVertex2f(float x, float y);
void sglVertex3f(float x, float y, float z);
void sglVertex3fv(const float *pointer);
void sglColor3f(float r, float g, float b);
void sglColor3fv(const float *pointer);
void sglFlush();

void sglMatrixMode(SGL_MATRIX_MODE mode);
void sglLoadIdentity();
void sglScalef(float x, float y, float z);
void sglRotatef(float angle, float x, float y, float z);
void sglTranslatef(float x, float y, float z);
void sgluLookAt(vec3 eye, vec3 target, vec3 up);
void sgluPerspective(float fovy, float aspect, float n, float f);
void sglViewport(uint x, uint y, uint w, uint h);

void sglShadeModel(SGL_SHADE_MODEL mode);
void sglTexCoord2f(float x, float y);
void sglTexCoord2fv(const float *pointer);
void sglGenTextures(uint n, uint *textures);
void sglLoadTexture(uint texture, const char *path);
void sglBindTexture(SGL_TEXTURE target, uint texture);

#endif