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

#include "System/Directory.hpp"

using namespace std;

const string SourceDirectories = "/Users/asifmamedov/Desktop/shaders/project/ProcedurGeneration16bitPeople/Images/Testing/Tr";

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

void addTexture(unique_ptr<Texture>& texture, const string_view& path)
{
    unique_ptr<Texture> tex = loadImage(path.data());
    
    randomDraw(tex);
    
    for (uint32_t i = 0; i < tex->width(); i++) {
        for (uint32_t j = 0; j < tex->height(); j++) {
            if (tex->at(i, j).alpha() > 0.0f) {
                texture->at(i, j).red(tex->at(i, j).red());
                texture->at(i, j).green(tex->at(i, j).green());
                texture->at(i, j).blue(tex->at(i, j).blue());
                texture->at(i, j).alpha(1.0);
                
            }
        }
    }
}

void clearTexture(unique_ptr<Texture>& texture) {
    vec4 back = texture->backgroundColor();
    
    for (uint32_t i = 0; i < texture->width(); i++) {
        for (uint32_t j = 0; j < texture->height(); j++) {
            texture->at(i, j).red(back.r);
            texture->at(i, j).green(back.b);
            texture->at(i, j).blue(back.g);
            texture->at(i, j).alpha(1.0);
        }
    }

}

string getFilePath(const Directory& dir)
{
    size_t size = dir.fileNames().size();
    string fileName;
    
    if (size <= 3) {
        fileName = "_";
    } else {
        while (fileName.find(".png") == std::string::npos) {
            fileName = dir.fileNames()[rand() % size];
        }
    }
    
    return (fileName == "_" ? "_" : dir.directoryPath() + "/" + fileName);
}

vector<string> getSourceGeneratePath() {
    vector<string> data;
    
    vector<string> genData = {
        "/Feet",
        "/Head",
        "/Torso",
        "/Bow",
        "/Hair",
        "/Helmet",
        "/Shield",
        "/Weapon"
    };
    
    string path = "";
    
    for (size_t i = 0; i < genData.size(); i++) {
        if (i < 3 || rand() % 2) {
            path = getFilePath(Directory(SourceDirectories + genData[i]));
            if (path != "_") {
                data.push_back(path);
            }
        }
    }
    
    return data;
}

int main()
{
    srand((unsigned int)time(nullptr));
    unique_ptr<Window> window (new Window("Window", 800, 600));
    unique_ptr<Context> context (new Context(*window));
    
    bool stay = true;
    unique_ptr<SDL_Event> event (new SDL_Event());
    
    context->clearColor(0.223529f, 0.223529f, 0.223529f, 0.0f);
    
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
    
    unique_ptr<Texture> texture (new Texture(2134, 2134, {0.223529f, 0.223529f, 0.223529f, 0.0f}));
    
    auto data = getSourceGeneratePath();
    
    for (size_t i = 0; i < data.size(); i++) {
        addTexture(texture, data[i]);
    }
    
    unique_ptr<TextureRender> renderTexture(new TextureRender(*texture, TextureRender::RGBA16_F, TextureParameter(), texture->width(), texture->height()));
    
    renderTexture->bind();
    
    glUniform1i(glGetUniformLocation(*prog, "ourTexture"), 0);
    
    while (stay) {
        while(SDL_PollEvent(&(*event))) {
            if (event->type == SDL_QUIT || (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)) {
                stay = false;
            } else if (event->key.keysym.scancode == SDL_SCANCODE_SPACE) {
                clearTexture(texture);
                
                data = getSourceGeneratePath();

                for (size_t i = 0; i < data.size(); i++) {
                    addTexture(texture, data[i]);
                }
                
                renderTexture->lock();
                renderTexture->updateData(*texture);
                renderTexture->unlock();
                
                renderTexture->bind();
                
            }
        }
        
        context->clear();
        context->draw(*arrayBuf, 6);
        window->present();
    }
    
    return 0;
}
