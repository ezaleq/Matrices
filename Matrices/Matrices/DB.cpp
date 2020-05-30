#include "DB.h"

void DB::operator>>(BoolMatriz& matriz)
{
	if (!buscar(matriz))
	{
		node_t* tmp = new node_t;
		tmp->Matriz = matriz;
		tmp->id = total;
		tmp->next = nullptr;
		if (!head)
		{
			head = tmp;
			tail = tmp;
		}
		else
		{
			tail->next = tmp;
			tail = tmp;
		}
		total++;
	}
	else
	{
		std::cout << "La matriz seleccionada ya existe en la base de datos!\n";
	}
}

bool DB::operator<<(int id)
{
	node_t* prev = nullptr;
	node_t* tmp = head;
	while (tmp)
	{
		if (tmp->id == id)
		{
			if (total != id + 1)
			{
				if (prev)
					prev->next = tmp->next;
				else
					head = tmp->next;
				delete tmp;
				reordenar();
				return true;
			}
			else
			{
				delete tmp;
				if (!prev)
				{
					head = nullptr;
					total = 1;
				}
				else
				{
					prev->next = nullptr;
					reordenar();
				}

				return true;
			}
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return false;
}

void DB::reordenar()
{
	node_t* tmp = head;
	for (int i = 1; tmp; i++)
	{
		tmp->id = i;
		tmp = tmp->next;
		total = i + 1;
	}
}

bool DB::opciones(BoolMatriz &A)
{
	int response = 0;
	std::cout << "1) Cargar matriz almacenada.\n";
	std::cout << "2) Agregar una nueva matriz.\n";
	do
		spc::input(response);
	while (response != 1 && response != 2);
	if (response == 1)
	{
		node_t* tmp = head;
		if (tmp)
		{
			for (int i = 1; tmp; i++)
			{
				std::cout << "Matriz " << i  << ')'<< '\n';
				for (int a = 0; a < tmp->Matriz.getFilas(); a++)
				{
					for (int b = 0; b < tmp->Matriz.getColumnas(); b++)
					{
						std::cout << tmp->Matriz(a, b) << ' ';
					}
					std::cout << '\n';
				}
				std::cout << '\n';
				tmp = tmp->next;
			}
			std::cout << "0) Salir.\n";
			std::cout << "\t:";
			spc::input(response);
			node_t* search = buscar(response);
			if (response == 0) { return true; }
			else if (search)
				A = search->Matriz;
			else
			{
				std::cout << "ERROR: Ingreso un valor invalido.\n\n";
				return opciones(A);
			}
			return false;
		}
		else
		{
			std::cout << "ERROR: No hay datos almacenados en la base de datos.\n";
			system("pause");
			return true;
		}
	}
	else
		return true;
}

bool DB::editar(int id)
{
	node_t* busqueda = buscar(id);
	if (busqueda)
	{
		system("cls");
		int filas = 0, columnas = 0;
		bool valor = false;
		filas = busqueda->Matriz.getFilas();
		columnas = busqueda->Matriz.getColumnas();
		std::cout << busqueda->Matriz << '\n';
		do
		{
			std::cout << "Ingrese la fila a modificar: ";
			spc::input(filas);
		} while (filas < 1 && filas > busqueda->Matriz.getFilas());
		do
		{
			std::cout << "Ingrese la columna a modificar: ";
			spc::input(columnas);
		} while (columnas < 1 && columnas > busqueda->Matriz.getColumnas());
		std::cout << "Ahora ingrese el valor: ";
		spc::input(valor);
		busqueda->Matriz(filas-1, columnas-1, valor);
		return true;
	}
	return false;
}

DB::~DB()
{
	node_t* tmp = nullptr;
	if (head)
		tmp = head->next;
	while (tmp)
	{
		delete head;
		head = tmp;
		tmp = tmp->next;
	}
	delete head;
}