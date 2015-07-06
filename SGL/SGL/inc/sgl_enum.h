#ifndef sgl_enum_h
#define sgl_enum_h

enum SGL_PRIMITIVE_TYPE {
    SGL_PRIMITIVE_TYPE_NULL = -1,
    SGL_TRIANGLES = 0,
    SGL_POINTS,
    SGL_QUADS,
    SGL_POLYGON,
};

enum SGL_MATRIX_MODE {
    SGL_MODELVIEW = 0,
    SGL_PROJECTION
};

enum SGL_SHADE_MODEL {
    SGL_FLAT = 0,
    SGL_SMOOTH
};

enum SGL_TEXTURE {
    SGL_TEXTURE_2D = 0,
};

#endif