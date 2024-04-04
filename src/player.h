#pragma once
#include <2dMath.h>
#include <2dGraphics.h>

#include "game.h"

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

Player *createPlayer(Vec2 pos, float rot);
void updatePlayer(GLFWwindow *window, Player *player, const Game *game);
