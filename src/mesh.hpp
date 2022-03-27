#pragma once
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shapes.hpp"


struct Mesh 
{
    Mesh(const glm::vec3& _scale, ShapeData shape)
     : scale(_scale), vertices(shape.vertices_size / sizeof(float)), indices(shape.indices_size / sizeof(unsigned int)) 
    {
        gen_buffers();

        memcpy(vertices.data(), shape.vertices, shape.vertices_size);
        memcpy( indices.data(),  shape.indices,  shape.indices_size);

        //resize(scale);

        upload_mesh();
    }
    
    void gen_buffers()
    {
        glGenVertexArrays(1, &VAO);
        
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    }

    void upload_mesh() const
    {
        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    void resize(const glm::vec3& scale) 
    {
        for (int i=0; i < vertices.size() / 3; i++)
        {
            int startIndex = i * 3;

            vertices[startIndex + 0] *= scale.x;
            vertices[startIndex + 1] *= scale.y;
            vertices[startIndex + 2] *= scale.z;
        }

        upload_mesh();
    }
    
    IShape shape;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    glm::vec3 scale;

    unsigned int VAO, VBO, EBO;
};