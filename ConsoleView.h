#pragma once
#include <string>

class ConsoleView {
public:
    void displayMessage(const std::string& message);
    std::string getUserInput(const std::string& prompt);
};