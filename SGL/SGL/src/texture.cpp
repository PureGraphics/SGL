#include "texture.h"

texture::texture() {
    _init();
}

texture::~texture() {
    _textures.clear();
}

void texture::_init() {
    _binding_texture = -1;
    _current_id = 0;
}

texture * texture::get_instance() {
    static texture *T = nullptr;
    if (T == nullptr) {
        T = new texture();
    }
    return T;
}

void texture::gen_textures(uint n, uint *textures) {
    for (int i = 0; i < n; i++) {
        int tex_id = _current_id++;
        textures[i] = tex_id;
        _textures[tex_id] = nullptr;
    }
}

void texture::load(uint texture, const char *path) {
    auto exist = _textures.find(texture);
    if (exist == _textures.end()) {
        return;
    }
    image_data *img = new image_data();
    img_load_image(path, img);
    _textures[texture] = img;
}

void texture::bind(uint texture) {
    _binding_texture = texture;
}

color texture::sampling(float u, float v) {
    assert(_binding_texture != -1);
    assert(u >= 0 && u <= 1);
    assert(v >= 0 && v <= 1);
    image_data *img = _textures[_binding_texture];
    uint tx = u * img->width;
    uint ty = v * img->height;
    uint ti = ty * img->width + tx;
    uint r, g, b, a;
    switch (img->format) {
    case IMG_FORMAT_RGB:
        r = img->pixels[ti];
        g = img->pixels[ti + 1];
        b = img->pixels[ti + 2];
        return color(r, g, b, 255);
    case IMG_FORMAT_BGR:
        b = img->pixels[ti];
        g = img->pixels[ti + 1];
        r = img->pixels[ti + 2];
        return color(r, g, b, 255);
    case IMG_FORMAT_RGBA:
        r = img->pixels[ti];
        g = img->pixels[ti + 1];
        b = img->pixels[ti + 2];
        a = img->pixels[ti + 3];
        return color(r, g, b, a);
    case IMG_FORMAT_BGRA:
        b = img->pixels[ti];
        g = img->pixels[ti + 1];
        r = img->pixels[ti + 2];
        a = img->pixels[ti + 3];
        return color(r, g, b, a);
    default:
        return color();
    }
}