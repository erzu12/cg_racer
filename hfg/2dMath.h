#pragma once

#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <stdbool.h>

#define PI 3.14159265359f
#define IndexMat3d {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f}

typedef struct Vec2 {
    float x;
    float y;
} Vec2;

void vec2ToArr(Vec2 a, float *dest);

Vec2 vec2(float x, float y);

Vec2 vec2zero();

Vec2 vec2Add(Vec2 a, Vec2 b);

Vec2 vec2Subtraction(Vec2 a, Vec2 b);

float vec2Magnitude(Vec2 a);

Vec2 vec2Noramlize(Vec2 a);

Vec2 vec2Scale(Vec2 a, float b);

float vec2Dot(Vec2 a, Vec2 b);

float vec2Angle(Vec2 a, Vec2 b);

Vec2 vec2Rot(Vec2 a, float rot);

Vec2 vec2Lerp(Vec2 a, Vec2 b, float t);

void vec2Print(Vec2 vec);

void printMat(float *mat);

void multMat(float *a, float *b, float *dest);

void rotationMat(float angle, float *dest);

void scalingMatrix(Vec2 scale, float *dest);

void translationMatrix(Vec2 translate, float *dest);

void rotateMat(float angle, float *mat);

void scaleMat(Vec2 scale, float *mat);

void translateMat(Vec2 translate, float *mat);

bool pointInPath(Vec2 point, Vec2 *poly, int polyLength);
