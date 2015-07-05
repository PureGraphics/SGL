#ifndef rasterizer_h
#define rasterizer_h

#include "common_header.h"
#include "color_buffer.h"
#include "vertex_buffer.h"

void ra_draw_line(int x0, int y0, int x1, int y1, const color &c);
void ra_draw_triangle(const vertex &v0,
                      const vertex &v1,
                      const vertex &v2);

#endif