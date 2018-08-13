#include<stdio.h>
#include<stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <iostream>
#include <stack>
using namespace std;

#define Status int
#define Wall 1
#define Road 0
#define Start 0
#define End 0
#define Esc 5
#define Up 1
#define Down 2
#define Left 3
#define Right 4
#define ERROR 0
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0
#define OUT 8
#define STEPPED 2
#define MAX 1000000
////////////////////////////////////////////////////////////////
/**************************************************************/
////////////////////////////////////////////////////////////////
//以下为函数申明，各种结构体的定义
//  建立节点结构体  
struct Point
{
	int row;
	int col;

	Point(int x, int y) {
		this->row = x;
		this->col = y;
	}

	bool operator!=(const Point& rhs) {							//不等号操作符重载
		if (this->row != rhs.row || this->col != rhs.col)       //判断出入口是否符合迷宫大小  
			return true;
		return false;
	}
};
//      定义当前点和起点的结构体
typedef struct
{
	int x, y;
	int parent_x, parent_y;
}QNode, *QueuePtr;
typedef QNode ElemType;//单一元素点
typedef struct SqQueue
{
	ElemType * base;
	int front;
	int rear;
}SqQueue;//元素点队列结构体
typedef struct
{
	int top, base, count;
	ElemType container[19000];
}SqStack;//元素点栈，container数组
Status InitStack(SqStack *s);
Status StackEmpty(SqStack s);
Status InitQueue(SqQueue *Q);//初始化队列          
Status QueueEmpty(SqQueue Q);//判断队列是否为空    
Status GetHead(SqQueue Q, ElemType *e);//取队列头元素  
Status EnQueue(SqQueue *Q, ElemType e);//入队       
Status DeQueue(SqQueue *Q, ElemType *e);//出队     
Status Push(SqStack *s, ElemType e);//入栈       
Status Pop(SqStack *s, ElemType *e);//出栈       
void game2(int **Map, int Height, int Width);//广度优先搜索走迷宫过的操作   
void gotoxy(int x, int y);												//移动光标的函数  
void paint(int **Map, int x, int y);									//打印迷宫墙和路的函数  
void paint2(int **Map, int x, int y);									//打印迷宫路径的函数  
int ** createMap(int Width, int Height);								//创建二维数组 用于储存迷宫 
void create1(int ** MAP, int x, int y, int Height, int Width, int speed);//随机生成迷宫函数 
void create2(int ** MAP, int x, int y, int Height, int Width);			//随机生成迷宫函数 
int get_key();															//接受方向键的函数 
void game(int **Map, int Height, int Width);							//游戏操作函数     
void hidden();															//隐藏光标的函数   
void print(int x, int y);												//打印路径函数     
void printM();															//打印菜单函数     
Point getAdjacentNotVisitedNode(bool** mark, Point point, int m, int n);//获取相邻未被访问的节点的函数   
void mazePath(void* maze, int m, int n, const Point& startP, Point endP, stack<Point>& pointStack);//给定二维迷宫，求可行路径的函数（DFS） 

				////////////////////////////////////////////////////////////////
				/**************************************************************/
				////////////////////////////////////////////////////////////////
				//以下为主函数
