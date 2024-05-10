#include <unity.h>
#include <map.h>
#include "Mockwindow.h"
#include "Mock2dGraphics.h"

void setUp(void) {
}

void tearDown(void) {
}

void testCreateGizmo(void) {
    Gizmo gizmo;
    unsigned int shader = 3;
    Rectangle rect;
    Rectangle handle1;
    Rectangle handle2;
    newRectangle_ExpectAndReturn(3, &rect);
    newRectangle_ExpectAndReturn(3, &handle1);
    newRectangle_ExpectAndReturn(3, &handle2);
    createGizmo(&gizmo, vec2(1.0f, 5.0f), 2.0f, shader, 3);
    TEST_ASSERT_EQUAL(1.0f, gizmo.pos.x);
    TEST_ASSERT_EQUAL(5.0f, gizmo.pos.y);
    TEST_ASSERT_EQUAL(2.0f, gizmo.angle);
    TEST_ASSERT_EQUAL(3, gizmo.handle1dist);
    TEST_ASSERT_EQUAL(3, gizmo.handle2dist);
    TEST_ASSERT_EQUAL(&rect, gizmo.rect);
    TEST_ASSERT_EQUAL(&handle1, gizmo.rectHandle1);
    TEST_ASSERT_EQUAL(&handle2, gizmo.rectHandle2);
}

void testCreateGizmoRectPos(void) {
    Gizmo gizmo;
    unsigned int shader = 3;
    Rectangle rect;
    Rectangle handle1;
    Rectangle handle2;
    newRectangle_ExpectAndReturn(3, &rect);
    newRectangle_ExpectAndReturn(3, &handle1);
    newRectangle_ExpectAndReturn(3, &handle2);
    createGizmo(&gizmo, vec2(1.0f, 5.0f), 0.0f, shader, 3);
    TEST_ASSERT_EQUAL(1.0f, gizmo.rect->transform.pos.x);
    TEST_ASSERT_EQUAL(5.0f, gizmo.rect->transform.pos.y);
    TEST_ASSERT_EQUAL(0.3f, gizmo.rect->transform.scale.x);
    TEST_ASSERT_EQUAL(0.3f, gizmo.rect->transform.scale.y);
    TEST_ASSERT_EQUAL(4.0f, gizmo.rectHandle1->transform.pos.x);
    TEST_ASSERT_EQUAL(5.0f, gizmo.rectHandle1->transform.pos.y);
    TEST_ASSERT_EQUAL(-2.0f, gizmo.rectHandle2->transform.pos.x);
    TEST_ASSERT_EQUAL(5.0f, gizmo.rectHandle2->transform.pos.y);
}

void testUpdateGizmo(void) {
    Gizmo gizmo;
    unsigned int shader = 3;
    Rectangle rect;
    Rectangle handle1;
    Rectangle handle2;
    newRectangle_ExpectAndReturn(3, &rect);
    newRectangle_ExpectAndReturn(3, &handle1);
    newRectangle_ExpectAndReturn(3, &handle2);
    createGizmo(&gizmo, vec2(0.0f, 0.0f), 0.0f, shader, 3);
    Window Window;
    Camera camera = {vec2(0.0f, 0.0f), vec2(1.0f, 1.0f), 1.0f};
    CallbackContext cbc = {vec2(0.0f, 0.0f), vec2(1.0f, 1.0f), &camera};
    isLeftMouseDown_ExpectAndReturn(&Window, true);
    updateGizmo(&gizmo, &Window, &cbc, &camera);
    isLeftMouseDown_ExpectAndReturn(&Window, true);
    cbc.mousePos = vec2(0.1f, 0.2f);
    updateGizmo(&gizmo, &Window, &cbc, &camera);
    TEST_ASSERT_EQUAL(0.1f, gizmo.pos.x);
    TEST_ASSERT_EQUAL(0.2f, gizmo.pos.y);
}

void testUpdateGizmoHandle1(void) {
    Gizmo gizmo;
    unsigned int shader = 3;
    Rectangle rect;
    Rectangle handle1;
    Rectangle handle2;
    newRectangle_ExpectAndReturn(3, &rect);
    newRectangle_ExpectAndReturn(3, &handle1);
    newRectangle_ExpectAndReturn(3, &handle2);
    createGizmo(&gizmo, vec2(0.0f, 0.0f), 0.0f, shader, 1);
    Window Window;
    Camera camera = {vec2(0.0f, 0.0f), vec2(1.0f, 1.0f), 1.0f};
    CallbackContext cbc = {vec2(1.0f, 0.5f), vec2(1.0f, 1.0f), &camera};
    isLeftMouseDown_ExpectAndReturn(&Window, true);
    updateGizmo(&gizmo, &Window, &cbc, &camera);
    isLeftMouseDown_ExpectAndReturn(&Window, true);
    cbc.mousePos = vec2(0.5f, 0.0f);
    updateGizmo(&gizmo, &Window, &cbc, &camera);
    TEST_ASSERT_EQUAL(0.0f, gizmo.rectHandle1->transform.pos.x);
    TEST_ASSERT_EQUAL(1.0f, gizmo.rectHandle1->transform.pos.y);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, PI/2, gizmo.angle);
}

