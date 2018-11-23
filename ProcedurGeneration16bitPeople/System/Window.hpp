//
//  Window.hpp
//  ProcedurGeneration16bitPeople
//
//  Created by Асиф Мамедов on 23/11/2018.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <SDL2/SDL.h>
#include <string>

#include <string_view>

using std::string_view;


class Window
{
public:
    Window(const string_view& windowName, uint32_t width, uint32_t height);
    
    void present();
    
    friend class Context;
    
private:
    
    /**
     * Данный блок отвечает за инициализацию системы.
     */
    
    static bool _podisitemInit;
    
    /**
     * Функция предназначенная для инициализации подсистем.
     *
     * @throw runtime_error если произошла ошибка при иницыализации подсистем
     */
    static void _init();
    
    /**
     * Функция предназначенная для освобождение инициализированных подсистем.
     */
    static void _quit() noexcept;
    
protected:
    SDL_Window* _window;
};

#endif /* Window_hpp */
