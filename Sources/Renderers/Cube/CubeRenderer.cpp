//
// Created by Mobile Capital on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#include "CubeRenderer.h"
#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

OpenGL::Renderers::CubeRenderer::CubeRenderer()
{
}

void OpenGL::Renderers::CubeRenderer::Render()
{
    const GLchar *vertSource =
            "#verion 330 core\n"\
            "layout (location = 0) in vec3 position;"\
            "layout (location = 1) in vec4 inColor;"\
            "out vec4 throughColor;"\
            "uniform mat4 mvp;"\
            "void main()"\
            "{"\
                "throughColor = inColor;"\
                "gl_Position = mvp * vec4(position.x, position.y, position.z, 1.0);"\
            "}";

    const GLchar *fragSource =
            "#version 330 core\n"\
            "in vec4 throughColor;"\
            "out vec4 outColor;"\
            "void main()"\
            "{"\
                "outColor = throughColor;"\
            "}";

    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertSource, NULL);
    glCompileShader(vert);
    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragSource, NULL);
    glCompileShader(frag);

    GLuint program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);
    glUseProgram(program);

    glDeleteShader(vert);
    glDeleteShader(frag);

    const GLfloat axesVertices[] = {
            -2.f, 0.f, 0.f,
            2.f, 0.f, 0.f,

            0.f, -2.f, 0.f,
            0.f, 2.f, 0.f,

            0.f, 0.f, -2.f,
            0.f, 0.f, 2.f
    };

    const GLfloat axesColors[] = {
            1.f, 0.f, 0.f, 1.f,
            1.f, 0.f, 0.f, 1.f,

            0.f, 1.f, 0.f, 1.f,
            0.f, 1.f, 0.f, 1.f,

            0.f, 0.f, 1.f, 1.f,
            0.f, 0.f, 1.f, 1.f,
    };

    const GLubyte axesIndices[] = {
            0, 1, 2, 3, 4, 5
    };

    const GLfloat cubeVertices[] = {
            -.5f, .5f, .5f,
            .5f, .5f, .5f,
            .5f, -.5f, .5f,
            -.5f, -.5f, .5f,

            -.5f, .5f, -.5f,
            .5f, .5f, -.5f,
            .5f, -.5f, -.5f,
            -.5f, -.5f, -.5f
    };

    const GLfloat cubeColors[] = {
            1.f, 1.f, 0.f, 1.f,
            1.f, 1.f, 0.f, 1.f,
            1.f, 1.f, 0.f, 1.f,
            1.f, 1.f, 0.f, 1.f,

            0.f, 1.f, 1.f, 1.f,
            0.f, 1.f, 1.f, 1.f,
            0.f, 1.f, 1.f, 1.f,
            0.f, 1.f, 1.f, 1.f
    };

    const GLubyte cubeIndices[] = {
            6, 7, 7, 8, 8, 9, 9, 6,
            10, 11, 11, 12, 12, 13, 13, 10,
            6, 10, 9, 13,
            7, 11, 8, 12
    };

    GLuint axesVAO;
    glGenVertexArrays(1, &axesVAO);
    GLuint axesVertexBuffer;
    glGenBuffers(1, &axesVertexBuffer);
    GLuint axesColorBuffer;
    glGenBuffers(1, &axesColorBuffer);
    GLuint axesIndexBuffer;
    glGenBuffers(1, &axesIndexBuffer);

    GLuint cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    GLuint cubeVertexBuffer;
    glGenBuffers(1, &cubeVertexBuffer);
    GLuint cubeColorBuffer;
    glGenBuffers(1, &cubeColorBuffer);
    GLuint cubeIndexBuffer;
    glGenBuffers(1, &cubeIndexBuffer);

    glBindVertexArray(axesVAO);
    glBindBuffer(GL_ARRAY_BUFFER, axesVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axesVertices), axesVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, axesColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axesColors), axesColors, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, axesIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(axesIndices), axesIndices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, cubeColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    glm::mat4 modelMatrix(1.f);
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(2.f, 3.f, 4.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 800.f / 600.f, .1f, 100.f);
    glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * projectionMatrix;

    {
        glBindVertexArray(axesVAO);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, 0);

        GLint mvp = glGetUniformLocation(program, "mvp");
        glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

        glDrawArrays(GL_LINES, 0, sizeof(axesIndices) / sizeof(GLubyte));

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }

    {
        glBindVertexArray(cubeVAO);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, 0);

        GLint mvp = glGetUniformLocation(program, "mvp");
        glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

        glDrawArrays(GL_LINES, 0, sizeof(cubeIndices) / sizeof(GLubyte));

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }

    glDisableVertexAttribArray(axesVAO);
    glDeleteBuffers(1, &axesVertexBuffer);
    glDeleteBuffers(1, &axesColorBuffer);
    glDeleteBuffers(1, &axesIndexBuffer);

    glDisableVertexAttribArray(cubeVAO);
    glDeleteBuffers(1, &cubeVertexBuffer);
    glDeleteBuffers(1, &cubeColorBuffer);
    glDeleteBuffers(1, &cubeIndexBuffer);

    glDeleteProgram(program);
}
