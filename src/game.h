#pragma once

#include <2dMath.h>

typedef struct Game {
    double deltaTime;
} Game;

typedef struct Camera {
    Vec2 pos;
    Vec2 aspecRatio;
    float pixelsPerUnit;
} Camera;

typedef struct CallbackContext {
    Vec2 mousePos;
    Vec2 screenSize;
    Camera *camera;
} CallbackContext;

Camera *createCamera(Vec2 pos, Vec2 aspecRatio, float pixelsPerUnit);
CallbackContext *createCallbackContext(Camera *camera);
