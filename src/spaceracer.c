#include "spaceracer.h"

#include <2dGraphics.h>
#include <2dMath.h>
#include <2dSpline.h>
#include <2dPhysics.h>

#include <stdio.h>
#include <stdbool.h>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int spaceracer()
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


ParticleSys *createParticleSys(Vec2 pos, Vec2 initalVel, const char *smokePath) {
    Image *smoke = newImage(smokePath, GL_RGBA, GL_RGBA);
    ParticleSys *particleSys = newParticleSys(200, smoke, pos, 1.0, initalVel);
    particleSys->randAngle = 0.1f;
    particleSys->randSpeed = 0.4f;
    particleSys->growth = 2.0f;
    particleSys->fade = 1.0f;
    return particleSys;
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
