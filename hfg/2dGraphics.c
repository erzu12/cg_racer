#include "2dGraphics.h"
#include <GLFW/glfw3.h>

Rectangle *newRectangle(unsigned int shader) {
    float vertices[] = {
        0.5f,  0.5f,
        0.5f, -0.5f,
        -0.5f, -0.5f,
        -0.5f,  0.5f
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,
        1, 2, 3
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    Rectangle *rectangle = malloc(sizeof(Rectangle));

    rectangle->VAO = VAO;
    rectangle->transform.pos = vec2zero();
    rectangle->transform.scale = vec2(1.0f, 1.0f);
    rectangle->transform.rot = 0.0f;
    rectangle->shader = shader;
    return rectangle;
}

void drawRectangle(struct Rectangle* rectangle, float *viewMat) {
    float transform[9] = IndexMat3d;

    scaleMat(rectangle->transform.scale, transform);
    rotateMat(rectangle->transform.rot, transform);
    translateMat(rectangle->transform.pos, transform);

    glUseProgram(rectangle->shader);
    UniformMat3v(rectangle->shader, "transform", transform);
    UniformMat3v(rectangle->shader, "view", viewMat);

    glBindVertexArray(rectangle->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

unsigned int LoadTextureWithSize(const char *path, GLint colorSpace, GLint internalColorSpace, int *texWidth, int *texHeight) {
    unsigned int texture;
    int nrChannels;
    unsigned char *data;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(path, texWidth, texHeight, &nrChannels, 0);

    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, colorSpace, *texWidth, *texHeight, 0, internalColorSpace, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        printf("faild to load texture: %s\n", path);
    }
    stbi_image_free(data);

    return texture;
}

unsigned int LoadTexture(const char *path, GLint colorSpace, GLint internalColorSpace) {
    int texWidth, texHeight;
    return LoadTextureWithSize(path, colorSpace, internalColorSpace, &texWidth, &texHeight);
}

Image *newImage(const char *path, GLint colorSpace, GLint internalColorSpace) {
    Image *image = malloc(sizeof(Image));

    int texWidth, texHeight;
    image->texture = LoadTextureWithSize(path, colorSpace, internalColorSpace, &texWidth, &texHeight);
    image->opacity = 1.0f;

    unsigned int shader = LoadAndCompileShaders("hfg/assets/image.vert", "hfg/assets/image.frag");
    Rectangle *rect = newRectangle(shader);
    glUseProgram(rect->shader);
    glUniform1i(glGetUniformLocation(rect->shader, "image"), 0);

    if(texWidth > texHeight) {
        rect->transform.scale.y = (float)texHeight / texWidth;
    }
    else {
        rect->transform.scale.x = (float)texWidth / texHeight;
    }

    image->rect = *rect;
    free(rect);
    return image;
}

void drawImage(Image *image, float *viewMat) {
    glUseProgram(image->rect.shader);
    glUniform1f(glGetUniformLocation(image->rect.shader, "opacity"), image->opacity);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, image->texture);
    drawRectangle(&image->rect, viewMat);
}

void freeImage(Image *image) {
    glDeleteTextures(1, &image->texture);
    free(image);
}

ParticleSys *newParticleSys(int maxParticles, Image *image, Vec2 pos, float initialSize, Vec2 initalVel) {
    ParticleSys *particleSys = malloc(sizeof(ParticleSys));
    particleSys->image = image;
    particleSys->maxParticles = maxParticles;
    particleSys->particleCount = 0;
    particleSys->pos = pos;
    particleSys->initalVel = initalVel;
    particleSys->initialSize = initialSize;
    particleSys->randAngle = 0.0f;
    particleSys->randSpeed = 0.0f;
    particleSys->initialOpacity = 1.0f;
    particleSys->growth = 0.0f;
    particleSys->fade = 0.0f;
    particleSys->particles = malloc(sizeof(ParticleSys) * maxParticles);

    return particleSys;

}

void spawnParticle(ParticleSys* particleSys, float lifeTime) {
    //Particle *particle = malloc(sizeof(Particle));
    if (particleSys == NULL) {
        printf("particleSys is NULL\n");
        return;
    }

    if(particleSys->particleCount < particleSys->maxParticles) {
        Particle particle;
        particle.image = *particleSys->image;
        particle.image.rect.transform.pos = particleSys->pos; 
        particle.image.rect.transform.scale = vec2(particleSys->initialSize, particleSys->initialSize); 
        float randSpeed = (float)rand()/(float)RAND_MAX  * particleSys->randSpeed * 2 - particleSys->randSpeed;
        Vec2 vel = vec2Scale(particleSys->initalVel, 1 + randSpeed);
        float randAngle = (float)rand()/(float)RAND_MAX  * particleSys->randAngle * 2 - particleSys->randAngle;
        vel = vec2Rot(vel, randAngle);
        particle.vel = vel;
        particle.lifeTime = lifeTime;
        particle.start = glfwGetTime();
        particleSys->particles[particleSys->particleCount] = particle;
        particleSys->particleCount++;
    }
    else {
        printf("can't spawn Particle, maxParticles reached\n");
    }

}

void drawParticleSys(ParticleSys *particleSys, float *viewMat, float deltaTime) {
    for(int i = 0; i < particleSys->particleCount; i++) {
        Particle particle = particleSys->particles[i];
        if(glfwGetTime() - particle.start > particle.lifeTime) {
            particleSys->particleCount--;
            if( particleSys->particleCount == 0 ) {
                break;
            }
            particle = particleSys->particles[particleSys->particleCount];
            particleSys->particles[i] = particle;
        }

        particleSys->particles[i].image.rect.transform.pos = vec2Add(particle.image.rect.transform.pos, vec2Scale(particle.vel, deltaTime));
        particleSys->particles[i].image.opacity = particle.image.opacity - particleSys->fade * deltaTime;
        Vec2 growthVec = vec2(particleSys->growth * deltaTime, particleSys->growth * deltaTime);
        particleSys->particles[i].image.rect.transform.scale = vec2Add(particle.image.rect.transform.scale, growthVec);
        drawImage(&particle.image, viewMat);
    }
}

void deleteParticleSys(ParticleSys *particleSys) {
    free(particleSys->particles);
    free(particleSys->image);
    free(particleSys);
}

Line *newLine(Vec2 *points, int pointCount, float thickness, bool closed, Line *line) {

    int vertCount = 4 * pointCount;
    float *verts = malloc(vertCount * sizeof(float));
    int indCount = 6 * (pointCount - 1);
    if(closed) {
        indCount += 6;
    }
    unsigned int *inds = malloc(indCount * sizeof(int));

    Vec2 start = vec2Noramlize(vec2Subtraction(points[1], points[0]));
    Vec2 p1 = vec2Add(points[0], vec2Scale(vec2Rot(start, PI / 2), thickness / 2));
    Vec2 p2 = vec2Add(points[0], vec2Scale(vec2Rot(start, -PI / 2), thickness / 2));

    verts[0] = p1.x;
    verts[1] = p1.y;
    verts[2] = p2.x;
    verts[3] = p2.y;

    for(int i = 1; i < pointCount; i++) {
        Vec2 current = vec2Noramlize(vec2Subtraction(points[i], points[i - 1]));
        Vec2 next;
        if(i == pointCount - 1) {
            next = current;
        }
        else {
            next = vec2Noramlize(vec2Subtraction(points[i + 1], points[i]));
        }
        float angle = vec2Angle(current, next) / 2;
        float dist = 1.0f / cos(angle);
        Vec2 p1 = vec2Add(points[i], vec2Scale(vec2Rot(current, PI / 2 + angle), thickness / 2 * dist));
        Vec2 p2 = vec2Add(points[i], vec2Scale(vec2Rot(current, -PI / 2 + angle), thickness / 2 * dist));

        verts[i * 4] = p1.x;
        verts[i * 4 + 1] = p1.y;
        verts[i * 4 + 2] = p2.x;
        verts[i * 4 + 3] = p2.y;

        inds[i * 6 - 6] = i * 2 - 2;
        inds[i * 6 - 5] = i * 2 - 1;
        inds[i * 6 - 4] = i * 2;
        inds[i * 6 - 3] = i * 2 - 1;
        inds[i * 6 - 2] = i * 2 + 1;
        inds[i * 6 - 1] = i * 2;
    }

    if(closed) {
        inds[indCount - 6] = 0;
        inds[indCount - 5] = 1;
        inds[indCount - 4] = pointCount * 2 - 2;
        inds[indCount - 3] = 1;
        inds[indCount - 2] = pointCount * 2 - 1;
        inds[indCount - 1] = pointCount * 2 - 2;
    }


    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(float), verts, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indCount * sizeof(unsigned int), inds, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    free(verts);
    free(inds);

    if(!line) {
        line = malloc(sizeof(Line));
    }

    line->VAO = VAO;
    line->indCount = indCount;
    line->transform.pos = vec2zero();
    line->transform.scale = vec2(1.0f, 1.0f);
    line->transform.rot = 0.0f;
    return line;
}

void drawLine(Line *line, float *viewMat) {

    float transform[9] = IndexMat3d;

    scaleMat(line->transform.scale, transform);
    rotateMat(line->transform.rot, transform);
    translateMat(line->transform.pos, transform);

    glUseProgram(line->shader);
    UniformMat3v(line->shader, "transform", transform);
    UniformMat3v(line->shader, "view", viewMat);

    glBindVertexArray(line->VAO);
    glDrawElements(GL_TRIANGLES, line->indCount, GL_UNSIGNED_INT, 0);
}

unsigned int LoadAndCompileShaders(const char* vertexPath, const char* fragmentPath) {

    FILE *fpVert, *fpFrag;
    unsigned int sizev, sizef;

    fpVert = fopen(vertexPath, "r");
    fpFrag = fopen(fragmentPath, "r");

    if(fpVert == NULL) {
        printf("faild to load %s\n", vertexPath);
        exit(EXIT_FAILURE);
    }
    if(fpFrag == NULL) {
        printf("faild to load %s\n", fragmentPath);
        exit(EXIT_FAILURE);
    }

    fseek(fpVert, 0, SEEK_END); 
    sizev = ftell(fpVert);
    fseek(fpVert, 0, SEEK_SET);

    fseek(fpFrag, 0, SEEK_END); 
    sizef = ftell(fpFrag);
    fseek(fpFrag, 0, SEEK_SET);

    char *vertCode = (char *)malloc((size_t)sizev + 1);
    if (vertCode == NULL) { printf("Memory error"); exit (EXIT_FAILURE); }
    char *fragCode = (char *)malloc((size_t)sizef + 1);
    if (fragCode == NULL) { printf("Memory error"); exit (EXIT_FAILURE); }

    int result = fread (vertCode, 1, sizev, fpVert);
    if (result != sizev) { printf("ERROR: faild to read: %s\n", vertexPath); }

    result = fread (fragCode, 1, sizef, fpFrag);
    if (result != sizef) { printf("ERROR: faild to read: %s\n", fragmentPath); }

    //for(int i = 0; i < sizev; i++){
    //	vertCode[i] = fgetc(fpVert);
    //}
    vertCode[sizev] = '\0';
    //for(int i = 0; i < sizef; i++){
    //	fragCode[i] = fgetc(fpFrag);
    //}
    fragCode[sizef] = '\0';

    fclose(fpVert);
    fclose(fpFrag);


    const char* vertCodeArr[1];
    const char* fragCodeArr[1];

    vertCodeArr[0] = vertCode;
    fragCodeArr[0] = fragCode;
    int success;
    char infoLog[512];

    //VertexShader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, vertCodeArr, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR: VertexShader: %s faild to compile:\n%s\n", vertexPath, infoLog);
        exit(EXIT_FAILURE);
    }

    //Fragment Shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, fragCodeArr, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    free(fragCode);
    free(vertCode);

    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR: FragmentShader: %s faild to compile:\n%s\n", fragmentPath, infoLog);
        exit(EXIT_FAILURE);
    }

    //Shader Program
    unsigned int shaderProgram;
    shaderProgram =glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR: shader_program linking faild", infoLog, "\n");
        exit(EXIT_FAILURE);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void UniformVec3(unsigned int shader, const char* name, float x, float y, float z) {
    glUseProgram(shader);
    unsigned int pos = glGetUniformLocation(shader, name);
    if(pos == -1) {
        printf("ERROR: UniformVec3: %s not found\n", name);
        return;
    }
    glUniform3f(pos, x, y, z);
}
void UniformVec3v(unsigned int shader, const char* name, const GLfloat *val) {
    glUseProgram(shader);
    unsigned int pos = glGetUniformLocation(shader, name);
    if(pos == -1) {
        printf("ERROR: UniformVec3v: %s not found\n", name);
        return;
    }
    glUniform3fv(pos, 1, val);
}
void UniformMat3v(unsigned int shader, const char* name, const GLfloat *val) {
    glUseProgram(shader);
    unsigned int pos = glGetUniformLocation(shader, name);
    if(pos == -1) {
        printf("ERROR: UniformMat3v: %s not found\n", name);
        return;
    }
    glUniformMatrix3fv(pos, 1, GL_TRUE, val);
}

void APIENTRY openglMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    if(severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;
    printf("---------------------opengl-callback-start------------\n");
    printf("message: %s\n", message);
    printf("type: ");
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            printf("ERROR");
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            printf("DEPRECATED_BEHAVIOR");
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            printf("UNDEFINED_BEHAVIOR");
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            printf("PORTABILITY");
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            printf("PERFORMANCE");
            break;
        case GL_DEBUG_TYPE_OTHER:
            printf("OTHER");
            break;
    }
    printf("\n");

    printf("id: %d\n", id);
    printf("severity: ");
    switch (severity){
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            printf("NOTIFICATION");
            break;
        case GL_DEBUG_SEVERITY_LOW:
            printf("LOW");
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            printf("MEDIUM");
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            printf("HIGH");
            break;
    }
    printf("\n");
    printf("---------------------opengl-callback-end--------------\n");
}
