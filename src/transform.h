
#include "screensize.h"
#include "2dGraphics.h"
#include <2dMath.h>

enum AnkerPosition {
    TOP_LEFT,
    LEFT,
    BOTTOM_LEFT,
    TOP_RIGHT,
    RIGHT,
    BOTTOM_RIGHT,
    TOP,
    BOTTOM,
    CENTER
};

class Size {
public:
    virtual Vec2 ToScreenSize(Vec2 parent_transform, Vec2 screen_size) = 0;
};

class PercentSize : public Size {
public:
    Vec2 percent;
    PercentSize(Vec2 percent) {
        this->percent = percent;
    }
    Vec2 ToScreenSize(Vec2 parent_transform, Vec2 screen_size) {
        return Vec2(percent.x * 0.01 * parent_transform.x, percent.y * 0.01 * parent_transform.y);
    }
};

class PixelSize : public Size {
public:
    Vec2 pixel;
    PixelSize(Vec2 pixel) {
        this->pixel = pixel;
    }
    Vec2 ToScreenSize(Vec2 parent_transform, Vec2 screen_size) {
        return Vec2(pixel.x / screen_size.x * 2, pixel.y / screen_size.y * 2);
    }
};

class ContainerTransform : ScreenSizeListener {
    Size &pos;
    Size &size;
    AnkerPosition screen_anker;
    AnkerPosition object_anker;
public:
    Transform transform;
    ContainerTransform *parent_transform;

    ContainerTransform(ContainerTransform *parent_transform, Size &pos, Size &size, AnkerPosition screen_anker, AnkerPosition object_anker);
    void Update();

    static ContainerTransform *CreateRoot() {
        PixelSize pos(Vec2(0, 0));
        int screen_width = ScreenSizeManager::getScreenWidth();
        int screen_height = ScreenSizeManager::getScreenHeight();
        PixelSize size(Vec2(screen_width, screen_height));
        return new ContainerTransform(nullptr, pos, size, TOP_LEFT, TOP_LEFT);
    }

    Transform *getTransform() {
        return &transform;
    }

private:
    int screen_width;
    int screen_height;

    void OnScreenSizeChange(int screen_width, int screen_height);
};
