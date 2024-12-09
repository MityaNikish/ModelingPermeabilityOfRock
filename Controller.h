#pragma once
#include "Field.h"
#include "Image.h"
#include "ConsoleView.h"

/**
 * @struct Controller
 * @brief Класс взаимодействия всех модулей.
 */
struct Controller
{
    //Field field;
    Image image;
    ConsoleView view;

    /**
    * @brief Запускает цикл работы с программой.
    */
    void run();

    /**
    * @brief Цикл подпрограммы.
    */
    void commandFile();
};
