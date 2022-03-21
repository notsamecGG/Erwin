#pragma once
#include <stdio.h>
#include <iostream>

#include <glad/glad.h>

#include "shapes.hpp"

struct Mesh 
{
    Mesh(const int& _vertices_size, const int& _indices_size, const float* _vertices, const unsigned int* _indices)
     : vertices_size(_vertices_size), indices_size(_indices_size),
     vertices(_vertices), indices(_indices)
    {
        gen_buffers();

        upload_mesh();
    }
    
    void gen_buffers()
    {
        glGenVertexArrays(1, &VAO);
        
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    }

    void upload_mesh()
    {
        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
    
    const int vertices_size;
    const float* vertices;

    const int indices_size;
    const unsigned int* indices;

    unsigned int VAO, VBO, EBO;
};