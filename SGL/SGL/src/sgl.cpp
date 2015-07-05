#include "GL/glew.h"

#include "sgl.h"
#include "color_buffer.h"
#include "vertex_buffer.h"

#include <assert.h>
#include <vector>

#include "sgl_math.h"
#include "sgl_context.h"

static std::vector<vertex_buffer*> s_vbs;
static color s_current_color;
static SGL_MATRIX_MODE s_current_matrix_mode;
static matrix4x4 s_mat_model_view;
static matrix4x4 s_mat_projection;
static sgl_viewport s_viewport;
static SGL_SHADE_MODEL s_current_shade_model;

static vertex_buffer * _get_current_vertex_buffer() {
    assert(s_vbs.size() > 0);
    return s_vbs[s_vbs.size() - 1];
}

static void _distroy_vbs() {
    for (int i = 0; i < s_vbs.size(); i++) {
        vertex_buffer *vb = s_vbs[i];
        delete vb;
    }
    s_vbs.clear();
}

void sgl_init_context() {
    s_current_matrix_mode = SGL_MODELVIEW;
    s_current_shade_model = SGL_FLAT;
}

void sglClear() {
    color_buffer::get_intance()->clear();
}

void sglBegin(SGL_PRIMITIVE_TYPE type) {
    s_vbs.clear();
    vertex_buffer *vb = new vertex_buffer();
    vb->set_primitive_type(type);
    s_vbs.push_back(vb);
}

void sglEnd() {
    //?
}

void sglVertex2f(float x, float y) {
    vertex_buffer *vb = _get_current_vertex_buffer();
    vertex v;
    v.x = x;
    v.y = y;
    v.set_color(s_current_color);
    vb->add_vertex(v);
}

void sglVertex3f(float x, float y, float z) {
    vertex_buffer *vb = _get_current_vertex_buffer();
    vertex v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.set_color(s_current_color);
    vb->add_vertex(v);
}

void sglColor3f(float r, float g, float b) {
    s_current_color.r = r;
    s_current_color.g = g;
    s_current_color.b = b;
}

void sglFlush() {
    //For a quick test.
    matrix4x4 mat_mvp = s_mat_model_view * s_mat_projection;
    for (int i = 0; i < s_vbs.size(); i++) {
        vertex_buffer *vb = s_vbs[i];
        vb->draw(&mat_mvp, &s_viewport, s_current_shade_model);
    }
    _distroy_vbs();
}

void sglMatrixMode(SGL_MATRIX_MODE mode) {
    s_current_matrix_mode = mode;
}

void sglLoadIdentity() {
    switch (s_current_matrix_mode) {
    case SGL_MODELVIEW:
        s_mat_model_view.identify();
        break;
    case SGL_PROJECTION:
        s_mat_projection.identify();
        break;
    default:
        break;
    }
}

void sglScalef(float x, float y, float z) {
    matrix4x4 s = matrix4x4::get_scale_matrix(x, y, z);
    switch (s_current_matrix_mode) {
    case SGL_MODELVIEW:
        s_mat_model_view = s_mat_model_view * s;
        break;
    case SGL_PROJECTION:
        s_mat_projection = s_mat_projection * s;
        break;
    default:
        break;
    }
}

void sglRotatef(float angle, float x, float y, float z) {
    matrix4x4 r;
    if (x == 1 && y == 0 && z == 0) {
        r = matrix4x4::get_rotate_x_matrix(angle);
    }
    else if (x == 0 && y == 1 && z == 0) {
        r = matrix4x4::get_rotate_y_matrix(angle);
    }
    else if (x == 0 && y == 0 && z == 1) {
        r = matrix4x4::get_rotate_z_matrix(angle);
    }

    switch (s_current_matrix_mode) {
    case SGL_MODELVIEW:
        s_mat_model_view = s_mat_model_view * r;
        break;
    case SGL_PROJECTION:
        s_mat_projection = s_mat_projection * r;
        break;
    default:
        break;
    }
}

void sglTranslatef(float x, float y, float z) {
    matrix4x4 t = matrix4x4::get_translation_matrix(x, y, z);
    switch (s_current_matrix_mode) {
    case SGL_MODELVIEW:
        s_mat_model_view = s_mat_model_view * t;
        break;
    case SGL_PROJECTION:
        s_mat_projection = s_mat_projection * t;
        break;
    default:
        break;
    }
}

void sgluLookAt(vec3 eye, vec3 target, vec3 up) {
    assert(s_current_matrix_mode == SGL_MODELVIEW);
    matrix4x4 v = matrix4x4::get_view_matrix(eye, target, up);
    s_mat_model_view = s_mat_model_view * v;
}

void sgluPerspective(float fovy, float aspect, float n, float f) {
    assert(s_current_matrix_mode == SGL_PROJECTION);
    matrix4x4 p = matrix4x4::get_perspective_matrix(fovy, aspect, n, f);
    s_mat_projection = s_mat_projection * p;
}

void sglViewport(uint x, uint y, uint w, uint h) {
    assert(x >= 0 && y >= 0 && w >= 0 && h >= 0);
    s_viewport.x = x;
    s_viewport.y = y;
    s_viewport.w = w;
    s_viewport.h = h;
}

void sglShadeModel(SGL_SHADE_MODEL mode) {
    s_current_shade_model = mode;
}