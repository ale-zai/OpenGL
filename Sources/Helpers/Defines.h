//
// Created by Aleksei Zaikin on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#ifndef OPENGL_DEFINES_H
#define OPENGL_DEFINES_H

#define STRIDE(x) (sizeof(GLfloat) * x)
#define GL_DRAW_COUNT(x) (sizeof(x) / sizeof(GLubyte))
#define ARRAY_LENGTH(x, type) (sizeof(x) / sizeof(type))

#endif //OPENGL_DEFINES_H
