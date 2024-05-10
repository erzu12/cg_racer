#include "input.h"

void processInput(Window *window)
{
    if(isEscKeyDown(window))
        setWindowShouldClose(window, true);
}

void mouse_callback(Window *window, double posX, double posY){
    struct CallbackContext *cbc = (struct CallbackContext *)windowGetUserPointer(window);
    cbc->mousePos.x = (float)posX;
    cbc->mousePos.y = (float)posY;
}

