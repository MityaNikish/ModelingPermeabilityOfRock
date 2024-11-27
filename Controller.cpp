#include "Controller.h"
#include <sstream>


void Controller::run() {
    view.displayMessage(std::string("������� help ��� ��������� ������ ������� ������ ������;\n"));
    while (true)
    {
        try {
            std::string command = view.getUserInput("~");

            if (command == std::string("help"))
            {
                view.displayMessage(std::string("help - ������ ������;"));
                view.displayMessage(std::string("exit - ���������� ������ ���������;"));
                view.displayMessage(std::string("file - ������ ������ � ����������������� ��������� ������������� ������ ������;\n"));
                continue;
            }
            if (command == std::string("file"))
            {
                commandFile();
                continue;
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

void Controller::commandFile()
{
    bool fileIsOpen = false;
    while (true)
    {
        try {
            std::string command = view.getUserInput("file~ ");
            if (command == std::string("help"))
            {
                view.displayMessage(std::string("help - ������ ������;"));
                view.displayMessage(std::string("exit - ������� �� ���������� file;"));
                view.displayMessage(std::string("open - ������� �����;"));
                view.displayMessage(std::string("print - ������� ���������� �����;"));
                view.displayMessage(std::string("cut - �������� ���������� �����;"));
                view.displayMessage(std::string("save - ��������� ������ � ����;\n"));
                continue;
            }
            if (command == std::string("open"))
            {
                std::string filename;
                if (!fileIsOpen)
                {
                    filename = view.getUserInput("������� �������� ����� (� �����������): ");
                }
                else
                {
                    filename = view.getUserInput("������� �������� ������� ����� (� �����������): ");
                }
                image.readPPM(filename);
                view.displayMessage(std::string("���� ������ �������."));
                fileIsOpen = true;
                continue;
            }
            if (command == std::string("print"))
            {
                if (!fileIsOpen)
                {
                    view.displayMessage(std::string("��� ������ �������������� �������� open ����� ������� ����."));
                }
                else
                {
                    image.print();
                }
                continue;
            }
            if (command == std::string("cut"))
            {
                if (!fileIsOpen)
                {
                    view.displayMessage(std::string("��� ������ �������������� �������� open ����� ������� ����."));
                }
                else
                {
                    std::string params = view.getUserInput("������� ��������� ������� (����� ������) [x1, y1, x2 - x1, y2 - y1] ");

                    std::stringstream ss(params);
                    int x, y, width, height;
                    ss >> x;
                    ss >> y;
                    ss >> width;
                    ss >> height;

                    image = image.crop(x, y, width, height);
                }
                continue;
            }
            if (command == std::string("save"))
            {
                if (!fileIsOpen)
                {
                    view.displayMessage(std::string("��� ������ �������������� �������� open ����� ������� ����."));
                }
                else
                {
                    std::string filename = view.getUserInput("������� �������� ����� (� �����������) ��� ����������: ");
                    image.savePPM(filename);
                }
                continue;
            }
            if (command == std::string("exit"))
            {
                view.displayMessage(std::string("������� �� ���������� file.\n"));
                break;
            }
        }
        catch (const std::exception& e) {
            view.displayMessage(std::string("������: ") + e.what());
            view.displayMessage(std::string("���������� �����.\n"));
        }
    }

    //Field field(image.getWidth(), image.getHeight());

    //for (size_t i = 0; i < image.getHeight(); i++)
    //{
    //    for (size_t j = 0; j < image.getWidth(); j++)
    //    {
    //        if (image.getPixel(i, j).color == 255)
    //        {
    //            field.getCell(i, j) = Cell::solid;
    //        }
    //    }
    //}

    //field.correction();
    //field.addBorders();

    //field.print();


}