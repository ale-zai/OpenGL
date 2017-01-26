//
// Created by Mobile Capital on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#ifndef OPENGL_TRIANGLERENDERER_H
#define OPENGL_TRIANGLERENDERER_H

#include "Renderer.h"

namespace OpenGL
{
    namespace Renderers
    {
        class TriangleRenderer : public Renderer
        {
        public:
            TriangleRenderer();
            void Render();
        };
    }
}

#endif //OPENGL_TRIANGLERENDERER_H