void testUpdateGizmoHandle2(void) {
    Gizmo gizmo;
    unsigned int shader = 3;
    Rectangle rect;
    Rectangle handle1;
    Rectangle handle2;
    newRectangle_ExpectAndReturn(3, &rect);
    newRectangle_ExpectAndReturn(3, &handle1);
    newRectangle_ExpectAndReturn(3, &handle2);
    createGizmo(&gizmo, vec2(0.0f, 0.0f), 0.0f, shader, 1);
    Window Window;
    Camera camera = {vec2(0.0f, 0.0f), vec2(1.0f, 1.0f), 1.0f};
    CallbackContext cbc = {vec2(0.0f, 0.5f), vec2(1.0f, 1.0f), &camera};
    isLeftMouseDown_ExpectAndReturn(&Window, true);
    updateGizmo(&gizmo, &Window, &cbc, &camera);
    isLeftMouseDown_ExpectAndReturn(&Window, true);
    cbc.mousePos = vec2(0.5f, 0.0f);
    updateGizmo(&gizmo, &Window, &cbc, &camera);
    TEST_ASSERT_EQUAL(0.0f, gizmo.rectHandle2->transform.pos.x);
    TEST_ASSERT_EQUAL(1.0f, gizmo.rectHandle2->transform.pos.y);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, -PI/2, gizmo.angle);
}

void testScreenSpaceToWorldSpace(void) {
    Vec2 mousePos = vec2(0.0f, 1.0f);
    Vec2 screenSize = vec2(2.0f, 2.0f);
    float pixelsPerUnit = 2.0f;
    Vec2 cameraPos = vec2(0.0f, 0.0f);
    Vec2 result = screenToWorldSpace(mousePos, pixelsPerUnit, screenSize, cameraPos);
    TEST_ASSERT_EQUAL(-1.0f, result.x);
    TEST_ASSERT_EQUAL(0.0f, result.y);
}

void testGizmoArrToPath(void) {
    Gizmo gizmos[4];
    newRectangle_IgnoreAndReturn(malloc(sizeof(Rectangle)));
    createGizmos(gizmos, 0);
    Vec2 *points = gizmoArrToPath(gizmos, 4, 10, NULL);
    TEST_ASSERT_EQUAL(0.0f, points[0].x);
    TEST_ASSERT_EQUAL(5.0f, points[0].y);
    TEST_ASSERT_EQUAL(-5.0f, points[10].x);
    TEST_ASSERT_EQUAL(0.0f, points[10].y);
    TEST_ASSERT_EQUAL(0.0f, points[20].x);
    TEST_ASSERT_EQUAL(-5.0f, points[20].y);
    TEST_ASSERT_EQUAL(5.0f, points[30].x);
    TEST_ASSERT_EQUAL(0.0f, points[30].y);
    free(points);
}

void testDrawGizmo(void) {
    float viewMatrix[16];
    translationMatrix(vec2zero(), viewMatrix);
    unsigned int shader = 3;
    Gizmo gizmo;
    Rectangle rect;
    Rectangle handle1;
    Rectangle handle2;
    newRectangle_ExpectAndReturn(3, &rect);
    newRectangle_ExpectAndReturn(3, &handle1);
    newRectangle_ExpectAndReturn(3, &handle2);
    createGizmo(&gizmo, vec2(0.0f, 0.0f), 0.0f, shader, 1.0f);

    drawRectangle_Expect(gizmo.rect, viewMatrix);
    drawRectangle_Expect(gizmo.rectHandle1, viewMatrix);
    drawRectangle_Expect(gizmo.rectHandle2, viewMatrix);

    Vec2 linePoints[3] = {gizmo.rectHandle1->transform.pos, gizmo.pos, gizmo.rectHandle2->transform.pos};
    Line *line1 = malloc(sizeof(Line));
    Line *line2 = malloc(sizeof(Line));
    newLine_ExpectAndReturn(linePoints, 2, 0.10f, false, NULL, line1);
    newLine_ExpectAndReturn(&linePoints[1], 2, 0.10f, false, NULL, line2);
    drawLine_Expect(line1, viewMatrix);
    drawLine_Expect(line1, viewMatrix);
    drawGizmo(&gizmo, viewMatrix, shader);
}


// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(testCreateGizmo);
    RUN_TEST(testCreateGizmoRectPos);
    RUN_TEST(testUpdateGizmo);
    RUN_TEST(testUpdateGizmoHandle1);
    RUN_TEST(testUpdateGizmoHandle2);
    RUN_TEST(testGizmoArrToPath);
    RUN_TEST(testScreenSpaceToWorldSpace);
    testDrawGizmo();
    return UNITY_END();
}
