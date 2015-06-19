#include "sgl.h"
#include "sglut.h"

#define WW 960
#define WH 640

static void _on_draw() {
    sglColor3f(255, 255, 0);

    sglBegin(SGL_TRIANGLES);
    sglVertex2f(200, 100);
    sglVertex2f(100, 200);
    sglVertex2f(300, 200);
    sglEnd();

    sglFlush();
}

void main() {
    sglut_init_window(WW, WH);
    sglut_display_func(_on_draw);
    sglut_main_loop();
}