#pragma once



#include <GLFW/glfw3.h>

#include <stdbool.h>
typedef struct Window {
    GLFWwindow *window;
    int width;
    int height;
    void (*cursorPosCallback)(struct Window *, double, double);
    void (*windowSizeCallback)(struct Window *, int, int);
} Window;

typedef struct _CallbackContext {
    void *context;
    Window *window;
} _CallbackContext;

Window *createWindow(int width, int height, const char *title);
bool windowShouldClose(Window *window);
void setWindowShouldClose(Window *window, bool value);
void windowTerminate();

void windowSetUserPointer(Window *window, void *pointer);
void *windowGetUserPointer(Window *window);

void setCursorPosCallback(Window *window, void (*callback)(Window *, double, double));
void setWindowSizeCallback(Window *window, void (*callback)(Window *, int, int));

void endFrame(Window *window);

bool isWKeyDown(Window *window);
bool isAKeyDown(Window *window);
bool isSKeyDown(Window *window);
bool isDKeyDown(Window *window);
bool isSpaceKeyDown(Window *window);
bool isLeftKeyDown(Window *window);
bool isRightKeyDown(Window *window);
bool isTabKeyDown(Window *window);
bool isEscKeyDown(Window *window);

bool isLeftMouseDown(Window *window);

double getTime();
