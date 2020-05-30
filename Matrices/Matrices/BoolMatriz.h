#pragma once
#include <iostream>
#include <vector>
#include "input.h"

class BoolMatriz
{
private:
	struct contenido
	{
		int filas = 0;
		int columnas = 0;
		std::vector<std::vector<bool>> matriz;
	};
	contenido data;

public:
	BoolMatriz(int filas, int columnas);
	BoolMatriz() { }
	BoolMatriz operator+(BoolMatriz &matriz2);
	BoolMatriz operator^(BoolMatriz &matriz2);
	BoolMatriz operator*(BoolMatriz &matriz2);
	BoolMatriz operator~();
	BoolMatriz operator!();
	BoolMatriz operator++();
	BoolMatriz operator--();
	void operator=(int num);
	bool operator()(int x, int y);
	void operator()(int x, int y, bool info);
	bool operator==(BoolMatriz &matriz2);
	bool operator==(int num);
	bool operator>=(BoolMatriz& matriz2);
	bool operator<=(BoolMatriz& matriz2);
	bool operator<(BoolMatriz &matriz2);
	bool operator>(BoolMatriz &matriz2);
	void resize(int filas, int columnas);
	int getColumnas();
	int getFilas();

	friend std::ostream& operator<<(std::ostream& output, BoolMatriz obj)
	{
		for (int a = 0; a < obj.getFilas(); a++)
		{
			for (int b = 0; b < obj.getColumnas(); b++)
			{
				output << obj(a, b) << ' ';
			}
			output << '\n';
		}

		return output;
	}
	friend void operator>>(std::istream& input, BoolMatriz& obj)
	{
		bool in = false;
		for (int a = 0; a < obj.getFilas(); a++)
		{
			for (int b = 0; b < obj.getColumnas(); b++)
			{
				std::cout << '[' << a + 1 << "][" << b + 1 << "] = ";
				spc::input(in);
				obj(a, b, in);
			}
		}
		std::cout << '\n';
	}
};
