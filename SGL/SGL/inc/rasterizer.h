#ifndef rasterizer_h
#define rasterizer_h

#include "common_header.h"
#include "color_buffer.h"

void ra_draw_line(uint x0, uint y0, uint x1, uint y1, color c);
void ra_draw_triangle(uint x0, uint y0,
                      uint x1, uint y1,
                      uint x2, uint y2, color c);

#endif