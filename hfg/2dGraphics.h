#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ostream>
#include <stb_image.h>

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <2dMath.h>

struct Shader {
    unsigned int shader;

    Shader(const char* vertexPath, const char* fragmentPath) {

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

        this->shader = shaderProgram;
    }

    void UniformVec3(const char* name, float x, float y, float z) {
        glUseProgram(shader);
        unsigned int pos = glGetUniformLocation(shader, name);
        if(pos == -1) {
            printf("ERROR: UniformVec3: %s not found\n", name);
            return;
        }
        glUniform3f(pos, x, y, z);
    }
    void UniformVec3v(const char* name, const GLfloat *val) {
        glUseProgram(shader);
        unsigned int pos = glGetUniformLocation(shader, name);
        if(pos == -1) {
            printf("ERROR: UniformVec3v: %s not found\n", name);
            return;
        }
        glUniform3fv(pos, 1, val);
    }
    void UniformMat3v(const char* name, const GLfloat *val) {
        glUseProgram(shader);
        unsigned int pos = glGetUniformLocation(shader, name);
        if(pos == -1) {
            printf("ERROR: UniformMat3v: %s not found\n", name);
            return;
        }
        glUniformMatrix3fv(pos, 1, GL_TRUE, val);
    }
};

struct Transform {
    Vec2 pos;
    Vec2 scale;
    float rot;

    friend std::ostream& operator<<(std::ostream& os, const Transform& t) {
        os << "pos: " << t.pos << " scale: " << t.scale << " rot: " << t.rot;
        return os;
    }

};


class Rectangle {
public:
    unsigned int VAO;
    Shader shader;
    Transform *transform;

    Rectangle(Shader shader) : shader(shader) {
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


        this->VAO = VAO;
        //this->transform->scale.Set(1.0f, 1.0f);
        //this->transform->rot = 0.0f;
    }

    void Draw(Mat3 *viewMat) {
        Mat3 transform;

        transform.ScaleMat(this->transform->scale);
        transform.RotateMat(this->transform->rot);
        transform.TranslateMat(this->transform->pos);

        glUseProgram(this->shader.shader);
        this->shader.UniformMat3v("transform", transform.mat);
        this->shader.UniformMat3v("view", viewMat->mat);

        glBindVertexArray(this->VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    
    void setShader(Shader shader) {
        this->shader = shader;
    }
};

class Image {
    Rectangle rect;
    float opacity;
    unsigned int texture;

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

    Image(const char *path, GLint colorSpace, GLint internalColorSpace) : rect(Shader("hfg/assets/image.vert", "hfg/assets/image.frag")) {

        int texWidth, texHeight;
        this->texture = LoadTextureWithSize(path, colorSpace, internalColorSpace, &texWidth, &texHeight);
        this->opacity = 1.0f;

        glUniform1i(glGetUniformLocation(this->rect.shader.shader, "image"), 0);

        if(texWidth > texHeight) {
            this->rect.transform->scale.y = (float)texHeight / texWidth;
        }
        else {
            this->rect.transform->scale.x = (float)texWidth / texHeight;
        }
    }

    void drawImage(Image *image, Mat3 *viewMat) {
        glUseProgram(image->rect.shader.shader);
        glUniform1f(glGetUniformLocation(image->rect.shader.shader, "opacity"), image->opacity);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, image->texture);
        this->rect.Draw(viewMat);
    }
};


struct Debug {
    static void APIENTRY openglMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
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
};
