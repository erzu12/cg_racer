#include "input.h"

void processInput(Window *window)
{
    if(isEscKeyDown(window))
        setWindowShouldClose(window, true);
}

/**
 * @brief GLFW callback for mouse movement
 *
 * @param window The window that received the event
 * @param posX The new x-coordinate, in screen coordinates, of the cursor
 * @param posY The new y-coordinate, in screen coordinates, of the cursor
 */
void mouse_callback(Window *window, double posX, double posY){
    struct CallbackContext *cbc = (struct CallbackContext *)windowGetUserPointer(window);
    cbc->mousePos.x = (float)posX;
    cbc->mousePos.y = (float)posY;
}

