#include "BoolMatriz.h"


BoolMatriz::BoolMatriz(short int filas, short int columnas)
{
	data.filas = filas;
	data.columnas = columnas;
	data.matriz.assign(filas, std::vector<bool>(columnas, 0));
}

BoolMatriz BoolMatriz::operator+(BoolMatriz &matriz2)
{
	BoolMatriz ans;
	if (data.filas == matriz2.getFilas() && data.columnas == matriz2.getColumnas())
	{
		ans.resize(data.filas, data.columnas);
		for (int a = 0; a < data.filas; a++)
		{
			for (int b = 0; b < data.columnas; b++)
			{
				ans(a, b, data.matriz[a][b] + matriz2(a, b));
			}
		}
	}
	return ans;
}

BoolMatriz BoolMatriz::operator^(BoolMatriz &matriz2)
{
	BoolMatriz ans;
	if (data.filas == matriz2.getFilas() && data.columnas == matriz2.getColumnas())
	{
		ans.resize(data.filas, data.columnas);
		for (int a = 0; a < data.filas; a++)
		{
			for (int b = 0; b < data.columnas; b++)
			{
				ans(a,b, data.matriz[a][b] * matriz2(a, b));
			}
		}
	}
	return ans;
}

BoolMatriz BoolMatriz::operator*(BoolMatriz &matriz2)
{
	BoolMatriz ans;
	if (data.columnas == matriz2.getFilas())
	{
		ans.resize(data.filas, matriz2.getColumnas());
		int n = data.filas;
		int m = matriz2.getColumnas();
		if (m <= data.columnas)
			for (int k = 0; k < m; k++)
			{
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < m; j++)
					{
						ans(i, j, ans(i,j) + (data.matriz[i][k] * matriz2(k, j)));
					}
				}
			}
		else
			for (int k = 0; k < m-1; k++)
			{
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < m; j++)
					{
						ans(i, j, ans(i, j) + (data.matriz[i][k] * matriz2(k, j)));
					}
				}
			}
	}
	return ans;
}

BoolMatriz BoolMatriz::operator++()
{
	BoolMatriz nuevo;
	if (data.filas == data.columnas)
	{
		nuevo.resize(data.filas, data.columnas);
		for (int a = 0; a < data.filas; a++)
			nuevo(a,a,1);
	}
	return nuevo;
}

BoolMatriz BoolMatriz::operator--()
{
	BoolMatriz nuevo;
	if (data.filas == data.columnas)
	{
		nuevo.resize(data.filas, data.columnas);
		for (int a = 0; a < data.filas; a++)
			nuevo(a,a,0);
	}
	return nuevo;
}

BoolMatriz BoolMatriz::operator~()
{
	BoolMatriz nuevo (data.columnas, data.filas);
	for (int a = 0; a < data.filas; a++)
		for (int b = 0; b < data.columnas; b++)
			nuevo(b,a, data.matriz[a][b]);
	return nuevo;
}

BoolMatriz BoolMatriz::operator!() 
{
	BoolMatriz ans(data.filas, data.columnas);
	for (int a = 0; a < data.filas; a++)
		for (int b = 0; b < data.columnas; b++)
			ans(a,b, !data.matriz[a][b]);
	return ans;
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
	if (data.filas == matriz2.getFilas() && data.columnas == matriz2.getColumnas())
	{
		for (int a = 0; a < data.filas; a++)
			for (int b = 0; b < data.columnas; b++)
			{
				if (data.matriz[a][b] != matriz2(a, b))
					return false;
			}
		return true;
	}
	else
		return false;
}

bool BoolMatriz::operator==(int num)
{
	BoolMatriz nueva(data.filas, data.columnas);
	if (num == 1)
		for (int a = 0; a < data.filas; a++)
			for (int b = 0; b < data.columnas; b++)
				nueva(a, b, 1);
	return (*this == nueva);
}

void BoolMatriz::operator()(short int x, short int y, bool info)
{
	data.matriz[x][y] = info;
}


bool BoolMatriz::operator()(short int x, short int y)
{
	return data.matriz[x][y];
}

short int BoolMatriz::getColumnas()
{
	return data.columnas;
}

short int BoolMatriz::getFilas()
{
	return data.filas;
}

void BoolMatriz::resize(short int filas, short int columnas)
{
	data.filas = filas;
	data.columnas = columnas;
	data.matriz.assign(filas, std::vector<bool>(columnas, 0));
}
