#pragma once

#include "transform.h"
#include "2dGraphics.h"
#include <iostream>

class Element {
public:
    virtual void SetTransform(ContainerTransform transform) = 0;
    //virtual ContainerTransform GetTransform() = 0;
    virtual void Draw() = 0;
};

class RectangleElement : public Element {
    Rectangle rectangle;
    Mat3 viewMatrix;
public:
    RectangleElement(ContainerTransform transform, Shader shader);

    void Draw() {
        rectangle.Draw(&viewMatrix);
    }

    void SetTransform(ContainerTransform transform) {
        rectangle.transform = transform.getTransform();
    }
};
