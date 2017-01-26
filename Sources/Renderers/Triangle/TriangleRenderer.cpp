//
// Created by Mobile Capital on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#include "TriangleRenderer.h"
#include <OPenGL/gl3.h>
#include "ShaderBuilder.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Vertex.h"
#include "Color.h"
#include "Defines.h"

OpenGL::Renderers::TriangleRenderer::TriangleRenderer()
{
}

void OpenGL::Renderers::TriangleRenderer::Render()
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

    auto program = ShaderProgram(vert, frag);
    program.Use();

    glDeleteShader(vert.ShaderId());
    glDeleteShader(frag.ShaderId());

    Vertex vertices[] = {
        { .x = 0.f, .y = .5f, .z = 0.f },
        { .x = -.5f, .y = -.5f, .z = 0.f },
        { .x = .5f, .y = -.5f, .z = 0.f }
    };

    Color colors[] = {
        { .r = 1.f, .g = 0.f, .b = 0.f, .a = 1.f },
        { .r = 0.f, .g = 1.f, .b = 0.f, .a = 1.f },
        { .r = 0.f, .g = 0.f, .b = 1.f, .a = 1.f }
    };
    
    GLubyte indices[] = {
        0, 1, 2
    };

    GLuint triangleVAO;
    glGenVertexArrays(1, &triangleVAO);
    glBindVertexArray(triangleVAO);

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE(3), 0);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, STRIDE(4), 0);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, GL_DRAW_COUNT(indices), GL_UNSIGNED_BYTE, 0);

    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &colorBuffer);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteVertexArrays(1, &triangleVAO);
    glDeleteProgram(program.ProgramId());
}
