#include <iostream>
#include <vector>
#include <fstream>
#include "input.h"

class BoolMatriz
{
private:
	struct contenido
	{
		short int filas = 0;
		short int columnas = 0;
		std::vector<std::vector<bool>> matriz;
	};
	void ERROR_INDEX() { std::cout << "ERROR: Los valores ingresados estan fuera del rango de la matriz.\n";}
	void ERROR_SET_RANGE() { std::cout << "ERROR: Los valores para filas y columnas no son validos.\n"; }
public:
	contenido data;
	BoolMatriz(short int filas, short int columnas);
	BoolMatriz() { }
	BoolMatriz operator+(BoolMatriz &matriz2);
	BoolMatriz operator^(BoolMatriz &matriz2);
	BoolMatriz operator*(BoolMatriz &matriz2);
	BoolMatriz operator~();
	BoolMatriz operator!();
	BoolMatriz operator++();
	BoolMatriz operator--();
	void operator=(int num);
	bool operator()(short int x, short int y);
	void operator()(short int x, short int y, bool info);
	bool operator==(BoolMatriz &matriz2);
	bool operator==(int num);
	bool operator>=(BoolMatriz& matriz2);
	bool operator<=(BoolMatriz& matriz2);
	bool operator<(BoolMatriz &matriz2);
	bool operator>(BoolMatriz &matriz2);
	void resize(short int filas, short int columnas);
	short int getColumnas();
	short int getFilas();
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
