//
// Created by Mobile Capital on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#ifndef OPENGL_CUBERENDERER_H
#define OPENGL_CUBERENDERER_H

#include "../Base/Renderer.h"

namespace OpenGL
{
    namespace Renderers
    {
        class CubeRenderer : public Renderer
        {
        public:
            CubeRenderer();
            void Render();
        };
    }
}

#endif //OPENGL_CUBERENDERER_H
