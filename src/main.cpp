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

    ShaderProgram shaders("res/shaders/main.vert", "res/shaders/this.frag");
    Mesh triangle(sizeof(Triangle::vertices), sizeof(Triangle::indices), Triangle::vertices, Triangle::indices);

    glBindVertexArray(triangle.VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, triangle.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle::vertices), Triangle::vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Triangle::indices), Triangle::indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(win))
    {
        glClearColor(0.3f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaders.id);
        glBindVertexArray(triangle.VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

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