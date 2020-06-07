#include "..\lib\matriz.h"
#include <math.h>

Matriz::Matriz(short int filas, short int columnas)
{
	data.filas = filas;
	data.columnas = columnas;
	data.matriz.assign(filas, std::vector<float>(columnas, 0));
}

Matriz Matriz::operator+(Matriz &matriz2)
{
	Matriz ans;
	if (getFilas() == matriz2.getFilas() && getColumnas() == matriz2.getColumnas())
	{
		ans.resize(getFilas(),getColumnas());
		for (int a = 0; a < getFilas(); a++)
		{
			for (int b = 0; b < getColumnas(); b++)
			{
				ans(a, b, (*this)(a,b) + matriz2(a, b));
			}
		}
	}
	return ans;
}

Matriz Matriz::tachar(short int x, short int y)
{
	short int size = getFilas();
	Matriz A(size-1, size-1);
	short int _i = 0, _j = 0;
	for (short int i = 0; i < size; i++)
	{
		for (short int j = 0; j < size; j++)
		{
			if (i == x)
			{
				_i--;
				break;
			}
			else if (j != y)
			{
				A(_i,_j, (*this)(i,j));
				_j++;
			}
		}
		_j = 0;
		_i++;
	}
	return A;
}

float Matriz::determinante()
{
	if (getFilas() == getColumnas())
	{
		short int size = getFilas();
		switch (size)
		{
			case 2:
			{
				float resultado = (*this)(0,0) * (*this)(1,1);
				resultado -= (*this)(0,1) * (*this)(1,0);
				return resultado;
				break;
			}
			case 3:
			{
				float resultado = (*this)(0,0) * (*this)(1,1) * (*this)(2,2);
				resultado += (*this)(1,0) * (*this)(2,1) * (*this)(0,2);
				resultado += (*this)(2,0) * (*this)(0,1) * (*this)(1,2);
				resultado -= (*this)(0,2) * (*this)(1,1) * (*this)(2,0);
				resultado -= (*this)(1,2) * (*this)(2,1) * (*this)(0,0);
				resultado -= (*this)(2,2) * (*this)(0,1) * (*this)(1,0);
				return resultado;
				break;
			}
			default:
			{
				float resultado = 0;
				for (int i = 0; i < size; i++)
				{
					if (i % 2  == 0)
						resultado += (*this)(i, 0) * tachar(i,0).determinante();
					else
						resultado += (*this)(i,0) * (-1) * tachar(i,0).determinante();
				}
				return resultado;
			}
		}
	}
	return 0;
}

Matriz Matriz::operator^(Matriz& matriz2)
{
	Matriz resultado;
	if (matriz2.getFilas() == getFilas() && matriz2.getColumnas() == getColumnas())
	{
		resultado.resize(getFilas(), getColumnas());
		for (int a = 0; a < getFilas(); a++)
			for (int b = 0; b < getColumnas(); b++)
				resultado(a, b, (*this)(a, b) * matriz2(a, b));
	}
	return resultado;

}

Matriz Matriz::cofactor()
{
	Matriz A;
	if (getFilas() == getColumnas())
	{
		short int size = getFilas();
		float resultado = 0;
		A.resize(size, size);
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				A(i, j, float(pow(-1, i + j)) * ((*this).tachar(i, j)).determinante());
	}
	return A;
}

Matriz Matriz::adjunta()
{
	Matriz A;
	if (getFilas() == getColumnas())
	{
		A = (*this);
		A = A.cofactor();
		return ~A;
	}
	return A;
}

Matriz Matriz::inversa()
{
	Matriz A;
	if (getFilas() == getColumnas())
	{
		if (determinante() != 0)
		{
			Matriz B = (*this).adjunta();
			std::cout << '\n' << B << '\n';
			return  B * (1/determinante());
		}
		else
			std::cout << "ERROR: La determinante de la matriz es 0, no existe su inversa.\n";
	}
	return A;
}

Matriz Matriz::operator*(Matriz &matriz2)
{
	Matriz ans;
	if (getColumnas() == matriz2.getFilas())
	{
		ans.resize(getFilas(), matriz2.getColumnas());
		int n = getFilas();
		int m = matriz2.getColumnas();
		int o = getColumnas();
		for (int k = 0; k < o; k++)
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					ans(i, j, ans(i,j) + ((*this)(i,k) * matriz2(k, j)));
				}
			}
		}
	}
	return ans;
}

Matriz Matriz::operator*(float num)
{
	Matriz A = (*this);
	float resultado = 0;
	for (int i = 0; i < getFilas(); i++)
		for (int j = 0; j < getColumnas(); j++)
		{
			resultado = A(i, j) * num;
			A(i, j, resultado);
		}
	return A;
}

Matriz Matriz::operator~()
{
	Matriz nuevo (getColumnas(), getFilas());
	for (int a = 0; a < getFilas(); a++)
		for (int b = 0; b < getColumnas(); b++)
			nuevo(b,a, (*this)(a,b));
	return nuevo;
}

void Matriz::operator=(float num)
{
	for (int a = 0; a < getFilas(); a++)
		for (int b = 0; b < getColumnas(); b++)
			(*this)(a,b, num);
}

bool Matriz::operator<(Matriz &matriz2)
{
	return matriz2 > *this;
}

bool Matriz::operator<=(Matriz& matriz2)
{
	return ((*this < matriz2) || (*this == matriz2));
}

bool Matriz::operator>=(Matriz& matriz2)
{
	return ((*this > matriz2) || (*this == matriz2));
}

bool Matriz::operator>(Matriz &matriz2)
{
	int contador0 = 0, contador1 = 0;
	if (getFilas() == matriz2.getFilas() && getColumnas() == matriz2.getColumnas())
	{
		for (int a = 0; a < getFilas(); a++)
		{
			for (int b = 0; b < getColumnas(); b++)
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

bool Matriz::operator==(Matriz& matriz2)
{
	if (getFilas() == matriz2.getFilas() && getColumnas() == matriz2.getColumnas())
	{
		for (int a = 0; a < getFilas(); a++)
			for (int b = 0; b < getColumnas(); b++)
			{
				if (data.matriz[a][b] != matriz2(a, b))
					return false;
			}
		return true;
	}
	else
		return false;
}

bool Matriz::operator==(int num)
{
	Matriz nueva(getFilas(), getColumnas());
	if (num == 1)
		for (int a = 0; a < getFilas(); a++)
			for (int b = 0; b < getColumnas(); b++)
				nueva(a, b, 1);
	return (*this == nueva);
}

void Matriz::operator()(short int x, short int y, float info)
{
	data.matriz[x][y] = info;
}

float Matriz::operator()(short int x, short int y)
{
	return data.matriz[x][y];
}

short int Matriz::getColumnas()
{
	return data.columnas;
}

short int Matriz::getFilas()
{
	return data.filas;
}

void Matriz::resize(short int filas, short int columnas)
{
	data.filas = filas;
	data.columnas = columnas;
	data.matriz.assign(filas, std::vector<float>(columnas, 0));
}
