//
//  Context.cpp
//  ProcedurGeneration16bitPeople
//
//  Created by Асиф Мамедов on 23/11/2018.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#include "Context.hpp"

#include <SDL2/SDL.h>
#include <GL/glew.h>

bool Context::_glewInitialize = false;

void Context::_initGlew() noexcept
{
    if (!_glewInitialize) {
        _glewInitialize = true;
        
        glewExperimental = GL_TRUE;
        glewInit();
    }
}

Context::Context(const Window& window) :
    _context(SDL_GL_CreateContext(window._window))
{
    _initGlew();
}

void Context::clearColor(float r, float g, float b, float a) const noexcept
{
    glClearColor(r, g, b, a);
}

void Context::clear() const noexcept
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Context::draw(uint32_t vaoHandle, int32_t size)
{
    glBindVertexArray(vaoHandle);
    glDrawArrays(GL_TRIANGLES, 0, size);
}
