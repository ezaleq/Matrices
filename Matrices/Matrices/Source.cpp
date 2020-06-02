#include <stdlib.h>
#include "DB.h"
void lecturaSize(short int& a, short int& b)
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

void guardado(DB& db, BoolMatriz& A, BoolMatriz& B, BoolMatriz& C)
{
	char resp = '\0';
	std::cout << "1) Guardar matriz1.\n";
	std::cout << "2) Guardar matriz2.\n";
	std::cout << "3) Guardar matriz resultante.\n";
	std::cout << "0) Continuar.\n";
	do
	{
		std::cout << "\t:";
		spc::input(resp);
		if (resp == '4') {}
		else if (resp == '1')
			db >> A;
		else if (resp == '2')
			db >> B;
		else if (resp == '3')
			db >> C;
	}
	while (resp != '0');
}

void guardado(DB& db, BoolMatriz& A, BoolMatriz& B)
{
	char resp = '\0';
	std::cout << "1) Guardar matriz1.\n";
	std::cout << "2) Guardar matriz2.\n";
	std::cout << "0) Continuar.\n";
	do
	{
		std::cout << "\t:";
		spc::input(resp);
		if (resp == '4') {}
		else if (resp == '1')
			db >> A;
		else if (resp == '2')
			db >> B;
	} while (resp != '0');
}

void lectura(DB& db, BoolMatriz& A, short int &filas, short int &columnas)
{
	if (db.opciones(A))
	{
		lecturaSize(filas, columnas);
		A.resize(filas, columnas);
		std::cin >> A;
	}
	else
	{
		filas = A.getFilas();
		columnas = A.getColumnas();
	}
}

