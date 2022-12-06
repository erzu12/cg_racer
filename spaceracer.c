#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <2dGraphics.h>
#include <2dMath.h>
#include <2dSpline.h>

#include <stdio.h>
#include <stdbool.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double posX, double posY);
Vec2 screenToWorldSpace(Vec2 screenPos, float pixelsPerUnit, Vec2 screenSize);
Vec2 **loadPathFromSvg(const char* path, int **pointCounts, int *pathCount);



typedef struct Player {
    Vec2 pos;
    Vec2 vel;
    float rot;
    float rotVel;
    Vec2 colCheck[4];
} Player;

typedef struct Camera {
    Vec2 pos;
    Vec2 aspecRatio;
    float pixelsPerUnit;
} Camera;

typedef struct Game {
    float deltaTime;
} Game;

struct CallbackContext {
    Vec2 mousePos;
    Vec2 screenSize;
    Camera *camera;
};

void updatePlayer(GLFWwindow *window, Player *player, Game *game);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        printf("raw mouse\n");
    }

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( openglMessageCallback, 0 );

    struct CallbackContext *cbc = malloc(sizeof(struct CallbackContext));

    Vec2 respawnPoint = {0.0f, 32.0f};
    float respawnRot = PI / 2;
    Player *player = malloc(sizeof(Player));
    player->pos = respawnPoint;
    player->vel = vec2zero();
    player->rot = respawnRot;
    player->rotVel = 0;
    player->colCheck[0] = vec2(1.0f, 0.0f);
    player->colCheck[1] = vec2(-1.0f, 0.0f);
    player->colCheck[2] = vec2(0.0f, 1.0f);
    player->colCheck[3] = vec2(0.0f, -1.0f);

    Camera camera;
    camera.pos = respawnPoint;

    camera.pixelsPerUnit = 70;
    float viewMat[9];

    camera.aspecRatio = vec2(1 / SCR_HEIGHT, 1 / SCR_WIDTH);

    cbc->camera = &camera;
    cbc->mousePos.x = 0.0f;
    cbc->mousePos.y = 0.0f;
    glfwSetWindowUserPointer(window, cbc);

    glfwSetCursorPosCallback(window, mouse_callback);

    Game *game = malloc(sizeof(Game));
    float currentFrame = glfwGetTime();
    float lastFrame = currentFrame;
    game->deltaTime = 0.0;




    unsigned int shader = LoadAndCompileShaders("assets/shader.vert", "assets/shader.frag");
    
    //struct Rectangle *rectangle = newRectangle();
    Image *ship = newImage("assets/ship.png", GL_RGBA, GL_RGBA);
    ship->rect->transform.scale = vec2Scale(ship->rect->transform.scale, 2.0f);
    //rectangle->shader = shader;
    //ship->rect->transform.scale = vec2(0.5f, 1.0f);

    //Image *image = newImage("assets/invasion.png", GL_RGBA, GL_RGBA);
    //image->rect->transform.scale = vec2Scale(image->rect->transform.scale, 10.0f);
    
    int *splinePointsCount;
    int pathCount;
    Vec2 **paths = loadPathFromSvg("assets/track1.svg", &splinePointsCount, &pathCount);

    if(pathCount != 2) {
        printf("error loading map path count %d\n", pathCount);
        exit(1);
    }

    Vec2 *splinePoints1 = paths[0];

    float mapScale = 30.0f;
    int splineRes = 40;
    int pointsCount1 = (splinePointsCount[0] - 1) / 3 * splineRes;
    Vec2 points1[pointsCount1];

    for(int i  = 0; i < splinePointsCount[0]; i++) { 
        splinePoints1[i] = screenToWorldSpace(splinePoints1[i], mapScale, vec2(1920, 1080));
    }

    for(int i  = 0, j = 0; i < splinePointsCount[0] - 1; i += 3, j++) {
        spline(&points1[j * splineRes], splineRes, splinePoints1[i], splinePoints1[i + 1], splinePoints1[i + 2], splinePoints1[i + 3]);
    }

    Line *line1 = newLine(points1, pointsCount1, 0.03f);
    line1->shader = shader;


    Vec2 *splinePoints2 = paths[1];

    int pointsCount2 = (splinePointsCount[1] - 1) / 3 * splineRes;
    Vec2 points2[pointsCount2];

    for(int i  = 0; i < splinePointsCount[1]; i++) { 
        splinePoints2[i] = screenToWorldSpace(splinePoints2[i], mapScale, vec2(1920, 1080));
    }

    for(int i  = 0, j = 0; i < splinePointsCount[1] - 1; i += 3, j++) {
        spline(&points2[j * splineRes], splineRes, splinePoints2[i], splinePoints2[i + 1], splinePoints2[i + 2], splinePoints2[i + 3]);
    }

    Line *line2 = newLine(points2, pointsCount2, 0.03f);
    line2->shader = shader;

    //line->transform.scale = vec2(0.01f, 0.01f);

    while (!glfwWindowShouldClose(window))
    {
        currentFrame = glfwGetTime();
        game->deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        updatePlayer(window, player, game);

        bool colliding = false;
        for(int i = 0; i < 4; i++) {
            if(!pointInPath(vec2Add(player->pos, vec2Rot(player->colCheck[i], player->rot)), points1, pointsCount1) ||
               pointInPath(vec2Add(player->pos, vec2Rot(player->colCheck[i], player->rot)), points2, pointsCount2))
            {
                colliding = true;
            }
        }
        if(colliding) {
            //printf("colliding\n");
            player->vel = vec2zero();
            player->pos = respawnPoint;
            player->rotVel = 0.0f;
            player->rot = respawnRot;
        }

        Vec2 viewScale = vec2Scale(camera.aspecRatio, camera.pixelsPerUnit / (1 + vec2Magnitude(player->vel) * 0.010f));
        camera.pos = vec2Lerp(camera.pos, player->pos, 3.0f * game->deltaTime);

        translationMatrix(vec2Subtraction(vec2zero(), camera.pos), viewMat);
        scaleMat(viewScale, viewMat);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ship->rect->transform.pos = player->pos;
        ship->rect->transform.rot = player->rot;

        glUseProgram(shader);
        UniformVec3(shader, "col", 1.0, 0.0, 0.0);

        //drawImage(image, viewMat);
        //drawRectangle(rectangle, viewMat);
        drawLine(line1, viewMat);
        drawLine(line2, viewMat);
        drawImage(ship, viewMat);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void updatePlayer(GLFWwindow *window, Player *player, Game *game) {
    Vec2 input = vec2zero();
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
        input = vec2Add(input, vec2(0.0f, 1.0f));
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        input = vec2Add(input, vec2(0.0f, -1.0f));
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
        input = vec2Add(input, vec2(1.0f, 0.0f));
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
        input = vec2Add(input, vec2(-1.0f, 0.0f));

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) 
        input = vec2Add(input, vec2(0.0f, 2.0f));

    float rotInput = 0.0f;
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) 
        rotInput += 1.0f;
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) 
        rotInput -= 1.0f;

    player->rotVel += rotInput * 10.0 * game->deltaTime;
    player->rot += player->rotVel * game->deltaTime;
    input = vec2Rot(input, player->rot);

    //vec2Noramlize(input);

    player->vel = vec2Add(player->vel, vec2Scale(input, 8.0 * game->deltaTime));
    player->pos = vec2Add(player->pos, vec2Scale(player->vel, game->deltaTime));
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void mouse_callback(GLFWwindow *window, double posX, double posY){
    struct CallbackContext *cbc = (struct CallbackContext *)glfwGetWindowUserPointer(window);
    cbc->mousePos.x = posX;
    cbc->mousePos.y = posY;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);

    struct CallbackContext *cbc = glfwGetWindowUserPointer(window);

    cbc->camera->aspecRatio = vec2(1.0f / width, 1.0f / height);

    cbc->screenSize.x = width;
    cbc->screenSize.y = height;
}

