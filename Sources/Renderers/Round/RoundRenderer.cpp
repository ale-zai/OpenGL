//
// Created by Mobile Capital on 27/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#include "RoundRenderer.h"
#include "ShaderBuilder.h"
#include "Vertex.h"
#include "Color.h"
#include "Defines.h"
#include <glm/glm.hpp>

OpenGL::Renderers::RoundRenderer::RoundRenderer()
{
}

void OpenGL::Renderers::RoundRenderer::SetUp()
{
    auto vertSource = OpenGL::ShaderBuilder()
        .SetIn("position", "vec4", 0)
        .SetIn("color", "vec4", 1)
        .SetOut("throughColor", "vec4")
        .BeginMain()
        .SetBody({
            "throughColor = color;",
            "gl_Position = position;"
        })
        .EndMain()
        .Build();

    auto fragSource = OpenGL::ShaderBuilder()
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

    _program = new ShaderProgram(vert, frag);
    _program->Use();

    const GLint segmentsCount = 360;
    const Vertex center = { .x = 0.f, .y = 0.f, .z = 0.f };
    const GLfloat radius = .5f;

    Vertex vertices[segmentsCount + 2];
    Color colors[segmentsCount + 2];

    vertices[0] = center;
    colors[0] = { .r = 1.f, .g = 1.f, .b = 0.f, .a = 1.f };
    GLfloat delta = glm::radians(360.f / segmentsCount);

    for (int i = 1; i < segmentsCount + 2; i++)
    {
        vertices[i] = {
            .x = center.x + radius * glm::cos(i * delta),
            .y = center.y + radius * glm::sin(i * delta),
            .z = center.z
        };
        colors[i] = { .r = 1.f, .g = 1.f, .b = 0.f, .a = 1.f };
    }

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

void OpenGL::Renderers::RoundRenderer::Render()
{
    glBindVertexArray(_vao);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLE_FAN, 0, _drawingCount);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindVertexArray(0);
}

void OpenGL::Renderers::RoundRenderer::CleanUp()
{
    glDeleteBuffers(1, &_vertexBuffer);
    glDeleteBuffers(1, &_colorBuffer);
    glDeleteVertexArrays(1, &_vao);

    delete _program;
}
