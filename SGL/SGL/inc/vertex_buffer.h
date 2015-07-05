#ifndef vertex_buffer_h
#define vertex_buffer_h

#include <vector>

#include "sgl_enum.h"
#include "color_buffer.h"
#include "sgl_math.h"
#include "sgl_context.h"

typedef struct vertex {
public:
    vertex() 
    :x(0),y(0),z(0),w(1),
     r(0),g(0),b(0),a(255) {
        
    }
    ~vertex() {}
public:
    void set_color(const color &c) {
        r = c.r;
        g = c.g;
        b = c.b;
        a = c.a;
    }

    float x, y, z, w;
    float r, g, b, a;
} vertex;

class vertex_buffer {
public:
    vertex_buffer();
    ~vertex_buffer();
public:
    void set_primitive_type(SGL_PRIMITIVE_TYPE type);
    void add_vertex(vertex v);
    void clear();
    SGL_PRIMITIVE_TYPE get_primitive_type() const;
    void draw(const matrix4x4 *mat_mvp, const sgl_viewport *viewport);
private:
    std::vector<vertex> _verts;
    SGL_PRIMITIVE_TYPE _primitive_type;
};

#endif