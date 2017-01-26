//
// Created by Mobile Capital on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <OpenGL/gl3.h>
#include <iostream>

namespace OpenGL
{
    class Shader
    {
    private:
        GLuint _shaderId;
    public:
        Shader(GLenum type, std::string source);
        virtual ~Shader();

        void Compile() const;
        GLuint ShaderId() const;
    };
}

#endif //OPENGL_SHADER_H
