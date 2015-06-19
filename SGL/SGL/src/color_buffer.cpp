#include "color_buffer.h"

#include <assert.h>

#define CHECK() \
    assert(_buffer_w > 0 && _buffer_h < 3000); \

color::color() 
:r(0),g(0),b(0),a(0) {
       
}

color::color(int pr, int pg, int pb, int pa) {
    r = pr;
    g = pg;
    b = pb;
    a = pa;
}

color::~color() {
    
}

void color::copy(const color &c) {
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;
}

color_buffer::color_buffer()
:interface_buffer() {
    
}

color_buffer::~color_buffer() {
    for (auto it = _buffer.begin(); it != _buffer.end(); ++it) {
        delete (*it);
    }
    _buffer.clear();
}

void color_buffer::set_viewport(int w, int h) {
    _buffer_w = w;
    _buffer_h = h;
    CHECK();
    _init_buffer();
}

void color_buffer::write_color(int x, int y, color c) {
    CHECK();
    color *pc = _buffer[y * _buffer_w + x];
    pc->copy(c);
}

void color_buffer::write_colors(int x, int y, image_data *img) {
    
}

void color_buffer::flush() {
    
}

void color_buffer::_init_buffer() {
    for (int row = 0; row < _buffer_h; row++) {
        for (int col = 0; col < _buffer_w; col++) {
            _buffer.push_back(new color());
        }
    }
}