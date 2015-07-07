#include "depth_buffer.h"
#include <memory.h>

depth_buffer::depth_buffer()
:interface_buffer(), _d_buffer(nullptr) {
    
}

depth_buffer::~depth_buffer() {
    delete[] _d_buffer;
}

depth_buffer * depth_buffer::get_instance() {
    static depth_buffer *T = nullptr;
    if (T == nullptr) {
        T = new depth_buffer();
    }
    return T;
}

void depth_buffer::set_viewport(int w, int h) {
    _buffer_w = w;
    _buffer_h = h;

    int sz = w * h;
    _d_buffer = new float[sz];
    for (int i = 0; i < sz; i++) {
        _d_buffer[i] = 1.0f;
    }
}

bool depth_buffer::d_test(uint x, uint y, float d) {
    if (x >= _buffer_w || y >= _buffer_h) {
        return false;
    }
    uint i = y * _buffer_w + x;
    if (_d_buffer[i] > d) {
        _d_buffer[i] = d;
        return true;
    }
    return false;
}

void depth_buffer::clear() {
    int sz = _buffer_w * _buffer_h;
    for (int i = 0; i < sz; i++) {
        _d_buffer[i] = 1.0f;
    }
}