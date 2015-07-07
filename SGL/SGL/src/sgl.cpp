#include "GL/glew.h"

#include "sgl.h"
#include "color_buffer.h"
#include "vertex_buffer.h"

#include <assert.h>
#include <vector>

#include "sgl_math.h"
#include "sgl_context.h"
#include "texture.h"
#include "depth_buffer.h"

static std::vector<vertex_buffer*> s_vbs;
static color s_current_color;
static SGL_MATRIX_MODE s_current_matrix_mode;
static matrix4x4 s_mat_model;
static matrix4x4 s_mat_view;
static matrix4x4 s_mat_projection;
static sgl_viewport s_viewport;
static SGL_SHADE_MODEL s_current_shade_model;
static float s_current_texcoord_x;
static float s_current_texcoord_y;
static uint s_current_binding_texture;

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
    s_current_texcoord_x = -1;
    s_current_texcoord_y = -1;
}

void sglClear() {
    color_buffer::get_intance()->clear();
    depth_buffer::get_instance()->clear();
}

void sglBegin(SGL_PRIMITIVE_TYPE type) {
    vertex_buffer *vb = new vertex_buffer();
    vb->set_primitive_type(type);
    s_vbs.push_back(vb);
}

void sglEnd() {
    vertex_buffer *vb = _get_current_vertex_buffer();
    vb->set_model_matrix(s_mat_model);
    vb->set_texture(s_current_binding_texture);
}

void sglVertex2f(float x, float y) {
    sglVertex3f(x, y, 0.0f);
}

void sglVertex3f(float x, float y, float z) {
    vertex_buffer *vb = _get_current_vertex_buffer();
    vertex v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.set_color(s_current_color);
    if (s_current_texcoord_x != -1 && s_current_texcoord_y != -1) {
        v.set_texcoord(s_current_texcoord_x, s_current_texcoord_y);
        s_current_texcoord_x = -1;
        s_current_texcoord_y = -1;
    }
    vb->add_vertex(v);
}

void sglVertex3fv(const float *pointer) {
    sglVertex3f(pointer[0], pointer[1], pointer[2]);
}

void sglColor3f(float r, float g, float b) {
    s_current_color.r = r;
    s_current_color.g = g;
    s_current_color.b = b;
}

void sglColor3fv(const float *pointer) {
    sglColor3f(pointer[0], pointer[1], pointer[2]);
}

void sglFlush() {
    matrix4x4 mat_view_proj = s_mat_view * s_mat_projection;
    for (int i = 0; i < s_vbs.size(); i++) {
        vertex_buffer *vb = s_vbs[i];
        vb->draw(&mat_view_proj, &s_viewport, s_current_shade_model);
    }
    _distroy_vbs();

    s_current_texcoord_x = -1;
    s_current_texcoord_y = -1;
}

void sglMatrixMode(SGL_MATRIX_MODE mode) {
    s_current_matrix_mode = mode;
}

void sglLoadIdentity() {
    switch (s_current_matrix_mode) {
    case SGL_MODELVIEW:
        s_mat_model.identify();
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
        s_mat_model = s_mat_model * s;
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
        s_mat_model = s_mat_model * r;
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
        s_mat_model = s_mat_model * t;
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
    s_mat_view = matrix4x4::get_view_matrix(eye, target, up);
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

void sglTexCoord2f(float x, float y) {
    s_current_texcoord_x = x;
    s_current_texcoord_y = y;
}

void sglTexCoord2fv(const float *pointer) {
    sglTexCoord2f(pointer[0], pointer[1]);
}

void sglGenTextures(uint n, uint *textures) {
    texture::get_instance()->gen_textures(n, textures);
}

void sglLoadTexture(uint texture, const char *path) {
    texture::get_instance()->load(texture, path);
}

void sglBindTexture(SGL_TEXTURE target, uint texture) {
    s_current_binding_texture = texture;
}