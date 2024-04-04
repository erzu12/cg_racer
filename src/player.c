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


void updatePlayer(GLFWwindow *window, Player *player, const Game *game) {
    Vec2 input = vec2zero();
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
        input = vec2Add(input, vec2(0.0f, 1.0f));
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        input = vec2Add(input, vec2(0.0f, -1.0f));
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
        input = vec2Add(input, vec2(1.0f, 0.0f));
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
        input = vec2Add(input, vec2(-1.0f, 0.0f));

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        input = vec2Add(input, vec2(0.0f, 2.0f));
        spawnParticle(player->engine, 1.0);
    }

    float rotInput = 0.0f;
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) 
        rotInput += 1.0f;
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) 
        rotInput -= 1.0f;

    player->rotVel += rotInput * 10.0f * (float)game->deltaTime;
    player->rot += player->rotVel * (float)game->deltaTime;
    input = vec2Rot(input, player->rot);

    player->vel = vec2Add(player->vel, vec2Scale(input, 8.0f * (float)game->deltaTime));
    player->pos = vec2Add(player->pos, vec2Scale(player->vel, (float)game->deltaTime));
}

