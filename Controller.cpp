#include "Controller.h"
#include <sstream>


void Controller::run() {
    view.displayMessage(std::string("Введите help для просмотра списка команд;\n"));
    while (true)
    {
        try {
            std::string command = view.getUserInput("~");

            if (command == std::string("help"))
            {
                view.displayMessage(std::string("help - список команд;"));
                view.displayMessage(std::string("exit - завершение работы программы;"));
                view.displayMessage(std::string("file - запуск подпрограммы для работы с сегментированными цифровыми изображениями горной породы;\n"));
                view.displayMessage(std::string("solver - запуск подпрограммы для решения уравнения Стокса;\n"));
                continue;
            }
            if (command == std::string("file"))
            {
                std::string filename = view.getUserInput("Введите название файла (с расширением): ");
                image.readPPM(filename);
                view.displayMessage(std::string("Файл открыт успешно.\n"));
                commandFile();
                continue;
            }
            if (command == std::string("solver"))
            {
                view.displayMessage(std::string("Подпрограмма находится на стадии разработки.\n"));
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

//Цикл подпрограммы
void Controller::commandFile()
{
    view.displayMessage(std::string("Введите help для просмотра списка команд;\n"));
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
                view.displayMessage(std::string("correct - удаление замкнутых пор и добавление границ;"));
                view.displayMessage(std::string("save - сохранить данные в файл;\n"));
                continue;
            }
            if (command == std::string("open"))
            {
                std::string filename;
                filename = view.getUserInput("Введите название другого файла (с расширением): ");
                image.readPPM(filename);
                view.displayMessage(std::string("Файл открыт успешно.\n"));
                continue;
            }
            if (command == std::string("print"))
            {
                view.displayMessage(std::string("Длина изображения: ") + std::to_string(image.getWidth()));
                view.displayMessage(std::string("Высота изображения: ") + std::to_string(image.getHeight()));
                print(image);
                continue;
            }
            if (command == std::string("cut"))
            {
                std::string params = view.getUserInput("Введите параметры обрезки (через пробел) [x1, y1, x2 - x1, y2 - y1] ");
                std::stringstream ss(params);
                int x, y, width, height;
                ss >> x;
                ss >> y;
                ss >> width;
                ss >> height;

                image = image.crop(x, y, width, height);
                view.displayMessage(std::string("Файл обрезан успешно.\n"));

                continue;
            }
            if (command == std::string("correct"))
            {
                Field field(image.getWidth(), image.getHeight());
                imageIntoField(image, field);
                field.correction();
                field.addBorders();
                fieldIntoImage(field, image);

                view.displayMessage(std::string("Файл обработан успешно.\n"));
            }
            if (command == std::string("save"))
            {
                std::string filename = view.getUserInput("Введите название файла (с расширением) для сохранения: ");
                image.savePPM(filename);
                view.displayMessage(std::string("Файл сохранен успешно.\n"));
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
}

//Отрисовка изображения
void Controller::print(const Image& img) const
{
    std::string message;
    for (size_t i = 0; i < img.getHeight(); i++)
    {
        for (size_t j = 0; j < img.getWidth(); j++)
        {
            message.append(std::to_string(static_cast<int>(img.getPixel(i, j).color)) + "\t");
        }
        message.append("\n");
    }
    message.append("\n");

    view.displayMessage(message);
}

//Перевод изображения в поле
void Controller::imageIntoField(const Image& img, Field& fld) const
{
    for (size_t i = 0; i < img.getHeight(); i++)
    {
        for (size_t j = 0; j < img.getWidth(); j++)
        {
            if (img.getPixel(i, j).color == 255)
            {
                fld.getCell(i, j) = Cell::solid;
            }
        }
    }
}

//Перевод поля в изображение
void Controller::fieldIntoImage(const Field& fld, Image& img) const
{
    for (size_t i = 0; i < fld.getHeight(); i++)
    {
        for (size_t j = 0; j < fld.getWidth(); j++)
        {
            if (fld.getCell(i, j) == Cell::solid)
            {
                img.getPixel(i, j).color = 255;
            }
            else
            {
                img.getPixel(i, j).color = 0;
            }
        }
    }
}