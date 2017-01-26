//
// Created by Mobile Capital on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#include "CubeRenderer.h"
#include "ShaderBuilder.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Vertex.h"
#include "Color.h"
#include "Defines.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

OpenGL::Renderers::CubeRenderer::CubeRenderer()
{
}

void OpenGL::Renderers::CubeRenderer::Render()
{

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

    auto program = OpenGL::ShaderProgram(vert, frag);
    program.Use();

    glDeleteShader(vert.ShaderId());
    glDeleteShader(frag.ShaderId());

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

    GLuint axesVAO;
    glGenVertexArrays(1, &axesVAO);
    glBindVertexArray(axesVAO);

    GLuint axesVertexBuffer;
    glGenBuffers(1, &axesVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, axesVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axesVertices), axesVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE(3), 0);

    GLuint axesColorBuffer;
    glGenBuffers(1, &axesColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, axesColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axesColors), axesColors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, STRIDE(4), 0);

    GLuint axesIndexBuffer;
    glGenBuffers(1, &axesIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, axesIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(axesIndices), axesIndices, GL_STATIC_DRAW);

    GLuint cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);

    GLuint cubeVertexBuffer;
    glGenBuffers(1, &cubeVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE(3), 0);

    GLuint cubeColorBuffer;
    glGenBuffers(1, &cubeColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, cubeColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, STRIDE(4), 0);

    GLuint cubeIndexBuffer;
    glGenBuffers(1, &cubeIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    glm::mat4 modelMatrix(1.f);
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(2.f, 3.f, 4.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.f), 800.f / 600.f, .1f, 100.f);
    glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

    GLint mvpLocation = glGetUniformLocation(program.ProgramId(), "mvpMatrix");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    glBindVertexArray(axesVAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawElements(GL_LINES, GL_DRAW_COUNT(axesIndices), GL_UNSIGNED_BYTE, 0);

    glBindVertexArray(cubeVAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawElements(GL_LINES, GL_DRAW_COUNT(cubeIndices), GL_UNSIGNED_BYTE, 0);

    
    glDisableVertexAttribArray(axesVAO);
    glDeleteBuffers(1, &axesVertexBuffer);
    glDeleteBuffers(1, &axesColorBuffer);
    glDeleteBuffers(1, &axesIndexBuffer);

    glDisableVertexAttribArray(cubeVAO);
    glDeleteBuffers(1, &cubeVertexBuffer);
    glDeleteBuffers(1, &cubeColorBuffer);
    glDeleteBuffers(1, &cubeIndexBuffer);

    glDeleteProgram(program.ProgramId());
}
