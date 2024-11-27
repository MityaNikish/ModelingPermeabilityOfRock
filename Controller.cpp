#include "Controller.h"
#include <sstream>


void Controller::run() {
    view.displayMessage(std::string("Введите help для просмотра списка комманд список команд;\n"));
    while (true)
    {
        try {
            std::string command = view.getUserInput("~");

            if (command == std::string("help"))
            {
                view.displayMessage(std::string("help - список команд;"));
                view.displayMessage(std::string("exit - завершение работы программы;"));
                view.displayMessage(std::string("file - начало работы с сегментированными цифровыми изображениями горной породы;\n"));
                continue;
            }
            if (command == std::string("file"))
            {
                commandFile();
                continue;
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

void Controller::commandFile()
{
    bool fileIsOpen = false;
    while (true)
    {
        try {
            std::string command = view.getUserInput("file~ ");
            if (command == std::string("help"))
            {
                view.displayMessage(std::string("help - список команд;"));
                view.displayMessage(std::string("exit - выхыход из подраздела file;"));
                view.displayMessage(std::string("open - открыть файла;"));
                view.displayMessage(std::string("print - вывести содержимое файла;"));
                view.displayMessage(std::string("cut - вырезать содержимое файла;"));
                view.displayMessage(std::string("save - сохранить данные в файл;\n"));
                continue;
            }
            if (command == std::string("open"))
            {
                std::string filename;
                if (!fileIsOpen)
                {
                    filename = view.getUserInput("Введите название файла (с расширением): ");
                }
                else
                {
                    filename = view.getUserInput("Введите название другого файла (с расширением): ");
                }
                image.readPPM(filename);
                view.displayMessage(std::string("Файл открыт успешно."));
                fileIsOpen = true;
                continue;
            }
            if (command == std::string("print"))
            {
                if (!fileIsOpen)
                {
                    view.displayMessage(std::string("Для начала воспользуйтесь командой open чтобы открыть файл."));
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
                    view.displayMessage(std::string("Для начала воспользуйтесь командой open чтобы открыть файл."));
                }
                else
                {
                    std::string params = view.getUserInput("Введите параметры обрезки (через пробел) [x1, y1, x2 - x1, y2 - y1] ");

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
                    view.displayMessage(std::string("Для начала воспользуйтесь командой open чтобы открыть файл."));
                }
                else
                {
                    std::string filename = view.getUserInput("Введите название файла (с расширением) для сохранения: ");
                    image.savePPM(filename);
                }
                continue;
            }
            if (command == std::string("exit"))
            {
                view.displayMessage(std::string("Выхыход из подраздела file.\n"));
                break;
            }
        }
        catch (const std::exception& e) {
            view.displayMessage(std::string("Ошибка: ") + e.what());
            view.displayMessage(std::string("Попробуйте снова.\n"));
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