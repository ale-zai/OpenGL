//
// Created by Mobile Capital on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#ifndef OPENGL_APPLICATION_H
#define OPENGL_APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../Renderers/Base/Renderer.h"

namespace OpenGL
{
    class Application
    {
    private:
        std::string _title;
        GLuint _windowWidth;
        GLuint _windowHeight;

        Renderers::Renderer *_renderer;

    public:
        Application(std::string title, GLuint windowWidth, GLuint windowHeight);
        void SetRenderer(Renderers::Renderer *renderer);
        void Run() const;
    };
}

#endif //OPENGL_APPLICATION_H
