#pragma once

#include <glad/glad.h>

#include "fileman.hpp"


struct Shader
{
    Shader(const int& type, const char* _path)
     : path(_path), isCompiled(false)
    {
        source = load_text(_path);
        id = glCreateShader(type);
    }

    ~Shader()
    {
        glDeleteShader(id);
    }

    void compile()
    {
        #include <iostream>
        std::cout << source << std::endl;
        glShaderSource(id, 1, &source, NULL);
        glCompileShader(id);
        
        int success;
        char infoLog[512];

        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 512, NULL, infoLog);
            fprintf(stderr, "ERROR::OpenGL::SHADER::COMPILATION: %s", infoLog);
        }

        isCompiled = (bool)success;
    }

    const char* source;
    const char* path;

    unsigned int id;

    bool isCompiled;
};

struct ShaderProgram
{
    ShaderProgram(const char* vertexPath, const char* fragmentPath)
     : vertex{Shader(GL_VERTEX_SHADER, vertexPath)}, 
     fragment{Shader(GL_FRAGMENT_SHADER, fragmentPath)} 
    { 
        id = glCreateProgram();
        
        link();
    }

    void link()
    {
        if (!vertex.isCompiled || !fragment.isCompiled)
        {
            vertex.compile();
            fragment.compile();
        }

        glAttachShader(id, vertex.id);
        glAttachShader(id, fragment.id);
        glLinkProgram(id);

        int success;
        char infoLog[512];

        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            fprintf(stderr, "ERROR::OpenGL::SHADER_PROGRAM::LINKING: %s", infoLog);
        }
        else
        {
            glUseProgram(id);
            glDeleteShader(vertex.id);
            glDeleteShader(fragment.id);

            // delete &vertex;
            // delete &fragment;
        }
    }

    unsigned int id;

    Shader vertex;
    Shader fragment;
};