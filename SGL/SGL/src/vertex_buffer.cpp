#include "vertex_buffer.h"

vertex_buffer::vertex_buffer() 
:_primitive_type(SGL_NULL) {
    
}

vertex_buffer::~vertex_buffer() {
    _verts.clear();
}

void vertex_buffer::set_primitive_type(SGL_PRIMITIVE_TYPE type) {
    _primitive_type = type;
}

void vertex_buffer::add_vertex(vertex v) {
    _verts.push_back(v);
}

void vertex_buffer::clear() {
    _verts.clear();
}

SGL_PRIMITIVE_TYPE vertex_buffer::get_primitive_type() const {
    return _primitive_type;
}

void vertex_buffer::draw() {
    //For quick test only...
    color_buffer::get_intance()->clear();
    for (int i = 0; i < _verts.size(); i++) {
        vertex *v = &_verts[i];
        color_buffer::get_intance()->write_color(v->x, v->y, color(v->r, v->g, v->b, 255));
    }
    color_buffer::get_intance()->flush();
}