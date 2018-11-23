//
//  VertexxBuffer.cpp
//  ProcedurGeneration16bitPeople
//
//  Created by Асиф Мамедов on 23/11/2018.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#include "VertexxBuffer.hpp"

#include <stdexcept>

using std::invalid_argument;
using std::runtime_error;

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &_handle);
    
    if (!_handle) {
        throw runtime_error("Error create vbo");
    }
}

VertexBuffer::~VertexBuffer()
{
        glDeleteBuffers(1, &_handle);
}

void VertexBuffer::data(const void *data, size_t lengh, GLenum usage)
{
    if (!data) {
        invalid_argument("Error zero pointer");
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, _handle);
    glBufferData(GL_ARRAY_BUFFER, lengh, data, usage);
}

void VertexBuffer::addData(const void *data, size_t offset, size_t lengh)
{
    if (!data) {
        invalid_argument("Error zero pointer");
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, _handle);
    glBufferSubData(GL_ARRAY_BUFFER, offset, lengh, data);
}

VertexBuffer::operator uint32_t() const noexcept
{
    return _handle;
}
