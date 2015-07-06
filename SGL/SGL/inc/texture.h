#ifndef texture_h
#define texture_h

#include "common_header.h"
#include "image.h"
#include "color_buffer.h"
#include <map>

class texture {
public:
    static texture * get_instance();
private:
    texture();
    ~texture();
public:
    void gen_textures(uint n, uint *textures);
    void load(uint texture, const char *path);
    void bind(uint texture);
    color sampling(float u, float v);
private:
    void _init();
private:
    std::map<uint, image_data*> _textures;
    int _binding_texture;
    int _current_id;
};

#endif