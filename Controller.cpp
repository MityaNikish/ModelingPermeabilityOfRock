#include "Controller.h"
#include <unordered_map>
#include <stdexcept>
#include <memory>

/**
 * @class Command
 * @brief Интерфейс для команд.
 */
class Command
{
protected:
    Controller& _controller;

public:
    Command(Controller& controller) : _controller(controller) { }

    virtual ~Command() = default;
    virtual void execute() const = 0;
    virtual void info() const = 0;
};

/**
 * @class ClearCommand
 * @brief Команда для очистки экрана.
 */
class ClearCommand : public Command
{
public:
    explicit ClearCommand(Controller& controller) : Command(controller) { }

    void execute() const override
    {
        _controller.view.clearScreen();
    }
    void info() const override
    {
        _controller.view.displayMessage(std::string("clear - очистка консоли;"));
    }
};

/**
 * @class ExitCommand
 * @brief Команда для выхода из программы/подпрограммы.
 */
class ExitCommand : public Command
{
public:
    explicit ExitCommand(Controller& controller) : Command(controller) { }

    void execute() const override
    {
        return;
    }
    void info() const override
    {
        _controller.view.displayMessage(std::string("exit - завершение работы программы;"));
    }
};

/**
 * @class OpenCommand
 * @brief Команда для открытия файла.
 */
class OpenCommand : public Command
{
public:
    explicit OpenCommand(Controller& controller) : Command(controller) { }

    void execute() const override
    {
        std::string filename;
        filename = _controller.view.getUserInput("Введите название другого файла (с расширением): ");
        _controller.image.readPPM(filename);
        _controller.view.displayMessage(std::string("Файл открыт успешно.\n"));
    }
    void info() const override
    {
        _controller.view.displayMessage(std::string("open - открыть файла;"));
    }
};

/**
 * @class OpenCommand
 * @brief Команда для запуска подпрограммы для .
 */
class FileCommand : public Command
{
public:
    explicit FileCommand(Controller& controller) : Command(controller) { }

    void execute() const override
    {
        std::string filename = _controller.view.getUserInput("Введите название файла (с расширением): ");
        _controller.image.readPPM(filename);
        _controller.view.displayMessage(std::string("Файл открыт успешно.\n"));
        _controller.commandFile();
    }
    void info() const override
    {
        _controller.view.displayMessage(std::string("file - запуск подпрограммы для работы с сегментированными цифровыми изображениями горной породы;"));
    }
};

/**
 * @class PrintCommand
 * @brief Команда для вывода изображения.
 */
class PrintCommand : public Command
{
public:
    explicit PrintCommand(Controller& controller) : Command(controller) { }

    void execute() const override
    {
        _controller.view.displayMessage(std::string("Длина изображения: ") + std::to_string(_controller.image.getWidth()));
        _controller.view.displayMessage(std::string("Высота изображения: ") + std::to_string(_controller.image.getHeight()));
        print();
    }
    void info() const override
    {
        _controller.view.displayMessage(std::string("print - вывести содержимое файла;"));
    }

private:
    void print() const
    {
        std::string message;
        for (size_t i = 0; i < _controller.image.getHeight(); i++)
        {
            for (size_t j = 0; j < _controller.image.getWidth(); j++)
            {
                message.append(std::to_string(static_cast<int>(_controller.image.getPixel(_controller.image.getHeight() - i, j).color)) + "\t");
            }
            message.append("\n");
        }
        message.append("\n");

        _controller.view.displayMessage(message);
    }
};

/**
 * @class CutCommand
 * @brief Команда для обрезания изображения.
 */
class CutCommand : public Command
{
public:
    explicit CutCommand(Controller& controller) : Command(controller) { }

    void execute() const override
    {
        std::vector<std::string> params = _controller.view.getUserInputList("Введите параметры обрезки (через пробел) [x1, y1, x2 - x1, y2 - y1] ");
        
        if (params.size() != 4)
        {
            throw std::runtime_error("Неверное количество аргументов");
        }
        int x = std::stoi(params[0]);
        int y = std::stoi(params[1]);
        int width = std::stoi(params[2]);
        int height = std::stoi(params[3]);

        _controller.image = _controller.image.crop(x, y, width, height);
        _controller.view.displayMessage(std::string("Файл обрезан успешно.\n"));
    }
    void info() const override
    {
        _controller.view.displayMessage(std::string("cut - вырезать содержимое файла;"));
    }
};

/**
 * @class CorrectCommand
 * @brief Команда для обработки изображения.
 */
class CorrectCommand : public Command
{
public:
    explicit CorrectCommand(Controller& controller) : Command(controller) { }

