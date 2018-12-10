//
//  LoadImage.hpp
//  ProcedurGeneration16bitPeople
//
//  Created by Асиф Мамедов on 24/11/2018.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#ifndef LoadImage_hpp
#define LoadImage_hpp

#include "../Data/Texture.h"

#include <string_view>

using std::string_view;

/**
 * Функция необходимая для загрузки изображения.
 *
 * @param path путь до изображения
 * @return указатель на текстуру
 */
unique_ptr<Texture> loadImage(const string_view& path);

void saveImage(unique_ptr<Texture>& tex, string_view name);

#endif /* LoadImage_hpp */
