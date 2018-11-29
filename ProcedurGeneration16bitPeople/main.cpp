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
    
//    unique_ptr<Texture> helment = loadImage("/Users/asifmamedov/Desktop/shaders/project/ProcedurGeneration16bitPeople/Images/Source/Helmet/helmet_01.png");
//    unique_ptr<Texture> shield = loadImage("/Users/asifmamedov/Desktop/shaders/project/ProcedurGeneration16bitPeople/Images/Source/Shield/shield_01.png");
//    unique_ptr<Texture> weapon = loadImage("/Users/asifmamedov/Desktop/shaders/project/ProcedurGeneration16bitPeople/Images/Source/Weapon/weapon_01.png");
//    unique_ptr<Texture> feet = loadImage("/Users/asifmamedov/Desktop/shaders/project/ProcedurGeneration16bitPeople/Images/Source/Feet/feet_02.png");
//    unique_ptr<Texture> bow = loadImage("/Users/asifmamedov/Desktop/shaders/project/ProcedurGeneration16bitPeople/Images/Source/Bow/bow_01.png");
//    unique_ptr<Texture> head = loadImage("/Users/asifmamedov/Desktop/shaders/project/ProcedurGeneration16bitPeople/Images/Source/Head/head_01.png");
//    unique_ptr<Texture> torso = loadImage("/Users/asifmamedov/Desktop/shaders/project/ProcedurGeneration16bitPeople/Images/Source/Torso/torso_01.png");
//    unique_ptr<Texture> hair = loadImage("/Users/asifmamedov/Desktop/shaders/project/ProcedurGeneration16bitPeople/Images/Source/Hair/hair_01.png");
//
//    helment->blend(*shield, .5);
//    helment->blend(*weapon, .5);
//    helment->blend(*feet, .5);
//    helment->blend(*bow, .5);
//    helment->blend(*head, .5);
//    helment->blend(*torso, .5);
//    helment->blend(*hair, .5);
//
//    unique_ptr<Texture> texture(new Texture(50, 50, {1.0f, 1.0f, 1.0f, 1.0f}));
    
//    for (size_t i = 0; i < texture->width() * texture->height(); i++) {
//
//        int ran = rand() % 5 + 100;
//        int del =  2;
//        texture->at(ran * (cos(i) + 1.0) + texture->width() / 2, ran / del * (sin(i) + 1.0) + texture->height() / 2).red(0.0f) ;
//        texture->at(ran * (cos(i) + 1.0) + texture->width() / 2, ran / del * (sin(i) + 1.0) + texture->height() / 2).green(0.0f);
//        texture->at(ran * (cos(i) + 1.0) + texture->width() / 2, ran / del * (sin(i) + 1.0) + texture->height() / 2).blue(0.0f);
//        texture->at(ran * (cos(i) + 1.0) + texture->width() / 2, ran / del * (sin(i) + 1.0) + texture->height() / 2).alpha(0.0f);
//    }
    
//    size_t oct = 8;
//
//    for (size_t j = 0; j < oct; j++) {
//        int ran = rand() % 5 + 10;
//        int del =  2;
//        uint32_t x = 0.0, y = 0.0;
//        for (size_t i = 0; i < texture->width() * texture->height(); i++) {
//            x += ran * (cos(i) + 1.0) + texture->width() / 2;
//            y += ran / del * (sin(i) + 1.0) + texture->height() / 2;
//        }
//
//        texture->at(x, y).red(0.0f);
//        texture->at(x, y).green(0.0f);
//        texture->at(x, y).blue(0.0f);
//        texture->at(x, y).alpha(0.0f);
//    }
//
//    for (size_t i = 0; i < texture->width() * texture->height(); i++) {
//        int ran = rand() % 3 + 2;
//        int del = rand() % 2 + 1;
//        uint32_t x = 0, y = 0;
//
//        for (size_t j = 0; j < oct; j++) {
//            x += ran = rand() % 3 + 2 * (cos(i)) ;
//            y += ran = rand() % 3 + 2  * (sin(i)) ;
//        }
//
//        x += texture->width() / 2;
//        y += texture->height() / 2;
//
//
//        texture->at(x, y).red(0.0f);
//        texture->at(x, y).green(0.0f);
//        texture->at(x, y).blue(0.0f);
//        texture->at(x, y).alpha(0.0f);
//    }
    
    unique_ptr<Texture> tex1 = loadImage("/Users/asifmamedov/Desktop/shaders/project/ProcedurGeneration16bitPeople/Images/Testing/head_1.png");
    unique_ptr<Texture> tex2 = loadImage("/Users/asifmamedov/Desktop/shaders/project/ProcedurGeneration16bitPeople/Images/Testing/feet_1.png");
    unique_ptr<Texture> tex3 = loadImage("/Users/asifmamedov/Desktop/shaders/project/ProcedurGeneration16bitPeople/Images/Testing/hair_1.png");
    unique_ptr<Texture> tex4 = loadImage("/Users/asifmamedov/Desktop/shaders/project/ProcedurGeneration16bitPeople/Images/Testing/hair_2.png");
    
    std::cout << "Fon color: " << tex1->at(0, 0).red() << ' ' <<  tex1->at(0, 0).green() << ' ' <<  tex1->at(0, 0).blue() << ' ' <<  tex1->at(0, 0).alpha() << std::endl;
    
    tex1->backgroundColor({0.0f, 1.0f, 1.0f, 0.752941f});
    tex3->blend(*tex4, 0.6);
    tex1->combination(*tex2);
    tex1->combination(*tex3);
//    tex1->combination(*tex4);
    
    unique_ptr<TextureRender> renderTexture(new TextureRender(*tex1, TextureRender::RGBA16_F, TextureParameter(), tex1->width(), tex1->height()));
    
    renderTexture->bind();
    
    glUniform1i(glGetUniformLocation(*prog, "ourTexture"), 0);
    
    GLuint location = glGetUniformLocation(*prog, "a");
    
    float a = 0.0f;
    
    while (stay) {
        while(SDL_PollEvent(&(*event))) {
            if (event->type == SDL_QUIT || (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)) {
                stay = false;
            }
        }
        
        a = 0.0001;
        
        std::cout << a << std::endl;
        
        glUniform1f(location, a);
        
        context->clear();
        context->draw(*arrayBuf, 6);
        window->present();
    }
    
    return 0;
}
