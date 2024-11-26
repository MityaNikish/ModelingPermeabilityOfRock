#pragma once
#include <vector>
#include <string>

struct Pixel {
    unsigned char color;
};

class Image {

    size_t _width, _height;
    std::vector<Pixel> _pixels;

    Image(int width, int height);

public:

    Image() = default;

    //  Гетэры
    Pixel& getPixel(int i, int j) noexcept;
    inline Pixel getPixel(int i, int j) const noexcept;

    size_t getWidth() const noexcept;
    size_t getHeight() const noexcept;

    // Чтение изображения PPM
    bool readPPM(const std::string& filename);

    // Сохранение изображения PPM
    bool savePPM(const std::string& filename);

    // Обрезка изображения (crop)
    Image crop(int x, int y, int newWidth, int newHeight);

    //  Вывод (для отладки)
    void print() const;
};