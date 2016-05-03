#include"Display.h"
#include"Snake.h"

Display::Display()
{
	cout << "\t\t简易贪吃蛇\n"
	<< "1.开始游戏" << endl
	<< "0.退出" << endl;
	cout << "请输入选择：";
	cin >> choice;
	
}

Display::~Display() {};

//打印边界
void Display::DisRou(Snake s,int mode)
{
	int i, j;

	system("cls");
	//数组初始化为贪吃蛇位置
	//snake初始化已设定第一点位置
	if (mode)
	{
		while(s.touse!=NULL)
		{
			num[s.touse->x][s.touse->y]=1;
			s.touse=s.touse->next;
		}
	}
	else
	{
		num[n/2][n + 1] = 1;
	}

	for (i = 0; i <= 2*(n+1); i++) cout << '*';
	cout << endl;
	for (i = 1; i <=n; i++)
	{
		for (j = 0; j <= 2 * (n + 1); j++)
		{
			if (j == 0 || j == 2 * (n + 1))	cout << '*';
			
			else if (num[i][j]==1) printf("0");	//输出蛇的身体

			else cout << " ";
		}
		cout << endl;
	}
	for (i = 0; i <= 2 * (n + 1); i++) cout << '*';
}

int Display::GetChoice() {return choice;}

void Display::ProCho()
{
	switch (choice)
	{
	case 1:
		system("cls");
		Start();
		break;
	case 0:
	{
		choice = 0;
		break;
	}
	default:
		break;
	}
}

//选择难度
void Display::Start()
{
	int choice;
	cout << "请选择难度:" << endl
		<< "1.6*6" << endl
		<< "2.10*10" << endl
		<< "3.20*20" << endl;
	cout << "请输入选择：";
	cin >> choice;

	switch (choice)
	{
	case 1:
	{
		this->n = 6;
		break;
	}
	case 2:
	{
		this->n = 10;
		break;
	}
	case 3:
	{
		this->n = 20;
		break;
	}
	default:
		break;
	}

	system("cls");
	//DisRou(s,0);
}

void Display::Flash(Snake s)
{
	while (!s.IsDead())
	{
		ToCont();	//控制移动 
		DisRou(s,1);
	}
}

//通知控制器键盘输入
int Display::ToCont()
{
	char com;
	com=getch();
	//printf("%d", com);
	switch(com)
	{
	case 72:
		return 0;
	case 80:
		return 1;
	case 75:
		return 2;
	case 77:
		return 3;
	}
}

int Display::GetN() { return this->n; }

void Display::GameOver()
{
	system("cls");
	cout<<endl<<endl<<endl<<endl<<endl
		<<"\t\t 游戏结束"<<endl
		<<"请按任意键结束";
	getch();
}

void Display::NewBean(Snake s)	//不能碰到蛇 
{	
	s.touse=s.head;
	while(s.touse!=NULL)
	{
		num[s.touse->x][s.touse->y]=1;
		s.touse=s.touse->next;
	}
	
	while(1)
	{
		srand((int)time(0));	//设置种子
		this->Bean.x= rand() % (n + 1);
		this->Bean.y= rand () % (n + 1);
		if(num[this->Bean.x][this->Bean.y]!=1)
		{
			num[Bean.x][Bean.y]=1;
			break;
		}
	}	
}

void Display::AllZero()
{
	int i,j;
	for(i=0;i<=99;i++)
		for(j=0;j<=99;j++)
			num[i][j]=0;
}

bool Display::IsFull()
{
	int i,j,flag=1;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(num[i][j]==0) flag=0;
		}
	}
	if (flag == 1) return true;
	return false;
}
