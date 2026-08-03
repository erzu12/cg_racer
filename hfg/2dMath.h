#pragma once

#include <ostream>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <stdbool.h>

#define PI 3.14159265359f
#define IndexMat3d {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f}

struct Vec2 {
    float x;
    float y;

    void ToArr(float *dest) {
        dest[0] = this->x;
        dest[1] = this->y;
    }

    Vec2(float x, float y) {
        this->x = x;
        this->y = y;
    }

    Vec2() {
        this->x = 0.0f;
        this->y = 0.0f;
    }

    void Set(float x, float y) {
        this->x = x;
        this->y = y;
    }

    static Vec2 Add(Vec2 a, Vec2 b) {
        return Vec2(a.x + b.x, a.y + b.y);
    }

    // overloaded operators
    Vec2 operator+(const Vec2& a) {
        return Vec2(this->x + a.x, this->y + a.y);
    }

    static Vec2 Subtraction(Vec2 a, Vec2 b) {
        return Vec2(a.x - b.x, a.y - b.y);
    }

    Vec2 operator-(const Vec2& a) {
        return Vec2(this->x - a.x, this->y - a.y);
    }

    float Magnitude() const {
        return sqrt(this->x*this->x + this->y*this->y);
    }

    Vec2 Noramlize() {
        float mag = this->Magnitude();
        if(mag == 0) return *this;
        this->x /= mag;
        this->y /= mag;
        return *this;
    }

    static Vec2 Scale(Vec2 a, float b) {
        a.x *= b;
        a.y *= b;
        return a;
    }

    Vec2 operator*(const float& a) {
        return Scale(*this, a);
    }

    static float Dot(Vec2 a, Vec2 b) {
        return a.x * b.x + a.y * b.y;
    }

    float operator*(const Vec2& a) {
        return Dot(*this, a);
    }

    static float Angle(Vec2 a, Vec2 b) {
        return  atan2(a.x * b.y - a.y * b.x, a.x * b.x + a.y * b.y);
    }

    Vec2 Rot(float rot) {
        Vec2 b;
        b.x = this->x * cos(rot) - this->y * sin(rot);
        b.y = this->x * sin(rot) + this->y * cos(rot);
        return b;
    }

    static Vec2 Lerp(Vec2 a, Vec2 b, float t) {
        Vec2 c;
        c.x = a.x + t * (b.x - a.x);
        c.y = a.y + t * (b.y - a.y);
        return c;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec2& vec) {
        os << "{" << vec.x << ", " << vec.y << "}";
        return os;
    }
};

struct Mat3 {
    float mat[9];

    void Print() {
        printf("{%f, %f, %f\n", mat[0], mat[1], mat[2]);
        printf(" %f, %f, %f\n", mat[3], mat[4], mat[5]);
        printf(" %f, %f, %f}\n", mat[6], mat[7], mat[8]);
    }

    Mat3() {
        mat[0] = 1.0f;
        mat[1] = 0.0f;
        mat[2] = 0.0f;
        mat[3] = 0.0f;
        mat[4] = 1.0f;
        mat[5] = 0.0f;
        mat[6] = 0.0f;
        mat[7] = 0.0f;
        mat[8] = 1.0f;
    }

