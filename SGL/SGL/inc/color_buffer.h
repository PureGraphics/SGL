#ifndef color_buffer_h
#define color_buffer_h

#include "interface_buffer.h"

#include <vector>

#include "image.h"

class color {
public:
    color();
    color(int pr, int pg, int pb, int pa);
    ~color();
public:
    void copy(const color &c);
public:
    int r, g, b, a;
};

class color_buffer : public interface_buffer {
public:
    color_buffer();
    ~color_buffer();
public:
    void set_viewport(int w, int h) override;
    void write_color(int x, int y, color c);
    void write_colors(int x, int y, image_data *img);
    void clear();
    void flush();
private:
    void _init_buffer();
private:
    std::vector<color*> _buffer;
    uchar *_pixels;
};

#endif