//
// Created by Mobile Capital on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#include "CubeRenderer.h"
#include <OpenGL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

OpenGL::Renderers::CubeRenderer::CubeRenderer()
{
}

void OpenGL::Renderers::CubeRenderer::Render()
{
    const GLchar *vertSource =
            "attribute vec4 position;"\
            "attribute vec4 inColor;"\
            "varying vec4 outColor;"\
            "uniform mat4 projection;"\
            "uniform mat4 view;"\
            "uniform mat4 model;"\
            "void main()"\
            "{"\
                "outColor = inColor;"\
                "gl_Position = projection * view * model * position;"\
            "}";

    const GLchar *fragSource =
            "varying lowp vec4 outColor;"\
            "void main()"\
            "{"\
                "gl_FragColor = outColor;"\
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

    const GLfloat vertices[] = {
            -2.0f, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
            2.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,

            0.0, -2.0f, 0.0, 0.0, 1.0, 0.0, 1.0,
            0.0, 2.0, 0.0, 0.0, 1.0, 0.0, 1.0,

            0.0, 0.0, -2.0f, 0.0, 0.0, 1.0, 1.0,
            0.0, 0.0, 2.0, 0.0, 0.0, 1.0, 1.0,

            -0.5f, 0.5, 0.5, 1.0, 1.0, 0.0, 1.0,
            0.5, 0.5, 0.5, 1.0, 1.0, 0.0, 1.0,
            0.5, -0.5f, 0.5, 1.0, 1.0, 0.0, 1.0,
            -0.5f, -0.5f, 0.5, 1.0, 1.0, 0.0, 1.0,

            -0.5f, 0.5, -0.5f, 1.0, 0.0, 1.0, 1.0,
            0.5, 0.5, -0.5f, 1.0, 0.0, 1.0, 1.0,
            0.5, -0.5f, -0.5f, 1.0, 0.0, 1.0, 1.0,
            -0.5f, -0.5f, -0.5f, 1.0, 0.0, 1.0, 1.0,
    };

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLubyte indices[] = {
            0, 1, 2, 3, 4, 5,

            6, 7, 7, 8, 8, 9, 9, 6,
            10, 11, 11, 12, 12, 13, 13, 10,
            6, 10, 9, 13,
            7, 11, 8, 12
    };

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint position = (GLuint) glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(position);
    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, 0);

    GLuint inColor = (GLuint) glGetAttribLocation(program, "inColor");
    glEnableVertexAttribArray(inColor);
    glVertexAttribPointer(inColor, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, (GLvoid *) (sizeof(GLfloat) * 3));

    GLuint projection = (GLuint) glGetUniformLocation(program, "projection");
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 16.f / 9.f, 0.1f, 100.f);
    glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    GLuint view = (GLuint) glGetUniformLocation(program, "view");
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(2.f, 3.f, 4.f), glm::vec3(.0f, .0f, .0f), glm::vec3(.0f, 1.f, .0f));
    glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    GLuint model = (GLuint) glGetUniformLocation(program, "model");
    glm::mat4 modelMatrix(1.f);
    glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawElements(GL_LINES, sizeof(indices) / sizeof(GLubyte), GL_UNSIGNED_BYTE, 0);

    glDisableVertexAttribArray(position);
    glDisableVertexAttribArray(inColor);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteProgram(program);
}
