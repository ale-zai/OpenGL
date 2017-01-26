//
// Created by Mobile Capital on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#include "ShaderProgram.h"

OpenGL::ShaderProgram::ShaderProgram(const OpenGL::Shader &vertex, const OpenGL::Shader &fragment)
{
    _programId = glCreateProgram();
    glAttachShader(_programId, vertex.ShaderId());
    glAttachShader(_programId, fragment.ShaderId());

    glLinkProgram(_programId);

    GLint success;
    GLchar infolog[512];
    glGetProgramiv(_programId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(_programId, 512, nullptr, infolog);
        std::cerr << "PROGRAM LINK ERROR: " << std::endl << infolog << std::endl;
        exit(EXIT_FAILURE);
    }
}

OpenGL::ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(_programId);
}

void OpenGL::ShaderProgram::Use() const
{
    glUseProgram(_programId);
}

GLuint OpenGL::ShaderProgram::ProgramId() const
{
    return _programId;
}
