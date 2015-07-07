#include "sgl.h"
#include "sglut.h"
#include "sgl_math.h"

#define WW 960
#define WH 640

static uint s_textures[3];

static void _init() {
    sglShadeModel(SGL_SMOOTH);
    sglMatrixMode(SGL_PROJECTION);
    sgluPerspective(60, (float)WW / WH, 0.1f, 1000.0f);

    sglMatrixMode(SGL_MODELVIEW);
    sglLoadIdentity();
    sgluLookAt(vec3(0, 0.6, -3.5), vec3(0, 0, 1), vec3(0, 1, 0));

    sglViewport(0, 0, WW, WH);

    sglGenTextures(3, s_textures);
    sglLoadTexture(s_textures[0], "E:/Girl.jpg");
    sglLoadTexture(s_textures[1], "E:/Carmack.jpg");
    sglLoadTexture(s_textures[2], "E:/Overlay.jpg");
}

static float s_rot_angle = 0;
static float s_scale = 1.0f;

float cube_pos[8][3] = {
    { -0.5, 0.5, 0.5 },
    { 0.5, 0.5, 0.5 },
    { 0.5, 0.5, -0.5 },
    { -0.5, 0.5, -0.5 },
    { -0.5, -0.5, 0.5 },
    { 0.5, -0.5, 0.5 },
    { 0.5, -0.5, -0.5 },
    { -0.5, -0.5, -0.5 }
};

float colors[][3] = {
    { 255, 0, 0 },
    { 0, 255, 0 },
    { 0, 0, 255 },
    { 255, 255, 255 }
};

float texcoord[][2] = {
    { 0, 0 },
    { 1, 0 },
    { 1, 1 },
    { 0, 1 }
};

static void _draw_cube(bool texture) {
    sglBegin(SGL_QUADS);
    //0.
    sglColor3fv(colors[0]);
    texture ? (sglTexCoord2fv(texcoord[0])) : (false);
    sglVertex3fv(cube_pos[0]);

    sglColor3fv(colors[1]);
    texture ? (sglTexCoord2fv(texcoord[1])) : (false);
    sglVertex3fv(cube_pos[1]);

    sglColor3fv(colors[2]);
    texture ? (sglTexCoord2fv(texcoord[2])) : (false);
    sglVertex3fv(cube_pos[2]);

    sglColor3fv(colors[3]);
    texture ? (sglTexCoord2fv(texcoord[3])) : (false);
    sglVertex3fv(cube_pos[3]);

    //1. 
    sglColor3fv(colors[0]);
    texture ? (sglTexCoord2fv(texcoord[0])) : (false);
    sglVertex3fv(cube_pos[3]);

    sglColor3fv(colors[1]);
    texture ? (sglTexCoord2fv(texcoord[1])) : (false);
    sglVertex3fv(cube_pos[2]);

    sglColor3fv(colors[2]);
    texture ? (sglTexCoord2fv(texcoord[2])) : (false);
    sglVertex3fv(cube_pos[6]);

    sglColor3fv(colors[3]);
    texture ? (sglTexCoord2fv(texcoord[3])) : (false);
    sglVertex3fv(cube_pos[7]);

    //2. 
    sglColor3fv(colors[0]);
    texture ? (sglTexCoord2fv(texcoord[0])) : (false);
    sglVertex3fv(cube_pos[4]);

    sglColor3fv(colors[1]);
    texture ? (sglTexCoord2fv(texcoord[1])) : (false);
    sglVertex3fv(cube_pos[5]);

    sglColor3fv(colors[2]);
    texture ? (sglTexCoord2fv(texcoord[2])) : (false);
    sglVertex3fv(cube_pos[6]);

    sglColor3fv(colors[3]);
    texture ? (sglTexCoord2fv(texcoord[3])) : (false);
    sglVertex3fv(cube_pos[7]);

    //3.
    sglColor3fv(colors[0]);
    texture ? (sglTexCoord2fv(texcoord[0])) : (false);
    sglVertex3fv(cube_pos[0]);

    sglColor3fv(colors[1]);
    texture ? (sglTexCoord2fv(texcoord[1])) : (false);
    sglVertex3fv(cube_pos[1]);

    sglColor3fv(colors[2]);
    texture ? (sglTexCoord2fv(texcoord[2])) : (false);
    sglVertex3fv(cube_pos[5]);

    sglColor3fv(colors[3]);
    texture ? (sglTexCoord2fv(texcoord[3])) : (false);
    sglVertex3fv(cube_pos[4]);

    //4.
    sglColor3fv(colors[0]);
    texture ? (sglTexCoord2fv(texcoord[0])) : (false);
    sglVertex3fv(cube_pos[0]);

    sglColor3fv(colors[1]);
    texture ? (sglTexCoord2fv(texcoord[1])) : (false);
    sglVertex3fv(cube_pos[3]);

    sglColor3fv(colors[2]);
    texture ? (sglTexCoord2fv(texcoord[2])) : (false);
    sglVertex3fv(cube_pos[7]);

    sglColor3fv(colors[3]);
    texture ? (sglTexCoord2fv(texcoord[3])) : (false);
    sglVertex3fv(cube_pos[6]);

    //5.
    sglColor3fv(colors[0]);
    texture ? (sglTexCoord2fv(texcoord[0])) : (false);
    sglVertex3fv(cube_pos[2]);

    sglColor3fv(colors[1]);
    texture ? (sglTexCoord2fv(texcoord[1])) : (false);
    sglVertex3fv(cube_pos[1]);

    sglColor3fv(colors[2]);
    texture ? (sglTexCoord2fv(texcoord[2])) : (false);
    sglVertex3fv(cube_pos[5]);

    sglColor3fv(colors[3]);
    texture ? (sglTexCoord2fv(texcoord[3])) : (false);
    sglVertex3fv(cube_pos[6]);

    sglEnd();
}

