//
//  Context.hpp
//  ProcedurGeneration16bitPeople
//
//  Created by Асиф Мамедов on 23/11/2018.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#ifndef Context_hpp
#define Context_hpp

#include "Window.hpp"

class Context
{
public:
    Context(const Window& window);
    
    /**
     * Метод задающий цвет очистки буфера цвета.
     *
     * @param r канал red
     * @param g канал green
     * @param b канал blue
     * @param a канал alpha
     */
    void clearColor(float r, float g, float b, float a) const noexcept;
    
    /**
     * Сетод предназначен для очистки буфера цвета.
     */
    void clear() const noexcept;
    
    void draw(uint32_t vaoHandle, int32_t size);
    
private:
    SDL_GLContext _context;
    
    /**
     * Блок отвечающий за инициализацию контекста GLEW.
     */
    static bool _glewInitialize;
    
    /**
     * Функция отвеччающая за инициалзацию контекста.
     */
    static void _initGlew() noexcept;
};


#endif /* Context_hpp */
