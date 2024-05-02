#include "player.h"

Player *createPlayer(Vec2 pos, float rot) {
    Player *player = malloc(sizeof(Player));
    player->pos = pos;
    player->vel = vec2zero();
    player->rot = rot;
    player->rotVel = 0;
    player->colCheck[0] = vec2(1.0f, 0.0f);
    player->colCheck[1] = vec2(-1.0f, 0.0f);
    player->colCheck[2] = vec2(0.0f, 1.0f);
    player->colCheck[3] = vec2(0.0f, -1.0f);
    player->respawnPoint = pos;
    player->respawnRot = rot;
    return player;
}


void updatePlayer(Window *window, Player *player, const Game *game) {
    Vec2 input = vec2zero();
    if(isWKeyDown(window))
        input = vec2Add(input, vec2(0.0f, 1.0f));
    if(isSKeyDown(window))
        input = vec2Add(input, vec2(0.0f, -1.0f));
    if(isDKeyDown(window))
        input = vec2Add(input, vec2(1.0f, 0.0f));
    if(isAKeyDown(window))
        input = vec2Add(input, vec2(-1.0f, 0.0f));

    if(isSpaceKeyDown(window)) {
        input = vec2Add(input, vec2(0.0f, 2.0f));
        spawnParticle(player->engine, 1.0);
    }

    float rotInput = 0.0f;
    if(isLeftKeyDown(window))
        rotInput += 1.0f;
    if(isRightKeyDown(window))
        rotInput -= 1.0f;

    player->rotVel += rotInput * 10.0f * (float)game->deltaTime;
    player->rot += player->rotVel * (float)game->deltaTime;
    input = vec2Rot(input, player->rot);

    player->vel = vec2Add(player->vel, vec2Scale(input, 8.0f * (float)game->deltaTime));
    player->pos = vec2Add(player->pos, vec2Scale(player->vel, (float)game->deltaTime));
}

