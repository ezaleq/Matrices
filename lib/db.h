#include "matriz.h"
#include <iostream>
class DB
{
private:
	struct node
	{
		Matriz Matriz;
		int id = 0;
		struct node* next = nullptr;
	};
	typedef struct node node_t;
	node_t* head = nullptr;
	node_t* tail = nullptr;
	int total = 1;
	node_t* buscar(int id)
	{
		node_t* tmp = head;
		while (tmp)
		{
			if (tmp->id == id)
				return tmp;
			tmp = tmp->next;
		}
		return nullptr;
	}
	node_t* buscar(Matriz A)
	{
		node_t* tmp = head;
		while (tmp)
		{
			if (tmp->Matriz == A)
				return tmp;
			tmp = tmp->next;
		}
		return nullptr;
	}
	void reordenar();
public:
	DB();
	~DB();
	Matriz getMatriz(int id);
	void operator>>(Matriz &matriz);
	bool operator<<(int id);
	bool opciones(Matriz &A);
	bool editar(int id);
	friend std::ostream& operator<<(std::ostream& output, DB &obj)
	{
		node_t* tmp = obj.head;
		for (int i = 1; tmp; i++)
		{
			output << "Matriz " << i << ')' << '\n';
			for (int a = 0; a < tmp->Matriz.getFilas(); a++)
			{
				for (int b = 0; b < tmp->Matriz.getColumnas(); b++)
				{
					output << tmp->Matriz << '\n';
				}
				output << '\n';
			}
			output << '\n';
			tmp = tmp->next;
		}
		return output;
	}
};

