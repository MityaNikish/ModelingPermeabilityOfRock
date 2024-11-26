#pragma once
#include <vector>

enum class Cell : uint8_t
{
    nan, solid, pore
};

class Field
{
    size_t _width, _height;
    std::vector<Cell> _cells;

public:

    Field(int width, int height);

    //  Гетэры
    Cell& getCell(int i, int j) noexcept;
    inline Cell getCell(int i, int j) const noexcept;

    size_t getWidth() const noexcept;
    size_t getHeight() const noexcept;

    //  Удаление замкнутых пор
    void correction() noexcept;

    //  Добавление нижней и верхней границ
    void addBorders();

    //  Вывод (для отладки)
    void print() const;

private:

    //  Алгоритм "Заражения" для удаления замкнутых пор
    void infectionAlgorithm() noexcept;

    //  Проверка условия, подходит ли сосед ячейки для обработки
    inline bool isNecessaryNeighbor(int i, int j, std::vector<bool>& flags) const noexcept;
};