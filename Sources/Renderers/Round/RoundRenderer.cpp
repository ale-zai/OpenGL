//
// Created by Mobile Capital on 27/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#include "RoundRenderer.h"
#include "ShaderBuilder.h"
#include "Vertex.h"
#include "Defines.h"
#include <glm/glm.hpp>

OpenGL::Renderers::RoundRenderer::RoundRenderer()
{
}

void OpenGL::Renderers::RoundRenderer::SetUp()
{
    const GLchar* vertSource = GLSL(
                                    layout (location = 0) in vec4 position;
                                    layout (location = 1) in vec4 color;
                                    out vec4 throughColor;
                                    void main() {
                                        throughColor = color;
                                        gl_Position = position;
                                    }
                               );
    
    const GLchar* fragSource = GLSL(
                                    in vec4 throughColor;
                                    out vec4 outColor;
                                    void main() {
                                        outColor = throughColor;
                                    }
                               );

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
    colors[0] = { .r = 1.f, .g = 1.f, .b = 1.f, .a = 1.f };
    GLfloat delta = glm::radians(360.f / segmentsCount);
    GLfloat hue = 0;

    for (int i = 1; i < segmentsCount + 2; i++)
    {
        vertices[i] = {
            .x = center.x + radius * glm::cos(i * delta),
            .y = center.y + radius * glm::sin(i * delta),
            .z = center.z
        };
        colors[i] = GetRGBFromHSB(hue, 100.0, 100.0);
        hue += 360.f / segmentsCount;
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

Color OpenGL::Renderers::RoundRenderer::GetRGBFromHSB(GLfloat hue, GLfloat saturation, GLfloat brightness)
{
    const GLint Hi = ((GLint) hue / 60) % 6;
    const GLfloat Bmin = ((100.f - saturation) * brightness) / 100.f;
    const GLfloat a = (brightness - Bmin) * (((GLint)hue % 60) / 60.f);
    const GLfloat Binc = Bmin + a;
    const GLfloat Bdec = brightness - a;
    
    if (Hi == 0) {
        return { .r = brightness / 100.f, .g = Binc / 100.f, .b = Bmin / 100.f, .a = 1.0 };
    } else if (Hi == 1) {
        return { .r = Bdec / 100.f, .g = brightness / 100.f, .b = Bmin / 100.f, .a = 1.0 };
    } else if (Hi == 2) {
        return { .r = Bmin / 100.f, .g = brightness / 100.f, .b = Binc / 100.f, .a = 1.0 };
    } else if (Hi == 3) {
        return { .r = Bmin / 100.f, .g = Bdec / 100.f, .b = brightness / 100.f, .a = 1.0 };
    } else if (Hi == 4) {
        return { .r = Binc / 100.f, .g = Bmin / 100.f, .b = brightness / 100.f, .a = 1.0 };
    } else if (Hi == 5) {
        return { .r = brightness / 100.f, .g = Bmin / 100.f, .b = Bdec / 100.f, .a = 1.0 };
    } else {
        return { .r = 0.0, .g = 0.0, .b = 0.0, .a = 1.0 };
    }
}
