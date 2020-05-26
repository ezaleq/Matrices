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
	void operator++();
	void operator--();
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
};
