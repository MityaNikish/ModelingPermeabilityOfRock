#include "Image.h"
#include <fstream>

#include <iostream>

Image::Image(int width, int height) : _width(width), _height(height) { }

Pixel& Image::getPixel(int i, int j) noexcept
{
    return _pixels[i * _width + j];
}

inline Pixel Image::getPixel(int i, int j) const noexcept
{
    return _pixels[i * _width + j];
}

size_t Image::getWidth() const noexcept
{
    return _width;
}

size_t Image::getHeight() const noexcept
{
    return _height;
}

// Чтение изображения PPM
bool Image::readPPM(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл");
    }

    file.read(reinterpret_cast<char*>(&_width), 8);
    file.read(reinterpret_cast<char*>(&_height), 8);

    _pixels.resize(_height * _width);
    for (size_t i = 0; i < _height; ++i) {
        for (size_t j = 0; j < _width; ++j) {
            file.read(reinterpret_cast<char*>(&getPixel(i, j).color), 1);
        }
    }
    return true;
}

// Сохранение изображения PPM
bool Image::savePPM(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл для записи");
    }

    for (size_t i = 0; i < _height; ++i) {
        for (size_t j = 0; j < _width; ++j) {
            file.write(reinterpret_cast<const char*>(&getPixel(i, j).color), 1);
        }
    }
    return true;
}

// Обрезка изображения (crop)
Image Image::crop(int x, int y, int newWidth, int newHeight) {
    Image crop_image(newWidth, newHeight);
    for (int i = 0; i < newHeight; ++i) {
        for (int j = 0; j < newWidth; ++j) {
            crop_image.getPixel(i, j) = getPixel(y + i, x + j);
        }
    }

    return crop_image;
}


//  Вывод (для отладки)
void Image::print() const
{
    for (size_t i = 0; i < _height; i++)
    {
        for (size_t j = 0; j < _width; j++)
        {
            std::cout << static_cast<int>(getPixel(i, j).color) << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}