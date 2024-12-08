#pragma once
#include "Field.h"
#include "Image.h"
#include "ConsoleView.h"

/**
 * @class Controller
 * @brief ����� �������������� ���� �������.
 */
class Controller {
    //Field field;
    Image image;
    ConsoleView view;

public:

    /**
    * @brief ��������� ���� ������ � ����������.
    */
    void run();

private:

    //���� ������������
    void commandFile();
    //��������� �����������
    void print(const Image& img) const;
    //����������� ����������� � ���� �����
    void imageIntoField(const Image& img, Field& fld) const;
    //����������� ���� ����� � �����������
    void fieldIntoImage(const Field& fld, Image& img) const;
};
