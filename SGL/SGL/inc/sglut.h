#ifndef sglut_h
#define sglut_h

#include "common_header.h"

enum ENUM_MOUSE_STATE {
    LBUTTON_DOWN = 0,
    LBUTTON_UP,
    LBUTTON_CLICK,
};

enum ENUM_KEYBOARD_STATE {
    KEY_DOWN = 0,
    KEY_UP,
    KEY_LAST
};

typedef void(*DISPLAY_FUNC)();
typedef void(*MOUSE_FUNC)(ENUM_MOUSE_STATE ms, int x, int y);
typedef void(*KEYBOARD_FUNC)(ENUM_KEYBOARD_STATE ks, int code);

bool sglut_init_window(uint w, uint h);
void sglut_display_func(DISPLAY_FUNC func);
void sglut_mouse_func(MOUSE_FUNC func);
void sglut_keyboard_func(KEYBOARD_FUNC func);
void sglut_main_loop();

#endif