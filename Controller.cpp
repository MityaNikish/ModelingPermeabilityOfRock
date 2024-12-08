#include "Controller.h"
#include <sstream>

#include <unordered_map>
#include <memory>


// ��������� ��� ������
class Command
{
public:
    virtual ~Command() = default;
    virtual void execute() const = 0;
    virtual void info() const = 0;
};

class ClearCommand : public Command
{
private:
    ConsoleView& _view;

public:
    explicit ClearCommand(ConsoleView& _view) : _view(_view) { }

    void execute() const override
    {
        _view.clearScreen();
    }
    void info() const override
    {
        _view.displayMessage(std::string("clear - ������� �������;"));
    }
};

class ExitCommand : public Command
{
private:
    ConsoleView& _view;

public:
    explicit ExitCommand(ConsoleView& _view) : _view(_view) { }

    void execute() const override
    {
        return;
    }
    void info() const override
    {
        _view.displayMessage(std::string("exit - ���������� ������ ���������;"));
    }
};

class OpenCommand : public Command
{
private:
    ConsoleView& _view;
    Image& _image;

public:
    explicit OpenCommand(ConsoleView& _view, Image& _image) : _view(_view), _image(_image) { }

    void execute() const override
    {
        std::string filename;
        filename = _view.getUserInput("������� �������� ������� ����� (� �����������): ");
        _image.readPPM(filename);
        _view.displayMessage(std::string("���� ������ �������.\n"));
    }
    void info() const override
    {
        _view.displayMessage(std::string("open - ������� �����;"));
    }
};

class PrintCommand : public Command
{
private:
    ConsoleView& _view;
    Image& _image;

public:
    explicit PrintCommand(ConsoleView& _view, Image& _image) : _view(_view), _image(_image) { }

    void execute() const override
    {
        _view.displayMessage(std::string("����� �����������: ") + std::to_string(_image.getWidth()));
        _view.displayMessage(std::string("������ �����������: ") + std::to_string(_image.getHeight()));
        print();
    }
    void info() const override
    {
        _view.displayMessage(std::string("print - ������� ���������� �����;"));
    }

private:
    void print() const
    {
        std::string message;
        for (size_t i = 0; i < _image.getHeight(); i++)
        {
            for (size_t j = 0; j < _image.getWidth(); j++)
            {
                message.append(std::to_string(static_cast<int>(_image.getPixel(i, j).color)) + "\t");
            }
            message.append("\n");
        }
        message.append("\n");

        _view.displayMessage(message);
    }
};

class CutCommand : public Command
{
private:
    ConsoleView& _view;
    Image& _image;

public:
    explicit CutCommand(ConsoleView& _view, Image& _image) : _view(_view), _image(_image) { }

    void execute() const override
    {
        std::string params = _view.getUserInput("������� ��������� ������� (����� ������) [x1, y1, x2 - x1, y2 - y1] ");
        std::stringstream ss(params);
        int x, y, width, height;
        ss >> x;
        ss >> y;
        ss >> width;
        ss >> height;

        _image = _image.crop(x, y, width, height);
        _view.displayMessage(std::string("���� ������� �������.\n"));
    }
    void info() const override
    {
        _view.displayMessage(std::string("cut - �������� ���������� �����;"));
    }
};

class CorrectCommand : public Command
{
private:
    ConsoleView& _view;
    Image& _image;

public:
    explicit CorrectCommand(ConsoleView& _view, Image& _image) : _view(_view), _image(_image) { }

    void execute() const override
    {
        Field field(_image.getWidth(), _image.getHeight());
        imageIntoField(_image, field);
        field.correction();
        field.addBorders();
        fieldIntoImage(field, _image);

        _view.displayMessage(std::string("���� ��������� �������.\n"));
    }
    void info() const override
    {
        _view.displayMessage(std::string("correct - �������� ��������� ���, �������� �� �������� ����� � ���������� ������;"));
    }

private:
    //������� ����������� � ����
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

    //������� ���� � �����������
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

class SaveCommand : public Command
{
private:
    ConsoleView& _view;
    Image& _image;

public:
    explicit SaveCommand(ConsoleView& _view, Image& _image) : _view(_view), _image(_image) { }

    void execute() const override
    {
        std::string filename = _view.getUserInput("������� �������� ����� (� �����������) ��� ����������: ");
        _image.savePPM(filename);
        _view.displayMessage(std::string("���� �������� �������.\n"));
    }
    void info() const override
    {
        _view.displayMessage(std::string("save - ��������� ������ � ����;"));
    }
};

class HelpCommand : public Command
{
private:
    ConsoleView& _view;
    const std::unordered_map<std::string, std::shared_ptr<Command>>& _commands;

public:
    HelpCommand(ConsoleView& _view, const std::unordered_map<std::string, std::shared_ptr<Command>>& cmds) : _view(_view), _commands(cmds) {}

    void execute() const override
    {
        _view.displayMessage(std::string("��������� �������:\n"));
        for (const auto& pair : _commands) {
            pair.second->info();
        }
    }
    void info() const override
    {
        _view.displayMessage(std::string("help - ������ ������;"));
    }
};

// �������� ������
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
    _view.displayMessage(std::string("������� help ��� ��������� ������ ������;\n"));
    CommandManager manager;

    // ��������� �������
    manager.addCommand("clear", std::make_shared<ClearCommand>(_view));
    manager.addCommand("exit", std::make_shared<ExitCommand>(_view));
    manager.addCommand("help", std::make_shared<HelpCommand>(_view, manager.getCommands()));

    std::string input;

    while (true)
    {
        try
        {
            input = _view.getUserInput("~ ");

            if (input == "exit")
            {
                break;
            }
            if (input == "file")
            {
                std::string filename = _view.getUserInput("������� �������� ����� (� �����������): ");
                _image.readPPM(filename);
                _view.displayMessage(std::string("���� ������ �������.\n"));
                commandFile();
            }

            manager.executeCommand(input);
        }
        catch (const std::exception& e)
        {
            _view.displayMessage(std::string("������: ") + e.what());
            _view.displayMessage(std::string("���������� �����.\n"));
        }
    }

}

//���� ������������
void Controller::commandFile()
{
    _view.displayMessage(std::string("������� help ��� ��������� ������ ������;\n"));
    CommandManager manager;

    // ��������� �������
    manager.addCommand("clear", std::make_shared<ClearCommand>(_view));
    manager.addCommand("exit", std::make_shared<ExitCommand>(_view));
    manager.addCommand("open", std::make_shared<OpenCommand>(_view, _image));
    manager.addCommand("print", std::make_shared<PrintCommand>(_view, _image));
    manager.addCommand("cut", std::make_shared<CutCommand>(_view, _image));
    manager.addCommand("correct", std::make_shared<CorrectCommand>(_view, _image));
    manager.addCommand("save", std::make_shared<SaveCommand>(_view, _image));
    manager.addCommand("help", std::make_shared<HelpCommand>(_view, manager.getCommands()));

    std::string input;

    while (true)
    {
        try
        {
            input = _view.getUserInput("file~ ");

            if (input == "exit") {
                break;
            }

            manager.executeCommand(input);
        }
        catch (const std::exception& e)
        {
            _view.displayMessage(std::string("������: ") + e.what());
            _view.displayMessage(std::string("���������� �����.\n"));
        }
    }
}