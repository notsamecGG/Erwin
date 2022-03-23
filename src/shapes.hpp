#pragma once
#include <glm/glm.hpp>


#define DATA_FUNC(vertices, incides) static ShapeData data() { return ShapeData(sizeof(vertices), sizeof(indices), vertices, indices); } 

struct ShapeData
{
    ShapeData(const int& _vertices_size, const int& _indices_size, const float* _vertices, const unsigned int* _indices)
     : vertices(_vertices), indices(_indices), vertices_size(_vertices_size), indices_size(_indices_size) { }

    const int vertices_size;
    const int indices_size;
    const float* vertices;
    const unsigned int* indices;
};

struct IShape 
{
    static float* vertices;
    static unsigned int* indices;
};

struct Triangle : public IShape 
{
    static constexpr float vertices[] = {
        -0.5f, -0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
         0.0f,  0.5f,  0.0f
    };
    
    static constexpr unsigned int indices[] = {
        0, 1, 2
    };

    DATA_FUNC(vertices, indices)
};

struct Square : public IShape 
{ 
    static constexpr float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f  // top left 
    };

    static constexpr unsigned int indices[] = {  // note that we start from 0!
        1, 2, 3,    // second triangle
        0, 1, 3   // first triangle
    };

    DATA_FUNC(vertices, indices)
};

struct Star  : public IShape
{ 
    static constexpr float vertices[] = {
        0.32f,  0.32f, 0.0f,  // top right
        0.32f, -0.32f, 0.0f,  // bottom right
        -0.32f, -0.32f, 0.0f,  // bottom left
        -0.32f,  0.32f, 0.0f,  // top left

        0.0f,  1.0f, 0.0f,
        1.0f,  0.0f, 0.0f, 
        0.0f, -1.0f, 0.0f,
        -1.0f,  0.0f, 0.0f
    };

    static constexpr unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3,    // second triangle

        0, 3, 4,
        1, 0, 5,
        2, 1, 6,
        3, 2, 7
    }; 

    DATA_FUNC(vertices, indices)
};

struct Cube : public IShape
{ 
    static constexpr float vertices[] = {
        -0.5f, -0.5f, -0.5f, //0  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, //1  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, //2  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, //3  0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f, //4  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, //5  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, //6  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, //7  0.0f, 1.0f,
    };

    static constexpr unsigned int indices[] = 
    {
        // Back
        0, 1, 2,
        2, 3, 0,
        
        // Front
        6, 5, 4, 
        4, 7, 6, 
        
        // Left
        0, 3, 7, 
        7, 4, 0, 
        
        // Right
        6, 2, 1, 
        1, 5, 6, 
        
        // Bot
        5, 1, 0, 
        0, 4, 5, 
        
        // Top
        3, 2, 6, 
        6, 7, 3
    };

    DATA_FUNC(vertices, indices)
};

struct Plane : public IShape
{ 
    static constexpr float _vertices[] = {
        -0.5f,  0.0f,  0.5f,
         0.5f,  0.0f,  0.5f, 
         0.5f,  0.0f, -0.5f, 
        -0.5f,  0.0f, -0.5f 
    };

    static constexpr unsigned int _indices[] = {
        0, 1, 2,
        0, 2, 3,

        2, 1, 0,
        3, 2, 0
    };

    DATA_FUNC(vertices, indices)
};
