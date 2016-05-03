#include "Snake.h"

Snake::Snake() {};

Snake::Snake(Display Dis) 
{
	touse=head = (Body *)malloc(sizeof(Body));
	head->x = Dis.GetN() / 2;
	head->y = Dis.GetN() + 1;
	//num[n / 2][n + 1] = 1;
	head->next = NULL;
}

Snake::~Snake()
{
	touse=head->next;
	while(touse!=NULL)
	{
		free(head);
		head=touse;
		touse=touse->next;
	}
}

bool Snake::IsDead()
{
	return Isdead;
}
