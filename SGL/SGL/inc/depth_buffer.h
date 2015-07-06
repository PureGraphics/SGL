#ifndef depth_buffer_h
#define depth_buffer_h

#include "common_header.h"
#include "interface_buffer.h"

class depth_buffer : public interface_buffer {
public:
    static depth_buffer * get_instance();
private:
    depth_buffer();
    ~depth_buffer();
public:
    void set_viewport(int w, int h) override;
    bool d_test(uint x, uint y, float d);
    void clear();
private:
    float *_d_buffer;
};

#endif