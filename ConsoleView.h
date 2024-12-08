#pragma once
#include <string>

/**
 * @class ConsoleView
 * @brief ����� ��� ��������� ����������������� ���������� � �������
 */
class ConsoleView {
public:
    /**
    * @brief ����������� ������ � �������
    */
    void displayMessage(const std::string& message) const;
    /**
    * @brief ������ ����� ������� � �������
    */
    std::string getUserInput(const std::string& prompt) const;
    /**
    * @brief ������� �������
    */
    void clearScreen() const;
};