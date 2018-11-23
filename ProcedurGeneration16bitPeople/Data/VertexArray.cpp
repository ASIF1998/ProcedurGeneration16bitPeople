//
//  VertexArray.cpp
//  ProcedurGeneration16bitPeople
//
//  Created by Асиф Мамедов on 23/11/2018.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#include "VertexArray.hpp"

#include <stdexcept>

using std::invalid_argument;
using std::runtime_error;

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &_handle);
    
    if (!_handle) {
        throw runtime_error("Error create vao");
    }
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &_handle);
}

void VertexArray::addAtribute(const VertexBuffer& vbo, uint32_t vboIndx, int32_t size, GLenum type)
{
    glBindVertexArray(_handle);
    glEnableVertexAttribArray(vboIndx);
    glVertexAttribPointer(vboIndx, size, type, GL_FALSE, 0, nullptr);
}

VertexArray::operator uint32_t() const noexcept
{
    return _handle;
}
