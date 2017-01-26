//
// Created by Mobile Capital on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#include "Shader.h"

OpenGL::Shader::Shader(GLenum type, std::string source)
{
    _shaderId = glCreateShader(type);
    const GLchar *src = source.c_str();
    glShaderSource(_shaderId, 1, &src, nullptr);
}

OpenGL::Shader::~Shader()
{
    glDeleteShader(_shaderId);
}

void OpenGL::Shader::Compile() const
{
    glCompileShader(_shaderId);

    GLint success;
    GLchar infolog[512];
    glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(_shaderId, 512, nullptr, infolog);
        std::cerr << "SHADER COMPILATION ERROR: " << std::endl << infolog << std::endl;
        exit(EXIT_FAILURE);
    }
}

GLuint OpenGL::Shader::ShaderId() const
{
    return _shaderId;
}
