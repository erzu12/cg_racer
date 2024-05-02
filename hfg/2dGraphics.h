#pragma once
#include <glad/glad.h>
#include <stb_image.h>

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <2dMath.h>

typedef struct Transform {
    Vec2 pos;
    Vec2 scale;
    float rot;
} Transform;

typedef struct Rectangle {
    unsigned int VAO;
    unsigned int shader;
    Transform transform;
} Rectangle;

typedef struct Image {
    Rectangle rect;
    float opacity;
    unsigned int texture;
} Image;

typedef struct Particle {
    Vec2 vel;
    float lifeTime;
    float start;
    Image image;
} Particle;

typedef struct ParticleSys {
    Particle *particles;
    Vec2 pos;
    Vec2 initalVel;
    float initialSize;
    float randAngle;
    float randSpeed;
    int maxParticles;
    int particleCount;
    float maxLifetime;
    float initialOpacity;
    float growth;
    float fade;
    Image *image;
} ParticleSys;

typedef struct Line {
    unsigned int VAO;
    unsigned int indCount;
    unsigned int shader;
    Transform transform;
} Line;

Rectangle *newRectangle(unsigned int shader);

void drawRectangle(struct Rectangle* rectangle, float *viewMat);

unsigned int LoadTextureWithSize(const char *path, GLint colorSpace, GLint internalColorSpace, int *texWidth, int *texHeight);

unsigned int LoadTexture(const char *path, GLint colorSpace, GLint internalColorSpace);

Image *newImage(const char *path, GLint colorSpace, GLint internalColorSpace);

void drawImage(Image *image, float *viewMat);

void freeImage(Image *image);

ParticleSys *newParticleSys(int maxParticles, Image *image, Vec2 pos, float initialSize, Vec2 initalVel);

void spawnParticle(ParticleSys* particleSys, float lifeTime);

void drawParticleSys(ParticleSys *particleSys, float *viewMat, float deltaTime);

void deleteParticleSys(ParticleSys *particleSys);

Line *newLine(Vec2 *points, int pointCount, float thickness, bool closed, Line *line);

void drawLine(Line *line, float *viewMat);

unsigned int LoadAndCompileShaders(const char* vertexPath, const char* fragmentPath);

void UniformVec3(unsigned int shader, const char* name, float x, float y, float z);
void UniformVec3v(unsigned int shader, const char* name, const GLfloat *val);
void UniformMat3v(unsigned int shader, const char* name, const GLfloat *val);

void openglMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

