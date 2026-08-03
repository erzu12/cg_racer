#include "transform.h"
#include <iostream>

Vec2 AnkorToVec2(AnkerPosition anker) {
    switch (anker) {
        case TOP_LEFT:
            return Vec2(-1, 1);
        case LEFT:
            return Vec2(-1, 0);
        case BOTTOM_LEFT:
            return Vec2(-1, -1);
        case TOP_RIGHT:
            return Vec2(1, 1);
        case RIGHT:
            return Vec2(1, 0);
        case BOTTOM_RIGHT:
            return Vec2(1, -1);
        case TOP:
            return Vec2(0, 1);
        case BOTTOM:
            return Vec2(0, -1);
        case CENTER:
            return Vec2(0, 0);
    }
}

ContainerTransform::ContainerTransform(ContainerTransform *parent_transform, Size &pos, Size &size, AnkerPosition screen_anker, AnkerPosition object_anker) : pos(pos), size(size) {
    this->screen_anker = screen_anker;
    this->object_anker = object_anker;
    this->parent_transform = parent_transform;
    Update();
    ScreenSizeManager::addListener(this);
}

void ContainerTransform::Update() {
    Vec2 parent_size;
    if (parent_transform == nullptr) {
        parent_size = Vec2(ScreenSizeManager::getScreenWidth(), ScreenSizeManager::getScreenHeight());
    } else {
        parent_size = parent_transform->transform.scale;
    }
    Vec2 screen_size = Vec2(ScreenSizeManager::getScreenWidth(), ScreenSizeManager::getScreenHeight());
    Vec2 pos_vec = pos.ToScreenSize(parent_size, screen_size);
    Vec2 size_vec = size.ToScreenSize(parent_size, screen_size);

    Vec2 screen_anker_vec = AnkorToVec2(screen_anker);
    Vec2 object_anker_vec = AnkorToVec2(object_anker);
    transform.scale = size_vec;

    Vec2 screen_pos = Vec2(pos_vec.x / screen_size.x * 2, pos_vec.y / screen_size.y * 2);
    Vec2 scaled_object_anker_vec(object_anker_vec.x * transform.scale.x * 0.5, object_anker_vec.y * transform.scale.y * 0.5);

    transform.pos = screen_anker_vec + screen_pos - scaled_object_anker_vec;
    transform.rot = 0.0f;
}

void ContainerTransform::OnScreenSizeChange(int screen_width, int screen_height) {
    std::cout << "ContainerTransform::OnScreenSizeChange " << screen_width << ", " << screen_height << std::endl;
    this->screen_width = screen_width;
    this->screen_height = screen_height;
    Update();
}
