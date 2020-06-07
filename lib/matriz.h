#include <iostream>
#include <vector>
#include <fstream>
#include "input.h"

class Matriz
{
private:
	struct contenido
	{
		short int filas = 0;
		short int columnas = 0;
		std::vector<std::vector<float>> matriz;
	};
	contenido data;
	Matriz tachar(short int x, short int y);

public:
	Matriz(short int filas, short int columnas);
	Matriz() { }
	// Suma
	Matriz operator+(Matriz &matriz2);
	// Producto matricial
	Matriz operator*(Matriz &matriz2);
	// Producto escalar
	Matriz operator*(float num);
	// Traspuesta
	Matriz operator~();
	// Producto entre elementos
	Matriz operator^(Matriz& matriz2);
	Matriz cofactor();
	Matriz adjunta();
	Matriz inversa();
	float determinante();
	void operator=(float num);
	float operator()(short int x, short int y);
	void operator()(short int x, short int y, float info);
	bool operator==(Matriz &matriz2);
	bool operator==(int num);
	bool operator>=(Matriz& matriz2);
	bool operator<=(Matriz& matriz2);
	bool operator<(Matriz &matriz2);
	bool operator>(Matriz &matriz2);
	void resize(short int filas, short int columnas);
	short int getColumnas();
	short int getFilas();
	friend std::ostream& operator<<(std::ostream& output, Matriz obj)
	{
		float _a = 1, _b = 1;
		float aux = 1;
		float num = 0;
		for (int a = 0; a < obj.getFilas(); a++)
		{
			for (int b = 0; b < obj.getColumnas(); b++)
			{
				num = obj(a,b);
				while (!(aux == num))
				{
					aux = _a/_b;
					if (aux < num)
						_a++;
					else if (aux > num)
					{
						_a--;
						_b++;
					}
				}
				output << _a << '/' << _b << ' ';
				_a = 1;
				_b = 1;
				aux = 1;
			}
			output << '\n';
		}
		return output;
	}

	friend void operator>>(std::istream& input, Matriz& obj)
	{
		float in = 0;
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