    static void multMat(const Mat3 *a, const Mat3 *b, Mat3 *dest) {
        float *temp;
        if(dest == a || dest == b) {
            float arr[9];
            temp = arr;
        }
        else {
            temp = dest->mat;
        }
        temp[0] = a->mat[0] * b->mat[0] + a->mat[1] * b->mat[3] + a->mat[2] * b->mat[6];
        temp[1] = a->mat[0] * b->mat[1] + a->mat[1] * b->mat[4] + a->mat[2] * b->mat[7];
        temp[2] = a->mat[0] * b->mat[2] + a->mat[1] * b->mat[5] + a->mat[2] * b->mat[8];
        temp[3] = a->mat[3] * b->mat[0] + a->mat[4] * b->mat[3] + a->mat[5] * b->mat[6]; 
        temp[4] = a->mat[3] * b->mat[1] + a->mat[4] * b->mat[4] + a->mat[5] * b->mat[7]; 
        temp[5] = a->mat[3] * b->mat[2] + a->mat[4] * b->mat[5] + a->mat[5] * b->mat[8]; 
        temp[6] = a->mat[6] * b->mat[0] + a->mat[7] * b->mat[3] + a->mat[8] * b->mat[6]; 
        temp[7] = a->mat[6] * b->mat[1] + a->mat[7] * b->mat[4] + a->mat[8] * b->mat[7]; 
        temp[8] = a->mat[6] * b->mat[2] + a->mat[7] * b->mat[5] + a->mat[8] * b->mat[8]; 
        if(dest == a || dest == b) {
            memcpy(dest->mat, temp, 9 * sizeof(float));
        }
    }

    Mat3 operator*(const Mat3 *a) {
        Mat3 b;
        multMat(this, a, &b);
        return b;
    }

    Mat3 operator*=(const Mat3 *a) {
        multMat(this, a, this);
        return *this;
    }

    static void RotationMat(float angle, Mat3 *dest) {
        dest->mat[0] = cos(angle);
        dest->mat[1] = -sin(angle);
        dest->mat[2] = 0.0f;
        dest->mat[3] = sin(angle);
        dest->mat[4] = cos(angle);
        dest->mat[5] = 0.0f;
        dest->mat[6] = 0.0f;
        dest->mat[7] = 0.0f;
        dest->mat[8] = 1.0f;
    }

    static void ScalingMatrix(Vec2 scale, Mat3 *dest) {
        dest->mat[0] = scale.x; 
        dest->mat[1] = 0.0f; 
        dest->mat[2] = 0.0f; 
        dest->mat[3] = 0.0f;
        dest->mat[4] = scale.y; 
        dest->mat[5] = 0.0f;
        dest->mat[6] = 0.0f;
        dest->mat[7] = 0.0f;
        dest->mat[8] = 1.0f;
    }

    static void TranslationMatrix(Vec2 translate, Mat3 *dest) {
        dest->mat[0] = 1.0f; 
        dest->mat[1] = 0.0f; 
        dest->mat[2] = translate.x; 
        dest->mat[3] = 0.0f; 
        dest->mat[4] = 1.0f;
        dest->mat[5] = translate.y;
        dest->mat[6] = 0.0f;
        dest->mat[7] = 0.0f;
        dest->mat[8] = 1.0f;
    }

    void RotateMat(float angle) {
        Mat3 rotMat;
        RotationMat(angle, &rotMat);
        multMat(&rotMat, this, this);
    }

    void ScaleMat(Vec2 scale) {
        Mat3 scaleMat;
        ScalingMatrix(scale, &scaleMat);
        multMat(&scaleMat, this, this);
    }

    void TranslateMat(Vec2 translate) {
        Mat3 translateionMat;
        TranslationMatrix(translate, &translateionMat);
        multMat(&translateionMat, this, this);
    }
};

//bool pointInPath(Vec2 point, Vec2 *poly, int polyLength) {
    //int j = polyLength - 1;
    //bool c = false;

    //for(int i = 0; i < polyLength; i++) {
        //if ((point.x == poly[i].x) && (point.y == poly[i].y)) {
            //// point is a corner
            //return true;
        //}
        //if ((poly[i].y > point.y) != (poly[j].y > point.y)) {
            //float slope = (point.x - poly[i].x) * (poly[j].y - poly[i].y) - (poly[j].x-poly[i].x) * (point.y-poly[i].y);

            //if(slope == 0) {
                //// point is on boundary
                //return true;
            //}
            //if ((slope < 0) != (poly[j].y < poly[i].y)) {
                //c = !c;
            //}
        //}
        //j = i;
    //}
    //return c;
//}
