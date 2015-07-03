#include "sgl.h"
#include "sglut.h"
#include "rasterizer.h"
#include "sgl_math.h"

#define WW 960
#define WH 640

static void _init() {
    sglMatrixMode(SGL_PROJECTION);
    sgluPerspective(60, (float)WW / WH, 0.1f, 1000.0f);

    sglMatrixMode(SGL_MODELVIEW);
    sglLoadIdentity();
}

static void _on_draw() {
    sglColor3f(255, 255, 0);

    //sglRotatef(20, 0, 0, 1);
    //sglScalef(2, 2, 2);
    //sglTranslatef(100, -200, 0);
    sgluLookAt(vec3(0, 0, 0), vec3(0, 0, 1), vec3(0, 1, 0));

    sglBegin(SGL_TRIANGLES);
    sglVertex3f(0, 1, 1.23f);
    sglVertex3f(-1, 0, 1);
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