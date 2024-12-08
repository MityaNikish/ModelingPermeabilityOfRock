#pragma once
#include "Field.h"
#include "Image.h"
#include "ConsoleView.h"

/**
 * @class Controller
 * @brief ����� �������������� ���� �������.
 */
class Controller
{
    //Field field;
    Image _image;
    ConsoleView _view;

public:
    /**
    * @brief ��������� ���� ������ � ����������.
    */
    void run();

private:

    //���� ������������
    void commandFile();
};
