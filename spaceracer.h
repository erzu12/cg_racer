#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <2dMath.h>
#include <2dGraphics.h>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

typedef struct Player {
    Vec2 pos;
    Vec2 vel;
    float rot;
    float rotVel;
    ParticleSys rcs[8];
    ParticleSys *engine;
    Vec2 colCheck[4];
    Vec2 respawnPoint;
    float respawnRot;
} Player;

typedef struct Camera {
    Vec2 pos;
    Vec2 aspecRatio;
    float pixelsPerUnit;
} Camera;

typedef struct CallbackContext {
    Vec2 mousePos;
    Vec2 screenSize;
    Camera *camera;
} CallbackContext;

typedef struct Game {
    float deltaTime;
} Game;

typedef struct Gizmo {
    Vec2 pos;
    float angle;
    float handle1dist;
    float handle2dist;
    Rectangle *rect;
    Rectangle *rectHandle1;
    Rectangle *rectHandle2;
} Gizmo;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double posX, double posY);
Vec2 screenToWorldSpace(Vec2 screenPos, float pixelsPerUnit, Vec2 screenSize, Vec2 cameraPos);

bool createGlfwWindow(GLFWwindow **window, int width, int height, const char *title);

Player *createPlayer(Vec2 pos, float rot);
void updatePlayer(GLFWwindow *window, Player *player, Game *game);

CallbackContext *createCallbackContext(Camera *camera);
Camera *createCamera(Vec2 pos, Vec2 aspecRatio, float pixelsPerUnit);
ParticleSys *createParticleSys(Vec2 pos, Vec2 initalVel, const char *smokePath);

Gizmo *createGizmo(Vec2 pos, float angle, unsigned int shader, float scale);
void createGizmos(Gizmo *gizmos, unsigned int shader);
void updateGizmo(Gizmo *gizmo, GLFWwindow *window, struct CallbackContext *cbc, Camera *camera);
void drawGizmo(Gizmo *gizmo, float *viewMat, unsigned int shader);
Vec2 *gizmoArrToPath(Gizmo *gizmo, int gizmoCount, int resolusion);

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
    CallbackContext *cbc
);
