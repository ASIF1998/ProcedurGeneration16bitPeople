#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "System/Window.hpp"
#include "System/Context.hpp"

#include "Data/VertexxBuffer.hpp"
#include "Data/VertexArray.hpp"

#include "Renderer/ShaderProgram.hpp"

#include "SOIL2/SOIL2.h"

#include "System/LoadImage.hpp"

#include "Renderer/TextureRender.h"

using namespace std;

int main()
{
    unique_ptr<Window> window (new Window("Window", 800, 600));
    unique_ptr<Context> context (new Context(*window));
    
    bool stay = true;
    unique_ptr<SDL_Event> event (new SDL_Event());
    
    context->clearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    GLfloat pos[] = {
        -1.0f, -1.0, 0.0f,
        -1.0f, 1.0, 0.0f,
        1.0f, 1.0, 0.0f,
        1.0f, 1.0, 0.0f,
        1.0f, -1.0, 0.0f,
        -1.0f, -1.0, 0.0f
    };

    GLfloat texCoord[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
    };
    
    unique_ptr<VertexBuffer> posBuf(new VertexBuffer());
    posBuf->data(pos, sizeof(pos));
    
    unique_ptr<VertexBuffer> texCoordBuf(new VertexBuffer());
    texCoordBuf->data(texCoord, sizeof(texCoord));
    
    unique_ptr<VertexArray> arrayBuf(new VertexArray());
    arrayBuf->addAtribute(*posBuf, 0, 3, GL_FLOAT);
    arrayBuf->addAtribute(*texCoordBuf, 1, 2, GL_FLOAT);
    
    unique_ptr<ShadereProgram> prog(new ShadereProgram("/Users/asifmamedov/Desktop/shaders/project/ProcedurGeneration16bitPeople/Renderer/Shaders/basic.vs.glsl",
                                                       "/Users/asifmamedov/Desktop/shaders/project/ProcedurGeneration16bitPeople/Renderer/Shaders/basic.fs.glsl"));
    
    prog->use();
    
    unique_ptr<Texture> texture = loadImage("/Users/asifmamedov/Desktop/shaders/project/ProcedurGeneration16bitPeople/Images/Testing/allSprites.png");
    
    unique_ptr<TextureRender> renderTexture(new TextureRender(*texture, TextureRender::RGBA16_F, TextureParameter(), texture->width(), texture->height()));
    
    renderTexture->bind();
    
    glUniform1i(glGetUniformLocation(*prog, "ourTexture"), 0);
    
    while (stay) {
        while(SDL_PollEvent(&(*event))) {
            if (event->type == SDL_QUIT || (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)) {
                stay = false;
            }
        }
        
        context->clear();
        context->draw(*arrayBuf, 6);
        window->present();
    }
    
    return 0;
}
