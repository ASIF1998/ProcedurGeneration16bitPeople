//
//  TextureRender.h
//
//  Created by Асиф Мамедов on 16.10.2018.
//  Copyright © 2018 PCG. All rights reserved.
//

#ifndef _RENDERER_TEXTURE_RENDER_H
#define _RENDERER_TEXTURE_RENDER_H

#include <GL/glew.h>

#include "../Data/Texture.h"

/**
 * Структура предназначена для использования, в случае если
 * пользователю при создании текстуры нужно указать настройки
 * для её создания.
 *
 * @property minFilter используется для определения того каким
 *   способом накладывать текстуру на поверхность которая больше
 *   самой текстуры. Для определения того какой цвет выдать пикселю
 *   необходимо указать какой алгоритм использовать (к примеру GL_NEAREST)
 * @property magFilter используется для определения того каким
 *   способом накладывать текстуру на поверхность меньшую или равную
 *   самой текстуре. Для определения того какой цвет выдать пикселю
 *   необходимо указать какой алгоритм использовать (к примеру GL_NEAREST)
 * @property wrapS необходим для определения того каким образом нужно
 *   отрисовывать текстуру по оси s в случе если текстурные координаты выйдут
 *   за пределы 0 или 1 (к примеру GL_REPEAT)
 * @property wrapT необходим для поределения того каким образом нужно
 *   отрисовывать текстуру по оси t в случе если текстурные координаты выйдут
 *   за пределы 0 или 1 (к примеру GL_REPEAT)
 */
struct TextureParameter
{
    GLenum minFilter;
    GLenum magFilter;
    GLenum wrapS;
    GLenum wrapT;
    
    /**
     * Конструктор.
     *
     * @param MinFilter способом налажения текстуры на поверхность которая больше самой текстуры
     * @param MagFilter способом налажения текстуры на поверхность меньшую или равную самой текстуре
     * @param WrapS отрисовка по оси s в случие выхода за пределы 0 или 1
     * @param WrapT отрисовка по оси t в случие выхода за пределы 0 или 1
     */
    TextureParameter(GLenum MinFilter = GL_LINEAR, GLenum MagFilter = GL_LINEAR, GLenum WrapS = GL_REPEAT, GLenum WrapT = GL_REPEAT);
};

/**
 * Данный класс отвечает за отрисовку объекта Texture.
 *
 * В его задачи входт выделение памяти в GPU для помещения туда текстуры
 * и активации текстурного слота для возможности работы с ней шейдерной программы.
 *
 * Помимо этого класс позваляет менять текстуру без перевыделения памяти в GPU
 * (но возможность динамической работы с памятью GPU отсутсвует).
 * Для того что бы это сделать вам необходимо заблокировать объект методом lock()
 * а зтем методом updateData поместить туда новую текстуру. После замены текструы не забудте
 * разблокировать объект методом unlock. Если этого не будет сделано, шейдерные программы
 * не смогут работать с новвой текструой.
 */
class TextureRender
{
public:
    
    /**
     * Определяет внутренний размер (в зависимости от количиства
     * инициализированных каналов и их размера) буфера в котором будт хранится текстура.
     */
    enum PixelFormat: GLenum
    {
        RGBA32_F = GL_RGBA32F,
        RGBA16_F = GL_RGBA16F,
        RGBA32_U = GL_RGBA32UI,
        RGBA16_U = GL_RGBA16UI,
        RGBA8_U = GL_RGBA8UI,
        RGBA32_S = GL_RGBA32I,
        RGBA16_S = GL_RGBA16I,
        RGBA8_S = GL_RGBA8I,
        
        RGB32_F = GL_RGB32F,
        RGB16_F = GL_RGB16F,
        RGB32_S = GL_RGB32I,
        RGB16_S = GL_RGB16I,
        RGB8_S = GL_RGB8I,
        RGB32_U = GL_RGB32UI,
        RGB16_U = GL_RGB16UI,
        RGB8_U = GL_RGB8UI,
        
        
        RG32_F = GL_RG32F,
        RG16_F = GL_RG16F,
        RG32_U = GL_RG32UI,
        RG16_U = GL_RG16UI,
        RG8_U = GL_RG8UI,
        RG32_S = GL_RG32I,
        RG16_S = GL_RG16I,
        RG8_S = GL_RG8I,
        
        BLACK_WHITE32_F = GL_R32F,
        BLACK_WHITE16_F = GL_R16F,
        BLACK_WHITE32_U = GL_R32UI,
        BLACK_WHITE16_U = GL_R16UI,
        BLACK_WHITE8_U = GL_R8UI,
        BLACK_WHITE32_S = GL_R32I,
        BLACK_WHITE16_S = GL_R16I,
        BLACK_WHITE8_S = GL_R8I
    };
    
    TextureRender() noexcept;
    
    /**
     * Конструктор выделяющий необходимое количество памяти для текстуры в GPU.
     *
     * Примечание !!!
     * Выделеннуя в GPU память нельзя будет изменить.
     *
     * @param storFrom формат хранения текстуры
     * @param width ширина текстуры.
     * @param height высота текстуры
     */
    TextureRender(PixelFormat storFrom, uint32_t width, uint32_t height) noexcept;
    
    TextureRender(TextureRender&& texureRender) noexcept;
    
    /**
     * Конструктор.
     *
     * Примечание !!!
     * Выделеннуя в GPU память нельзя будет изменить.
     *
     * @param texture текстура которую нужно выводить
     * @param storFrom формат хранения текстуры
     * @param width ширина текстуры.
     * @param height высота текстуры
     */
    TextureRender(const Texture& texture, PixelFormat storFrom, TextureParameter parametr, uint32_t width, uint32_t height) noexcept;
    
    TextureRender(const TextureRender&) = delete;
    
    ~TextureRender();
    
    /**
     * Метод который делает текстуру активной и задаёт ей текструный слот.
     *
     * @param slot текстурный слот.
     */
    void bind(int slot = 0) const noexcept;
    
    /**
     * Метод, делающий текстуру не активной.
     */
    void unbind() const noexcept;
    
    uint32_t width() const noexcept;
    uint32_t height() const noexcept;
    bool loced() const noexcept;
    
    /**
     * Блокирует текстуру.
     */
    void lock() noexcept;
    
    /**
     * Разблокирует текстуру.
     */
    void unlock() noexcept;
    
    /**
     * Данный метод необходим для загрузки новой текстуры.
     * Что бы это сделать не забудте заблокировать объект.
     *
     * @param texture текстура которую нужно загрузить
     * @param parametr настройки отображения текстуры
     */
    void updateData(const Texture& texture, TextureParameter parametr = TextureParameter()) noexcept;
    
private:
    GLuint _handler;
    GLuint _width;
    GLuint _height;
    bool _locked;
    PixelFormat _sorageFormat;
};


#endif // !_RENDERER_TEXTURE_RENDER_H
