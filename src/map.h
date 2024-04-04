#pragma once

#include <2dMath.h>
#include <2dGraphics.h>

#include "game.h"

typedef struct Gizmo {
    Vec2 pos;
    float angle;
    float handle1dist;
    float handle2dist;
    Rectangle *rect;
    Rectangle *rectHandle1;
    Rectangle *rectHandle2;
} Gizmo;

void createGizmo(Gizmo *gizmo, Vec2 pos, float angle, unsigned int shader, float scale);
void freeGizmos(Gizmo *gizmo, int count);

void createGizmos(Gizmo *gizmos, unsigned int shader);
void updateGizmo(Gizmo *gizmo, GLFWwindow *window, const CallbackContext *cbc, const Camera *camera);
void drawGizmo(Gizmo *gizmo, float *viewMat, unsigned int shader);
Vec2 *gizmoArrToPath(const Gizmo *gizmo, int gizmoCount, int resolusion, Vec2 *path);
Vec2 screenToWorldSpace(Vec2 screenPos, float pixelsPerUnit, Vec2 screenSize, Vec2 cameraPos);
