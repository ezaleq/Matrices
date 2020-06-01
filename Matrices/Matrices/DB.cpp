#include <fstream>
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

DB::DB()
{
	std::cout << "Cargando base de datos...\n";
	std::ifstream file("data.bin", std::ios::binary | std::ios::ate);
	if (file.is_open())
	{
		short int filas = 0, columnas = 0;
		std::streampos size = file.tellg();
		file.seekg(0, std::ios::beg);
		BoolMatriz A;
		bool res = false;
		while (size > 0)
		{
			file.read((char*)&filas, sizeof(short int));
			file.read((char*)&columnas, sizeof(short int));
			size -= sizeof(int) * 2;
			A.resize(filas, columnas);
			for (int i = 0; i < filas; i++)
				for (int j = 0; j < columnas; j++)
				{
					file.read((char*)&res, sizeof(bool));
					size -= sizeof(bool);
					A(i, j, res);
				}
			(*this) >> A;
			std::cout << "Matriz recuperada.\n";
		}
		file.close();
	}
	system("cls");
}

DB::~DB()
{
	node_t* tmp = head;
	std::cout << "Guardando matrices...\n";
	std::ofstream file("data.bin", std::ios::binary);
	while (tmp)
	{
		int filas = tmp->Matriz.getFilas();
		int columnas = tmp->Matriz.getColumnas();
		file.write((char*)&filas, sizeof(short int));
		file.write((char*)&columnas, sizeof(short int));
		bool res = false;
		for (int i = 0; i < filas; i++)
		{
			for (int j = 0; j < columnas; j++)
			{
				res = tmp->Matriz(i,j);
				file.write((char*)&res, sizeof(bool));
			}
		}
		tmp = tmp->next;
		delete head;
		head = tmp;
		std::cout << "Matriz guardada.\n";
	}
	file.close();
	delete head;
	system("cls");
}