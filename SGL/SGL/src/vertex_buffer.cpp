#include "vertex_buffer.h"

#include <assert.h>

#include "rasterizer.h"

vertex::vertex() {
    _init();
}

vertex::~vertex() {
    
}

static inline void _swap_f(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

void vertex::swap(vertex &va, vertex &vb) {
    _swap_f(&va.x, &vb.x);
    _swap_f(&va.y, &vb.y);
    _swap_f(&va.z, &vb.z);
    _swap_f(&va.w, &vb.w);
    _swap_f(&va.r, &vb.r);
    _swap_f(&va.g, &vb.g);
    _swap_f(&va.b, &vb.b);
    _swap_f(&va.a, &vb.a);
    _swap_f(&va.u, &vb.u);
    _swap_f(&va.v, &vb.v);
}

void vertex::set_color(const color &c) {
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;
}

const color & vertex::get_color() const {
    _c.r = r;
    _c.g = g;
    _c.b = b;
    _c.a = a;
    return _c;
}

vertex vertex::clone() const {
    vertex v = *this;
    return v;
}

void vertex::set_texcoord(float u, float v) {
    this->u = u;
    this->v = v;
}

void vertex::_init() {
    x = y = z = 0;
    w = 1;
    r = g = b = a = 0;
    u = v = -1;
}

vertex_buffer::vertex_buffer() 
:_primitive_type(SGL_PRIMITIVE_TYPE_NULL) {
    
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

void vertex_buffer::draw(const matrix4x4 *mat_mvp, const sgl_viewport *viewport, SGL_SHADE_MODEL shade_mode) {
    for (int i = 0; i < _verts.size(); i++) {
        vertex *v = &_verts[i];
        vec4 vec(v->x, v->y, v->z, v->w);
        vec = vec * (*mat_mvp);
        v->x = vec.x / vec.w;
        v->y = vec.y / vec.w;
        v->z = vec.z / vec.w;
        v->w = 1;

        v->x = (v->x + 1)*(viewport->w - viewport->x) / 2 + viewport->x;
        v->y = (v->y + 1)*(viewport->y - viewport->h) / 2 + viewport->h;
    }

    switch (_primitive_type) {
    case SGL_PRIMITIVE_TYPE_NULL:
        assert(false);
        break;
    case SGL_TRIANGLES:
        for (int i = 0; i < _verts.size(); i+=3) {
            vertex *v0 = &_verts[i];
            vertex *v1 = &_verts[i + 1];
            vertex *v2 = &_verts[i + 2];
            
            ra_draw_triangle(*v0, *v1, *v2, shade_mode);
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

            ra_draw_triangle(*v0, *v1, *v2, shade_mode);
            ra_draw_triangle(*v0, *v2, *v3, shade_mode);
        }
        break;
    case SGL_POLYGON:
        break;
    default:
        break;
    }
   
    color_buffer::get_intance()->flush();
}