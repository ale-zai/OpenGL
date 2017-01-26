//
// Created by Mobile Capital on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#ifndef OPENGL_SHADERBUILDER_H
#define OPENGL_SHADERBUILDER_H

#include <iostream>
#include <list>
#include <sstream>

namespace OpenGL
{
    class ShaderBuilder
    {
    private:
        std::ostringstream _contentsStream;

    public:
        ShaderBuilder();

        ShaderBuilder &SetIn(std::string name, std::string type, int location);
        ShaderBuilder &SetIn(std::string name, std::string type);
        ShaderBuilder &SetOut(std::string name, std::string type);
        ShaderBuilder &SetUniform(std::string name, std::string type);
        ShaderBuilder &BeginMain();
        ShaderBuilder &SetBody(std::list<std::string> body);
        ShaderBuilder &EndMain();
        std::string Build();
    };
}

#endif //OPENGL_SHADERBUILDER_H
