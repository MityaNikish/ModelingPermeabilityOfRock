#include "ConsoleView.h"
#include <iostream>
#include <cstdlib>

void ConsoleView::displayMessage(const std::string& message) const
{
    std::cout << message << std::endl;
}

std::string ConsoleView::getUserInput(const std::string& prompt) const
{
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void ConsoleView::clearScreen() const
{
    system("cls");
}