#include "spaceracer.h"

#include <2dGraphics.h>
#include <2dMath.h>
#include <2dSpline.h>
#include <2dPhysics.h>

#include <stdio.h>
#include <stdbool.h>

int main()
{
    GLFWwindow* window;
    if(!createGlfwWindow(&window, SCR_WIDTH, SCR_HEIGHT, "Space Racer")) {
        return -1;
    }
    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( openglMessageCallback, 0 );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Vec2 respawnPoint = {0.0f, 0.0f};
    float respawnRot = PI / 2;
    Player *player = createPlayer(respawnPoint, respawnRot);

    Camera *camera = createCamera(respawnPoint, vec2(1.0f / SCR_WIDTH, 1.0f / SCR_HEIGHT), 70.0f);

    CallbackContext *cbc = createCallbackContext(camera);
    glfwSetWindowUserPointer(window, cbc);

    glfwSetCursorPosCallback(window, mouse_callback);

    Game *game = malloc(sizeof(Game));
    game->deltaTime = 0.0;

    unsigned int shader = LoadAndCompileShaders("assets/shader.vert", "assets/shader.frag");

    Image *ship = newImage("assets/ship.png", GL_RGBA, GL_RGBA);
    ship->rect.transform.scale = vec2Scale(ship->rect.transform.scale, 2.0f);

    Vec2 initalVel = vec2(10.0f, 0.0f);
    ParticleSys *particleSys = createParticleSys(respawnPoint, initalVel, "assets/smoke1.png");
    player->engine = particleSys;

    Gizmo gizmos[4];
    createGizmos(gizmos, shader);

    Vec2 *path = gizmoArrToPath(gizmos, 4, 40, NULL);
    Line *line = newLine(path, 4 * 40, 6.0f, true, NULL);

    loop(window, game, player, camera, shader, ship, particleSys, gizmos, path, line, cbc);

    deleteParticleSys(particleSys);
    freeGizmos(gizmos, 4);
    free(path);
    free(line);
    free(player);
    free(camera);
    free(game);
    freeImage(ship);
    free(cbc);

    glfwTerminate();
    return 0;
}

bool createGlfwWindow(GLFWwindow **window, int width, int height, const char *title) {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    *window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(*window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);

    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(*window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        printf("raw mouse\n");
    }

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return false;
    }
    return true;
}

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

CallbackContext *createCallbackContext(Camera *camera) {
    struct CallbackContext *cbc = malloc(sizeof(struct CallbackContext));
    cbc->camera = camera;
    cbc->mousePos.x = 0.0f;
    cbc->mousePos.y = 0.0f;
    return cbc;
}

Camera *createCamera(Vec2 pos, Vec2 aspecRatio, float pixelsPerUnit) {
    Camera *camera = malloc(sizeof(Camera));
    camera->pos = pos;
    camera->pixelsPerUnit = pixelsPerUnit;
    camera->aspecRatio = aspecRatio;
    return camera;
}

ParticleSys *createParticleSys(Vec2 pos, Vec2 initalVel, const char *smokePath) {
    Image *smoke = newImage(smokePath, GL_RGBA, GL_RGBA);
    ParticleSys *particleSys = newParticleSys(200, smoke, pos, 1.0, initalVel);
    particleSys->randAngle = 0.1f;
    particleSys->randSpeed = 0.4f;
    particleSys->growth = 2.0f;
    particleSys->fade = 1.0f;
    return particleSys;
}

void createGizmos(Gizmo *gizmos, unsigned int shader) {
    createGizmo(&gizmos[0], vec2(0.0f, 5.0f), 0.0f, shader, 3);
    createGizmo(&gizmos[1], vec2(-5.0f, 0.0f), PI/2, shader, 3);
    createGizmo(&gizmos[2], vec2(0.0f, -5.0f), PI, shader, 3);
    createGizmo(&gizmos[3], vec2(5.0f, 0.0f), PI + PI/2, shader, 3);
}

void freeGizmos(Gizmo *gizmos, int count) {
    for(int i = 0; i < count; i++) {
        free(gizmos[i].rect);
        free(gizmos[i].rectHandle1);
        free(gizmos[i].rectHandle2);
    }
}

