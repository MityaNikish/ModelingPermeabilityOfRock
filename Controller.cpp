#include "Controller.h"


void Controller::run() {
    while (true)
    {
        try {
            std::string command = view.getUserInput("~/");
            if (command == std::string("help"))
            {
                view.displayMessage(std::string("help - ������ ������;\n"));
                view.displayMessage(std::string("exit - ���������� ������ ���������;\n"));
                view.displayMessage(std::string("file - ������ ������ � ����������������� ��������� ������������� ������ ������;\n"));

                continue;
            }
            if (command == std::string("file"))
            {
                std::string filename = view.getUserInput("������� �������� ����� (� �����������): ");

                Image image;
                image.readPPM(filename);

                Field field(image.getWidth(), image.getHeight());

                for (size_t i = 0; i < image.getHeight(); i++)
                {
                    for (size_t j = 0; j < image.getWidth(); j++)
                    {
                        if (image.getPixel(i, j).color == 255)
                        {
                            field.getCell(i, j) = Cell::solid;
                        }
                    }
                }

                field.correction();
                field.addBorders();

                field.print();
            }
            if (command == std::string("exit"))
            {
                view.displayMessage(std::string("���������� ���������.\n"));
                break;
            }
        }
        catch (const std::exception& e) {
            view.displayMessage(std::string("������: ") + e.what());
            view.displayMessage(std::string("���������� �����.\n"));
        }
    }
}