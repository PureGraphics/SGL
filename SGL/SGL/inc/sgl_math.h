#ifndef math_h
#define math_h

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
    vec4 operator*(float s) const;
public:
    float x, y, z, w;
};

#endif