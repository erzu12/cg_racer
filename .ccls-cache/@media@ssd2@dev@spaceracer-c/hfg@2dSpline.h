#pragma once

#include <stdio.h>

#include "2dMath.h"

void spline(Vec2 *points, int pointCount, Vec2 start, Vec2 control1, Vec2 control2, Vec2 end) {
    float interval = (float)1 / pointCount;
    for(int i = 0; i < pointCount; i++) {
        float t = i * interval;
        //points[i].x = pow((1-t), 3) * start.x + 3 * pow((1-t), 2) * t * control1.x + 3 * (1-t) * pow(t, 2) * control2.x + pow(t, 3) * end.x;
        //points[i].y = pow((1-t), 3) * start.y + 3 * pow((1-t), 2) * t * control1.y + 3 * (1-t) * pow(t, 2) * control2.y + pow(t, 3) * end.y;
        Vec2 a = vec2Lerp(start, control1, t);
        Vec2 b = vec2Lerp(control1, control2, t);
        Vec2 c = vec2Lerp(control2, end, t);
        points[i] = vec2Lerp(vec2Lerp(a, b, t), vec2Lerp(b, c, t), t);
    }
}
