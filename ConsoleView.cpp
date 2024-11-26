#include "ConsoleView.h"
#include <iostream>

void ConsoleView::displayMessage(const std::string& message) {
    std::cout << message << std::endl;
}

std::string ConsoleView::getUserInput(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}