int main()
{
	int choose = 0;
	srand((unsigned)time(NULL));
	while (1)
	{
		system("CLS");
		printM();
		scanf("%d", &choose);//此处还可以设置防止输入不在1-4之间或输入其它错误输入的措施。
		if (choose == 1)
		{
			hidden();
			system("CLS");
			int i = 0, j = 0;
			//输入行和列
			int Height = 0, Width = 0, speed = 0;
			printf("请输入行数列数以及打通相邻点的时间差（单位ms）（以空格隔开后敲击回车，行列仅可以输入奇数）\n");
			scanf("%d %d %d", &Height, &Width, &speed);
			system("CLS");
			//生成储存迷宫的数组
			int ** Map = createMap(Width, Height);
			//初始化迷宫
			for (i = 0; i <= Height + 1; ++i)
				for (j = 0; j <= Width + 1; ++j)
					if (i == 0 || i == Height + 1 || j == 0 || j == Width + 1)
						Map[i][j] = Road;
					else Map[i][j] = Wall;
					//创建迷宫
					for (i = 1; i <= Height; i++)
						for (j = 1; j <= Width; j++) //画出迷宫
							paint(Map, i, j);
					create1(Map, 2 * (rand() % (Height / 2) + 1), 2 * (rand() % (Width / 2) + 1), Height, Width, speed);
					//边界处理
					for (i = 0; i <= Height + 1; ++i)
					{
						Map[i][0] = Wall;
						Map[i][Width + 1] = Wall;
					}
					//边界处理
					for (j = 0; j <= Width + 1; ++j)
					{
						Map[0][j] = Wall;
						Map[Height + 1][j] = Wall;
					}
					//迷宫出入口设置
					Map[2][1] = Start;
					Map[Height - 1][Width] = End;
					for (i = 1; i <= Height; i++)
						for (j = 1; j <= Width; j++) //画出迷宫
							paint(Map, i, j);
					gotoxy(0, 1);
					printf("入");
					gotoxy(Width * 2 - 2, Height - 2);
					printf("出");
					printf("\n\n按任意键回到菜单");
					getch();

		}
		else if (choose == 2)
		{
			void hidden();
			int i = 0, j = 0;
			srand((unsigned)time(NULL));
			//输入行和列
			int Height = 0, Width = 0;
			system("CLS");
			printf("请输入行数列数（以空格隔开，并敲击回车,只准输入奇数）\n");
			scanf("%d %d", &Height, &Width);
			system("CLS");
			//生成储存迷宫的数组
			int ** Map = createMap(Width, Height);
			//初始化迷宫
			for (i = 0; i <= Height + 1; ++i)
				for (j = 0; j <= Width + 1; ++j)
					if (i == 0 || i == Height + 1 || j == 0 || j == Width + 1)
						Map[i][j] = Road;
					else Map[i][j] = Wall;
					//创建迷宫
					create2(Map, 2 * (rand() % (Height / 2) + 1), 2 * (rand() % (Width / 2) + 1), Height, Width);
					//边界处理
					for (i = 0; i <= Height + 1; ++i)
					{
						Map[i][0] = Wall;
						Map[i][Width + 1] = Wall;
					}
					//边界处理
					for (j = 0; j <= Width + 1; ++j)
					{
						Map[0][j] = Wall;
						Map[Height + 1][j] = Wall;
					}
					//迷宫出入口设置
					Map[2][1] = Start;
					Map[Height - 1][Width] = End;
					Sleep(500);
					for (i = 1; i <= Height; i++)
						for (j = 1; j <= Width; j++) //画出迷宫
							paint(Map, i, j);
					gotoxy(0, 1);
					printf("入");
					gotoxy(Width * 2 - 2, Height - 2);
					printf("出");
					gotoxy(Width * 2 - 2, Height);
					printf("\n\n");
					printf("上下左右键操控*号，按ESC出现路径\n按任意键开始(ESC没按起多按几次就行)");
					getch();
					game(Map, Height, Width);
		}
		else if (choose == 3)
		{
			void hidden();
			int i = 0, j = 0;
			srand((unsigned)time(NULL));
			//输入行和列
			int Height = 0, Width = 0;
			system("CLS");
			printf("请输入行数列数（以空格隔开，并敲击回车,只准输入奇数）\n");
			scanf("%d%d", &Height, &Width);
			system("CLS");
			//生成储存迷宫的数组
			int ** Map = createMap(Width, Height);
			//初始化迷宫
			for (i = 0; i <= Height + 1; ++i)
				for (j = 0; j <= Width + 1; ++j)
					if (i == 0 || i == Height + 1 || j == 0 || j == Width + 1)
						Map[i][j] = Road;
					else Map[i][j] = Wall;
					//创建迷宫
					create2(Map, 2 * (rand() % (Height / 2) + 1), 2 * (rand() % (Width / 2) + 1), Height, Width);
					//边界处理
					for (i = 0; i <= Height + 1; ++i)
					{
						Map[i][0] = Wall;
						Map[i][Width + 1] = Wall;
					}
					//边界处理
					for (j = 0; j <= Width + 1; ++j)
					{
						Map[0][j] = Wall;
						Map[Height + 1][j] = Wall;
					}
					//迷宫出入口设置
					Map[2][1] = Start;
					Map[Height - 1][Width] = End;
					Sleep(500);
					for (i = 1; i <= Height; i++)
						for (j = 1; j <= Width; j++) //画出迷宫
							paint(Map, i, j);
					gotoxy(0, 1);
					printf("入");
					gotoxy(Width * 2 - 2, Height - 2);
					printf("出");
					gotoxy(Width * 2 + 3, Height);
					printf("\n\n");
					printf("上下左右键操控问号，按ESC出现金手指\n按任意键开始(ESC没按起多按几次就行)");
					getch();
					game2(Map, Height, Width);

		}
		else if (choose == 4) exit(0);
		else if ((choose != 1) && (choose != 2) && (choose != 3) && (choose != 4))
		{
			printf("\n请输入1-4之间的数字");
		}
	}
	return 0;
}


