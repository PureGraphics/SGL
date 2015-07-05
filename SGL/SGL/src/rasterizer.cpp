#include "rasterizer.h"

#include <math.h>

static inline void _swap_i(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static inline void _swap_vertex(vertex &va, vertex &vb) {
    vertex::swap(va, vb);
}

static inline float _lerp(float lv, float rv, float l) {
    return lv * (1 - l) + rv * l;
}

void ra_draw_line(int x0, int y0, int x1, int y1, const color &c) {
    if (x0 > x1) {
        _swap_i(&x0, &x1);
        _swap_i(&y0, &y1);
    }
    float m = ((float)y1 - y0) / ((float)x1 - x0);
    float y = y0;
    for (int x = x0; x <= x1; x++) {
        color_buffer::get_intance()->write_color(x, round(y), c);
        y += m;
    }
}

static void _flat_draw_triangle_flat_bottom(vertex &v0, vertex &v1, vertex &v2) {
    if (v0.y == v1.y) {
        _swap_vertex(v0, v2);
    }
    else if (v0.y == v2.y) {
        _swap_vertex(v0, v1);
    }
    if (v1.x > v2.x) {
        _swap_vertex(v1, v2);
    }

    int x0 = v0.x;
    int y0 = v0.y;
    int x1 = v1.x;
    int y1 = v1.y;
    int x2 = v2.x;
    int y2 = v2.y;

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

static void _smooth_draw_triangle_flat_bottom(vertex &v0, vertex &v1, vertex &v2) {
    if (v0.y == v1.y) {
        _swap_vertex(v0, v2);
    }
    else if (v0.y == v2.y) {
        _swap_vertex(v0, v1);
    }
    if (v1.x > v2.x) {
        _swap_vertex(v1, v2);
    }

    int x0 = v0.x;
    int y0 = v0.y;
    int x1 = v1.x;
    int y1 = v1.y;
    int x2 = v2.x;
    int y2 = v2.y;

    float xs = x0;
    float xe = x0;
    int y_end = (y1 > y2) ? y1 : y2;
    float y_dis = y_end - y0;
    float crs = v0.r;
    float cre = v0.r;
    float cgs = v0.g;
    float cge = v0.g;
    float cbs = v0.b;
    float cbe = v0.b;
    float cas = v0.a;
    float cae = v0.a;
    for (int y = y0; y < y_end; y++) {
        float ly = ((float)y - y0) / y_dis;
        xs = _lerp(x0, x1, ly);
        xe = _lerp(x0, x2, ly);
        crs = _lerp(v0.r, v1.r, ly);
        cre = _lerp(v0.r, v2.r, ly);
        cgs = _lerp(v0.g, v1.g, ly);
        cge = _lerp(v0.g, v2.g, ly);
        cbs = _lerp(v0.b, v1.b, ly);
        cbe = _lerp(v0.b, v2.b, ly);
        cas = _lerp(v0.a, v1.a, ly);
        cae = _lerp(v0.a, v2.a, ly);
        float x_dis = xe - xs;
        for (int x = xs; x < xe; x++) {
            float lx = ((float)x - xs) / x_dis;
            color c;
            c.r = _lerp(crs, cre, lx);
            c.g = _lerp(cgs, cge, lx);
            c.b = _lerp(cbs, cbe, lx);
            c.a = _lerp(cas, cae, lx);
            color_buffer::get_intance()->write_color(x, y, c);
        }
    }
}

static void _draw_triangle_flat_bottom(vertex &v0, vertex &v1, vertex &v2, SGL_SHADE_MODEL shade_mode) {
    switch (shade_mode) {
    case SGL_FLAT:
        _flat_draw_triangle_flat_bottom(v0, v1, v2);
        break;
    case SGL_SMOOTH:
        _smooth_draw_triangle_flat_bottom(v0, v1, v2);
        break;
    default:
        assert(false);
        break;
    }
}

static void _flat_draw_triangle_flat_top(vertex &v0, vertex &v1, vertex &v2) {
    if (v0.y == v2.y) {
        _swap_vertex(v1, v2);
    }
    else if (v1.y == v2.y) {        
        _swap_vertex(v0, v1);
        _swap_vertex(v1, v2);
    }
    if (v0.x > v1.x) {
        _swap_vertex(v0, v1);
    }

    int x0 = v0.x;
    int y0 = v0.y;
    int x1 = v1.x;
    int y1 = v1.y;
    int x2 = v2.x;
    int y2 = v2.y;

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

static void _smooth_draw_triangle_flat_top(vertex &v0, vertex &v1, vertex &v2) {
    if (v0.y == v2.y) {
        _swap_vertex(v1, v2);
    }
    else if (v1.y == v2.y) {
        _swap_vertex(v0, v1);
        _swap_vertex(v1, v2);
    }
    if (v0.x > v1.x) {
        _swap_vertex(v0, v1);
    }

    int x0 = v0.x;
    int y0 = v0.y;
    int x1 = v1.x;
    int y1 = v1.y;
    int x2 = v2.x;
    int y2 = v2.y;

    float xs = x0;
    float xe = x1;
    float crs = v0.r;
    float cre = v1.r;
    float cgs = v0.g;
    float cge = v1.g;
    float cbs = v0.b;
    float cbe = v1.b;
    float cas = v0.a;
    float cae = v1.a;
    float y_dis = y2 - y0;
    for (int y = y0; y < y2; y++) {
        float ly = (float(y) - y0) / y_dis;
        xs = _lerp(x0, x2, ly);
        xe = _lerp(x1, x2, ly);
        crs = _lerp(v0.r, v2.r, ly);
        cre = _lerp(v1.r, v2.r, ly);
        cgs = _lerp(v0.g, v2.g, ly);
        cge = _lerp(v1.g, v2.g, ly);
        cbs = _lerp(v0.b, v2.b, ly);
        cbe = _lerp(v1.b, v2.b, ly);
        cas = _lerp(v0.a, v2.a, ly);
        cae = _lerp(v1.a, v2.a, ly);
        float x_dis = xe - xs;
        for (int x = xs; x < xe; x++) {
            float lx = ((float)x - xs) / x_dis;
            color c;
            c.r = _lerp(crs, cre, lx);
            c.g = _lerp(cgs, cge, lx);
            c.b = _lerp(cbs, cbe, lx);
            c.a = _lerp(cas, cae, lx);
            color_buffer::get_intance()->write_color(x, y, c);
        }
    }
}

static void _draw_triangle_flat_top(vertex &v0, vertex &v1, vertex &v2, SGL_SHADE_MODEL shade_mode) {
    switch (shade_mode) {
    case SGL_FLAT:
        _flat_draw_triangle_flat_top(v0, v1, v2);
        break;
    case SGL_SMOOTH:
        _smooth_draw_triangle_flat_top(v0, v1, v2);
        break;
    default:
        assert(false);
        break;
    }
}

static void _get_split_vertex(vertex &v_ret, const vertex &va, const vertex &vb, float y) {
    float ly = (y - va.y) / (vb.y - va.y);
    v_ret.x = _lerp(va.x, vb.x, ly);
    v_ret.y = y;
    v_ret.z = _lerp(va.z, vb.z, ly);
    v_ret.w = 1;
    v_ret.r = _lerp(va.r, vb.r, ly);
    v_ret.g = _lerp(va.g, vb.g, ly);
    v_ret.b = _lerp(va.b, vb.b, ly);
    v_ret.a = _lerp(va.a, vb.a, ly);
}

void ra_draw_triangle(vertex &v0, vertex &v1, vertex &v2, SGL_SHADE_MODEL shade_mode) {
    float x0 = v0.x;
    float y0 = v0.y;
    float x1 = v1.x;
    float y1 = v1.y;
    float x2 = v2.x;
    float y2 = v2.y;

    if (y0 == y1) {
        if (y2 < y0)
            _draw_triangle_flat_bottom(v0, v1, v2, shade_mode);
        else
            _draw_triangle_flat_top(v0, v1, v2, shade_mode);
    }
    else if (y0 == y2) {
        if (y1 < y0)
            _draw_triangle_flat_bottom(v0, v1, v2, shade_mode);
        else
            _draw_triangle_flat_top(v0, v1, v2, shade_mode);
    }
    else if (y1 == y2) {
        if (y0 < y1)
            _draw_triangle_flat_bottom(v0, v1, v2, shade_mode);
        else
            _draw_triangle_flat_top(v0, v1, v2, shade_mode);
    }
    else {
        if ((y0 > y1 && y0 < y2) || (y0 < y1 && y0 > y2)) {
            vertex v_mid;
            _get_split_vertex(v_mid, v1, v2, v0.y);
            vertex v0_c = v0.clone();
            vertex v_mid_c = v_mid.clone();
            vertex v2_c = v2.clone();
            ra_draw_triangle(v1, v0, v_mid, shade_mode);
            ra_draw_triangle(v0_c, v_mid_c, v2_c, shade_mode);
        }
        else if ((y1 > y0 && y1 < y2) || (y1 < y0 && y1 > y2)) {
            vertex v_mid;
            _get_split_vertex(v_mid, v0, v2, v1.y);
            vertex v1_c = v1.clone();
            vertex v_mid_c = v_mid.clone();
            vertex v2_c = v2.clone();
            ra_draw_triangle(v0, v1, v_mid, shade_mode);
            ra_draw_triangle(v1_c, v_mid_c, v2_c, shade_mode);
        }
        else {
            vertex v_mid;
            _get_split_vertex(v_mid, v0, v1, v2.y);
            vertex v2_c = v2.clone();
            vertex v_mid_c = v_mid.clone();
            vertex v1_c = v1.clone();
            ra_draw_triangle(v0, v2, v_mid, shade_mode);
            ra_draw_triangle(v2_c, v_mid_c, v1_c, shade_mode);
        }
    }
}