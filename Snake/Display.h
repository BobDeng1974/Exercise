#pragma once
#include<iostream>
#include"Snake.h"
#include<conio.h>
#include<time.h>
#define MAX 100

using namespace std;

class Display
{
public:
	Display();
	~Display();

	void Display::DisRou(class Snake, int mode);
	void NewBean(class Snake);
	//void DisRou(Snake s);
	
	void ProCho();
	void Start();
	void GameOver();
	void AllZero();

	void Display::Flash(class Snake);	//不断刷新
	int ToCont();
	//void FrSnake(class Snake);

	int GetChoice();
	int GetN();
	bool IsFull();
	
	struct bean
	{
		int x, y;
	}Bean;

private:
	int n=0,choice=1;
	int num[MAX][MAX]={0};
};
