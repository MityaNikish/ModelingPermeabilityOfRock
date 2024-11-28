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

    void print(const Image& img) const;

    //void formating() const;

    void imageIntoField(Image& img, Field& fld) const;
    void fieldIntoImage(Field& fld, Image& img) const;
};
