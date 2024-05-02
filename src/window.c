#include <glad/glad.h>
#include "window.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


bool createGlfwWindow(Window *window, int width, int height, const char *title) {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    window->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window->window);
    glfwSwapInterval(1);

    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(window->window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        printf("raw mouse\n");
    }

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return false;
    }

    _CallbackContext *cbc = malloc(sizeof(_CallbackContext));
    cbc->window = window;
    glfwSetWindowUserPointer(window->window, cbc);

    return true;
}

Window *createWindow(int width, int height, const char *title) {
    Window *window = malloc(sizeof(Window));
    window->width = width;
    window->height = height;
    if (!createGlfwWindow(window, width, height, title)) {
        return NULL;
    }
    return window;
}

bool windowShouldClose(Window *window) {
    return glfwWindowShouldClose(window->window);
}

void setWindowShouldClose(Window *window, bool value) {
    glfwSetWindowShouldClose(window->window, value);
}

void windowTerminate() {
    glfwTerminate();
}

void windowSetUserPointer(Window *window, void *pointer) {
    _CallbackContext *cbc = (_CallbackContext *)glfwGetWindowUserPointer(window->window);
    cbc->context = pointer;
}


void *windowGetUserPointer(Window *window) {
    assert(window->window != NULL);
    _CallbackContext *cbc = (_CallbackContext *)glfwGetWindowUserPointer(window->window);
    return cbc->context;
}

void cursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
    _CallbackContext *cbc = (_CallbackContext *)glfwGetWindowUserPointer(window);
    if (cbc->window->cursorPosCallback != NULL) {
        cbc->window->cursorPosCallback(cbc->window, xpos, ypos);
    }
}

void setCursorPosCallback(Window *window, void (*callback)(Window *, double, double)) {
    glfwSetCursorPosCallback(window->window, cursorPosCallback);
    window->cursorPosCallback = callback;
}

void windowSizeCallback(GLFWwindow *window, int width, int height) {
    _CallbackContext *cbc = (_CallbackContext *)glfwGetWindowUserPointer(window);
    if (cbc->window->windowSizeCallback != NULL) {
        cbc->window->windowSizeCallback(cbc->window, width, height);
    }
}

void setWindowSizeCallback(Window *window, void (*callback)(Window *, int, int)) {
    glfwSetWindowSizeCallback(window->window, windowSizeCallback);
    window->windowSizeCallback = callback;
}

void endFrame(Window *window) {
    glfwSwapBuffers(window->window);
    glfwPollEvents();
}

bool isWKeyDown(Window *window) {
    return glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS;
}
bool isAKeyDown(Window *window) {
    return glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS;
}
bool isSKeyDown(Window *window) {
    return glfwGetKey(window->window, GLFW_KEY_S) == GLFW_PRESS;
}
bool isDKeyDown(Window *window) {
    return glfwGetKey(window->window, GLFW_KEY_D) == GLFW_PRESS;
}
bool isSpaceKeyDown(Window *window) {
    return glfwGetKey(window->window, GLFW_KEY_SPACE) == GLFW_PRESS;
}
bool isLeftKeyDown(Window *window) {
    return glfwGetKey(window->window, GLFW_KEY_LEFT) == GLFW_PRESS;
}
bool isRightKeyDown(Window *window) {
    return glfwGetKey(window->window, GLFW_KEY_RIGHT) == GLFW_PRESS;
}
bool isTabKeyDown(Window *window) {
    return glfwGetKey(window->window, GLFW_KEY_TAB) == GLFW_PRESS;
}
bool isEscKeyDown(Window *window) {
    return glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}

bool isLeftMouseDown(Window *window) {
    return glfwGetMouseButton(window->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}

double getTime() {
    return glfwGetTime();
}
