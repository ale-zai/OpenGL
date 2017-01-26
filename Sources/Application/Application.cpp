//
// Created by Mobile Capital on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#include "Application.h"

OpenGL::Application::Application(std::string title, GLuint windowWidth, GLuint windowHeight) :
        _title(title),
        _windowWidth(windowWidth),
        _windowHeight(windowHeight)
{
}

void OpenGL::Application::SetRenderer(Renderers::Renderer *renderer)
{
    _renderer = renderer;
}

void OpenGL::Application::Run() const
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    auto window = glfwCreateWindow(_windowWidth, _windowHeight, _title.c_str(), nullptr, nullptr);

    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initalize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, screenWidth, screenHeight);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        _renderer->Render();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}
