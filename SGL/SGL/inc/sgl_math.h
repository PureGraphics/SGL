#ifndef sgl_math_h
#define sgl_math_h

#include "common_header.h"

class vec2 {
public:
    vec2();
    vec2(float x, float y);
    vec2(const vec2 &v);
    ~vec2();
public:
    //TODO...
public:
    float x, y;
};

class vec3 {
public:
    vec3();
    vec3(float x, float y, float z);
    vec3(const vec3 &v);
    ~vec3();
public:
    float operator[](uint index) const;
    vec3 operator+(const vec3 &v) const;
    vec3 operator-(const vec3 &v) const;
    vec3 operator*(float s) const;
public:
    float dot(const vec3 &v) const;
    vec3 cross(const vec3 &v) const;
    float length() const;
    void normalize();
public:
    float x, y, z;
};

class vec4 {
public:
    vec4();
    vec4(float x, float y, float z, float w);
    vec4(const vec3 &v);
public:
    vec4 operator+(const vec4 &v) const;
    //vec4 operator*(float s) const;
public:
    float x, y, z, w;
};

class matrix4x4 {
public:
    matrix4x4();
    matrix4x4(const float *mat_array);
    ~matrix4x4();
public:
    static matrix4x4 get_scale_matrix(float sx, float sy, float sz);
    static matrix4x4 get_rotate_x_matrix(float angle);
    static matrix4x4 get_rotate_y_matrix(float angle);
    static matrix4x4 get_rotate_z_matrix(float angle);
    static matrix4x4 get_translation_matrix(float tx, float ty, float tz);
public:
    void fill_matrix(const float *mat_array);
public:
    float m[4][4];
};

static vec4 operator*(const vec4 &v, const matrix4x4 &m) {
    vec4 tv;
    tv.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + v.w * m.m[3][0];
    tv.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + v.w * m.m[3][1];
    tv.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + v.w * m.m[3][2];
    tv.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + v.w * m.m[3][3];
    return tv;
}

#define M_PI 3.14159265358979323846

static float deg_2_rad(float deg) {
    return M_PI / 180 * deg;
}

static float rad_2_deg(float rad) {
    return 180 / M_PI * rad;
}

#endif