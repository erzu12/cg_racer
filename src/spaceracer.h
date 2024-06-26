#pragma once


#include <glad/glad.h>

#include <2dMath.h>
#include <2dGraphics.h>

#include "player.h"
#include "map.h"
#include "input.h"


int spaceracer();

void framebuffer_size_callback(Window* window, int width, int height);

bool createGlfwWindow(Window **window, int width, int height, const char *title);

ParticleSys *createParticleSys(Vec2 pos, Vec2 initalVel, const char *smokePath);

void loop(Window *window,
    Game *game,
    Player *player,
    Camera *camera,
    unsigned int shader,
    Image *ship,
    ParticleSys *particleSys,
    Gizmo *gizmos,
    Vec2 *path,
    Line *line,
    const CallbackContext *cbc
);
