#include <unity.h>
#include <player.h>
#include "Mockwindow.h"

void setUp(void) {
    Window window;
    isWKeyDown_IgnoreAndReturn(false);
    isSKeyDown_IgnoreAndReturn(false);
    isDKeyDown_IgnoreAndReturn(false);
    isAKeyDown_IgnoreAndReturn(false);
    isSpaceKeyDown_IgnoreAndReturn(false);
    isLeftKeyDown_IgnoreAndReturn(false);
    isRightKeyDown_IgnoreAndReturn(false);
}

void tearDown(void) {
}

void testCreatePlayer(void) {
    Player *player = createPlayer(vec2(1.0f, 2.0f), 3.0f);
    TEST_ASSERT_EQUAL(1.0f, player->pos.x);
    TEST_ASSERT_EQUAL(2.0f, player->pos.y);
    TEST_ASSERT_EQUAL(0.0f, player->vel.x);
    TEST_ASSERT_EQUAL(0.0f, player->vel.y);
    TEST_ASSERT_EQUAL(3.0f, player->rot);
    TEST_ASSERT_EQUAL(0.0f, player->rotVel);
    TEST_ASSERT_EQUAL(1.0f, player->colCheck[0].x);
    TEST_ASSERT_EQUAL(0.0f, player->colCheck[0].y);
    TEST_ASSERT_EQUAL(-1.0f, player->colCheck[1].x);
    TEST_ASSERT_EQUAL(0.0f, player->colCheck[1].y);
    TEST_ASSERT_EQUAL(0.0f, player->colCheck[2].x);
    TEST_ASSERT_EQUAL(1.0f, player->colCheck[2].y);
    TEST_ASSERT_EQUAL(0.0f, player->colCheck[3].x);
    TEST_ASSERT_EQUAL(-1.0f, player->colCheck[3].y);
    TEST_ASSERT_EQUAL(1.0f, player->respawnPoint.x);
    TEST_ASSERT_EQUAL(2.0f, player->respawnPoint.y);
    TEST_ASSERT_EQUAL(3.0f, player->respawnRot);
    free(player);
}

void testUpdatePlayerSpaceBar(void) {
    Player *player = createPlayer(vec2(0.0f, 0.0f), 0.0f);
    Game game;
    game.deltaTime = 1.0;
    Window window;
    isSpaceKeyDown_IgnoreAndReturn(true);
    updatePlayer(&window, player, &game);
    TEST_ASSERT_EQUAL(0.0f, player->pos.x);
    TEST_ASSERT_EQUAL(16.0f, player->pos.y);
    TEST_ASSERT_EQUAL(0.0f, player->vel.x);
    TEST_ASSERT_EQUAL(16.0f, player->vel.y);
    free(player);
}

void testUpdatePlayerWKeyDown(void) {
    Player *player = createPlayer(vec2(0.0f, 0.0f), 0.0f);
    Game game;
    game.deltaTime = 1.0;
    Window window;
    isWKeyDown_IgnoreAndReturn(true);
    updatePlayer(&window, player, &game);
    TEST_ASSERT_EQUAL(0.0f, player->pos.x);
    TEST_ASSERT_EQUAL(8.0f, player->pos.y);
    TEST_ASSERT_EQUAL(0.0f, player->vel.x);
    TEST_ASSERT_EQUAL(8.0f, player->vel.y);
    free(player);
}

void testUpdatePlayerSKeyDown(void) {
    Player *player = createPlayer(vec2(0.0f, 0.0f), 0.0f);
    Game game;
    game.deltaTime = 1.0;
    Window window;
    isSKeyDown_IgnoreAndReturn(true);
    updatePlayer(&window, player, &game);
    TEST_ASSERT_EQUAL(0.0f, player->pos.x);
    TEST_ASSERT_EQUAL(-8.0f, player->pos.y);
    TEST_ASSERT_EQUAL(0.0f, player->vel.x);
    TEST_ASSERT_EQUAL(-8.0f, player->vel.y);
    free(player);
}

void testUpdatePlayerDKeyDown(void) {
    Player *player = createPlayer(vec2(0.0f, 0.0f), 0.0f);
    Game game;
    game.deltaTime = 1.0;
    Window window;
    isDKeyDown_IgnoreAndReturn(true);
    updatePlayer(&window, player, &game);
    TEST_ASSERT_EQUAL(8.0f, player->pos.x);
    TEST_ASSERT_EQUAL(0.0f, player->pos.y);
    TEST_ASSERT_EQUAL(8.0f, player->vel.x);
    TEST_ASSERT_EQUAL(0.0f, player->vel.y);
    free(player);
}

