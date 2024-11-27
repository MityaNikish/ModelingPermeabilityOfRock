#pragma once
#include "Field.h"
#include "Image.h"
#include "ConsoleView.h"

class Controller {
    //Field field;
    Image image;
    ConsoleView view;

public:

    void run();

private:

    void commandFile();
};