////////////////////////////////////////////////////////////////
/**************************************************************/
////////////////////////////////////////////////////////////////
//以下为函数的定义
void printM()
{
	//gotoxy(32, 64);
	printf(" *************************************************\n");
	printf(" * 简易迷宫                                      *\n");

	printf(" * By Jason_Lee  西南科技大学信息学院            *\n");
	printf(" *************************************************\n");
	printf("   1. 迷宫生成演示                                \n");
	printf("   2. 深度优先搜索走迷宫                          \n");
	printf("   3. 广度优先搜索走迷宫                          \n");
	printf("   4. 退出                                        \n");
	printf("   Please Choose 1-4 :\n");
	printf(" *************************************************\n");
}
void gotoxy(int x, int y)//光标位置
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void paint(int **Map, int x, int y)
{
	gotoxy(2 * y - 2, x - 1);//使用的unicode字符，占2个字符位，故纵坐标乘2.
	switch (Map[x][y])		 //且因为从原点开始，故横纵坐标减一：2*(y-1)；
	{

	case Wall:
		printf("█"); break; //画墙
	case Road:
		printf("　"); break; //画路
	}
}
void paint2(int **Map, int x, int y)
{
	gotoxy(2 * y - 2, x - 1);
	printf("　"); //画路
}

int ** createMap(int Width, int Height)//创建(width+2)*(height+2)的二维数组
{
	Width += 2;
	Height += 2;
	int **MAP;
	int i = 0;
	MAP = (int**)malloc(Height * sizeof(int*));
	int * p = (int*)malloc(Height*Width * sizeof(int));
	for (i = 0; i<Height; i++)
		MAP[i] = &p[i*Width];
	return MAP;
}
void create1(int ** MAP, int x, int y, int Height, int Width, int speed)//生成迷宫路径函数
{
	int c[4][2] = { 0,1,1,0,0,-1,-1,0 };
	int i, j, t;
	for (i = 0; i < 4; i++)//上下左右四方向
	{
		j = rand() % 4;
		t = c[i][0]; c[i][0] = c[j][0]; c[j][0] = t;
		t = c[i][1]; c[i][1] = c[j][1]; c[j][1] = t;
	}
	MAP[x][y] = Road;
	Sleep(speed);
	paint(MAP, x, y);
	for (i = 0; i < 4; i++)
		if (MAP[x + 2 * c[i][0]][y + 2 * c[i][1]] == Wall)//(x,y)的下一个方向再下一方向，不满足就从(x,y)继续
		{
			MAP[x + c[i][0]][y + c[i][1]] = Road;
			Sleep(speed);
			paint(MAP, x + c[i][0], y + c[i][1]);
			create1(MAP, x + 2 * c[i][0], y + 2 * c[i][1], Height, Width, speed);//(x,y)的下一个方向再下一方向继续迭代
		}
}
void create2(int ** MAP, int x, int y, int Height, int Width)
{
	int c[4][2] = { 0,1,1,0,0,-1,-1,0 };
	int i, j, t;
	for (i = 0; i < 4; i++)
	{
		j = rand() % 4;
		t = c[i][0]; c[i][0] = c[j][0]; c[j][0] = t;
		t = c[i][1]; c[i][1] = c[j][1]; c[j][1] = t;
	}
	MAP[x][y] = Road;

	for (i = 0; i < 4; i++)
		if (MAP[x + 2 * c[i][0]][y + 2 * c[i][1]] == Wall)
		{
			MAP[x + c[i][0]][y + c[i][1]] = Road;
			create2(MAP, x + 2 * c[i][0], y + 2 * c[i][1], Height, Width);
		}
}
int get_key() //接收按键
{
	char c;
	while (c = getch())
	{
		if (c == 27) return Esc; //Esc
								 //if (c != -32)continue;
		c = getch();
		if (c == 72) return Up; //上
		if (c == 80) return Down; //下
		if (c == 75) return Left; //左
		if (c == 77) return Right; //右
	}
	return 0;
}
void game(int **Map, int Height, int Width)
{
	int x = 2, y = 1;		//初始位置在入口处
	int c;				//负责接收按键
	while (TRUE)
	{
		gotoxy(2 * y - 2, x - 1);
		printf("*");
		if ((x == Height - 1) && (y == Width))
		{
			system("CLS");
			gotoxy(2 * Width - 1, Height - 2);
			printf("Game Over 穿过迷宫（按任意键返回）");
			getch();
			break;
		}
		c = get_key();
		if (c == Esc)
		{
			gotoxy(Width + 3, Height + 3);
			printf("\n\n");
			printf("                                    \n");
			printf("这玩意也好意思开挂。（按回车继续你这无耻的行为）");
			getch();
			Point startP(x, y);
			Point endP(Height - 1, Width);
			stack<Point>  pointStack;
			mazePath(&Map[0][0], Height + 2, Width + 2, startP, endP, pointStack);

			//没有找到可行解
			if (pointStack.empty() == true)
				cout << "no right path" << endl;
			else {
				stack<Point> tmpStack;
				while (pointStack.empty() == false) {
					tmpStack.push(pointStack.top());
					pointStack.pop();
				}
				while (tmpStack.empty() == false) {
					Sleep(75);
					print(tmpStack.top().row, tmpStack.top().col);
					tmpStack.pop();
				}
			}
			Sleep(1500);
			system("CLS");
			printf("\n\nGame Over 你可以滚了（按回车滚粗）");
			getch();
			break;
		}
		switch (c)
		{
		case Up:    if (Map[x - 1][y] != Wall) { paint(Map, x, y); --x; break; }
		case Down:  if (Map[x + 1][y] != Wall) { paint(Map, x, y); ++x; break; }
		case Left:  if (Map[x][y - 1] != Wall) { paint(Map, x, y); --y; break; }
		case Right: if (Map[x][y + 1] != Wall) { paint(Map, x, y); ++y; break; }
		}
	}
}
void game2(int **Map, int Height, int Width)
{
	Map[Height - 1][Width] = 3;
	int x = 2, y = 1;		//初始位置在入口处
	int c;				//负责接收按键
	while (TRUE)
	{
		gotoxy(2 * y - 2, x - 1);
		printf("*");
		if ((x == Height - 1) && (y == Width))
		{
			system("CLS");
			gotoxy(2 * Width - 1, Height - 2);
			printf("Game Over 你可以滚了（按任意键滚粗）");
			getch();
			break;
		}
		c = get_key();
		if (c == Esc)
		{
			gotoxy(Width + 3, Height + 3);
			printf("\n\n");
			printf("                                                                        \n");
			printf("这玩意也好意思开挂。（按回车继续你这无耻的行为）");
			getch();
			int dx[] = { 0,1,0,-1 };//方向偏移量
			int dy[] = { 1,0,-1,0 };
			int direction; //出口标志
			int flag = FALSE;
			int now_x, now_y;
			int next_x, next_y;
			SqQueue sqq;
			SqStack sqs, sqsout;
			ElemType start, et;


			InitQueue(&sqq); //初始化队列sqq
			InitStack(&sqs); //初始化栈sqs
			InitStack(&sqsout); //初始化栈sqsout

			start.x = y;
			start.y = x;
			start.parent_x = -1;
			start.parent_y = -1;

			EnQueue(&sqq, start); //入队

			for (; (flag != TRUE) && (!QueueEmpty(sqq));)
			{
				GetHead(sqq, &et); //获取取队首元素
				now_x = et.x;
				now_y = et.y;
				for (direction = 0; direction < 4; direction++)
				{
					next_x = now_x + dx[direction];
					next_y = now_y + dy[direction];

					if (Map[next_y][next_x] == 0 || Map[next_y][next_x] == 3) //下一点可通过
					{
						et.x = next_x;
						et.y = next_y;
						et.parent_x = now_x; //下一点的路径上的前驱是当前点
						et.parent_y = now_y;
						EnQueue(&sqq, et); //将下一点入队

						if (Map[next_y][next_x] != 3)
						{
							Map[next_y][next_x] = STEPPED;
						}
					}

					if (Map[next_y][next_x] == 3) //如果下一个点是出口
					{
						flag = TRUE; //标志位置TRUE
						break; //路径找到退出循环
					}
				}
				DeQueue(&sqq, &et);//出队
				Push(&sqs, et);//奖所有出队的元素都将别压入栈sqs
			}

			if (QueueEmpty(sqq)) //尝试每条路径，若均无法通过，队列为空
			{
				printf("此迷宫无法通过!!!\n");
			}

			if (flag == TRUE) //找到路径
			{
				while (!QueueEmpty(sqq))
				{
					DeQueue(&sqq, &et);
					Push(&sqs, et);
				}

				Pop(&sqs, &start);
				Push(&sqsout, start);

				while (!StackEmpty(sqs))
				{
					Pop(&sqs, &et);
					if (et.x == start.parent_x && et.y == start.parent_y)
					{
						start = et;
						Push(&sqsout, et);
					}
				}
				while (!StackEmpty(sqsout))
				{
					Pop(&sqsout, &et);
					//printf("(%d,%d)\t", et.x, et.y);
					Sleep(75);
					print(et.y, et.x);
				}
				Sleep(1500);
				system("CLS");
				printf("\n\nGame Over 你可以滚了（按回车滚粗）");
				getch();
				break;
			}
		}
		switch (c)
		{
		case Up:    if (Map[x - 1][y] != Wall) { paint(Map, x, y); --x; break; }
		case Down:  if (Map[x + 1][y] != Wall) { paint(Map, x, y); ++x; break; }
		case Left:  if (Map[x][y - 1] != Wall) { paint(Map, x, y); --y; break; }
		case Right: if (Map[x][y + 1] != Wall) { paint(Map, x, y); ++y; break; }
		}
	}
}
void hidden()//隐藏光标函数
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = 1;
	SetConsoleCursorInfo(hOut, &cci);
}
Point getAdjacentNotVisitedNode(bool** mark, Point point, int m, int n) {
	Point resP(-1, -1);
	if (point.row - 1 >= 0 && mark[point.row - 1][point.col] == false) {    //上节点未遍历过
		resP.row = point.row - 1;
		resP.col = point.col;
		return resP;
	}
	if (point.col + 1<n&&mark[point.row][point.col + 1] == false) {         //右节点未遍历过
		resP.row = point.row;
		resP.col = point.col + 1;
		return resP;
	}
	if (point.row + 1<m&&mark[point.row + 1][point.col] == false) {         //下节点未遍历过
		resP.row = point.row + 1;
		resP.col = point.col;
		return resP;
	}
	if (point.col - 1 >= 0 && mark[point.row][point.col - 1] == false) {     //左节点未遍历过
		resP.row = point.row;
		resP.col = point.col - 1;
		return resP;
	}
	return resP;
}
void mazePath(void* maze, int m, int n, const Point& startP, Point endP, stack<Point>& pointStack) {
	//将给定的任意列数的二维数组还原为指针数组，以支持下标操作
	int** maze2d = new int*[m];
	for (int i = 0; i<m; ++i) {
		maze2d[i] = (int*)maze + i*n;
	}

	if (maze2d[startP.row][startP.col] == 1 || maze2d[endP.row][endP.col] == 1)
		return;                    //输入错误

								   //建立各个节点访问标记
	bool** mark = new bool*[m];
	for (int i = 0; i<m; ++i) {
		mark[i] = new bool[n];
	}
	for (int i = 0; i<m; ++i) {
		for (int j = 0; j<n; ++j) {
			mark[i][j] = *((int*)maze + i*n + j);//根据maze[][]里面的值判定是false还是true
		}										 //maze[][]即原来的Map[][],里面若是路径，则为false(0)
	}

	//将起点入栈
	pointStack.push(startP);
	mark[startP.row][startP.col] = true;

	//栈不空并且栈顶元素不为结束节点
	while (pointStack.empty() == false && pointStack.top() != endP) {
		Point adjacentNotVisitedNode = getAdjacentNotVisitedNode(mark, pointStack.top(), m, n);
		if (adjacentNotVisitedNode.row == -1) {         //没有未被访问的相邻节点
			pointStack.pop();                           //回溯到上一个节点
			continue;
		}

		//入栈并设置访问标志为true
		mark[adjacentNotVisitedNode.row][adjacentNotVisitedNode.col] = true;
		pointStack.push(adjacentNotVisitedNode);
	}
}//mazePath这个函数，遍历Map[][]的空格路径false(0)，找到其中一条可以通向endP的路径保存再这个pointStack中。
void print(int x, int y)
{
	gotoxy(2 * y - 2, x - 1);
	printf("*");
}



