#ifndef rasterizer_h
#define rasterizer_h

#include "common_header.h"
#include "color_buffer.h"

void ra_draw_line(int x0, int y0, int x1, int y1, color c);
void ra_draw_triangle(int x0, int y0,
                      int x1, int y1,
                      int x2, int y2, color c);

#endif