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

    //  ������
    Cell& getCell(int i, int j) noexcept;
    inline Cell getCell(int i, int j) const noexcept;

    size_t getWidth() const noexcept;
    size_t getHeight() const noexcept;

    //  �������� ��������� ���
    void correction() noexcept;

    //  ���������� ������ � ������� ������
    void addBorders();

    //  ����� (��� �������)
    void print() const;

private:

    //  �������� "���������" ��� �������� ��������� ���
    void infectionAlgorithm() noexcept;

    //  �������� �������, �������� �� ����� ������ ��� ���������
    inline bool isNecessaryNeighbor(int i, int j, std::vector<bool>& flags) const noexcept;
};