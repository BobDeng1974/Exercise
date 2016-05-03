#pragma once
#include<stdlib.h>
#include"Display.h"

class Snake
{
public:
	Snake();
	Snake(class Display);
	~Snake();
	bool IsDead();

	typedef struct body
	{
		int x, y;
		struct body *next;
	}Body;
	Body* head = NULL;
	Body* touse = NULL;

	bool Isdead=false;
	
	int Score;
};
