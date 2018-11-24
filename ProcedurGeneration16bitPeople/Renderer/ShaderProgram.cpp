//
//  ShaderProgram.cpp
//  ProcedurGeneration16bitPeople
//
//  Created by Асиф Мамедов on 23/11/2018.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#include "ShaderProgram.hpp"

#include <stdexcept>

#include <string>

#include <fstream>
#include <iostream>

using std::invalid_argument;
using std::runtime_error;
using std::string;

std::string readFile (const std::string& fileName) {
    std::ifstream f (fileName);
    f.seekg (0, std::ios::end);
    size_t size = f.tellg();
    std::string s (size, ' ');
    f.seekg (0);
    f.read (&s[0], size);
    return s;
}

/**
 * Функция предназначенная для компиляции шедера.
 *
 * @param handle дескриптор шейдера
 * @param Shad тип шедера
 * @param path путь до файла с кодом шейдра
 & @throw runtime_error в случчае если не получилось скомпилировать шейдер
 */
void compileShader(GLuint& handle, GLenum Shad, const string_view& path)
{
    handle = glCreateShader(Shad);
    
    if (!handle) {
        throw runtime_error("Error create shader");
    }
    
    string shaderCodeString(readFile(path.data()));
    const char* shaderCode = shaderCodeString.c_str();
    
    glShaderSource(handle, 1, &shaderCode, nullptr);

    glCompileShader(handle);
    
    GLint check;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &check);
    
    if (!check) {
        std::cout << path << std::endl;
        throw runtime_error("Error compile shader");
    }
}

ShadereProgram::ShadereProgram(const string_view& vertPath, const string_view& fragPath) :
    _vertexShaderHandle(0),
    _fragmentShaderProgram(0),
    _handle(glCreateProgram())
{
    if (!_handle) {
        throw runtime_error("Error create shader program");
    }
    
    setVertexxShader(vertPath);
    setFragmentShader(fragPath);
    link();
}

void ShadereProgram::setVertexxShader(const string_view& path)
{
    compileShader(_vertexShaderHandle, GL_VERTEX_SHADER, path);
}

void ShadereProgram::setFragmentShader(const string_view &path)
{
    compileShader(_fragmentShaderProgram, GL_FRAGMENT_SHADER, path);
}

void ShadereProgram::link()
{
    glAttachShader(_handle, _vertexShaderHandle);
    glAttachShader(_handle, _fragmentShaderProgram);
    
    glLinkProgram(_handle);
    
    GLint check;
    glGetProgramiv(_handle, GL_LINK_STATUS, &check);
    
    if (!check) {
        throw runtime_error("Error link shader program");
    }
}

void ShadereProgram::use() const noexcept
{
    glUseProgram(_handle);
}

ShadereProgram::operator uint32_t() const noexcept
{
    return _handle;
}
