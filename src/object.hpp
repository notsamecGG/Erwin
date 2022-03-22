#pragma once


#include <glm/glm.hpp>

#include "mesh.hpp"
#include "shaders.hpp"

struct Object
{
    Mesh mesh;

    unsigned int indices;
    float vertices;

    glm::vec3 position;
};