static void _draw_overlay() {
    sglMatrixMode(SGL_MODELVIEW);
    sglLoadIdentity();

    sglScalef(1.5, 1.5, 1.5);
    sglTranslatef(0, 2.5, 1);

    sglBindTexture(SGL_TEXTURE_2D, s_textures[2]);
    sglBegin(SGL_QUADS);

    sglTexCoord2f(0, 0);
    sglVertex3f(-0.5, 0.5, 0.1);

    sglTexCoord2f(1, 0);
    sglVertex3f(0.5, 0.5, 0.1);

    sglTexCoord2f(1, 1);
    sglVertex3f(0.5, -0.5, 0.1);

    sglTexCoord2f(0, 1);
    sglVertex3f(-0.5, -0.5, 0.1);

    sglEnd();
}

static void _on_draw() {
    sglClear();
    sglMatrixMode(SGL_MODELVIEW);

    //0. overlay stuff.
    _draw_overlay();

    sglMatrixMode(SGL_MODELVIEW);
    sglLoadIdentity();
    sglRotatef(s_rot_angle, 0, 1, 0);
    if (++s_rot_angle > 360)
        s_rot_angle = 0;

    //1. colored cube.
    _draw_cube(false);

    //2. textured cube 1.
    sglBindTexture(SGL_TEXTURE_2D, s_textures[0]);
    sglTranslatef(-0.6, 1.2, 0);
    _draw_cube(true);

    //3. textured cube 2.
    sglBindTexture(SGL_TEXTURE_2D, s_textures[1]);
    sglTranslatef(1, 0, 0.8);
    _draw_cube(true);

    //4. ...
    sglTranslatef(1.3, -1.8, 0);
    sglBegin(SGL_QUADS);

    sglColor3fv(colors[0]);
    sglVertex3f(-0.5, 0.5, 0);

    sglColor3fv(colors[1]);
    sglVertex3f(0.5, 0.5, 0);

    sglColor3fv(colors[2]);
    sglVertex3f(0.5, -0.5, 0);

    sglColor3fv(colors[3]);
    sglVertex3f(-0.5, -0.5, 0);

    sglColor3fv(colors[0]);
    sglVertex3f(0, 0.5, -0.5);

    sglColor3fv(colors[1]);
    sglVertex3f(0, 0.5, 0.5);

    sglColor3fv(colors[2]);
    sglVertex3f(0, -0.5, 0.5);

    sglColor3fv(colors[3]);
    sglVertex3f(0, -0.5, -0.5);

    sglEnd();

    sglFlush();
}

void main() {
    sglut_init_window(WW, WH);
    _init();
    sglut_display_func(_on_draw);
    sglut_main_loop();
}