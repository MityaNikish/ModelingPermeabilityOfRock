#include "Controller.h"


void Controller::run() {
    while (true)
    {
        try {
            std::string command = view.getUserInput("~/");
            if (command == std::string("help"))
            {
                view.displayMessage(std::string("help - список команд;\n"));
                view.displayMessage(std::string("exit - завершение работы программы;\n"));
                view.displayMessage(std::string("file - начало работы с сегментированными цифровыми изображениями горной породы;\n"));

                continue;
            }
            if (command == std::string("file"))
            {
                std::string filename = view.getUserInput("Введите название файла (с расширением): ");

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
                view.displayMessage(std::string("Завершение программы.\n"));
                break;
            }
        }
        catch (const std::exception& e) {
            view.displayMessage(std::string("Ошибка: ") + e.what());
            view.displayMessage(std::string("Попробуйте снова.\n"));
        }
    }
}