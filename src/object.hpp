#pragma once


#include <glm/glm.hpp>

#include "mesh.hpp"
#include "shaders.hpp"

struct Object
{
    Object(Mesh& _mesh, ShaderProgram _material) : mesh(_mesh), material(_material) { }
    Object(Mesh& _mesh, ShaderProgram _material, const glm::vec3& _position, const glm::vec3& _scale) 
     : mesh(_mesh), material(_material), position(_position), scale(_scale) { }

    void render() { }

public:
    Mesh mesh;

    unsigned int indices;
    float vertices;

    glm::vec3 position;
    glm::vec3 scale;
    // glm::vec3 up;
    // glm::vec3 front;

    ShaderProgram material;
};