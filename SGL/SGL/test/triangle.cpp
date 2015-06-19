#include "sglut.h"
#include "color_buffer.h"
#include "image.h"

#define WW 940
#define WH 640

static color_buffer *s_color_buffer = nullptr;

static void _init_color_buffer() {
    s_color_buffer = new color_buffer();
    s_color_buffer->set_viewport(WW, WH);
}

static void _on_draw() {
    s_color_buffer->clear();
    for (int x = 100; x < 200; x++) {
        s_color_buffer->write_color(x, 100, color(255, 255, 0, 255));
    }
    s_color_buffer->flush();
}

void main() {
    sglut_init_window(WW, WH);
    _init_color_buffer();
    sglut_display_func(_on_draw);
    sglut_main_loop();
}