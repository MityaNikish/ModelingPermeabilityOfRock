#pragma once
#include "Field.h"
#include "Image.h"
#include "ConsoleView.h"

/**
 * @class Controller
 * @brief Класс взаимодействия всех модулей.
 */
class Controller
{
    //Field field;
    Image _image;
    ConsoleView _view;

public:
    /**
    * @brief Запускает цикл работы с программой.
    */
    void run();

private:

    //Цикл подпрограммы
    void commandFile();
};