void test()
{
	char response = '\0';
	DB database;
	short int filas = 0, columnas = 0;
	do
	{
		system("cls");
		std::cout << "\t\tOpciones\n\n";
		std::cout << "1) Suma logica o disyuncion.\n";
		std::cout << "2) Producto logico o conjuncion.\n";
		std::cout << "3) Producto matricial booleano.\n";
		std::cout << "4) Transpuesta.\n";
		std::cout << "5) Complemento.\n";
		std::cout << "6) Producto logico con I.\n";
		std::cout << "7) Clasificacion.\n";
		std::cout << "8) Comparar matrices.\n";
		std::cout << "9) Menu de matrices guardadas.\n";
		std::cout << "0) Salir.\n\t:";
		spc::input(response);
		if (response == '0') { }
		else if (response == '1')
		{
			BoolMatriz A;
			system("cls");
			std::cout << "\t\tSuma logica\n\n";
			std::cout << "Matriz 1\n";
			lectura(database, A, filas, columnas);
			
			system("cls");
			std::cout << "Matriz 1:\n";
			std::cout << A << '\n';
			BoolMatriz B(filas, columnas);
			std::cout << "\nMatriz 2\n";
			if (database.opciones(B))
				std::cin >> B;

			if (B.getFilas() == A.getFilas() && B.getColumnas() == A.getColumnas())
			{
				system("cls");
				std::cout << A << " v\n" << B << " =\n";
				BoolMatriz C;
				C = A + B;
				std::cout << C << '\n';
				guardado(database, A, B, C);
			}
			else
			{
				std::cout << "ERROR: Ambas matrices deben tener las mismas dimensiones.\n";
				system("pause");
			}
		}
		else if (response == '2')
		{
			system("cls");
			std::cout << "\t\tProducto logico\n\n";
			std::cout << "Matriz 1\n";
			BoolMatriz A;
			lectura(database, A, filas, columnas);

			BoolMatriz B(filas, columnas);
			system("cls");
			std::cout << "Matriz 1:\n" << A;
			std::cout << "\nMatriz 2\n";
			if (database.opciones(B))
				std::cin >> B;

			if (B.getFilas() == A.getFilas() && B.getColumnas() == A.getColumnas())
			{
				system("cls");
				std::cout << A << " ^\n" << B << " =\n";
				BoolMatriz C;
				C = A ^ B;
				std::cout << C << '\n';
				guardado(database, A, B, C);
			}
			else
			{
				std::cout << "ERROR: Ambas matrices deben tener las mismas dimensiones.\n";
				system("pause");
			}
		}
		else if (response == '3')
		{
			system("cls");
			std::cout << "\t\tProducto matricial\n\n";
			BoolMatriz A;
			std::cout << "Matriz 1\n";
			lectura(database, A, filas, columnas);

			BoolMatriz B;
			system("cls");
			std::cout << "Matriz 1:\n";
			std::cout << A << '\n';
			std::cout << "\nMatriz 2\n";
			if(database.opciones(B))
			{
				std::cout << "Ingrese el N de columnas: ";
				spc::input(columnas);
				B.resize(A.getColumnas(), columnas);
				std::cin >> B;
			}

			if (B.getFilas() == A.getColumnas())
			{
				system("cls");
				std::cout << A << " X\n" << B << " =\n";
				BoolMatriz C;
				C = A * B;
				std::cout << C << '\n';
				guardado(database, A, B, C);
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
			BoolMatriz A;
			lectura(database, A, filas, columnas);
			system("cls");
			std::cout << A << " = \n";
			
			BoolMatriz C;
			C = ~A;
			std::cout << C << '\n'; 
			guardado(database, A, C);
		}
		else if (response == '5')
		{
			system("cls");
			std::cout << "\t\tComplemento de la matriz\n\n";
			std::cout << "Matriz \n";
			BoolMatriz A;
			lectura(database, A, filas, columnas);
			system("cls");
			std::cout << A << " = \n";

			BoolMatriz C;
			C = !A;
			std::cout << C << '\n';
			guardado(database, A, C);
		}
		else if (response == '6')
		{
			system("cls");
			std::cout << "\t\tProducto logico con I\n\n";
			std::cout << "Matriz \n";
			BoolMatriz A;
			if (database.opciones(A))
			{
				std::cout << "Ingrese las filas/columnas: ";
				spc::input(filas);
				A.resize(filas, filas);
				std::cin >> A;
			}
			if (A.getColumnas() == A.getFilas())
			{
				system("cls");
				std::cout << A << " x \n";
				BoolMatriz I(filas, filas);
				I = ++I;
				std::cout << I << " = \n";
				BoolMatriz C;
				C = I ^ A;
				std::cout << C << '\n';
				guardado(database, A, I, C);
			}
			else
			{
				system("cls");
				std::cout << "ERROR: La matriz debe ser cuadrada (filas=columnas).\n";
				system("pause");
			}
			
		}
		else if (response == '7')
		{
			system("cls");
			std::cout << "\t\tClasificacion de la matriz\n\n";
			std::cout << "Matriz \n";
			BoolMatriz A;
			if (database.opciones(A))
			{
				std::cout << "Ingrese las filas/columnas: ";
				spc::input(filas);
				A.resize(filas, filas);
				std::cin >> A;
			}
			system("cls");
			if (A.getColumnas() != A.getFilas())
				std::cout << "ERROR: La matriz debe ser cuadrada (filas=columnas).\n";
			else
			{
				BoolMatriz I(filas, filas);
				++I;
				BoolMatriz AA;
				AA = A * A;
			
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
				
				if (AA <= A)
					std::cout << "Transitiva.\n";
			}
			system("pause");
			std::cout << A << '\n';
			std::cout << "Desea guardar la matriz? S/N";
			spc::input(response);
			if (response == 's' || response == 'S')
			{
				std::cout << "Guardando...\n";
				database >> A;
				system("pause");
			}
			response = '\0';
			
		}
		else if (response == '8')
		{
			system("cls");
			std::cout << "\t\tComparar matrices\n\n";
			std::cout << "Matriz A\n";
			BoolMatriz A;
			lectura(database, A, filas, columnas);

			BoolMatriz B(filas, columnas);
			std::cout << "\nMatriz B\n";
			if (database.opciones(B))
				std::cin >> B;

			if (B.getFilas() == filas && B.getColumnas() == columnas)
			{
				guardado(database, A, B);
				int resultado = 0;
				do
				{
					system("cls");
					std::cout << "Matriz A\n" << A;
					std::cout << "\nMatriz B\n" << B << '\n';
					std::cout << "\t\tMenu de opciones\n\n";
					std::cout << "1) A < B\n";
					std::cout << "2) A > B\n";
					std::cout << "3) A <= B\n";
					std::cout << "4) A >= B\n";
					std::cout << "5) A == B\n";
					std::cout << "0) Volver.\n";
					spc::input(resultado);
					system("cls");
					auto x = [](bool num){
						if (num)
							return (char*)"Verdadero.";
						else
							return (char*)"Falso.";
					};
					if (resultado == 0) { }
					else
					{
						if (resultado == 1)
							std::cout << x(A < B) << '\n';
						else if (resultado == 2)
							std::cout << x(A > B) << '\n';
						else if (resultado == 3)
							std::cout << x(A <= B) << '\n';
						else if (resultado == 4)
							std::cout << x(A >= B) << '\n';
						else if (resultado == 5)
							std::cout << x(A == B) << '\n';
						system("pause");
					}

				} while (resultado != 0);
			}
			else
			{
				std::cout << "ERROR: Ambas matrices deben tener las mismas dimensiones.\n";
				system("pause");
			}
		}
		else if (response == '9')
		{
			do
			{
				system("cls");
				std::cout << "\t\tMenu de matrices guardadas\n\n";
				std::cout << "1) Guardar matriz.\n";
				std::cout << "2) Editar matriz.\n";
				std::cout << "3) Borrar matriz.\n";
				std::cout << "4) Ver matrices almacenadas.\n";
				std::cout << "0) Volver al menu principal.\n\t:";
				spc::input(response);

				if (response == '1')
				{
					system("cls");
					std::cout << "\t\tGuardar matriz\n\n";
					std::cout << "Matriz\n";
					lecturaSize(filas, columnas);
					BoolMatriz A(filas, columnas);
					std::cout << "1) Setear todo a 0.\n";
					std::cout << "2) Setear todo a 1.\n";
					std::cout << "3) Ingresar valores a mano.\n";
					spc::input(response);
					if (response == '1')
						A = 0;
					else if (response == '2')
						A = 1;
					else
					{
						std::cin >> A;
						std::cout << A;
					}
					std::cout << "\nGuardando...\n";
					database >> A;
					response = '\0';
					system("pause");
				}
				else if (response == '2')
				{
					system("cls");
					std::cout << "\t\tEditar matriz\n\n";
					std::cout << database << "\n0) Salir.\n\t:";
					int respuesta = 0;
					spc::input(respuesta);
					if (respuesta == 0) {}
					else
					{
						if (database.editar(respuesta))
							std::cout << "Matriz editada con exito!\n";
						else
							std::cout << "No se encontro la matriz seleccionado.\n";
						system("pause");
					}
				}
				else if (response == '3')
				{
					system("cls");
					std::cout << "\t\tEliminar matriz\n\n";
					std::cout << database << "\n0) Salir.\n\t:";
					int respuesta = 0;
					spc::input(respuesta);
					if (respuesta == 0) { }
					else
					{
						if(database << respuesta)
							std::cout << "Elemento eliminado con exito!\n";
						else
							std::cout << "No se encontro el elemento seleccionado.\n";
						system("pause");
					}
				}
				else if (response == '4')
				{
					system("cls");
					std::cout << database << '\n';
					system("pause");
				}

			} while (response != '0');
			response = '9';
			
		}

	} while (response != '0');
	

}

#include <bitset>
int main()
{
	test();
}

