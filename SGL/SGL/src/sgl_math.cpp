#include "sgl_math.h"

#include <assert.h>
#include <math.h>

vec2::vec2() 
:x(0), y(0) {
    
}

vec2::vec2(float x, float y)
:x(x), y(y) {
    
}

vec2::vec2(const vec2 &v)
:x(v.x), y(v.y) {
    
}

vec2::~vec2() {
    
}

vec3::vec3()
:x(0), y(0), z(0) {
    
}

vec3::vec3(float x, float y, float z)
:x(x), y(y), z(z) {
    
}

vec3::vec3(const vec3 &v)
:x(v.x), y(v.y), z(v.z) {
    
}

vec3::~vec3() {
    
}

float vec3::operator[](uint index) const {
    assert(index >= 0 && index <= 2);
    if (index == 0)
        return x;
    else if (index == 1)
        return y;
    else if (index == 2)
        return z;
    return 0;
}

vec3 vec3::operator+(const vec3 &v) const {
    return vec3(x + v.x, y + v.y, z + v.z);
}

vec3 vec3::operator-(const vec3 &v) const {
    return vec3(x - v.x, y - v.y, z - v.z);
}

vec3 vec3::operator*(float s) const {
    return vec3(x * s, y * s, z * s);
}

float vec3::dot(const vec3 &v) const {
    return x * v.x + y * v.y + z * v.z;
}

vec3 vec3::cross(const vec3 &v) const {
    return vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

float vec3::length() const {
    return sqrtf(x*x + y*y + z*z);
}

void vec3::normalize() {
    float s = 1.0f / length();
    x *= s;
    y *= s;
    z *= s;
}

vec4::vec4() {
    
}

vec4::vec4(float x, float y, float z, float w)
:x(x), y(y), z(z), w(w)
{
    
}

vec4::vec4(const vec3 &v)
: x(v.x), y(v.y), z(v.z), w(1.0f)
{
    
}

vec4 vec4::operator+(const vec4 &v) const{
    return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
}

//vec4 vec4::operator*(float s) const{
//    return vec4(x * s, y * s, z * s, w * s);
//}

matrix4x4::matrix4x4() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i][j] = 0;
        }
    }
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
}

matrix4x4::matrix4x4(const float *mat_array) {
    fill_matrix(mat_array);
}

matrix4x4::~matrix4x4() {
    
}

matrix4x4 matrix4x4::get_scale_matrix(float sx, float sy, float sz) {
    float mat[] = {
        sx, 0, 0, 0,
        0, sy, 0, 0,
        0, 0, sz, 0,
        0, 0, 0,  1
    };
    return matrix4x4(mat);
}

matrix4x4 matrix4x4::get_rotate_x_matrix(float angle) {
    float a = deg_2_rad(angle);
    float mat[] = {
        1, 0, 0, 0,
        0, cos(a), sin(a), 0,
        0, -sin(a), cos(a), 0,
        0, 0, 0, 1
    };
    return matrix4x4(mat);
}

matrix4x4 matrix4x4::get_rotate_y_matrix(float angle) {
    float a = deg_2_rad(angle);
    float mat[] = {
        cos(a), 0, -sin(a), 0,
        0, 1, 0, 0,
        sin(a), 0, cos(a), 0,
        0, 0, 0, 1
    };
    return matrix4x4(mat);
}

matrix4x4 matrix4x4::get_rotate_z_matrix(float angle) {
    float a = deg_2_rad(angle);
    float mat[] = {
        cos(a), sin(a), 0, 0,
        -sin(a), cos(a), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    return matrix4x4(mat);
}

matrix4x4 matrix4x4::get_translation_matrix(float tx, float ty, float tz) {
    float mat[] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        tx, ty, tz, 1
    };
    return matrix4x4(mat);
}

void matrix4x4::fill_matrix(const float *mat_array) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i][j] = mat_array[i * 4 + j];
        }
    }
}