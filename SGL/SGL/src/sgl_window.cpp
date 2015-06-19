#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "GL/glew.h"
#include "common_header.h"
#include "image.h"
#include "sglut.h"
#include "utils.h"

#define WINDOW_CLASS_NAME "WIN_LAUNCHER"

static DISPLAY_FUNC s_on_draw;
static MOUSE_FUNC s_on_mouse;
static KEYBOARD_FUNC s_on_keyboard;

static HWND s_hwnd = NULL;
static uint s_fps = 30;

static uint s_win_width = 100;
static uint s_win_height = 100;

static void _set_pixel_format(HDC hdc) {
    PIXELFORMATDESCRIPTOR pfd;

    int color_deep = GetDeviceCaps(hdc, BITSPIXEL);
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = color_deep;
    pfd.cDepthBits = 0;
    pfd.cStencilBits = 0;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int pixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pixelFormat, &pfd);
}

static void _init_ogl(HWND hwnd) {
    HDC hdc = GetDC(hwnd);
    _set_pixel_format(hdc);
    HGLRC glrc = wglCreateContext(hdc);
    if (glrc == 0) {
        exit(1);
    }
    wglMakeCurrent(hdc, glrc);

    if (glewInit() != GLEW_OK) {
        exit(1);
    }
    glViewport(0, 0, s_win_width, s_win_height);

    ReleaseDC(hwnd, hdc);
}

static void _get_mouse_xy(LPARAM lParam, int *x, int *y) {
    *x = (short)(lParam & 0xffff);
    *y = (short)((lParam >> 16) & 0xffff);
}

LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
    case WM_CREATE:
        _init_ogl(hwnd);
        SetTimer(hwnd, 0, s_fps, NULL);
        break;
    case WM_TIMER:
        if (s_on_draw) {
            s_on_draw();
        }
        InvalidateRect(hwnd, NULL, false);
        break;
    case WM_PAINT:
        if (GetUpdateRect(hwnd, NULL, false)) {
            HDC hdc = GetDC(hwnd);
            SwapBuffers(hdc);
            ValidateRect(hwnd, NULL);
            ReleaseDC(hwnd, hdc);
        }
        return 0;
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_LBUTTONDBLCLK:
        if (s_on_mouse) {
            int x, y;
            _get_mouse_xy(lparam, &x, &y);
            ENUM_MOUSE_STATE ms = (ENUM_MOUSE_STATE)(msg - WM_LBUTTONDOWN);
            s_on_mouse(ms, x, y);
        }
        break;
    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_KEYLAST:
        if (s_on_keyboard) {
            ENUM_KEYBOARD_STATE ks;
            switch (msg) {
            case WM_KEYDOWN:
                ks = KEY_DOWN;
                break;
            case WM_KEYUP:
                ks = KEY_UP;
                break;
            case WM_KEYLAST:
                ks = KEY_LAST;
                break;
            default:
                break;
            }
            s_on_keyboard(ks, wparam);
        }
        break;
    case WM_DESTROY:
        img_lib_dispose();
        ::CoUninitialize();
        PostQuitMessage(0);
        return 0;
    default:
        break;
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}

bool sglut_init_window(uint width, uint height) {
    ::CoInitialize(NULL);
    img_lib_init();

    assert(width > 0 && width < 3000);
    assert(width > 0 && width < 3000);
    s_win_width = width;
    s_win_height = height;

    WNDCLASSEX winclass;
    HWND hwnd;

    winclass.cbSize = sizeof(WNDCLASSEX);
    winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    winclass.lpfnWndProc = window_proc;
    winclass.cbClsExtra = 0;
    winclass.cbWndExtra = 0;
    winclass.hInstance = GetModuleHandleW(0);
    winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    winclass.lpszMenuName = NULL;
    winclass.lpszClassName = char2wchar_t(WINDOW_CLASS_NAME);
    winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&winclass))
        return false;

    hwnd = CreateWindowEx(NULL,
        char2wchar_t(WINDOW_CLASS_NAME),
        char2wchar_t("SGL"),
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100,
        width, height,
        NULL,
        NULL,
        GetModuleHandleW(0),
        NULL);
    if (hwnd == NULL)
        return false;

    s_hwnd = hwnd;
    return true;
}

void sglut_main_loop() {
    MSG msg;
    while (true) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}

extern void main();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    main();
    return 0;
}

void sglut_display_func(DISPLAY_FUNC func) {
    s_on_draw = func;
}

void sglut_mouse_func(MOUSE_FUNC func) {
    s_on_mouse = func;
}

void sglut_keyboard_func(KEYBOARD_FUNC func) {
    s_on_keyboard = func;
}