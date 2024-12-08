#pragma once
#include <string>

/**
 * @class ConsoleView
 * @brief Класс для отрисовки пользовательского интерфейса в консоль
 */
class ConsoleView {
public:
    /**
    * @brief Отображение текста в консоль
    */
    void displayMessage(const std::string& message) const;
    /**
    * @brief Запрос ввода даннных с консоли
    */
    std::string getUserInput(const std::string& prompt) const;
    /**
    * @brief Очищает консоль
    */
    void clearScreen() const;
};