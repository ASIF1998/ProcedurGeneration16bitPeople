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

#include <glm/glm.hpp>

#include <random>

using namespace std;

using glm::vec4;
using glm::mix;
using glm::smoothstep;

void randomDraw(unique_ptr<Texture>& texture)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.2, 1.0);
    
    vec4 c = {
        dis(gen),
        dis(gen),
        dis(gen),
        1.0f
    };
    
    float e = dis(gen);
    
    for (uint32_t i = 0; i < texture->width(); i++) {
        for (uint32_t j = 0; j < texture->height(); j++) {
            if (texture->at(i, j).alpha() > 0.0f) {
                
                float r =texture->at(i, j).red();
                float g =texture->at(i, j).green();
                float b =texture->at(i, j).blue();
                
                if (r != 0.0 && g != 0.0 && b != 0.0) {
//                    float _r = r * c.r;
//                    float _g = g * c.g;
//                    float _b = b * c.b;
                    
                    float _r = mix(r, c.r,e);
                    float _g = mix(g, c.g, e);
                    float _b = mix(b, c.b, e);
                    
//                    float _r = smoothstep(r, c.r, e);
//                    float _g = smoothstep(g, c.g, e);
//                    float _b = smoothstep(b, c.b, e);
                    
                    texture->at(i, j).red(_r);
                    texture->at(i, j).green(_g);
                    texture->at(i, j).blue(_b);
                    texture->at(i, j).alpha(1.0);
                }
            }
        }
    }
}

int main()
{
    srand((unsigned int)time(nullptr));
    unique_ptr<Window> window (new Window("Window", 800, 600));
    unique_ptr<Context> context (new Context(*window));
    
    bool stay = true;
    unique_ptr<SDL_Event> event (new SDL_Event());
    
    context->clearColor(0.223529, 0.223529, 0.223529, 0.0f);
    
    GLfloat pos[] = {
        -0.5f, -0.5, 0.0f,
        -0.5f, 0.5, 0.0f,
        0.5, 0.5, 0.0f,
        0.5, 0.5, 0.0f,
        0.5, -0.5, 0.0f,
        -0.5, -0.5, 0.0f
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
    
    unique_ptr<Texture> tex1 = loadImage("/Users/asifmamedov/Desktop/shaders/project/ProcedurGeneration16bitPeople/Images/Testing/Tr/head_01.png");

    randomDraw(tex1);
    
    unique_ptr<TextureRender> renderTexture(new TextureRender(*tex1, TextureRender::RGBA16_F, TextureParameter(), tex1->width(), tex1->height()));
    
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