Status InitQueue(SqQueue *Q)//初始化队列
{
	Q->base = (ElemType *)malloc(MAX * sizeof(ElemType));
	if (!Q->base)
	{
		exit(OVERFLOW);
	}
	Q->front = Q->rear = 0;
	return TRUE;
}
Status QueueEmpty(SqQueue Q)
{
	if (Q.front == Q.rear)
	{
		return TRUE;
	}
	return FALSE;
}
Status GetHead(SqQueue Q, ElemType *e)
{
	if (Q.front == Q.rear)
	{
		return ERROR;
	}
	*e = Q.base[Q.front];
	return TRUE;
}
Status EnQueue(SqQueue *Q, ElemType e)
{
	if (Q->rear>MAX - 1)//队列满
	{
		return ERROR;
	}
	Q->base[Q->rear] = e;
	(Q->rear)++;
	return TRUE;
}
Status DeQueue(SqQueue *Q, ElemType *e)
{
	if (Q->front == Q->rear)  //队列空                                                                                                              
	{
		return ERROR;
	}
	*e = Q->base[Q->front];
	(Q->front)++;
	return TRUE;
}
Status InitStack(SqStack *s)
{
	s->top = -1;
	s->base = 0;
	s->count = 0;
	//
	return TRUE;
}
Status StackEmpty(SqStack s)
{
	if (s.count != 0)
	{
		return FALSE;
	}
	return TRUE;
}
Status Push(SqStack *s, ElemType e)
{
	s->top++;
	s->container[s->top] = e;
	s->count++;
	return TRUE;
}
Status Pop(SqStack *s, ElemType *e)
{
	if (s->top<s->base)
	{
		return ERROR;
	}
	*e = s->container[s->top];
	s->top--;
	s->count--;
	return TRUE;
}