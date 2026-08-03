#include "2dGraphics.h"
#include "2dMath.h"

bool pointInRect(Rectangle *rect, Vec2 p) {
    //check if point is in rectangle rectangle is by pos in the middle of the rectangle
    return (p.x > rect->transform.pos.x - rect->transform.scale.x / 2 &&
            p.x < rect->transform.pos.x + rect->transform.scale.x / 2 &&
            p.y > rect->transform.pos.y - rect->transform.scale.y / 2 &&
            p.y < rect->transform.pos.y + rect->transform.scale.y / 2);
}

bool pointOnPath(Vec2 *path, int pathLen, Vec2 p, float width) {
    float minDist = 1000000.0;
    for(int i = 0; i < pathLen - 1; i++) {
        minDist = fmin(minDist, vec2Magnitude(vec2Subtraction(p, path[i])));
    }
    return minDist < width;
}
