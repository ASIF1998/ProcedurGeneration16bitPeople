//
//  Window.cpp
//  ProcedurGeneration16bitPeople
//
//  Created by Асиф Мамедов on 23/11/2018.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#include "Window.hpp"

#include <stdexcept>

#include <string>

using std::string;
using std::invalid_argument;
using std::runtime_error;

/**
 * Данный блок отвечает за инициализацию системы.
 */

inline void setOpenGLAttributes()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

inline void _systemError()
{
    string msg(SDL_GetError());
    SDL_ClearError();
    throw runtime_error(msg);
}

bool Window::_podisitemInit = false;

void Window::_init()
{
    if (!_podisitemInit) {
        if (SDL_Init(SDL_INIT_EVERYTHING)) {
            _systemError();
        }
        setOpenGLAttributes();
        _podisitemInit = true;
    }
}

void Window::_quit() noexcept
{
    if (_podisitemInit) {
        _podisitemInit = false;
        SDL_Quit();
    }
}

/**
  * Данный блок отвечает за окно.
 */

Window::Window(const string_view& windowName, uint32_t width, uint32_t height)
{
    if (!_podisitemInit) {
        _init();
    }
    
    _window = SDL_CreateWindow(windowName.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (!_window) {
        _systemError();
    }
}

void Window::present()
{
    SDL_GL_SwapWindow(_window);
}