Vec2 screenToWorldSpace(Vec2 screenPos, float pixelsPerUnit, Vec2 screenSize) {
    float x = screenPos.x - screenSize.x / 2;
    float y = screenPos.y - screenSize.y / 2;

    x /= pixelsPerUnit / 2;
    y /= -pixelsPerUnit / 2;

    return vec2(x, y);
}

Vec2 stringToVec2(const char *str) {
    float x = atof (str);

    char *comaLoc = strchr (str, ',');
    if (comaLoc == NULL) {
        printf("Vec2 parse error\n");
        return vec2(0.0f, 0.0f);
    }
    
    float y = atof(comaLoc + 1);

    return vec2(x, y);
}

void readSvgC(char **str, Vec2 *points, int *curPoint, bool isRelativ) {
    char *cur = *str;
    Vec2 lastPoint = points[*curPoint - 1];
    int cpoint = 0;
    while(*cur != 'Z' && *cur != 'z' && cur[1] != 'C' && cur[1] != 'c' && *cur != '\0') {
        if(*cur == ' ' && cur[1] != 'Z' && cur[1] != 'z' && cur[1] != 'C' && cur[1] != 'c') {
            if(isRelativ) {
                points[*curPoint] = vec2Add(stringToVec2(cur), lastPoint);
                if(cpoint % 3 == 2) {
                    lastPoint = points[*curPoint];
                }
            }
            else {
                points[*curPoint] = stringToVec2(cur);
            }
            (*curPoint)++;
            cpoint++;
        }
        cur++;
    }
    *str = cur;
}

