#include <unity.h>
#include <map.h>
#include <player.h>

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
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

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(testCreatePlayer);
    return UNITY_END();
}
