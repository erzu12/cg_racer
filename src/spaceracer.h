#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <2dMath.h>
#include <2dGraphics.h>

#include "player.h"
#include "game.h"
#include "map.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double posX, double posY);
Vec2 screenToWorldSpace(Vec2 screenPos, float pixelsPerUnit, Vec2 screenSize, Vec2 cameraPos);

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
