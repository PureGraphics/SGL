#include "GL/glew.h"

#include "sgl.h"
#include "color_buffer.h"
#include "vertex_buffer.h"

#include <assert.h>
#include <vector>

#include "sgl_math.h"

static std::vector<vertex_buffer*> s_vbs;
static color s_current_color;
static SGL_MATRIX_MODE s_current_matrix_mode;
static matrix4x4 s_mat_model_view;
static matrix4x4 s_mat_projection;

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
        vb->draw(&mat_mvp);
    }
    _distroy_vbs();

    s_mat_model_view.identify();
    s_mat_projection.identify();
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
        s_mat_model_view = s_mat_model_view * s;
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
        s_mat_model_view = s_mat_model_view * r;
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
        s_mat_model_view = s_mat_model_view * t;
        break;
    default:
        break;
    }
}