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
public:
	void operator>>(BoolMatriz &matriz);
	void eliminar(int id);
	void print();
	bool opciones(BoolMatriz &A);
	BoolMatriz obtener(int id);
	~DB();
};

