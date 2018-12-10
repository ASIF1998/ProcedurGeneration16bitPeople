//
//  LoadImage.cpp
//  ProcedurGeneration16bitPeople
//
//  Created by Асиф Мамедов on 24/11/2018.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#include "Image.hpp"

#include "../SOIL2/SOIL2.h"

#include <iostream>

#include <vector>

using std::cout;
using std::endl;

unique_ptr<Texture> loadImage(const string_view& path)
{
    int32_t width, height;
    uint8_t* Uimage = SOIL_load_image(path.data(), &width, &height, 0, SOIL_LOAD_RGBA);
    float* Fimage = new float[width * height * 4];
    
    for (int32_t i = 0; i < width * height * 4; i++) {
        Fimage[i] = (float)Uimage[i] / (float)255.0f;
    }

    unique_ptr<Texture> tex (new Texture(width , height , Fimage));
    
    delete [] Uimage;
    delete [] Fimage;
    
    return tex;
}

void saveImage(unique_ptr<Texture>& tex, string_view name)
{
    vector< unsigned char > uf( tex->_width * tex->_height * 4);
    
    for (size_t i = 0; i < uf.size(); i++) {
        uf[i] = tex->_data[i] * 255;
    }
    
    string path = "/Users/asifmamedov/Desktop/shaders/project/ProcedurGeneration16bitPeople/SaveImages/";
    path += name.data();
    
    SOIL_save_image(path.c_str(), SOIL_SAVE_TYPE_PNG, tex->_width, tex->_height, 4, &uf[0]);
}
