#include<stdio.h>
#include<stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <iostream>
#include <stack>
using namespace std;

#define Esc 5
#define Up 1
#define Down 2
#define Left 3
#define Right 4

int get_key() //���հ���
{
	char c;
	while (c = getch())
	{
		if (c == 27) return Esc; //Esc
								 //if (c != -32)continue;
		//c = getch();
		if (c == 72) return Up; //��
		if (c == 80) return Down; //��
		if (c == 75) return Left; //��
		if (c == 77) return Right; //��
	}
	return 0;
}
int main()
{
	printf("�����ַ���\n");
	int c;
	c = get_key();
	switch (c)
	{
		case Esc: printf("input ESC !");break;
		case Up: printf("input UP !");break;
		case Down: printf("input DOWN !");break;
		case Left: printf("input LEFT !");break;
		case Right: printf("input RIGHT !");break;
		break;
	}
		
	
}