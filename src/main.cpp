#include <chrono>
#include <stdio.h>
#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "shapes.hpp"
#include "mesh.hpp"
#include "shaders.hpp"


void glfw_error_callback(int, const char*);


GLFWwindow* win;

int main()
{
    if (!glfwInit())
        return -1;

    glfwSetErrorCallback(glfw_error_callback);

    win = glfwCreateWindow(600, 600, "Erwin window", NULL, NULL);
    
    if (!win)
        return -1;

    glfwMakeContextCurrent(win); 
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // link with glad

    //glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CW);

    std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();

    ShaderProgram shaders("res/shaders/main.vert", "res/shaders/main.frag");
    Mesh square(glm::vec3(1.0f), Square::data());
    
    while (!glfwWindowShouldClose(win))
    {
        glClearColor(0.05f, 0.02f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaders.id);
        glBindVertexArray(square.VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        using ms = std::chrono::duration<float, std::milli>;
        auto deltaTime = std::chrono::duration_cast<ms>(std::chrono::system_clock::now() - startTime).count() / 1000.0f;

        shaders.upload("u_time", deltaTime);
        shaders.upload("u_resolution", glm::vec2(600));

        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void glfw_error_callback(int code, const char* info)
{
    fprintf(stderr, "ERROR::GLFW: %s", info);
}