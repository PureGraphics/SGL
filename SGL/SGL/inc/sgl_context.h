#ifndef sgl_context_h
#define sgl_context_h

void sgl_init_context();

typedef struct sgl_viewport {
    int x, y, w, h;
} sgl_viewport;

#endif