#pragma once
#include "BoolMatriz.h"

class DB
{
private:
	struct node
	{
		BoolMatriz Matriz;
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
	node_t* buscar(BoolMatriz A)
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
	void operator>>(BoolMatriz &matriz);
	bool operator<<(int id);
	bool opciones(BoolMatriz &A);
	~DB();
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
					output << tmp->Matriz(a, b) << ' ';
				}
				output << '\n';
			}
			output << '\n';
			tmp = tmp->next;
		}
		return output;
	}
};

