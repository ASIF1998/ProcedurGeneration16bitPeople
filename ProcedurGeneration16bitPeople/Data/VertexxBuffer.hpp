//
//  VertexxBuffer.hpp
//  ProcedurGeneration16bitPeople
//
//  Created by Асиф Мамедов on 23/11/2018.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#ifndef VertexxBuffer_hpp
#define VertexxBuffer_hpp

#include <GL/glew.h>

class VertexBuffer
{
public:
    
    friend class VertexArray;
    
    VertexBuffer();
    VertexBuffer(const VertexBuffer&) = delete;
    
    ~VertexBuffer();
    
    /**
     * Метод необходимый для загрузки данных в vbo.
     *
     * @param data указатель на данные.
     * @param lengh размер данных в байтах
     * @param usage как использовать данные
     * @throw invalid_argument в случчае если data указывает на nullptr
     */
    void data(const void* data, size_t lengh, GLenum usage = GL_STATIC_DRAW);
    
    /**
     * Метод необходимый для добавления данных в vbo.
     *
     * @param data указатель на данные.
     * @param offset откуда заполнять данные
     * @param lengh размер данных в байтах
     * @throw invalid_argument в случчае если data указывает на nullptr
     */
    void addData(const void* data, size_t offset, size_t lengh);
    
    operator uint32_t() const noexcept;
    
private:
    uint32_t _handle;
};

#endif /* VertexxBuffer_hpp */