Vec2 **loadPathFromSvg(const char* path, int **pointCounts, int *pathCount) {
    FILE * pFile;
    long lSize;
    char * buffer;
    size_t result;
    
    pFile = fopen ( path , "r" );
    if (pFile==NULL) {
        fputs ("File error",stderr); exit (1);
        printf("File error\n");
    }
    
    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);
    
    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {
        fputs ("Memory error",stderr); exit (2);
        printf("Memory error\n");
    }
    
    // copy the file into the buffer:
    result = fread (buffer,1,lSize,pFile);
    if (result != lSize) {
        fputs ("Reading error",stderr); exit (3);
        printf("Reading error\n");
    }

    Vec2 points[1000];
    int interPointCounts[100];
    int lastPointCount = 0;
    int curPoint = 0;
    int curPath = 0;
    
    char *pathloc = strstr (buffer, "<path");
    while (pathloc != NULL) {

        char *cur = &pathloc[5];
        while(cur[0] != '>') {
            if(cur[0] == 'd' && cur[1] == '=' && cur[2] == '"') {
                cur = &cur[3];
                while(cur[0] != '"') {
                    switch(*cur) {
                        case 'M':
                            cur++;
                            points[curPoint] = stringToVec2(cur);
                            curPoint++;
                            cur++;
                            break;
                        case 'm':
                            cur++;
                            //points[curPoint] = vec2Add(stringToVec2(cur), points[curPoint - 1]);
                            points[curPoint] = stringToVec2(cur);
                            curPoint++;
                            cur++;
                            break;
                        case 'C':
                            readSvgC(&cur, points, &curPoint, false);
                            break;
                        case 'c':
                            readSvgC(&cur, points, &curPoint, true);
                            break;
                        case 'Z':
                            cur++;
                            break;
                        default:
                            cur++;
                            break;
                    }
                }
                break;
            }
            cur++;
        }
        interPointCounts[curPath] = curPoint - lastPointCount;
        lastPointCount = interPointCounts[curPath];
        curPath++;
        pathloc = strstr (cur, "<path");
    }

    *pathCount = curPath;

    *pointCounts = malloc(sizeof(int) * *pathCount);
    memcpy(*pointCounts, interPointCounts, sizeof(int) * *pathCount);

    Vec2 *retPoints = malloc(sizeof(Vec2) * curPoint);
    memcpy(retPoints, points, sizeof(Vec2) * curPoint);
    
    Vec2 **paths = malloc(sizeof(Vec2*) * *pathCount);
    lastPointCount = 0;
    for(int i = 0; i < *pathCount; i++) {
        paths[i] = &retPoints[lastPointCount];
        lastPointCount = *pointCounts[i];
    }
    
    // terminate
    fclose (pFile);
    free (buffer);

    return paths;
}
