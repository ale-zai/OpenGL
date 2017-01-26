//
// Created by Mobile Capital on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

namespace OpenGL
{
    namespace Renderers
    {
        class Renderer
        {
        public:
            Renderer();
            virtual ~Renderer();
            virtual void Render() = 0;
        };
    }
}

#endif //OPENGL_RENDERER_H
