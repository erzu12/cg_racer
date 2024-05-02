#include "map.h"

#include <2dSpline.h>
#include <2dPhysics.h>

void createGizmos(Gizmo *gizmos, unsigned int shader) {
    createGizmo(&gizmos[0], vec2(0.0f, 5.0f), 0.0f, shader, 3);
    createGizmo(&gizmos[1], vec2(-5.0f, 0.0f), PI/2, shader, 3);
    createGizmo(&gizmos[2], vec2(0.0f, -5.0f), PI, shader, 3);
    createGizmo(&gizmos[3], vec2(5.0f, 0.0f), PI + PI/2, shader, 3);
}

void freeGizmos(Gizmo *gizmos, int count) {
    for(int i = 0; i < count; i++) {
        free(gizmos[i].rect);
        free(gizmos[i].rectHandle1);
        free(gizmos[i].rectHandle2);
    }
}

void createGizmo(Gizmo * gizmo, Vec2 pos, float angle, unsigned int shader, float scale) {
    gizmo->pos = pos;
    gizmo->angle = angle;
    gizmo->handle1dist = scale;
    gizmo->handle2dist = scale;

    Vec2 handle1dir = vec2Rot(vec2(scale, 0.0f), angle);
    Vec2 handle2dir = vec2Rot(vec2(-scale, 0.0f), angle);

    gizmo->rect = newRectangle(shader);
    gizmo->rect->transform.pos = pos;
    gizmo->rect->transform.scale = vec2(0.3f, 0.3f);

    gizmo->rectHandle1 = newRectangle(shader);
    gizmo->rectHandle1->transform.pos = vec2Add(pos, handle1dir);
    gizmo->rectHandle1->transform.scale = vec2(0.3f, 0.3f);

    gizmo->rectHandle2 = newRectangle(shader);
    gizmo->rectHandle2->transform.pos = vec2Add(pos, handle2dir);
    gizmo->rectHandle2->transform.scale = vec2(0.3f, 0.3f);
}

void updateGizmoPos(Gizmo *gizmo) {
    Vec2 posHandle1 = vec2Rot(vec2(gizmo->handle1dist, 0.0f), gizmo->angle);
    Vec2 posHandle2 = vec2Rot(vec2(-gizmo->handle2dist, 0.0f), gizmo->angle);
    posHandle1 = vec2Add(posHandle1, gizmo->pos);
    posHandle2 = vec2Add(posHandle2, gizmo->pos);

    gizmo->rect->transform.pos = gizmo->pos;
    gizmo->rectHandle1->transform.pos = posHandle1;
    gizmo->rectHandle2->transform.pos = posHandle2;
}


void updateGizmo(Gizmo *gizmo, Window *window, const CallbackContext *cbc, const Camera *camera) {
    static int draging = 0;
    static Gizmo *dragingGizmo = NULL;
    if (isLeftMouseDown(window)) {
        Vec2 mousePos = screenToWorldSpace(cbc->mousePos, camera->pixelsPerUnit, cbc->screenSize, camera->pos);
        if(pointInRect(gizmo->rect, mousePos)) {
            draging = 1;
            dragingGizmo = gizmo;
        }
        else if(pointInRect(gizmo->rectHandle1, mousePos)) {
            draging = 2;
            dragingGizmo = gizmo;
        }
        else if(pointInRect(gizmo->rectHandle2, mousePos)) {
            draging = 3;
            dragingGizmo = gizmo;
        }
        switch (draging) {
            case 0:
                break;
            case 1:
                dragingGizmo->pos = mousePos;
                break;
            case 2:
                dragingGizmo->handle1dist = vec2Magnitude(vec2Subtraction(mousePos, dragingGizmo->pos));
                dragingGizmo->angle = -vec2Angle(vec2Subtraction(mousePos, dragingGizmo->pos), vec2(1.0f, 0.0f));
                break;
            case 3:
                dragingGizmo->handle2dist = vec2Magnitude(vec2Subtraction(mousePos, dragingGizmo->pos));
                dragingGizmo->angle = -vec2Angle(vec2Subtraction(mousePos, dragingGizmo->pos), vec2(-1.0f, 0.0f));
                break;
            default:
                printf("error\n");
                break;
        }
        updateGizmoPos(gizmo);
    }
    else {
        draging = 0;
    }
}

void drawGizmo(Gizmo *gizmo, float *viewMat, unsigned int shader) {

    drawRectangle(gizmo->rect, viewMat);
    drawRectangle(gizmo->rectHandle1, viewMat);
    drawRectangle(gizmo->rectHandle2, viewMat);

    Vec2 linePoints[3] = {gizmo->rectHandle1->transform.pos, gizmo->pos, gizmo->rectHandle2->transform.pos};

    Line *line1 = newLine(linePoints, 2, 0.10f, false, NULL);
    line1->shader = shader;
    Line *line2 = newLine(&linePoints[1], 2, 0.10f, false, NULL);
    line2->shader = shader;

    drawLine(line1, viewMat);
    drawLine(line2, viewMat);
    free(line1);
    free(line2);
}

Vec2 *gizmoArrToPath(const Gizmo *gizmo, int gizmoCount, int resolusion, Vec2 *points) {
    if(!points) {
        points = malloc(sizeof(Vec2) * gizmoCount * resolusion);
    }
    for(int i = 0; i < gizmoCount; i++) {
        int iplus1 = (i + 1) % gizmoCount;
        spline(&points[i * resolusion], resolusion, gizmo[i].pos, gizmo[i].rectHandle2->transform.pos, gizmo[iplus1].rectHandle1->transform.pos, gizmo[iplus1].pos);
    }
    return points;
}

Vec2 screenToWorldSpace(Vec2 screenPos, float pixelsPerUnit, Vec2 screenSize, Vec2 cameraPos) {
    float x = screenPos.x - screenSize.x / 2;
    float y = screenPos.y - screenSize.y / 2;

    x /= pixelsPerUnit / 2;
    y /= -pixelsPerUnit / 2;

    x += cameraPos.x;
    y += cameraPos.y;

    return vec2(x, y);
}

