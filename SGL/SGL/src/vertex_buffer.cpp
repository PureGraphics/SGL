#include "vertex_buffer.h"

#include <assert.h>

#include "rasterizer.h"

vertex_buffer::vertex_buffer() 
:_primitive_type(SGL_ENUM_NULL) {
    
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
    color_buffer::get_intance()->clear();

    switch (_primitive_type) {
    case SGL_ENUM_NULL:
        assert(false);
        break;
    case SGL_TRIANGLES:
        for (int i = 0; i < _verts.size(); i+=3) {
            vertex *v0 = &_verts[i];
            vertex *v1 = &_verts[i + 1];
            vertex *v2 = &_verts[i + 2];
            
            ra_draw_triangle(v0->x, v0->y, v1->x, v1->y, v2->x, v2->y, color(v0->r, v0->g, v0->b, v0->a));
        }
        break;
    case SGL_POINTS:
        for (int i = 0; i < _verts.size(); i++) {
            vertex *v = &_verts[i];
            color_buffer::get_intance()->write_color(v->x, v->y, color(v->r, v->g, v->b, v->a));
        }
        break;
    case SGL_QUADS:
        for (int i = 0; i < _verts.size(); i += 4) {
            vertex *v0 = &_verts[i];
            vertex *v1 = &_verts[i + 1];
            vertex *v2 = &_verts[i + 2];
            vertex *v3 = &_verts[i + 3];

            ra_draw_triangle(v0->x, v0->y, v1->x, v1->y, v2->x, v2->y, color(v0->r, v0->g, v0->b, v0->a));
            ra_draw_triangle(v0->x, v0->y, v2->x, v2->y, v3->x, v3->y, color(v0->r, v0->g, v0->b, v0->a));
        }
        break;
    case SGL_POLYGON:
        break;
    default:
        break;
    }
   
    color_buffer::get_intance()->flush();
}