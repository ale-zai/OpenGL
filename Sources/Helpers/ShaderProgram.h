//
// Created by Mobile Capital on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#ifndef OPENGL_SHADERPROGRAM_H
#define OPENGL_SHADERPROGRAM_H

#include <OpenGL/gl3.h>
#include "Shader.h"

namespace OpenGL
{
    class ShaderProgram
    {
    private:
        GLuint _programId;
    public:

        ShaderProgram(const Shader &vertex, const Shader &fragment);
        virtual ~ShaderProgram();

        void Use() const;
        GLuint ProgramId() const;
    };
}

#endif //OPENGL_SHADERPROGRAM_H
