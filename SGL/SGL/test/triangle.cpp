#include "sgl.h"
#include "sglut.h"
#include "rasterizer.h"

#define WW 960
#define WH 640

static void _on_draw() {
    sglColor3f(255, 255, 0);

    sglBegin(SGL_TRIANGLES);
    sglVertex2f(200, 100);
    sglVertex2f(100, 200);
    sglVertex2f(300, 200);
    sglEnd();

    ra_draw_line(50, 50, 800, 100, color(255, 255, 0, 255));
    ra_draw_line(50, 150, 800, 150, color(255, 255, 0, 255));

    ra_draw_triangle(150, 50, 100, 150, 200, 150, color(255, 255, 0, 255));

    sglFlush();
}

void main() {
    sglut_init_window(WW, WH);
    sglut_display_func(_on_draw);
    sglut_main_loop();
}