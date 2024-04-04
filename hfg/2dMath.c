#include "2dMath.h"

void vec2ToArr(Vec2 a, float *dest) {
    dest[0] = a.x;
    dest[1] = a.y;
}

Vec2 vec2(float x, float y) {
    Vec2 a = {x, y};
    return a;
}

Vec2 vec2zero() {
    Vec2 a = {0.0f, 0.0f};
    return a;
}

Vec2 vec2Add(Vec2 a, Vec2 b) {
    Vec2 c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

Vec2 vec2Subtraction(Vec2 a, Vec2 b) {
    Vec2 c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return c;
}

float vec2Magnitude(Vec2 a) {
    return sqrt(a.x*a.x + a.y*a.y);
}

Vec2 vec2Noramlize(Vec2 a) {
    float mag = vec2Magnitude(a);
    if(mag == 0) return a;
    a.x /= mag;
    a.y /= mag;
    return a;
}

Vec2 vec2Scale(Vec2 a, float b) {
    a.x *= b;
    a.y *= b;
    return a;
}

float vec2Dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}

float vec2Angle(Vec2 a, Vec2 b) {
    return  atan2(a.x * b.y - a.y * b.x, a.x * b.x + a.y * b.y);
}

Vec2 vec2Rot(Vec2 a, float rot) {
    Vec2 b;
    b.x = a.x * cos(rot) - a.y * sin(rot);
    b.y = a.x * sin(rot) + a.y * cos(rot);
    return b;
}

Vec2 vec2Lerp(Vec2 a, Vec2 b, float t) {
    Vec2 c;
    c.x = a.x + t * (b.x - a.x);
    c.y = a.y + t * (b.y - a.y);
    return c;
}

void vec2Print(Vec2 vec) {
    printf("{%f ,", vec.x);
    printf("%f}\n", vec.y);
}

void printMat(float *mat) {
    printf("{%f, %f, %f\n", mat[0], mat[1], mat[2]);
    printf(" %f, %f, %f\n", mat[3], mat[4], mat[5]);
    printf(" %f, %f, %f}\n", mat[6], mat[7], mat[8]);
}

void multMat(float *a, float *b, float *dest) {
    float *temp;
    if(dest == a || dest == b) {
        float arr[9];
        temp = arr;
    }
    else {
        temp = dest;
    }
    temp[0] = a[0] * b[0] + a[1] * b[3] + a[2] * b[6];
    temp[1] = a[0] * b[1] + a[1] * b[4] + a[2] * b[7];
    temp[2] = a[0] * b[2] + a[1] * b[5] + a[2] * b[8];
    temp[3] = a[3] * b[0] + a[4] * b[3] + a[5] * b[6]; 
    temp[4] = a[3] * b[1] + a[4] * b[4] + a[5] * b[7]; 
    temp[5] = a[3] * b[2] + a[4] * b[5] + a[5] * b[8]; 
    temp[6] = a[6] * b[0] + a[7] * b[3] + a[8] * b[6]; 
    temp[7] = a[6] * b[1] + a[7] * b[4] + a[8] * b[7]; 
    temp[8] = a[6] * b[2] + a[7] * b[5] + a[8] * b[8]; 
    if(dest == a || dest == b) {
        memcpy(dest, temp, 9 * sizeof(float));
    }
}

void rotationMat(float angle, float *dest) {
    dest[0] = cos(angle);
    dest[1] = -sin(angle);
    dest[2] = 0.0f;
    dest[3] = sin(angle);
    dest[4] = cos(angle);
    dest[5] = 0.0f;
    dest[6] = 0.0f;
    dest[7] = 0.0f;
    dest[8] = 1.0f;
}

void scalingMatrix(Vec2 scale, float *dest) {
    dest[0] = scale.x; 
    dest[1] = 0.0f; 
    dest[2] = 0.0f; 
    dest[3] = 0.0f;
    dest[4] = scale.y; 
    dest[5] = 0.0f;
    dest[6] = 0.0f;
    dest[7] = 0.0f;
    dest[8] = 1.0f;
}

void translationMatrix(Vec2 translate, float *dest) {
    dest[0] = 1.0f; 
    dest[1] = 0.0f; 
    dest[2] = translate.x; 
    dest[3] = 0.0f; 
    dest[4] = 1.0f;
    dest[5] = translate.y;
    dest[6] = 0.0f;
    dest[7] = 0.0f;
    dest[8] = 1.0f;
}

void rotateMat(float angle, float *mat) {
    float rotMat[9];
    rotationMat(angle, rotMat);
    multMat(rotMat, mat, mat);
}

void scaleMat(Vec2 scale, float *mat) {
    float scaleMat[9];
    scalingMatrix(scale, scaleMat);
    multMat(scaleMat, mat, mat);
}

void translateMat(Vec2 translate, float *mat) {
    float translateionMat[9];
    translationMatrix(translate, translateionMat);
    multMat(translateionMat, mat, mat);
}

bool pointInPath(Vec2 point, Vec2 *poly, int polyLength) {
    int j = polyLength - 1;
    bool c = false;

    for(int i = 0; i < polyLength; i++) {
        if ((point.x == poly[i].x) && (point.y == poly[i].y)) {
            // point is a corner
            return true;
        }
        if ((poly[i].y > point.y) != (poly[j].y > point.y)) {
            float slope = (point.x - poly[i].x) * (poly[j].y - poly[i].y) - (poly[j].x-poly[i].x) * (point.y-poly[i].y);

            if(slope == 0) {
                // point is on boundary
                return true;
            }
            if ((slope < 0) != (poly[j].y < poly[i].y)) {
                c = !c;
            }
        }
        j = i;
    }
    return c;
}
