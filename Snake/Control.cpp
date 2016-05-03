#include"Control.h"

//增长身体 吃豆子 刷新豆子
//死亡 增速
//不按键自动移动 

//移动身体
void Control::ToSnake(int x,Snake s,int n)
{
	s.touse=s.head;
	s.head = (Snake::Body*)malloc(sizeof(Snake::Body));
	s.head->next=s.touse;
	s.head->x=s.touse->x;
	s.head->y=s.touse->y;

	while(s.touse->next!=NULL)
		s.touse=s.touse->next;
	free(s.touse);

	switch(x)
	{
	case 0:
		{
			s.head->x++;
			break;
		}
	case 1:
		{
			s.head->x--;
			break;
		}
	case 2:
		{
			s.head->y--;
			break;
		}
	case 3:
		{
			s.head->y++;
			break;
		}
	}
}

//蛇死亡 
void Control::IsBumped(Snake s,int n)
{
	if(s.head->x==n+1||s.head->y==n+1) s.Isdead=true;
	
	//撞自己 
	s.touse=s.head;
	while(s.touse!=NULL)
	{
		if (s.touse->x == s.head->x&&s.touse->y == s.head->y)
			s.Isdead = true;
	}
}

bool Control::HadBean(Snake s,Display dis)
{
	if(s.head->x==dis.Bean.x&&s.head->y==dis.Bean.y)
		s.Score++;
		return true;
	return false;	
}

void Control::OneMore(Snake s)
{
	s.touse=(Snake::Body*)malloc(sizeof(Snake::Body));
	s.touse->x=s.head->next->x;
	s.touse->y=s.head->next->y;
	s.touse->next=s.head->next;
	s.head->next=s.touse;
}
