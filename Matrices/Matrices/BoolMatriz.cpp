#include "BoolMatriz.h"
#include "input.h"

BoolMatriz::BoolMatriz(int filas, int columnas)
{
	data.filas = filas;
	data.columnas = columnas;
	alocarMatriz();
}

BoolMatriz::~BoolMatriz()
{
	dealocarMatriz();
}

void BoolMatriz::alocarMatriz()
{
	data.matriz = new bool* [data.filas];
	for (int i = 0; i < data.filas; i++)
	{
		data.matriz[i] = new bool[data.columnas];
		for (int j = 0; j < getColumnas(); j++)
		{
			data.matriz[i][j] = false;
		}
	}
}

void BoolMatriz::dealocarMatriz()
{
	for (int i = 0; i < data.filas; i++)
		delete[] data.matriz[i];
	delete[] data.matriz;
	data.matriz = nullptr;
}

void BoolMatriz::operator+=(BoolMatriz &matriz2)
{
	if (data.filas == matriz2.getFilas() && data.columnas == matriz2.getColumnas())
	{
		for (int a = 0; a < data.filas; a++)
		{
			for (int b = 0; b < data.columnas; b++)
			{
				data.matriz[a][b] += matriz2(a, b);
			}
		}
	}
}

void BoolMatriz::operator^=(BoolMatriz &matriz2)
{
	if (data.filas == matriz2.getFilas() && data.columnas == matriz2.getColumnas())
	{
		for (int a = 0; a < data.filas; a++)
		{
			for (int b = 0; b < data.columnas; b++)
			{
				data.matriz[a][b] *= matriz2(a, b);
			}
		}
	}
}

void BoolMatriz::operator*=(BoolMatriz &matriz2)
{
	if (data.columnas == matriz2.getFilas())
	{
		BoolMatriz producto(data.filas, matriz2.getColumnas());
		int n = data.filas;
		int m = matriz2.getColumnas();
		for (int k = 0; k < m; k++)
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					producto(i, j) += data.matriz[i][k] * matriz2(k,j);
				}
			}
		}
		*this = producto;
	}
}

void BoolMatriz::operator=(BoolMatriz &matriz2)
{
	dealocarMatriz();
	data.filas = matriz2.getFilas();
	data.columnas = matriz2.getColumnas();
	alocarMatriz();
	for (int a = 0; a < getFilas(); a++)
		for (int b = 0; b < getColumnas(); b++)
			data.matriz[a][b] = matriz2(a, b);
}

void BoolMatriz::operator++()
{
	if (data.filas == data.columnas)
	{
		for (int a = 0; a < data.filas; a++)
			data.matriz[a][a] = 1;
	}
}

void BoolMatriz::operator--()
{
	if (data.filas == data.columnas)
	{
		for (int a = 0; a < data.filas; a++)
			data.matriz[a][a] = 0;
	}
}

void BoolMatriz::operator=(int num)
{
	for (int a = 0; a < data.filas; a++)
		for (int b = 0; b < data.columnas; b++)
			data.matriz[a][b] = num;
}

bool BoolMatriz::operator<(BoolMatriz &matriz2)
{
	return matriz2 > *this;
}

bool BoolMatriz::operator<=(BoolMatriz& matriz2)
{
	return ((*this < matriz2) || (*this == matriz2));
}

bool BoolMatriz::operator>=(BoolMatriz& matriz2)
{
	return ((*this > matriz2) || (*this == matriz2));
}

bool BoolMatriz::operator>(BoolMatriz &matriz2)
{
	int contador0 = 0, contador1 = 0;
	if (data.filas == matriz2.getFilas() && data.columnas == matriz2.getColumnas())
	{
		for (int a = 0; a < data.filas; a++)
		{
			for (int b = 0; b < data.columnas; b++)
			{
				if (data.matriz[a][b] == 1)
					contador0++;
				if (matriz2(a, b) == 1)
					contador1++;
			}
		}
	}
	return (contador0 > contador1);
}

bool BoolMatriz::operator==(BoolMatriz& matriz2)
{
	for (int a = 0; a < data.filas; a++)
		for (int b = 0; b < data.columnas; b++)
		{
			if (data.matriz[a][b] != matriz2(a, b))
				return false;
		}
	return true;
}

bool BoolMatriz::operator==(int num)
{
	BoolMatriz nueva(data.filas, data.columnas);
	if (num == 1)
		for (int a = 0; a < data.filas; a++)
			for (int b = 0; b < data.columnas; b++)
				nueva(a, b) = 1;
	return (*this == nueva);
}

bool& BoolMatriz::operator()(int x, int y)
{
	return data.matriz[x][y];
}

void BoolMatriz::operator~()
{
	BoolMatriz nuevo(data.columnas, data.filas);
	for (int a = 0; a < data.filas; a++)
		for (int b = 0; b < data.columnas; b++)
			nuevo(b, a) = data.matriz[a][b];
	*this = nuevo;
}

void BoolMatriz::operator!() 
{
	for (int a = 0; a < data.filas; a++)
		for (int b = 0; b < data.columnas; b++)
			data.matriz[a][b] = !data.matriz[a][b];
}


int BoolMatriz::getColumnas()
{
	return data.columnas;
}

int BoolMatriz::getFilas()
{
	return data.filas;
}

void BoolMatriz::resize(int filas, int columnas)
{
	dealocarMatriz();
	data.filas = filas;
	data.columnas = columnas;
	alocarMatriz();
}

