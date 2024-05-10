#include <stdlib.h>
#include <unity.h>
#include <game.h>

void setUp(void) {
}

void tearDown(void) {
}

void testCreateCamera(void) {
    Camera *camera = createCamera(vec2(1.0f, 5.0f), vec2(1.0f, 1.0f), 2.0f);
    TEST_ASSERT_EQUAL(1.0f, camera->pos.x);
    TEST_ASSERT_EQUAL(5.0f, camera->pos.y);
    TEST_ASSERT_EQUAL(2.0f, camera->pixelsPerUnit);
    TEST_ASSERT_EQUAL(1.0f, camera->aspecRatio.x);
    TEST_ASSERT_EQUAL(1.0f, camera->aspecRatio.y);
    free(camera);
}

void testCreateCallbackContext(void) {
    Camera *camera = createCamera(vec2(1.0f, 5.0f), vec2(1.0f, 1.0f), 2.0f);
    CallbackContext *cbc = createCallbackContext(camera);
    TEST_ASSERT_EQUAL(camera, cbc->camera);
    TEST_ASSERT_EQUAL(0.0f, cbc->mousePos.x);
    TEST_ASSERT_EQUAL(0.0f, cbc->mousePos.y);
    free(camera);
    free(cbc);
}


// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(testCreateCamera);
    RUN_TEST(testCreateCallbackContext);
    return UNITY_END();
}
