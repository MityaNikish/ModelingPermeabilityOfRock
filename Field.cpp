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

//  Удаление замкнутых пор
void Field::correction() noexcept
{
    infectionAlgorithm();
}

//  Добавление нижней и верхней границ
void Field::addBorders()
{
    for (size_t j = 0; j < _width; j++)
    {
        getCell(0, j) = Cell::solid;
        getCell(_height - 1, j) = Cell::solid;
    }
}

//  Вывод (для отладки)
void Field::print() const
{
    for (size_t i = 0; i < _height; i++)
    {
        for (size_t j = 0; j < _width; j++)
        {
            std::cout << static_cast<int>(getCell(i, j)) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

//  Алгоритм "Заражения" для удаления замкнутых пор
void Field::infectionAlgorithm() noexcept
{
    std::vector<bool> flags(_width * _height, false);
    std::vector<std::pair<int, int>> pool;

    for (size_t i = 0; i < _height; i++)
    {
        if (getCell(i, 0) != Cell::solid)
        {
            getCell(i, 0) = Cell::pore;
            pool.push_back(std::make_pair(i, 0));
            flags[i * _width] = true;
        }
    }

    while (!pool.empty())
    {
        std::pair<int, int> pos = pool.back();
        pool.pop_back();

        if (isNecessaryNeighbor(pos.first - 1, pos.second, flags)) pool.push_back(std::make_pair(pos.first - 1, pos.second));
        if (isNecessaryNeighbor(pos.first + 1, pos.second, flags)) pool.push_back(std::make_pair(pos.first + 1, pos.second));
        if (isNecessaryNeighbor(pos.first, pos.second - 1, flags)) pool.push_back(std::make_pair(pos.first, pos.second - 1));
        if (isNecessaryNeighbor(pos.first, pos.second + 1, flags)) pool.push_back(std::make_pair(pos.first, pos.second + 1));

        getCell(pos.first, pos.second) = Cell::pore;
    }

    for (size_t n = 0; n < _width * _height; n++)
    {
        if (_cells[n] == Cell::nan) _cells[n] = Cell::solid;
    }
}

//  Проверка условия, подходит ли сосед ячейки для обработки
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
