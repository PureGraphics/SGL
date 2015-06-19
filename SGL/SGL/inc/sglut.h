#ifndef sglut_h
#define sglut_h

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

void sglut_init_window();
void sglut_display_func();
void sglut_mouse_func();
void sglut_keyboard_func();
void sglut_main_loop();

#endif