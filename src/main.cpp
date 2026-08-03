#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <2dGraphics.h>
#include <2dMath.h>

#include <iostream>
#include <unistd.h>

#include "elements.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;


class Application {
public:
    int run()
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
        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GUI", NULL, NULL);
        ScreenSizeManager::notifyListeners(SCR_WIDTH, SCR_HEIGHT);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
        glDebugMessageCallback(Debug::openglMessageCallback, 0);


        Shader shader("assets/shader.vert", "assets/shader.frag");
        shader.UniformVec3("col", 1.0f, 0.0f, 0.0f);


        Mat3 viewMatrix;
        viewMatrix.Print();


        ContainerTransform *root = ContainerTransform::CreateRoot();
        PixelSize pos(Vec2(0, 0));
        PixelSize size(Vec2(100, 100));
        ContainerTransform rect_transform(root, pos, size, TOP_LEFT, TOP_LEFT);

        RectangleElement rect(rect_transform, shader);


        while (!glfwWindowShouldClose(window)) {
            processInput(window);
            glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // black background
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(shader.shader);
            rect.Draw();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }


        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
        return 0;
    }
private:

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    static void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // ---------------------------------------------------------------------------------------------
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
        ScreenSizeManager::notifyListeners(width, height);
    }
};

int main()
{
    Application app;
    return app.run();
}
