#include "sgl.h"
#include "sglut.h"
#include "sgl_math.h"

#define WW 960
#define WH 640

static uint s_textures[2];

static void _init() {
    sglShadeModel(SGL_SMOOTH);
    sglMatrixMode(SGL_PROJECTION);
    sgluPerspective(60, (float)WW / WH, 0.1f, 1000.0f);

    sglMatrixMode(SGL_MODELVIEW);
    sglLoadIdentity();
    sgluLookAt(vec3(0, 0.6, -3.5), vec3(0, 0, 1), vec3(0, 1, 0));

    sglViewport(0, 0, WW, WH);

    sglGenTextures(2, s_textures);
    sglLoadTexture(s_textures[0], "E:/Girl.jpg");
    sglLoadTexture(s_textures[1], "E:/Carmack.jpg");
}

static float s_rot_angle = 0;
static float s_scale = 1.0f;

static void _on_draw() {
    sglClear();
    sglMatrixMode(SGL_MODELVIEW);
    sglLoadIdentity();

    sglRotatef(s_rot_angle, 0, 1, 0);
    if (++s_rot_angle > 360)
        s_rot_angle = 0;

    sglBegin(SGL_QUADS);
    //0.
    sglColor3f(255, 0, 0);
    sglVertex3f(-0.5, 0.5, 0.5);

    sglColor3f(0, 255, 0);
    sglVertex3f(0.5, 0.5, 0.5);

    sglColor3f(0, 0, 255);
    sglVertex3f(0.5, 0.5, -0.5);

    sglColor3f(255, 255, 255);
    sglVertex3f(-0.5, 0.5, -0.5);
    
    //1. 
    sglColor3f(255, 0, 0);
    sglVertex3f(-0.5, 0.5, -0.5);

    sglColor3f(0, 255, 0);
    sglVertex3f(0.5, 0.5, -0.5);

    sglColor3f(0, 0, 255);
    sglVertex3f(0.5, -0.5, -0.5);

    sglColor3f(255, 255, 255);
    sglVertex3f(-0.5, -0.5, -0.5);

    //2. 
    sglColor3f(255, 0, 0);
    sglVertex3f(-0.5, -0.5, 0.5);

    sglColor3f(0, 255, 0);
    sglVertex3f(0.5, -0.5, 0.5);

    sglColor3f(0, 0, 255);
    sglVertex3f(0.5, -0.5, -0.5);

    sglColor3f(255, 255, 255);
    sglVertex3f(-0.5, -0.5, -0.5);

    //3.
    sglColor3f(255, 0, 0);
    sglVertex3f(-0.5, 0.5, 0.5);

    sglColor3f(0, 255, 0);
    sglVertex3f(0.5, 0.5, 0.5);

    sglColor3f(0, 0, 255);
    sglVertex3f(0.5, -0.5, 0.5);

    sglColor3f(255, 255, 255);
    sglVertex3f(-0.5, -0.5, 0.5);

    //4.
    sglColor3f(255, 0, 0);
    sglVertex3f(-0.5, 0.5, 0.5);

    sglColor3f(0, 255, 0);
    sglVertex3f(-0.5, 0.5, -0.5);

    sglColor3f(0, 0, 255);
    sglVertex3f(-0.5, -0.5, -0.5);

    sglColor3f(255, 255, 255);
    sglVertex3f(-0.5, -0.5, 0.5);

    //5.
    sglColor3f(255, 0, 0);
    sglVertex3f(0.5, 0.5, 0.5);

    sglColor3f(0, 255, 0);
    sglVertex3f(0.5, 0.5, -0.5);

    sglColor3f(0, 0, 255);
    sglVertex3f(0.5, -0.5, -0.5);

    sglColor3f(255, 255, 255);
    sglVertex3f(0.5, -0.5, 0.5);

    sglEnd();

    sglBindTexture(SGL_TEXTURE_2D, s_textures[0]);
    sglTranslatef(-0.6, 1.2, 0);

    sglBegin(SGL_QUADS);
    //0.
    sglTexCoord2f(0, 0);
    sglVertex3f(-0.5, 0.5, 0.5);

    sglTexCoord2f(1, 0);
    sglVertex3f(0.5, 0.5, 0.5);

    sglTexCoord2f(1, 1);
    sglVertex3f(0.5, 0.5, -0.5);

    sglTexCoord2f(0, 1);
    sglVertex3f(-0.5, 0.5, -0.5);

    //1. 
    sglTexCoord2f(0, 0);
    sglVertex3f(-0.5, 0.5, -0.5);

    sglTexCoord2f(1, 0);
    sglVertex3f(0.5, 0.5, -0.5);

    sglTexCoord2f(1, 1);
    sglVertex3f(0.5, -0.5, -0.5);

    sglTexCoord2f(0, 1);
    sglVertex3f(-0.5, -0.5, -0.5);

    //2. 
    sglTexCoord2f(0, 0);
    sglVertex3f(-0.5, -0.5, 0.5);

    sglTexCoord2f(1, 0);
    sglVertex3f(0.5, -0.5, 0.5);

    sglTexCoord2f(1, 1);
    sglVertex3f(0.5, -0.5, -0.5);

    sglTexCoord2f(0, 1);
    sglVertex3f(-0.5, -0.5, -0.5);

    //3.
    sglTexCoord2f(0, 0);
    sglVertex3f(-0.5, 0.5, 0.5);

    sglTexCoord2f(1, 0);
    sglVertex3f(0.5, 0.5, 0.5);

    sglTexCoord2f(1, 1);
    sglVertex3f(0.5, -0.5, 0.5);

    sglTexCoord2f(0, 1);
    sglVertex3f(-0.5, -0.5, 0.5);

    //4.
    sglTexCoord2f(0, 0);
    sglVertex3f(-0.5, 0.5, 0.5);

    sglTexCoord2f(1, 0);
    sglVertex3f(-0.5, 0.5, -0.5);

    sglTexCoord2f(1, 1);
    sglVertex3f(-0.5, -0.5, -0.5);

    sglTexCoord2f(0, 1);
    sglVertex3f(-0.5, -0.5, 0.5);

    //5.
    sglTexCoord2f(0, 0);
    sglVertex3f(0.5, 0.5, 0.5);

    sglTexCoord2f(1, 0);
    sglVertex3f(0.5, 0.5, -0.5);

    sglTexCoord2f(1, 1);
    sglVertex3f(0.5, -0.5, -0.5);

    sglTexCoord2f(0, 1);
    sglVertex3f(0.5, -0.5, 0.5);

    sglEnd();

    sglBindTexture(SGL_TEXTURE_2D, s_textures[1]);
    sglTranslatef(1, 0, 0.8);

    sglBegin(SGL_QUADS);
    //0.
    sglTexCoord2f(0, 0);
    sglVertex3f(-0.5, 0.5, 0.5);

    sglTexCoord2f(1, 0);
    sglVertex3f(0.5, 0.5, 0.5);

    sglTexCoord2f(1, 1);
    sglVertex3f(0.5, 0.5, -0.5);

    sglTexCoord2f(0, 1);
    sglVertex3f(-0.5, 0.5, -0.5);

    //1. 
    sglTexCoord2f(0, 0);
    sglVertex3f(-0.5, 0.5, -0.5);

    sglTexCoord2f(1, 0);
    sglVertex3f(0.5, 0.5, -0.5);

    sglTexCoord2f(1, 1);
    sglVertex3f(0.5, -0.5, -0.5);

    sglTexCoord2f(0, 1);
    sglVertex3f(-0.5, -0.5, -0.5);

    //2. 
    sglTexCoord2f(0, 0);
    sglVertex3f(-0.5, -0.5, 0.5);

    sglTexCoord2f(1, 0);
    sglVertex3f(0.5, -0.5, 0.5);

    sglTexCoord2f(1, 1);
    sglVertex3f(0.5, -0.5, -0.5);

    sglTexCoord2f(0, 1);
    sglVertex3f(-0.5, -0.5, -0.5);

    //3.
    sglTexCoord2f(0, 0);
    sglVertex3f(-0.5, 0.5, 0.5);

    sglTexCoord2f(1, 0);
    sglVertex3f(0.5, 0.5, 0.5);

    sglTexCoord2f(1, 1);
    sglVertex3f(0.5, -0.5, 0.5);

    sglTexCoord2f(0, 1);
    sglVertex3f(-0.5, -0.5, 0.5);

    //4.
    sglTexCoord2f(0, 0);
    sglVertex3f(-0.5, 0.5, 0.5);

    sglTexCoord2f(1, 0);
    sglVertex3f(-0.5, 0.5, -0.5);

    sglTexCoord2f(1, 1);
    sglVertex3f(-0.5, -0.5, -0.5);

    sglTexCoord2f(0, 1);
    sglVertex3f(-0.5, -0.5, 0.5);

    //5.
    sglTexCoord2f(0, 0);
    sglVertex3f(0.5, 0.5, 0.5);

    sglTexCoord2f(1, 0);
    sglVertex3f(0.5, 0.5, -0.5);

    sglTexCoord2f(1, 1);
    sglVertex3f(0.5, -0.5, -0.5);

    sglTexCoord2f(0, 1);
    sglVertex3f(0.5, -0.5, 0.5);

    sglEnd();

    sglFlush();
}

void main() {
    sglut_init_window(WW, WH);
    _init();
    sglut_display_func(_on_draw);
    sglut_main_loop();
}