//
// Created by Mobile Capital on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#include "CubeRenderer.h"
#include "ShaderBuilder.h"
#include "Vertex.h"
#include "Color.h"
#include "Defines.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

OpenGL::Renderers::CubeRenderer::CubeRenderer()
{
}

void OpenGL::Renderers::CubeRenderer::SetUp()
{
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    auto vertSource = OpenGL::ShaderBuilder()
        .SetIn("position", "vec4", 0)
        .SetIn("color", "vec4", 1)
        .SetUniform("mvpMatrix", "mat4")
        .SetOut("throughColor", "vec4")
        .BeginMain()
        .SetBody({
            "throughColor = color;",
            "gl_Position = mvpMatrix * position;"
        })
        .EndMain()
        .Build();

    auto fragSource = ShaderBuilder()
        .SetIn("throughColor", "vec4")
        .SetOut("outColor", "vec4")
        .BeginMain()
        .SetBody({
            "outColor = throughColor;"
        })
        .EndMain()
        .Build();


    const auto &vert = OpenGL::Shader(GL_VERTEX_SHADER, vertSource);
    vert.Compile();

    const auto &frag = OpenGL::Shader(GL_FRAGMENT_SHADER, fragSource);
    frag.Compile();

    _program = new OpenGL::ShaderProgram(vert, frag);
    _program->Use();

    const Vertex axesVertices[] = {
        { .x = -2.f, .y = 0.f, .z = 0.f },
        { .x = 2.f, .y = 0.f, .z = 0.f },

        { .x = 0.f, .y = -2.f, .z = 0.f },
        { .x = 0.f, .y = 2.f, .z = 0.f },

        { .x = 0.f, .y = 0.f, .z = -2.f },
        { .x = 0.f, .y = 0.f, .z = 2.f },
    };

    const Color axesColors[] = {
        { .r = 1.f, .g = 0.f, .b = 0.f, .a = 1.f },
        { .r = 1.f, .g = 0.f, .b = 0.f, .a = 1.f },

        { .r = 0.f, .g = 1.f, .b = 0.f, .a = 1.f },
        { .r = 0.f, .g = 1.f, .b = 0.f, .a = 1.f },

        { .r = 0.f, .g = 0.f, .b = 1.f, .a = 1.f },
        { .r = 0.f, .g = 0.f, .b = 1.f, .a = 1.f },
    };

    const GLubyte axesIndices[] = {
        0, 1, 2, 3, 4, 5
    };

    const Vertex cubeVertices[] = {
        { .x = -.5f, .y = .5f, .z = .5f },
        { .x = .5f, .y = .5f, .z = .5f },
        { .x = .5f, .y = -.5f, .z = .5f },
        { .x = -.5f, .y = -.5f, .z = .5f },

        { .x = -.5f, .y = .5f, .z = -.5f },
        { .x = .5f, .y = .5f, .z = -.5f },
        { .x = .5f, .y = -.5f, .z = -.5f },
        { .x = -.5f, .y = -.5f, .z = -.5f }
    };

    const Color cubeColors[] = {
        { .r = 1.f, .g = 1.f, .b = 0.f, .a = 1.f },
        { .r = 1.f, .g = 1.f, .b = 0.f, .a = 1.f },
        { .r = 1.f, .g = 1.f, .b = 0.f, .a = 1.f },
        { .r = 1.f, .g = 1.f, .b = 0.f, .a = 1.f },

        { .r = 1.f, .g = 0.f, .b = 1.f, .a = 1.f },
        { .r = 1.f, .g = 0.f, .b = 1.f, .a = 1.f },
        { .r = 1.f, .g = 0.f, .b = 1.f, .a = 1.f },
        { .r = 1.f, .g = 0.f, .b = 1.f, .a = 1.f }
    };

    const GLubyte cubeIndices[] = {
        0, 1, 1, 2, 2, 3, 3, 0,
        4, 5, 5, 6, 6, 7, 7, 4,
        0, 4, 3, 7,
        1, 5, 2, 6
    };

    glGenVertexArrays(1, &_axesVAO);
    glBindVertexArray(_axesVAO);

    glGenBuffers(1, &_axesVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _axesVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axesVertices), axesVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE(3), 0);

    glGenBuffers(1, &_axesColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _axesColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axesColors), axesColors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, STRIDE(4), 0);

    glGenBuffers(1, &_axesIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _axesIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(axesIndices), axesIndices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &_cubeVAO);
    glBindVertexArray(_cubeVAO);

    glGenBuffers(1, &_cubeVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _cubeVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE(3), 0);

    glGenBuffers(1, &_cubeColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _cubeColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, STRIDE(4), 0);

    glGenBuffers(1, &_cubeIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _cubeIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    _axesDrawingCount = GL_DRAW_COUNT(axesIndices);
    _cubeDrawingCount = GL_DRAW_COUNT(cubeIndices);
}

void OpenGL::Renderers::CubeRenderer::Render()
{
    glm::mat4 modelMatrix(1.f);
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(2.f, 3.f, 4.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.f), 800.f / 600.f, .1f, 100.f);
    glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

    GLint mvpLocation = glGetUniformLocation(_program->ProgramId(), "mvpMatrix");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    glBindVertexArray(_axesVAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawElements(GL_LINES, _axesDrawingCount, GL_UNSIGNED_BYTE, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindVertexArray(_cubeVAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawElements(GL_LINES, _cubeDrawingCount, GL_UNSIGNED_BYTE, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindVertexArray(0);
}

void OpenGL::Renderers::CubeRenderer::CleanUp()
{
    glDisableVertexAttribArray(_axesVAO);
    glDeleteBuffers(1, &_axesVertexBuffer);
    glDeleteBuffers(1, &_axesColorBuffer);
    glDeleteBuffers(1, &_axesIndexBuffer);

    glDisableVertexAttribArray(_cubeVAO);
    glDeleteBuffers(1, &_cubeVertexBuffer);
    glDeleteBuffers(1, &_cubeColorBuffer);
    glDeleteBuffers(1, &_cubeIndexBuffer);

    delete _program;
}
