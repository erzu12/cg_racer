#include "screensize.h"
#include <iostream>

int ScreenSizeManager::screen_width = 0;
int ScreenSizeManager::screen_height = 0;
std::vector<ScreenSizeListener *> ScreenSizeManager::listeners;

void ScreenSizeManager::addListener(ScreenSizeListener *listener) {
    std::cout << "ScreenSizeManager::addListener" << std::endl;
    listeners.push_back(listener);
}

void ScreenSizeManager::removeListener(ScreenSizeListener *listener) {
    for (int i = 0; i < listeners.size(); i++) {
        if (listeners[i] == listener) {
            listeners.erase(listeners.begin() + i);
            return;
        }
    }
}

void ScreenSizeManager::notifyListeners(int screen_width, int screen_height) {
    std::cout << "ScreenSizeManager::notifyListeners" << std::endl;
    ScreenSizeManager::screen_width = screen_width;
    ScreenSizeManager::screen_height = screen_height;
    for (int i = 0; i < listeners.size(); i++) {
        listeners[i]->OnScreenSizeChange(screen_width, screen_height);
    }
}

int ScreenSizeManager::getScreenWidth() {
    return screen_width;
}

int ScreenSizeManager::getScreenHeight() {
    return screen_height;
}
