#include <stdlib.h>
#include "BoolMatriz.h"


std::ostream& operator<<(std::ostream& output, BoolMatriz obj)
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

void operator>>(std::istream& input, BoolMatriz& obj)
{
	bool in = false;
	for (int a = 0; a < obj.getFilas(); a++)
	{
		for (int b = 0; b < obj.getColumnas(); b++)
		{
			std::cout << '[' << a+1 << "][" << b+1 << "] = ";
			spc::input(in);
			obj(a, b, in);
		}
	}
	std::cout << '\n';
}

void lecturaSize(int& a, int& b)
{
	do
	{
		std::cout << "Ingrese el N de filas: ";
		spc::input(a);
	} while (a < 1);
	do
	{
		std::cout << "Ingrese el N de columnas: ";
		spc::input(b);
	} while (b < 1);
}


int main()
{
	char response;
	int filas = 0, columnas = 0;
	do
	{
		system("cls");
		std::cout << "\t\tOpciones\n\n";
		std::cout << "1) Suma logica o disyuncion.\n";
		std::cout << "2) Producto logico o conjuncion.\n";
		std::cout << "3) Producto matricial booleano.\n";
		std::cout << "4) Transpuesta.\n";
		std::cout << "5) Complemento.\n";
		std::cout << "6) Ver variables guardadas.\n";
		std::cout << "7) Producto matricial con I.\n";
		std::cout << "8) Clasificacion.\n";
		std::cout << "0) Salir.\n\t:";
		spc::input(response);
		if (response == '0') { }
		else if (response == '1')
		{
			system("cls");
			std::cout << "\t\tSuma logica\n\n";
			std::cout << "Matriz 1\n";
			lecturaSize(filas, columnas);
			BoolMatriz A(filas, columnas);
			std::cin >> A;
			
			BoolMatriz B(filas, columnas);
			std::cout << "\nMatriz 2\n";
			std::cin >> B;

			std::cout << A << " v\n" << B << " =\n";
			BoolMatriz C;
			C = A + B;
			std::cout << C << '\n';
			system("pause");
		}
		else if (response == '2')
		{
			system("cls");
			std::cout << "\t\tProducto logico\n\n";
			std::cout << "Matriz 1\n";
			lecturaSize(filas, columnas);
			BoolMatriz A(filas, columnas);
			std::cin >> A;

			BoolMatriz B(filas, columnas);
			std::cout << "\nMatriz 2\n";
			std::cin >> B;

			std::cout << A << " ^\n" << B << " =\n";
			BoolMatriz C;
			C = A ^ B;
			std::cout << C << '\n';
			system("pause");
		}
		else if (response == '3')
		{
			system("cls");
			std::cout << "\t\tProducto matricial\n\n";
			std::cout << "Matriz 1\n";
			lecturaSize(filas, columnas);
			BoolMatriz A(filas, columnas);
			std::cin >> A;

			std::cout << "\nMatriz 2\n";
			lecturaSize(filas, columnas);
			if (filas == A.getColumnas())
			{
				BoolMatriz B(filas, columnas);
				std::cin >> B;

				std::cout << A << " X\n" << B << " =\n";
				BoolMatriz C;
				C = A * B;
				std::cout << C << '\n';
			}
			else
				std::cout << "ERROR: Las columnas de la matriz 1 deben corresponder a las filas de la matriz 2.\n";
			system("pause");
		}
		else if (response == '4')
		{
			system("cls");
			std::cout << "\t\tTraspuesta de la matriz\n\n";
			std::cout << "Matriz \n";
			lecturaSize(filas, columnas);
			BoolMatriz A(filas, columnas);
			std::cin >> A;
			std::cout << A << " = \n";
			
			BoolMatriz C;
			C = ~A;
			std::cout << C << '\n'; 
			system("pause");
		}
		else if (response == '5')
		{
			system("cls");
			std::cout << "\t\tComplemento de la matriz\n\n";
			std::cout << "Matriz \n";
			lecturaSize(filas, columnas);
			BoolMatriz A(filas, columnas);
			std::cin >> A;
			std::cout << A << " = \n";

			BoolMatriz C;
			C = !A;
			std::cout << C << '\n';
			system("pause");
		}
		else if (response == '7')
		{
			system("cls");
			std::cout << "\t\tProducto matricial con I\n\n";
			std::cout << "Matriz \n";
			std::cout << "Ingrese las filas/columnas: ";
			spc::input(filas);
			BoolMatriz A(filas, filas);
			std::cin >> A;
			std::cout << A << " x \n";
			BoolMatriz I(filas, filas);
			I = 1;
			std::cout << I << " = \n";
			I = I * A;
			std::cout << I << '\n';
			system("pause");
		}
		else if (response == '8')
		{
			system("cls");
			std::cout << "\t\tClasificacion de la matriz\n\n";
			std::cout << "Matriz \n";
			std::cout << "Ingrese las filas/columnas: ";
			spc::input(filas);
			BoolMatriz A(filas, filas);
			std::cin >> A;


			BoolMatriz I(filas, filas);
			++I;

			
			BoolMatriz At;
			At = ~A;

			// A ^ At
			BoolMatriz AAt;
			AAt = A ^ At;

			std::cout << A << " = \n";
			bool one = false, zero = false;
			for (int i = 0; i < filas; i++)
			{
				if (A(i, i) == 1)
					one = true;
				else
					zero = true;
				if (one && zero)
					break;
			}
			if (one && !zero)
				std::cout << "Reflexiva.\n";
			else if (!one && zero)
				std::cout << "A-reflexiva.\n";

			if (A == At)
				std::cout << "Simetrica.\n";
			else if (AAt == 0)
				std::cout << "A-simetrica.\n";
			if (AAt <= I)
				std::cout << "Anti-simetrico.\n";

			if (A * A <= A)
				std::cout << "Transitiva.\n";
			system("pause");
		}

	} while (response != '0');
	
	return 0;
}

