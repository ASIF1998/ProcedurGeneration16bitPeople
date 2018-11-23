//
//  VertexArray.hpp
//  ProcedurGeneration16bitPeople
//
//  Created by Асиф Мамедов on 23/11/2018.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#ifndef VertexArray_hpp
#define VertexArray_hpp

#include <GL/glew.h>

#include "VertexxBuffer.hpp"

class VertexArray
{
public:
    VertexArray();
    VertexArray(const VertexArray&) = delete;
    
    ~VertexArray();
    
    void addAtribute(const VertexBuffer& vbo, uint32_t vboIndx, int32_t size, GLenum type);
    
    operator uint32_t() const noexcept;
    
private:
    uint32_t _handle;
};

#endif /* VertexArray_hpp */
