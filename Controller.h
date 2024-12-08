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
public:
    //Field field;
    Image image;
    ConsoleView view;

    /**
    * @brief Запускает цикл работы с программой.
    */
    void run();

private:

    //Цикл подпрограммы
    void commandFile();
};
