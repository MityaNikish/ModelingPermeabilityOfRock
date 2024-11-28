#include <iostream>
//#include <fstream>
//#include <vector>
//#include <string>
//#include <sstream>

//#include "Field.h"
//#include "Image.h"
#include "Controller.h"


void test_field()
{
    Field field(5, 5);
    field.print();

    field.getCell(0, 0) = Cell::solid;
    field.getCell(0, 1) = Cell::solid;
    field.getCell(0, 2) = Cell::solid;
    field.getCell(0, 3) = Cell::solid;
    field.getCell(1, 4) = Cell::solid;
    field.getCell(1, 0) = Cell::solid;
    field.getCell(2, 0) = Cell::solid;
    field.getCell(3, 0) = Cell::solid;
    field.getCell(1, 1) = Cell::solid;
    field.getCell(2, 2) = Cell::solid;
    field.getCell(3, 3) = Cell::solid;
    field.getCell(3, 1) = Cell::solid;

    field.print();

    field.correction();

    field.addBorders();
    field.print();
}

void test_image()
{
    Image image;

    image.readPPM("source.raw");
    image.crop(10, 10, 10, 10);
}

int main() {
    setlocale(LC_ALL, "Russian");

    //test_field();
    //test_image();

    Controller ctrl;

    ctrl.run();

    return 0;
}

