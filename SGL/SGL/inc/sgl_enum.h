#ifndef sgl_enum_h
#define sgl_enum_h

enum SGL_PRIMITIVE_TYPE {
    SGL_ENUM_NULL = -1,
    SGL_TRIANGLES = 0,
    SGL_POINTS,
    SGL_QUADS,
    SGL_POLYGON,
};

enum SGL_MATRIX_MODE {
    SGL_MODELVIEW = 0,
    SGL_PROJECTION
};

#endif