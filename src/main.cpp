#include <chrono>
#include <stdio.h>
#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "mesh.hpp"
#include "object.hpp"
#include "shaders.hpp"
#include "shapes.hpp"


#define MOVEMENT_SPEED 0.01f

void glfw_error_callback(int, const char*);
void glfw_win_resize_callback(GLFWwindow* win, int width, int height);
void glfw_key_callback(GLFWwindow* win, int key, int scancode, int action, int mode);
void glfw_scroll_callback(GLFWwindow* win, double x_offset, double y_offset);

void Input();

GLFWwindow* win;
glm::vec2 speed;
float* zoom;

int main()
{
    if (!glfwInit())
        return -1;


    win = glfwCreateWindow(600, 600, "Erwin window", NULL, NULL);
    
    if (!win)
        return -1;

    glfwSetErrorCallback(glfw_error_callback);
    glfwSetWindowSizeCallback(win, glfw_win_resize_callback);
    glfwSetKeyCallback(win, glfw_key_callback);
    glfwSetScrollCallback(win, glfw_scroll_callback);

    glfwMakeContextCurrent(win); 
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // link with glad

    //glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CW);

    std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();

    ShaderProgram shaders("res/shaders/main.vert", "res/shaders/1stgen_mandelbrot.frag");
    Mesh square(glm::vec3(1.0f), Square::data());
    Object sq(square, shaders, glm::vec3(0.), glm::vec3(2.));

    glm::vec2 position = glm::vec2(0.0f);
    glm::vec<2, double> mousePos;
    glm::vec<2, int32_t> winSize;

    zoom = new float();
    
    while (!glfwWindowShouldClose(win))
    {
        speed = glm::vec2(0.0f);

        glClearColor(0.05f, 0.02f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        sq.render();

        using ms = std::chrono::duration<float, std::milli>;
        auto deltaTime = std::chrono::duration_cast<ms>(std::chrono::system_clock::now() - startTime).count() / 1000.0f;

        glfwGetWindowSize(win, &winSize.x, &winSize.y);

        shaders.upload("u_time", deltaTime);
        shaders.upload("u_resolution", winSize);
        shaders.upload("u_position", position);
        shaders.upload("u_zoom", *zoom);
        shaders.upload("u_mousePos", (glm::vec2)mousePos);

        Input();

        glfwGetCursorPos(win, &mousePos.x, &mousePos.y);

        position += speed;

        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    glfwTerminate();

    delete zoom;

    return 0;
}

void glfw_error_callback(int code, const char* info)
{
    fprintf(stderr, "ERROR::GLFW: %s", info);
}

void glfw_win_resize_callback(GLFWwindow* win, int width, int height)
{
    glViewport(0, 0, width, height);
}

void glfw_key_callback(GLFWwindow* win, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(win, true);
    }
}

void glfw_scroll_callback(GLFWwindow* win, double x_offset, double y_offset)
{
    *zoom += y_offset;
}

// TODO: multiply x by x/y ratio

void Input()
{
    if (glfwGetKey(win, GLFW_KEY_W))
        speed.y -= MOVEMENT_SPEED * 1. / glm::pow(10, *zoom / 10.);

    if (glfwGetKey(win, GLFW_KEY_S))
        speed.y += MOVEMENT_SPEED * 1. / glm::pow(10, *zoom / 10.);    
        
    if (glfwGetKey(win, GLFW_KEY_A))
        speed.x += MOVEMENT_SPEED * 1. / glm::pow(10, *zoom / 10.);

    if (glfwGetKey(win, GLFW_KEY_D))
        speed.x -= MOVEMENT_SPEED * 1. / glm::pow(10, *zoom / 10.);
}