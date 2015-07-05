#ifndef rasterizer_h
#define rasterizer_h

#include "common_header.h"
#include "color_buffer.h"
#include "vertex_buffer.h"
#include "sgl_enum.h"

void ra_draw_line(int x0, int y0, int x1, int y1, const color &c);
void ra_draw_triangle(vertex &v0,
                      vertex &v1,
                      vertex &v2, SGL_SHADE_MODEL shade_mode);

#endif