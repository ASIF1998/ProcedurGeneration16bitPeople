//
//  LoadImage.cpp
//  ProcedurGeneration16bitPeople
//
//  Created by Асиф Мамедов on 24/11/2018.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#include "LoadImage.hpp"

#include "../SOIL2/SOIL2.h"

#include <iostream>

using std::cout;
using std::endl;

unique_ptr<Texture> loadImage(const string_view& path)
{
    cout << "-----------Loading Image-----------" << endl;
    
    int32_t width, height;
    uint8_t* Uimage = SOIL_load_image(path.data(), &width, &height, 0, SOIL_LOAD_RGBA);
    float* Fimage = new float[width * height * 4];
    
    for (int32_t i = 0; i < width * height * 4; i++) {
        Fimage[i] = (float)Uimage[i] / (float)255.0f;
    }
    
    cout << "Size Image:\nWidth: " << width << "\nHeight: " << height << endl;
    
    std::cout << "_________One image pixel color: " << Fimage[0] << ' ' << Fimage[1] << ' ' << Fimage[2] << ' ' << Fimage[3] << "_________\n";
    
    delete [] Uimage;
    delete [] Fimage;
    
    return unique_ptr<Texture>(new Texture(width , height , Fimage));
}
