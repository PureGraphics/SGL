#include "GL/glew.h"

#include "sgl.h"
#include "color_buffer.h"
#include "vertex_buffer.h"

#include <assert.h>
#include <vector>

static std::vector<vertex_buffer*> s_vbs;
static color s_current_color;

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
    for (int i = 0; i < s_vbs.size(); i++) {
        vertex_buffer *vb = s_vbs[i];
        vb->draw();
    }
    _distroy_vbs();
}

void sglMatrixMode(SGL_MATRIX_MODE mode) {
    
}

void sglScalef(float x, float y, float z) {
    
}