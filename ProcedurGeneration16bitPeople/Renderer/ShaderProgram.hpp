//
//  ShaderProgram.hpp
//  ProcedurGeneration16bitPeople
//
//  Created by Асиф Мамедов on 23/11/2018.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <GL/glew.h>

#include <string_view>

using std::string_view;

class ShadereProgram
{
public:
    ShadereProgram(const string_view& vertPath, const string_view& fragPath);
    
    void use() const noexcept;
    
    operator uint32_t() const noexcept;
    
private:
    
    /**
     * Метод необходимый для установки вершинного шейдера.
     *
     * @param path путь до кода с вершинным шейдером
     */
    inline void setVertexxShader(const string_view& path);
    
    /**
     * Метод необходимый для установки фрагментного шейдера.
     *
     * @param path путь до кода с фрагментным шейдером
     */
    inline void setFragmentShader(const string_view& path);
    
    /**
     * Метод предназначенный для линковки шейдерной программы.
     *
     * @throw runtime_error в случчае если не получилось слинковать
     *        шейдерную программу
     */
    void link();

    uint32_t _vertexShaderHandle;
    uint32_t _fragmentShaderProgram;
    uint32_t _handle;
};

#endif /* ShaderProgram_hpp */
