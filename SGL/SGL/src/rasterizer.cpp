#include "rasterizer.h"

#include <math.h>

static void _swap(uint *a, uint *b) {
    uint temp = *a;
    *a = *b;
    *b = temp;
}

void ra_draw_line(uint x0, uint y0, uint x1, uint y1, color c) {
    if (x0 > x1) {
        _swap(&x0, &x1);
        _swap(&y0, &y1);
    }
    float m = ((float)y1 - y0) / ((float)x1 - x0);
    float y = y0;
    for (uint x = x0; x <= x1; x++) {
        color_buffer::get_intance()->write_color(x, round(y), c);
        y += m;
    }
}

static void _draw_triangle_flat_bottom(uint x0, uint y0, uint x1, uint y1, uint x2, uint y2, color c) {
    if (y1 > y0 && y1 > y2) {
        _swap(&x0, &x1);
        _swap(&y0, &y1);
    }
    else if (y2 > y0 && y2 > y1) {
        _swap(&x0, &x2);
        _swap(&y0, &y2);
    }

    if (x1 > x2) {
        _swap(&x1, &x2);
        _swap(&y1, &y2);
    }

    float dx_left = ((float)x1 - x0) / ((float)y1 - y0);
    float dx_right = ((float)x2 - x0) / ((float)y2 - y0);
    float xs = x0;
    float xe = x0;
    uint y_end = (y1 > y2) ? y1 : y2;
    for (uint y = y0; y < y_end; y++) {
        ra_draw_line(round(xs), y, round(xe), y, c);
        xs += dx_left;
        xe += dx_right;
    }
}

void ra_draw_triangle(uint x0, uint y0, uint x1, uint y1, uint x2, uint y2, color c) {
    _draw_triangle_flat_bottom(x0, y0, x1, y1, x2, y2, c);
}