//still way to long
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
) {
    double currentFrame = glfwGetTime();
    double lastFrame = currentFrame;

    bool editMode = true;
    bool justPressed = false;
    float viewMat[9];

    while (!glfwWindowShouldClose(window))
    {
        currentFrame = glfwGetTime();
        game->deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

        Vec2 viewScale = vec2Scale(camera->aspecRatio, camera->pixelsPerUnit);

        if(glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE) {
            justPressed = false;
        }

        if(editMode) {
            path = gizmoArrToPath(gizmos, 4, 40, path);
            line = newLine(path, 4 * 40, 6.0f, true, line);
            line->shader = shader;
            if(glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && !justPressed) {
                editMode = false;
                justPressed = true;
            }
            camera->pos = vec2zero();
        }
        else {
            updatePlayer(window, player, game);
            particleSys->pos = vec2Add(player->pos, vec2Rot(vec2(0.0f, -1.0f), player->rot));
            particleSys->initalVel = vec2Add(player->vel, vec2Rot(vec2(0.0f, -10.0f), player->rot));

            bool colliding = false;
            player->respawnPoint = gizmos[0].pos;

            if(glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && !justPressed) {
                editMode = true;
                justPressed = true;
                colliding = true;
            }

            if(!pointOnPath(path, 4 * 40 + 1, player->pos, 2.7f)) {
                colliding = true;
            }

            if(colliding) {
                player->vel = vec2zero();
                player->pos = player->respawnPoint;
                player->rotVel = 0.0f;
                player->rot = player->respawnRot;
            }
            camera->pos = vec2Lerp(camera->pos, player->pos, 3.0f * (float)game->deltaTime);

            ship->rect.transform.pos = player->pos;
            ship->rect.transform.rot = player->rot;
        }

        translationMatrix(vec2Subtraction(vec2zero(), camera->pos), viewMat);
        scaleMat(viewScale, viewMat);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        for(int i = 0; i < 4; i++) {
            updateGizmo(&gizmos[i], window, cbc, camera);
        }

        glUseProgram(shader);

        UniformVec3(shader, "col", 0.3f, 0.4f, 0.5f);
        drawLine(line, viewMat);
        UniformVec3(shader, "col", 1.0f, 0.0f, 0.0f);
        if(editMode) {
            for(int i = 0; i < 4; i++) {
                drawGizmo(&gizmos[i], viewMat, shader);
            }
        }
        else {
            drawImage(ship, viewMat);
            drawParticleSys(player->engine, viewMat, (float)game->deltaTime);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
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

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void mouse_callback(GLFWwindow *window, double posX, double posY){
    struct CallbackContext *cbc = (struct CallbackContext *)glfwGetWindowUserPointer(window);
    cbc->mousePos.x = (float)posX;
    cbc->mousePos.y = (float)posY;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);

    struct CallbackContext *cbc = glfwGetWindowUserPointer(window);

    cbc->camera->aspecRatio = vec2(1.0f / (float)width, 1.0f / (float)height);

    cbc->screenSize.x = (float)width;
    cbc->screenSize.y = (float)height;
}

Vec2 screenToWorldSpace(Vec2 screenPos, float pixelsPerUnit, Vec2 screenSize, Vec2 cameraPos) {
    float x = screenPos.x - screenSize.x / 2;
    float y = screenPos.y - screenSize.y / 2;

    x /= pixelsPerUnit / 2;
    y /= -pixelsPerUnit / 2;

    x += cameraPos.x;
    y += cameraPos.y;

    return vec2(x, y);
}

Vec2 stringToVec2(const char *str) {
    float x = (float)atof(str);

    const char *comaLoc = strchr (str, ',');
    if (comaLoc == NULL) {
        printf("Vec2 parse error\n");
        return vec2(0.0f, 0.0f);
    }
    
    float y = (float)atof(comaLoc + 1);

    return vec2(x, y);
}

void createGizmo(Gizmo * gizmo, Vec2 pos, float angle, unsigned int shader, float scale) {

    gizmo->pos = pos;
    gizmo->angle = angle;
    gizmo->handle1dist = scale;
    gizmo->handle2dist = scale;

    Vec2 handle1dir = vec2Rot(vec2(scale, 0.0f), angle);
    Vec2 handle2dir = vec2Rot(vec2(-scale, 0.0f), angle);

    gizmo->rect = newRectangle(shader);
    gizmo->rect->transform.pos = pos;
    gizmo->rect->transform.scale = vec2(0.3f, 0.3f);

    gizmo->rectHandle1 = newRectangle(shader);
    gizmo->rectHandle1->transform.pos = vec2Add(pos, handle1dir);
    gizmo->rectHandle1->transform.scale = vec2(0.3f, 0.3f);

    gizmo->rectHandle2 = newRectangle(shader);
    gizmo->rectHandle2->transform.pos = vec2Add(pos, handle2dir);
    gizmo->rectHandle2->transform.scale = vec2(0.3f, 0.3f);
}

void updateGizmoPos(Gizmo *gizmo) {
    Vec2 posHandle1 = vec2Rot(vec2(gizmo->handle1dist, 0.0f), gizmo->angle);
    Vec2 posHandle2 = vec2Rot(vec2(-gizmo->handle2dist, 0.0f), gizmo->angle);
    posHandle1 = vec2Add(posHandle1, gizmo->pos);
    posHandle2 = vec2Add(posHandle2, gizmo->pos);

    gizmo->rect->transform.pos = gizmo->pos;
    gizmo->rectHandle1->transform.pos = posHandle1;
    gizmo->rectHandle2->transform.pos = posHandle2;
}


void updateGizmo(Gizmo *gizmo, GLFWwindow *window, const CallbackContext *cbc, const Camera *camera) {
    static int draging = 0;
    static Gizmo *dragingGizmo = NULL;
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS) {
        Vec2 mousePos = screenToWorldSpace(cbc->mousePos, camera->pixelsPerUnit, cbc->screenSize, camera->pos);
        if(pointInRect(gizmo->rect, mousePos)) {
            draging = 1;
            dragingGizmo = gizmo;
        }
        else if(pointInRect(gizmo->rectHandle1, mousePos)) {
            draging = 2;
            dragingGizmo = gizmo;
        }
        else if(pointInRect(gizmo->rectHandle2, mousePos)) {
            draging = 3;
            dragingGizmo = gizmo;
        }
        switch (draging) {
            case 0:
                break;
            case 1:
                dragingGizmo->pos = mousePos;
                break;
            case 2:
                dragingGizmo->handle1dist = vec2Magnitude(vec2Subtraction(mousePos, dragingGizmo->pos));
                dragingGizmo->angle = -vec2Angle(vec2Subtraction(mousePos, dragingGizmo->pos), vec2(1.0f, 0.0f));
                break;
            case 3:
                dragingGizmo->handle2dist = vec2Magnitude(vec2Subtraction(mousePos, dragingGizmo->pos));
                dragingGizmo->angle = -vec2Angle(vec2Subtraction(mousePos, dragingGizmo->pos), vec2(-1.0f, 0.0f));
                break;
            default:
                printf("error\n");
                break;
        }
        updateGizmoPos(gizmo);
    }
    else {
        draging = 0;
    }
}

void drawGizmo(Gizmo *gizmo, float *viewMat, unsigned int shader) {

    drawRectangle(gizmo->rect, viewMat);
    drawRectangle(gizmo->rectHandle1, viewMat);
    drawRectangle(gizmo->rectHandle2, viewMat);

    Vec2 linePoints[3] = {gizmo->rectHandle1->transform.pos, gizmo->pos, gizmo->rectHandle2->transform.pos};

    Line *line1 = newLine(linePoints, 2, 0.10f, false, NULL);
    line1->shader = shader;
    Line *line2 = newLine(&linePoints[1], 2, 0.10f, false, NULL);
    line2->shader = shader;

    drawLine(line1, viewMat);
    drawLine(line2, viewMat);
    free(line1);
    free(line2);
}

Vec2 *gizmoArrToPath(const Gizmo *gizmo, int gizmoCount, int resolusion, Vec2 *points) {
    if(!points) {
        points = malloc(sizeof(Vec2) * gizmoCount * resolusion);
    }
    for(int i = 0; i < gizmoCount; i++) {
        int iplus1 = (i + 1) % gizmoCount;
        spline(&points[i * resolusion], resolusion, gizmo[i].pos, gizmo[i].rectHandle2->transform.pos, gizmo[iplus1].rectHandle1->transform.pos, gizmo[iplus1].pos);
    }
    return points;
}
