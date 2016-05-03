#pragma once
#include"Snake.h"

class Control
{
public:
	void ToSnake(int,Snake,int);
	//void ToDis();
	void IsBumped(Snake,int);
	
	bool HadBean(class Snake,class Display);
	void OneMore(class Snake);
private:
	//enum Key { up, down, left, right };
};
