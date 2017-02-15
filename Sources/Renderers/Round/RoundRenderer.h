//
// Created by Mobile Capital on 27/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#ifndef OPENGL_ROUNDRENDERER_H
#define OPENGL_ROUNDRENDERER_H

#include <OpenGL/OpenGL.h>
#include "ShaderProgram.h"
#include "Renderer.h"
#include "Color.h"

namespace OpenGL
{
    namespace Renderers
    {
        class RoundRenderer : public Renderer
        {
        private:
            GLuint _vao;
            GLuint _vertexBuffer;
            GLuint _colorBuffer;

            GLuint _drawingCount;

            ShaderProgram *_program;
            
            Color GetRGBFromHSB(GLfloat hue, GLfloat saturation, GLfloat brightness);

        public:
            RoundRenderer();

            void SetUp();
            void Render();
            void CleanUp();
        };
    }
}

#endif //OPENGL_ROUNDRENDERER_H
