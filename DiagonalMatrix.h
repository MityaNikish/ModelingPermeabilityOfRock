#pragma once
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iomanip>

template <class Type>
concept FloatingType = std::is_floating_point_v<Type>;

template <FloatingType Type = double>
class DiagonalMatrix
{
	size_t _order_of_matrix;
	size_t _block_size;
	std::vector<Type> _main_diagonal;
	std::vector<Type> _side_diagonal;
	std::vector<Type> _upper_side_diagonal;

public:
	DiagonalMatrix(std::filesystem::path file_path)
	{
		std::ifstream fin(file_path, std::ios::binary);
		fin.read((char*)&_order_of_matrix, sizeof(size_t));
		fin.read((char*)&_block_size, sizeof(size_t));
		const size_t& n = _order_of_matrix;
		const size_t& m = _block_size;
		_main_diagonal.resize(n);
		_side_diagonal.resize(n - 1);
		_upper_side_diagonal.resize(n - m);
		fin.read((char*)_main_diagonal.data(), sizeof(Type) * n);
		fin.read((char*)_side_diagonal.data(), sizeof(Type) * (n - 1));
		fin.read((char*)_upper_side_diagonal.data(), sizeof(Type) * (n - m));
	}

	Type getElem(int i, int j) const
	{
		if (i == j)
		{
			return _main_diagonal[i];
		}
		if (i - 1 == j || i + 1 == j)
		{
			return _side_diagonal[i < j ? i : j];
		}
		if (i + _block_size == j || i - _block_size == j)
		{
			return _upper_side_diagonal[i < j ? i : j];
		}
		return 0.0;
	}

	void write(std::filesystem::path file_path)
	{
		std::ofstream fout(file_path, std::ios::binary | std::ios::trunc);
		fout.write((char*)&_order_of_matrix, sizeof(size_t));
		fout.write((char*)&_block_size, sizeof(size_t));
		size_t& n = _order_of_matrix;
		size_t& m = _block_size;
		fout.write((char*)_main_diagonal.data(), sizeof(Type) * n);
		fout.write((char*)_side_diagonal.data(), sizeof(Type) * (n - 1));
		fout.write((char*)_upper_side_diagonal.data(), sizeof(Type) * (n - m));
	}

	void print(size_t n_setw = 1) const noexcept
	{
		for (size_t i = 0; i < _order_of_matrix; i++)
		{
			for (size_t j = 0; j < _order_of_matrix; j++)
			{
				std::cout << std::setw(n_setw * 2 + 1) << std::right << getElem(i, j);
			}
			std::cout << std::string(n_setw - 1, '\n') << std::endl;
		}
		std::cout << std::endl;
	}
};

void createSLAU(size_t Nx, size_t Ny, std::string file_path)
{
	size_t n = Nx * Ny;
	size_t m = Nx;

	double Lx = 1;
	double Ly = 1;

	double hx = Lx / (Nx - 1);
	double hy = Ly / (Ny - 1);

	std::vector<double> main_diagonal(n, 2.0 / (hx * hx) + 2.0 / (hy * hy));
	std::vector<double> side_diagonal(n - 1, -1.0 / (hx * hx));
	for (size_t i = 1; i < Ny; i++)
	{
		side_diagonal[i * Nx - 1] = 0;
	}
	std::vector<double> upper_side_diagonal(n - m, -1.0 / (hy * hy));

	std::ofstream fout(file_path, std::ios::binary | std::ios::trunc);
	fout.write((char*)&n, sizeof(size_t));
	fout.write((char*)&m, sizeof(size_t));
	fout.write((char*)main_diagonal.data(), sizeof(double) * n);
	fout.write((char*)side_diagonal.data(), sizeof(double) * (n - 1));
	fout.write((char*)upper_side_diagonal.data(), sizeof(double) * (n - m));
}