//
// Created by Mobile Capital on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#ifndef OPENGL_TRIANGLERENDERER_H
#define OPENGL_TRIANGLERENDERER_H

#include <OpenGL/gl3.h>
#include "Renderer.h"
#include "ShaderProgram.h"

namespace OpenGL
{
    namespace Renderers
    {
        class TriangleRenderer : public Renderer
        {
        private:
            ShaderProgram *_program;

            GLuint _vao;
            GLuint _vertexBuffer;
            GLuint _colorBuffer;
            GLuint _drawingCount;

        public:
            TriangleRenderer();

            void SetUp();
            void Render();
            void CleanUp();
        };
    }
}

#endif //OPENGL_TRIANGLERENDERER_H