    void execute() const override
    {
        Field field(_controller.image.getWidth(), _controller.image.getHeight());
        imageIntoField(_controller.image, field);
        field.correction();
        field.addBorders();
        fieldIntoImage(field, _controller.image);

        _controller.view.displayMessage(std::string("Файл обработан успешно.\n"));
    }
    void info() const override
    {
        _controller.view.displayMessage(std::string("correct - удаление замкнутых пор, удаление не сквозных путей и добавление границ;"));
    }

private:
    //Перевод изображения в поле
    void imageIntoField(const Image& img, Field& fld) const
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
    void fieldIntoImage(const Field& fld, Image& img) const
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
};

/**
 * @class SaveCommand
 * @brief Команда для сохранения изображения.
 */
class SaveCommand : public Command
{
public:
    explicit SaveCommand(Controller& controller) : Command(controller) { }

    void execute() const override
    {
        std::string filename = _controller.view.getUserInput("Введите название файла (с расширением) для сохранения: ");
        _controller.image.savePPM(filename);
        _controller.view.displayMessage(std::string("Файл сохранен успешно.\n"));
    }
    void info() const override
    {
        _controller.view.displayMessage(std::string("save - сохранить данные в файл;"));
    }
};

/**
 * @class HelpCommand
 * @brief Команда для демонстрации списка команд.
 */
class HelpCommand : public Command
{
private:
    const std::unordered_map<std::string, std::shared_ptr<Command>>& _commands;

public:
    HelpCommand(Controller& controller, const std::unordered_map<std::string, std::shared_ptr<Command>>& cmds) : Command(controller), _commands(cmds) { }

    void execute() const override
    {
        _controller.view.displayMessage(std::string("________________________________________________________________"));
        _controller.view.displayMessage(std::string("Доступные команды:\n"));
        for (const auto& pair : _commands) {
            pair.second->info();
        }
        _controller.view.displayMessage(std::string("________________________________________________________________\n"));
    }
    void info() const override
    {
        _controller.view.displayMessage(std::string("help - список команд;"));
    }
};

/**
 * @class CommandManager
 * @brief Менеджер комманд.
 */
class CommandManager {
private:
    std::unordered_map<std::string, std::shared_ptr<Command>> _commands;

public:
    void addCommand(const std::string& name, std::shared_ptr<Command> command)
    {
        _commands[name] = command;
    }

    void executeCommand(const std::string& name) const
    {
        auto it = _commands.find(name);
        if (it != _commands.end()) {
            it->second->execute();
        }
    }

    const auto& getCommands() const
    {
        return _commands;
    }
};


void Controller::run()
{
    CommandManager manager;

    // Добавляем команды
    manager.addCommand("help", std::make_shared<HelpCommand>(*this, manager.getCommands()));
    manager.addCommand("clear", std::make_shared<ClearCommand>(*this));
    manager.addCommand("exit", std::make_shared<ExitCommand>(*this));
    manager.addCommand("file", std::make_shared<FileCommand>(*this));

    std::string input;

    view.displayMessage(std::string("Введите help для просмотра списка команд.\n"));
    while (true)
    {
        try
        {
            input = view.getUserInput("~ ");

            if (input == "exit")
            {
                break;
            }

            manager.executeCommand(input);
        }
        catch (const std::exception& e)
        {
            view.displayMessage(std::string("Ошибка: ") + e.what());
            view.displayMessage(std::string("Попробуйте снова.\n"));
        }
    }

}

//Цикл подпрограммы
void Controller::commandFile()
{
    CommandManager manager;

    // Добавляем команды
    manager.addCommand("help", std::make_shared<HelpCommand>(*this, manager.getCommands()));
    manager.addCommand("clear", std::make_shared<ClearCommand>(*this));
    manager.addCommand("exit", std::make_shared<ExitCommand>(*this));
    manager.addCommand("open", std::make_shared<OpenCommand>(*this));
    manager.addCommand("print", std::make_shared<PrintCommand>(*this));
    manager.addCommand("cut", std::make_shared<CutCommand>(*this));
    manager.addCommand("correct", std::make_shared<CorrectCommand>(*this));
    manager.addCommand("save", std::make_shared<SaveCommand>(*this));

    std::string input;

    view.displayMessage(std::string("Введите help для просмотра списка команд.\n"));
    while (true)
    {
        try
        {
            input = view.getUserInput("file~ ");

            if (input == "exit") {
                break;
            }

            manager.executeCommand(input);
        }
        catch (const std::exception& e)
        {
            view.displayMessage(std::string("Ошибка: ") + e.what());
            view.displayMessage(std::string("Попробуйте снова.\n"));
        }
    }
}