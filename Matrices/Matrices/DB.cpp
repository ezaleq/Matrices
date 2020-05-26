#include "DB.h"

void DB::operator>>(BoolMatriz& matriz)
{
	if (!buscar(matriz))
	{
		node_t* tmp = new node_t;
		tmp->Matriz = matriz;
		tmp->id = total;
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

void DB::eliminar(int id)
{
	node_t* tmp = head;
	while (tmp)
	{
		if (tmp->next)
		{
			if (tmp->next->id == id)
			{
				tmp->next = tmp->next->next;
				delete tmp->next;
			}
		}
	}
}

void DB::print()
{
	node_t* tmp = head;
	for (int i = 1; tmp; i++)
	{
		std::cout << "Matriz " << i << ')' << '\n';
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

BoolMatriz DB::obtener(int id)
{
	node_t* tmp = head;
	while (tmp)
	{
		if (tmp->id == id)
			return tmp->Matriz;
		tmp = tmp->next;
	}
	return BoolMatriz();
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