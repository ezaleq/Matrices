#pragma once
#include <iostream>

class BoolMatriz
{
private:
	void alocarMatriz();
	void dealocarMatriz();
	struct contenido
	{
		int filas = 0;
		int columnas = 0;
		bool** matriz = nullptr;
	};
	contenido data;
	void error0();

public:
	BoolMatriz(int filas, int columnas);
	BoolMatriz() { }
	~BoolMatriz();
	void operator+=(BoolMatriz &matriz2);
	void operator^=(BoolMatriz &matriz2);
	void operator*=(BoolMatriz &matriz2);
	void operator=(BoolMatriz &matriz2);
	void operator=(int num);
	void operator~();
	void operator!();
	void operator++();
	void operator--();
	bool& operator()(int x, int y);
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

