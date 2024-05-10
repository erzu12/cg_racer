#include <unity.h>
#include <input.h>
#include "Mockwindow.h"

void setUp(void) {
}

void tearDown(void) {
}

void testProcessInput(void) {
    Window Window;
    isEscKeyDown_ExpectAndReturn(&Window, 0);
    processInput(&Window);
}

void testProcessInputKeyDown(void) {
    Window Window;
    isEscKeyDown_ExpectAndReturn(&Window, 1);
    setWindowShouldClose_Expect(&Window, 1);
    processInput(&Window);
}

void testMouseCallback(void) {
    Window Window;
    struct CallbackContext cbc;
    windowGetUserPointer_ExpectAndReturn(&Window, &cbc);
    mouse_callback(&Window, 1.0, 2.0);
    TEST_ASSERT_EQUAL_FLOAT(1.0, cbc.mousePos.x);
    TEST_ASSERT_EQUAL_FLOAT(2.0, cbc.mousePos.y);
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(testProcessInput);
    RUN_TEST(testProcessInputKeyDown);
    RUN_TEST(testMouseCallback);
    return UNITY_END();
}
