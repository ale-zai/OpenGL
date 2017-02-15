//
// Created by Mobile Capital on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#ifndef OPENGL_CUBERENDERER_H
#define OPENGL_CUBERENDERER_H

#include <OpenGL/gl3.h>
#include "Renderer.h"
#include "ShaderProgram.h"

namespace OpenGL
{
    namespace Renderers
    {
        class CubeRenderer : public Renderer
        {
        private:
            ShaderProgram *_program;

            GLuint _axesVAO;
            GLuint _axesVertexBuffer;
            GLuint _axesColorBuffer;
            GLuint _axesIndexBuffer;
            GLuint _axesDrawingCount;

            GLuint _cubeVAO;
            GLuint _cubeVertexBuffer;
            GLuint _cubeColorBuffer;
            GLuint _cubeIndexBuffer;
            GLuint _cubeDrawingCount;

            GLfloat _rotationAngle;

        public:
            CubeRenderer();

            void SetUp() override;
            void Render() override;
            void CleanUp() override;
        };
    }
}

#endif //OPENGL_CUBERENDERER_H
