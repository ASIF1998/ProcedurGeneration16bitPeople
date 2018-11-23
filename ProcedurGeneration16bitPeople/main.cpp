#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "System/Window.hpp"
#include "System/Context.hpp"

#include "Data/VertexxBuffer.hpp"
#include "Data/VertexArray.hpp"

#include "Renderer/ShaderProgram.hpp"

int main()
{
    Window window("Window", 800, 600);
    Context context (window);
    
    bool stay = true;
    SDL_Event event;
    
    context.clearColor(1.0, 1.0, 1.0, 1.0);
    
    GLfloat pos[] = {
        -1.0f, -1.0, 0.0f,
        -1.0f, 1.0, 0.0f,
        1.0f, 1.0, 0.0f,
        1.0f, 1.0, 0.0f,
        1.0f, -1.0, 0.0f,
        -1.0f, -1.0, 0.0f
    };
    
    VertexBuffer buf;
    buf.data(pos, sizeof(pos));
    
    VertexArray bufArray;
    bufArray.addAtribute(buf, 0, 3, GL_FLOAT);
    
   ShadereProgram prog ("/Users/asifmamedov/Desktop/рабочий стол/программирование/гпо/PCG/ProcedurGeneration16bitPeople/ProcedurGeneration16bitPeople/Renderer/Shaders/basic.vs.glsl",
                        "/Users/asifmamedov/Desktop/рабочий стол/программирование/гпо/PCG/ProcedurGeneration16bitPeople/ProcedurGeneration16bitPeople/Renderer/Shaders/basic.fs.glsl");
    
    prog.use();
    
    while (stay) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)) {
                stay = false;
            }
        }
        
        context.clear();
        context.draw(bufArray, 6);
        window.present();
    }
    
    return 0;
}
