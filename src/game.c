#include "game.h"

#include <stdlib.h>

Camera *createCamera(Vec2 pos, Vec2 aspecRatio, float pixelsPerUnit) {
    Camera *camera = malloc(sizeof(Camera));
    camera->pos = pos;
    camera->pixelsPerUnit = pixelsPerUnit;
    camera->aspecRatio = aspecRatio;
    return camera;
}

CallbackContext *createCallbackContext(Camera *camera) {
    struct CallbackContext *cbc = malloc(sizeof(struct CallbackContext));
    cbc->camera = camera;
    cbc->mousePos.x = 0.0f;
    cbc->mousePos.y = 0.0f;
    return cbc;
}

