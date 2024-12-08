#pragma once
#include "Field.h"
#include "Image.h"
#include "ConsoleView.h"

/**
 * @class Controller
 * @brief Класс взаимодействия всех модулей.
 */
class Controller {
    //Field field;
    Image image;
    ConsoleView view;

public:

    /**
    * @brief Запускает цикл работы с программой.
    */
    void run();

private:

    //Цикл подпрограммы
    void commandFile();
    //Отрисовка изображения
    void print(const Image& img) const;
    //Конвертация изображения в поле ячеек
    void imageIntoField(const Image& img, Field& fld) const;
    //Конвертация поля ячеек в изображение
    void fieldIntoImage(const Field& fld, Image& img) const;
};
