//
//  TextureRender.cpp
//  createNoise
//
//  Created by Асиф Мамедов on 19.10.2018.
//  Copyright © 2018 PCG. All rights reserved.
//

#include "TextureRender.h"
TextureParameter::TextureParameter(GLenum MinFilter, GLenum MagFilter, GLenum WrapS, GLenum WrapT) :
    minFilter(MinFilter),
    magFilter(MagFilter),
    wrapS(WrapS),
    wrapT(WrapT)
{
}

TextureRender::TextureRender() noexcept :
    _handler(0),
    _width(0),
    _height(0),
    _locked(false),
    _sorageFormat(TextureRender::BLACK_WHITE32_F)
{
}

TextureRender::TextureRender(PixelFormat storFrom, uint32_t width, uint32_t height) noexcept :
    _width(width),
    _height(height),
    _locked(false),
    _sorageFormat(storFrom)
{
    glGenTextures(1, &_handler);
    glBindTexture(GL_TEXTURE_2D, _handler);
    glTexStorage2D(GL_TEXTURE_2D, 1, storFrom, width, height);
}

TextureRender::TextureRender(TextureRender&& textureRender) noexcept :
    _handler(textureRender._handler),
    _width(textureRender._width),
    _height(textureRender._height),
    _locked(false),
    _sorageFormat(textureRender._sorageFormat)
{
    textureRender._handler = 0;
}

TextureRender::TextureRender(const Texture& texture, PixelFormat storFrom, TextureParameter parametr, uint32_t width, uint32_t height) noexcept :
TextureRender(storFrom, width, height)
{
    _locked = true;
    updateData(texture, parametr);
    _locked = false;
}

TextureRender::~TextureRender()
{
    if (_handler) {
        glDeleteTextures(1, &_handler);
    }
}

void TextureRender::bind(int slot) const noexcept
{
    if (!_locked) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, _handler);
    }
}

void TextureRender::unbind() const noexcept
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

uint32_t TextureRender::width() const noexcept
{
    return _width;
}

uint32_t TextureRender::height() const noexcept
{
    return _height;
}

bool TextureRender::loced() const noexcept
{
    return _locked;
}

void TextureRender::lock() noexcept
{
    _locked = true;
}

void TextureRender::unlock() noexcept
{
    _locked = false;
}

void TextureRender::updateData(const Texture &texture, TextureParameter parametr) noexcept
{
    if (_locked && _handler) {
        glBindTexture(GL_TEXTURE_2D, _handler);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _width, _height, GL_RGBA, GL_FLOAT, texture._data);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, parametr.magFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, parametr.minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, parametr.wrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, parametr.wrapT);
        
    }
}
