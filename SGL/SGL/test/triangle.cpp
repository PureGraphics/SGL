#include "sgl.h"
#include "sglut.h"
#include "rasterizer.h"
#include "sgl_math.h"

#define WW 960
#define WH 640

static void _init() {
    sglShadeModel(SGL_SMOOTH);
    sglMatrixMode(SGL_PROJECTION);
    sgluPerspective(60, (float)WW / WH, 0.1f, 1000.0f);

    sglMatrixMode(SGL_MODELVIEW);
    sglLoadIdentity();

    sglViewport(0, 0, WW, WH);
}

static float s_rot_angle = 0;
static float s_scale = 1.0f;

static void _on_draw() {
    sglClear();

    sglMatrixMode(SGL_MODELVIEW);
    sglLoadIdentity();
    sglRotatef(s_rot_angle, 0, 0, 1);
    if (++s_rot_angle > 360)
        s_rot_angle = 0;
    /*
    sglScalef(s_scale, s_scale, s_scale);
    s_scale += 0.16f;
    if (s_scale >= 2)
    s_scale = 1.0f;*/
    //sglTranslatef(100, -200, 0);
    sgluLookAt(vec3(0, 0, -2), vec3(0, 0, 1), vec3(0, 1, 0));

    sglBegin(SGL_TRIANGLES);
    sglColor3f(255, 0, 0);
    sglVertex3f(0, 1, 1);
    sglColor3f(0, 255, 0);
    sglVertex3f(-1, 0, 1);
    sglColor3f(0, 0, 255);
    sglVertex3f(1, 0, 1);
    sglEnd();

    sglFlush();
}

void main() {
    sglut_init_window(WW, WH);
    _init();
    sglut_display_func(_on_draw);
    sglut_main_loop();
}