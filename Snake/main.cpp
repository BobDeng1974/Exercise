#include <iostream>
#include"Snake.h"
#include"Display.h"
#include"Control.h"

using namespace std;

int main()
{
	Display dis;
	
	Control con;

	dis.ProCho();	//初次输出边界和蛇
	Snake s(dis);

	while (dis.GetChoice())
	{
		while(!s.IsDead())
		{
			dis.ToCont();
			dis.Flash(s);	//不断刷新界面直到蛇死亡
			con.ToSnake(dis.ToCont(),s,dis.GetN());	//移动
			if(con.HadBean(s,dis)) con.OneMore(s);
			if(dis.IsFull()) break;
			con.IsBumped(s,dis.GetN());
			
			dis.AllZero();
			dis.NewBean(s);
		}
		if(dis.IsFull())
		{
			system("cls");
			cout<<"恭喜你 成功通关"<<endl
				<<"分数为"<<s.Score;
		}
		else dis.GameOver();
	}

	return 0;
}
