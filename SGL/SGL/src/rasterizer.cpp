#include "rasterizer.h"

#include <math.h>

static inline void _swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static inline float _lerp(float lv, float rv, float l) {
    return lv * (1 - l) + rv * l;
}

void ra_draw_line(int x0, int y0, int x1, int y1, const color &c) {
    if (x0 > x1) {
        _swap(&x0, &x1);
        _swap(&y0, &y1);
    }
    float m = ((float)y1 - y0) / ((float)x1 - x0);
    float y = y0;
    for (int x = x0; x <= x1; x++) {
        color_buffer::get_intance()->write_color(x, round(y), c);
        y += m;
    }
}

static void _draw_triangle_flat_bottom(const vertex &v0, const vertex &v1, const vertex &v2) {
    int x0 = v0.x;
    int y0 = v0.y;
    int x1 = v1.x;
    int y1 = v1.y;
    int x2 = v2.x;
    int y2 = v2.y;

    if (y0 == y1) {
        _swap(&x0, &x2);
        _swap(&y0, &y2);
    }
    else if (y0 == y2) {
        _swap(&x0, &x1);
        _swap(&y0, &y1);
    }
    if (x1 > x2) {
        _swap(&x1, &x2);
        _swap(&y1, &y2);
    }

    float dx_left = ((float)x1 - x0) / ((float)y1 - y0);
    float dx_right = ((float)x2 - x0) / ((float)y2 - y0);
    float xs = x0;
    float xe = x0;
    int y_end = (y1 > y2) ? y1 : y2;
    for (int y = y0; y < y_end; y++) {
        ra_draw_line(round(xs), y, round(xe), y, v0.get_color());
        xs += dx_left;
        xe += dx_right;
    }
}

static void _draw_triangle_flat_bottom_lerp_for_test(const vertex &v0, const vertex &v1, const vertex &v2) {
    int x0 = v0.x;
    int y0 = v0.y;
    int x1 = v1.x;
    int y1 = v1.y;
    int x2 = v2.x;
    int y2 = v2.y;

    if (y0 == y1) {
        _swap(&x0, &x2);
        _swap(&y0, &y2);
    }
    else if (y0 == y2) {
        _swap(&x0, &x1);
        _swap(&y0, &y1);
    }
    if (x1 > x2) {
        _swap(&x1, &x2);
        _swap(&y1, &y2);
    }

    float xs = x0;
    float xe = x0;
    int y_end = (y1 > y2) ? y1 : y2;
    float y_h = y_end - y0;
    for (int y = y0; y < y_end; y++) {
        ra_draw_line(round(xs), y, round(xe), y, v0.get_color());
        float l = (float)(y - y0) / y_h;
        xs = _lerp(x0, x1, l);
        xe = _lerp(x0, x2, l);
    }
}

static void _draw_triangle_flat_top(const vertex &v0, const vertex &v1, const vertex &v2) {
    int x0 = v0.x;
    int y0 = v0.y;
    int x1 = v1.x;
    int y1 = v1.y;
    int x2 = v2.x;
    int y2 = v2.y;

    if (y0 == y2) {
        _swap(&x1, &x2);
        _swap(&y1, &y2);
    }
    else if (y1 == y2) {        
        _swap(&x0, &x1);
        _swap(&y0, &y1);
        _swap(&x1, &x2);
        _swap(&y1, &y2);
    }
    if (x0 > x1) {
        _swap(&x0, &x1);
        _swap(&y0, &y1);
    }
    float dx_left = ((float)x2 - x0) / (y2 - y0);
    float dx_right = ((float)x2 - x1) / (y2 - y1);
    float xs = x0;
    float xe = x1;
    for (int y = y0; y < y2; y++) {
        ra_draw_line(round(xs), y, round(xe), y, v0.get_color());
        xs += dx_left;
        xe += dx_right;
    }
}

void ra_draw_triangle(const vertex &v0, const vertex &v1, const vertex &v2) {
    int x0 = v0.x;
    int y0 = v0.y;
    int x1 = v1.x;
    int y1 = v1.y;
    int x2 = v2.x;
    int y2 = v2.y;

    if (y0 == y1) {
        if (y2 < y0)
            _draw_triangle_flat_bottom(v0, v1, v2);
        else
            _draw_triangle_flat_top(v0, v1, v2);
    }
    else if (y0 == y2) {
        if (y1 < y0)
            _draw_triangle_flat_bottom(v0, v1, v2);
        else
            _draw_triangle_flat_top(v0, v1, v2);
    }
    else if (y1 == y2) {
        if (y0 < y1)
            //_draw_triangle_flat_bottom(x0, y0, x1, y1, x2, y2);
            _draw_triangle_flat_bottom_lerp_for_test(v0, v1, v2);
        else
            _draw_triangle_flat_top(v0, v1, v2);
    }
    else {
        if ((y0 > y1 && y0 < y2) || (y0 < y1 && y0 > y2)) {
            float s = abs((float)y0 - y1) / abs((float)y0 - y2);
            float mid_x = (x1 + x2 * s) / (1 + s);
            ra_draw_triangle(vertex(x1, y1), vertex(x0, y0), vertex(mid_x, y0));
            ra_draw_triangle(vertex(x0, y0), vertex(mid_x, y0), vertex(x2, y2));
        }
        else if ((y1 > y0 && y1 < y2) || (y1 < y0 && y1 > y2)) {
            float s = abs((float)y1 - y0) / abs((float)y1 - y2);
            float mid_x = (x0 + x2 * s) / (1 + s);
            ra_draw_triangle(vertex(x0, y0), vertex(x1, y1), vertex(mid_x, y1));
            ra_draw_triangle(vertex(x1, y1), vertex(mid_x, y1), vertex(x2, y2));
        }
        else {
            float s = abs((float)y2 - y0) / abs((float)y2 - y1);
            float mid_x = (x0 + x1 * s) / (1 + s);
            ra_draw_triangle(vertex(x0, y0), vertex(x2, y2), vertex(mid_x, y2));
            ra_draw_triangle(vertex(x2, y2), vertex(mid_x, y2), vertex(x1, y1));
        }
    }
}