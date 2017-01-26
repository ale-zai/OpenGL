//
// Created by Mobile Capital on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#include "TriangleRenderer.h"
#include "ShaderBuilder.h"
#include "Vertex.h"
#include "Color.h"
#include "Defines.h"

OpenGL::Renderers::TriangleRenderer::TriangleRenderer()
{
}

void OpenGL::Renderers::TriangleRenderer::SetUp()
{
    auto vertexSource = ShaderBuilder()
        .SetIn("position", "vec4", 0)
        .SetIn("color", "vec4", 1)
        .SetOut("throughColor", "vec4")
        .BeginMain()
        .SetBody({
            "throughColor = color;"
                "gl_Position = position;"
        })
        .EndMain()
        .Build();

    auto fragmentSource = ShaderBuilder()
        .SetIn("throughColor", "vec4")
        .SetOut("outColor", "vec4")
        .BeginMain()
        .SetBody({
            "outColor = throughColor;"
        })
        .EndMain()
        .Build();

    const auto &vert = Shader(GL_VERTEX_SHADER, vertexSource);
    vert.Compile();

    const auto &frag = Shader(GL_FRAGMENT_SHADER, fragmentSource);
    frag.Compile();

    _program = new ShaderProgram(vert, frag);
    _program->Use();

    const Vertex vertices[] =
        {
            {.x = 0.f, .y = .5f, .z = 0.f},
            {.x = -.5f, .y = -.5f, .z = 0.f},
            {.x = .5f, .y = -.5f, .z = 0.f}
        };

    const Color colors[] =
        {
            {.r = 1.f, .g = 0.f, .b = 0.f, .a = 1.f},
            {.r = 0.f, .g = 1.f, .b = 0.f, .a = 1.f},
            {.r = 0.f, .g = 0.f, .b = 1.f, .a = 1.f}
        };

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE(3), 0);

    glGenBuffers(1, &_colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, STRIDE(4), 0);

    glBindVertexArray(0);

    _drawingCount = ARRAY_LENGTH(vertices, Vertex);
}

void OpenGL::Renderers::TriangleRenderer::Render()
{
    glBindVertexArray(_vao);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, _drawingCount);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindVertexArray(0);
}

void OpenGL::Renderers::TriangleRenderer::CleanUp()
{
    glDeleteBuffers(1, &_vertexBuffer);
    glDeleteBuffers(1, &_colorBuffer);
    glDeleteVertexArrays(1, &_vao);
    delete _program;
}
