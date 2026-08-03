#include "elements.h"


RectangleElement::RectangleElement(ContainerTransform transform, Shader shader) : rectangle(shader) {
    this->rectangle.transform = transform.getTransform();
}
