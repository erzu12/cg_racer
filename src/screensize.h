#pragma once

#include <vector>

class ScreenSizeListener {
    public:
        virtual void OnScreenSizeChange(int screen_width, int screen_height) = 0;
};

class ScreenSizeManager {
    static std::vector<ScreenSizeListener*> listeners;
    static int screen_width;
    static int screen_height;
public:
    static void addListener(ScreenSizeListener *listener);
    static void removeListener(ScreenSizeListener *listener);
    static void notifyListeners(int screen_width, int screen_height);
    static int getScreenWidth();
    static int getScreenHeight();
};
