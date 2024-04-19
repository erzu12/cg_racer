#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <2dMath.h>
#include <2dGraphics.h>

#include "player.h"
#include "game.h"
#include "map.h"


int spaceracer();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double posX, double posY);

bool createGlfwWindow(GLFWwindow **window, int width, int height, const char *title);

ParticleSys *createParticleSys(Vec2 pos, Vec2 initalVel, const char *smokePath);

void loop(GLFWwindow *window,
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
