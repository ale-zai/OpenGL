//
// Created by Mobile Capital on 26/01/2017.
// Copyright (c) 2017 Mobile Capital. All rights reserved.
//

#include "ShaderBuilder.h"

OpenGL::ShaderBuilder::ShaderBuilder()
{
    _contentsStream << "#version 330 core" << std::endl;
}

OpenGL::ShaderBuilder &OpenGL::ShaderBuilder::SetIn(std::string name, std::string type, int location)
{
    _contentsStream << "layout (location = " << location << ") in " << type << " " << name << ";" << std::endl;
    return *this;
}

OpenGL::ShaderBuilder &OpenGL::ShaderBuilder::SetIn(std::string name, std::string type)
{
    _contentsStream << "in " << type << " " << name << ";" << std::endl;
    return *this;
}

OpenGL::ShaderBuilder &OpenGL::ShaderBuilder::SetOut(std::string name, std::string type)
{
    _contentsStream << "out " << type << " " << name << ";" << std::endl;
    return *this;
}

OpenGL::ShaderBuilder &OpenGL::ShaderBuilder::SetUniform(std::string name, std::string type)
{
    _contentsStream << "uniform " << type << " " << name << ";" << std::endl;
    return *this;
}

OpenGL::ShaderBuilder &OpenGL::ShaderBuilder::BeginMain()
{
    _contentsStream << "void main()" << std::endl << "{" << std::endl;
    return *this;
}

OpenGL::ShaderBuilder &OpenGL::ShaderBuilder::SetBody(std::list<std::string> body)
{
    for (auto item : body)
    {
        _contentsStream << "    " << item << std::endl;
    }
    return *this;
}

OpenGL::ShaderBuilder &OpenGL::ShaderBuilder::EndMain()
{
    _contentsStream << "}" << std::endl;
    return *this;
}

std::string OpenGL::ShaderBuilder::Build()
{
    return _contentsStream.str();
}
