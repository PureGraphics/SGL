#include "sgl.h"
#include "sglut.h"
#include "rasterizer.h"
#include "sgl_math.h"

#define WW 960
#define WH 640

static void _on_draw() {
    sglColor3f(255, 255, 0);

    sglRotatef(20, 0, 0, 1);
    sglScalef(2, 2, 2);
    sglTranslatef(100, -200, 0);

    sglBegin(SGL_TRIANGLES);
    sglVertex2f(200, 200);
    sglVertex2f(100, 300);
    sglVertex2f(300, 300);
    sglEnd();

    sglFlush();
}

void main() {
    sglut_init_window(WW, WH);
    sglut_display_func(_on_draw);
    sglut_main_loop();
}