void testUpdatePlayerAKeyDown(void) {
    Player *player = createPlayer(vec2(0.0f, 0.0f), 0.0f);
    Game game;
    game.deltaTime = 1.0;
    Window window;
    isAKeyDown_IgnoreAndReturn(true);
    updatePlayer(&window, player, &game);
    TEST_ASSERT_EQUAL(-8.0f, player->pos.x);
    TEST_ASSERT_EQUAL(0.0f, player->pos.y);
    TEST_ASSERT_EQUAL(-8.0f, player->vel.x);
    TEST_ASSERT_EQUAL(0.0f, player->vel.y);
    free(player);
}

void testUpdatePlayerLeftKeyDown(void) {
    Player *player = createPlayer(vec2(0.0f, 0.0f), 0.0f);
    Game game;
    game.deltaTime = 1.0;
    Window window;
    isLeftKeyDown_IgnoreAndReturn(true);
    updatePlayer(&window, player, &game);
    TEST_ASSERT_EQUAL(10.0f, player->rotVel);
    TEST_ASSERT_EQUAL(10.0f, player->rot);
    free(player);
}

void testUpdatePlayerRightKeyDown(void) {
    Player *player = createPlayer(vec2(0.0f, 0.0f), 0.0f);
    Game game;
    game.deltaTime = 1.0;
    Window window;
    isRightKeyDown_IgnoreAndReturn(true);
    updatePlayer(&window, player, &game);
    TEST_ASSERT_EQUAL(-10.0f, player->rotVel);
    TEST_ASSERT_EQUAL(-10.0f, player->rot);
    free(player);
}

void testUpdatePlayerMomentum(void) {
    Player *player = createPlayer(vec2(0.0f, 0.0f), 0.0f);
    Game game;
    game.deltaTime = 1.0;
    Window window;
    isWKeyDown_IgnoreAndReturn(true);
    updatePlayer(&window, player, &game);
    TEST_ASSERT_EQUAL(0.0f, player->pos.x);
    TEST_ASSERT_EQUAL(8.0f, player->pos.y);
    TEST_ASSERT_EQUAL(0.0f, player->vel.x);
    TEST_ASSERT_EQUAL(8.0f, player->vel.y);
    isWKeyDown_IgnoreAndReturn(false);
    updatePlayer(&window, player, &game);
    TEST_ASSERT_EQUAL(0.0f, player->pos.x);
    TEST_ASSERT_EQUAL(16.0f, player->pos.y);
    TEST_ASSERT_EQUAL(0.0f, player->vel.x);
    TEST_ASSERT_EQUAL(8.0f, player->vel.y);
    free(player);
}

void testUpdatePlayerAngularMomentum(void) {
    Player *player = createPlayer(vec2(0.0f, 0.0f), 0.0f);
    Game game;
    game.deltaTime = 1.0;
    Window window;
    isLeftKeyDown_IgnoreAndReturn(true);
    updatePlayer(&window, player, &game);
    TEST_ASSERT_EQUAL(10.0f, player->rotVel);
    TEST_ASSERT_EQUAL(10.0f, player->rot);
    isLeftKeyDown_IgnoreAndReturn(false);
    updatePlayer(&window, player, &game);
    TEST_ASSERT_EQUAL(10.0f, player->rotVel);
    TEST_ASSERT_EQUAL(20.0f, player->rot);
    free(player);
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(testCreatePlayer);
    RUN_TEST(testUpdatePlayerSpaceBar);
    RUN_TEST(testUpdatePlayerWKeyDown);
    RUN_TEST(testUpdatePlayerSKeyDown);
    RUN_TEST(testUpdatePlayerDKeyDown);
    RUN_TEST(testUpdatePlayerAKeyDown);
    RUN_TEST(testUpdatePlayerLeftKeyDown);
    RUN_TEST(testUpdatePlayerRightKeyDown);
    RUN_TEST(testUpdatePlayerMomentum);
    RUN_TEST(testUpdatePlayerAngularMomentum);
    return UNITY_END();
}
