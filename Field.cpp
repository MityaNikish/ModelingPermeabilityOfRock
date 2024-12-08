#include "Field.h"
#include <iostream>


Field::Field(int width, int height) : _width(width), _height(height), _cells(_width* _height, Cell::nan) { };

Cell& Field::getCell(int i, int j) noexcept
{
    return _cells[i * _width + j];
}

inline Cell Field::getCell(int i, int j) const noexcept
{
    return _cells[i * _width + j];
}

size_t Field::getWidth() const noexcept
{
    return _width;
}

size_t Field::getHeight() const noexcept
{
    return _height;
}

//  �������� ��������� ���
void Field::correction() noexcept
{
    infectionAlgorithm();
}

//  ���������� ������ � ������� ������
void Field::addBorders()
{
    for (size_t j = 0; j < _width; j++)
    {
        getCell(0, j) = Cell::solid;
        getCell(_height - 1, j) = Cell::solid;
    }
}

//  ����� (��� �������)
//void Field::print() const
//{
//    for (size_t i = 0; i < _height; i++)
//    {
//        for (size_t j = 0; j < _width; j++)
//        {
//            std::cout << static_cast<int>(getCell(i, j)) << " ";
//        }
//        std::cout << "\n";
//    }
//    std::cout << "\n";
//}

//  �������� "���������" ��� �������� ��������� ���
void Field::infectionAlgorithm() noexcept
{
    std::vector<bool> flags(_width * _height, false);
    std::vector<std::pair<int, int>> pool;

    //���� ����� �������
    for (size_t i = 0; i < _height; i++)
    {
        if (getCell(i, 0) != Cell::solid)
        {
            getCell(i, 0) = Cell::pore;
            pool.push_back(std::make_pair(i, 0));
            flags[i * _width] = true;
        }
    }

    //���������� ��������� ���
    while (!pool.empty())
    {
        std::pair<int, int> pos = pool.back();
        pool.pop_back();
        const int i = pos.first;
        const int j = pos.second;

        if (isNecessaryNeighbor(i - 1, j, flags)) pool.push_back(std::make_pair(i - 1, j));
        if (isNecessaryNeighbor(i + 1, j, flags)) pool.push_back(std::make_pair(i + 1, j));
        if (isNecessaryNeighbor(i, j - 1, flags)) pool.push_back(std::make_pair(i, j - 1));
        if (isNecessaryNeighbor(i, j + 1, flags)) pool.push_back(std::make_pair(i, j + 1));

        getCell(i, j) = Cell::pore;
    }

    //���������� �� ��������� ��� ��������
    for (size_t n = 0; n < _width * _height; n++)
    {
        if (_cells[n] == Cell::nan) _cells[n] = Cell::solid;
    }

    //�������� �� �������� �������
    size_t i = 0;
    while (i < _height)
    {
        if (getCell(i, 0) != Cell::solid)
        {
            through(std::make_pair(i, 0));
            while (i + 1 < _height && getCell(i + 1, 0) != Cell::solid)
            {
                i++;
            }
        }
        i++;
    }
}

//�������� �� �������� �����  
void Field::through(const std::pair<int, int>& pos) noexcept
{
    std::vector<bool> flags(_width * _height, false);
    std::vector<std::pair<int, int>> pool;

    pool.push_back(pos);

    bool is_through = false;
    while (!pool.empty())
    {
        std::pair<int, int> pos = pool.back();
        pool.pop_back();
        const int i = pos.first;
        const int j = pos.second;

        if (isPore(i - 1, j, flags)) pool.push_back(std::make_pair(i - 1, j));
        if (isPore(i + 1, j, flags)) pool.push_back(std::make_pair(i + 1, j));
        if (isPore(i, j - 1, flags)) pool.push_back(std::make_pair(i, j - 1));
        if (isPore(i, j + 1, flags)) pool.push_back(std::make_pair(i, j + 1));

        if (j == _width - 1)   is_through = true;
    }

    if (is_through) return;

    for (size_t i = 0; i < _height; i++)
    {
        for (size_t j = 0; j < _width; j++)
        {
            if (flags[i * _width + j])
            {
                getCell(i, j) = Cell::solid;
            }
        }
    }

    return;
}

//  �������� �������, �������� �� ����� ������ ��� ���������
inline bool Field::isPore(int i, int j, std::vector<bool>& flags) const noexcept
{
    if (i < 0 || i >= _height || j < 0 || j >= _width)
    {
        return false;
    }

    bool flags_before = flags[i * _width + j];
    flags[i * _width + j] = true;
    return !flags_before && getCell(i, j) == Cell::pore;
}

//  �������� �������, �������� �� ����� ������ ��� ���������
inline bool Field::isNecessaryNeighbor(int i, int j, std::vector<bool>& flags) const noexcept
{
    if (i < 0 || i >= _height || j < 0 || j >= _width)
    {
        return false;
    }

    bool flags_before = flags[i * _width + j];
    flags[i * _width + j] = true;
    return !flags_before && getCell(i, j) == Cell::nan;
}

////  �������� �������, �������� �� ����� ������ ��� ���������
//inline bool Field::isCheck(bool& state_cell, bool conditions) const noexcept
//{
//    bool state_cell_temp = state_cell;
//    state_cell = true;
//    return !state_cell_temp && conditions;
//}
//
////  �������� �������, �������� �� ����� ������ ��� ���������
//inline bool Field::isPore(int i, int j) const noexcept
//{
//    if (i < 0 || i >= _height || j < 0 || j >= _width)
//    {
//        return false;
//    }
//    return getCell(i, j) == Cell::pore;
//}
//
////  �������� �������, �������� �� ����� ������ ��� ���������
//inline bool Field::isNan(int i, int j) const noexcept
//{
//    if (i < 0 || i >= _height || j < 0 || j >= _width)
//    {
//        return false;
//    }
//    return getCell(i, j) == Cell::nan;
//}f (isCheck(flags[(pos.first - 1) * _width + pos.second], isPore(pos.first - 1, pos.second)) pool.push_back(std::make_pair(pos.first - 1, pos.second));