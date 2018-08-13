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
//����Ϊ�������������ֽṹ��Ķ���
//  �����ڵ�ṹ��  
struct Point
{
	int row;
	int col;

	Point(int x, int y) {
		this->row = x;
		this->col = y;
	}

	bool operator!=(const Point& rhs) {							//���ȺŲ���������
		if (this->row != rhs.row || this->col != rhs.col)       //�жϳ�����Ƿ�����Թ���С  
			return true;
		return false;
	}
};
//      ���嵱ǰ������Ľṹ��
typedef struct
{
	int x, y;
	int parent_x, parent_y;
}QNode, *QueuePtr;
typedef QNode ElemType;//��һԪ�ص�
typedef struct SqQueue
{
	ElemType * base;
	int front;
	int rear;
}SqQueue;//Ԫ�ص���нṹ��
typedef struct
{
	int top, base, count;
	ElemType container[19000];
}SqStack;//Ԫ�ص�ջ��container����
Status InitStack(SqStack *s);
Status StackEmpty(SqStack s);
Status InitQueue(SqQueue *Q);//��ʼ������          
Status QueueEmpty(SqQueue Q);//�ж϶����Ƿ�Ϊ��    
Status GetHead(SqQueue Q, ElemType *e);//ȡ����ͷԪ��  
Status EnQueue(SqQueue *Q, ElemType e);//���       
Status DeQueue(SqQueue *Q, ElemType *e);//����     
Status Push(SqStack *s, ElemType e);//��ջ       
Status Pop(SqStack *s, ElemType *e);//��ջ       
void game2(int **Map, int Height, int Width);//��������������Թ����Ĳ���   
void gotoxy(int x, int y);												//�ƶ����ĺ���  
void paint(int **Map, int x, int y);									//��ӡ�Թ�ǽ��·�ĺ���  
void paint2(int **Map, int x, int y);									//��ӡ�Թ�·���ĺ���  
int ** createMap(int Width, int Height);								//������ά���� ���ڴ����Թ� 
void create1(int ** MAP, int x, int y, int Height, int Width, int speed);//��������Թ����� 
void create2(int ** MAP, int x, int y, int Height, int Width);			//��������Թ����� 
int get_key();															//���ܷ�����ĺ��� 
void game(int **Map, int Height, int Width);							//��Ϸ��������     
void hidden();															//���ع��ĺ���   
void print(int x, int y);												//��ӡ·������     
void printM();															//��ӡ�˵�����     
Point getAdjacentNotVisitedNode(bool** mark, Point point, int m, int n);//��ȡ����δ�����ʵĽڵ�ĺ���   
void mazePath(void* maze, int m, int n, const Point& startP, Point endP, stack<Point>& pointStack);//������ά�Թ��������·���ĺ�����DFS�� 

				////////////////////////////////////////////////////////////////
				/**************************************************************/
				////////////////////////////////////////////////////////////////
				//����Ϊ������
int main()
{
	int choose = 0;
	srand((unsigned)time(NULL));
	while (1)
	{
		system("CLS");
		printM();
		scanf("%d", &choose);//�˴����������÷�ֹ���벻��1-4֮�������������������Ĵ�ʩ��
		if (choose == 1)
		{
			hidden();
			system("CLS");
			int i = 0, j = 0;
			//�����к���
			int Height = 0, Width = 0, speed = 0;
			printf("���������������Լ���ͨ���ڵ��ʱ����λms�����Կո�������û��س������н���������������\n");
			scanf("%d %d %d", &Height, &Width, &speed);
			system("CLS");
			//���ɴ����Թ�������
			int ** Map = createMap(Width, Height);
			//��ʼ���Թ�
			for (i = 0; i <= Height + 1; ++i)
				for (j = 0; j <= Width + 1; ++j)
					if (i == 0 || i == Height + 1 || j == 0 || j == Width + 1)
						Map[i][j] = Road;
					else Map[i][j] = Wall;
					//�����Թ�
					for (i = 1; i <= Height; i++)
						for (j = 1; j <= Width; j++) //�����Թ�
							paint(Map, i, j);
					create1(Map, 2 * (rand() % (Height / 2) + 1), 2 * (rand() % (Width / 2) + 1), Height, Width, speed);
					//�߽紦��
					for (i = 0; i <= Height + 1; ++i)
					{
						Map[i][0] = Wall;
						Map[i][Width + 1] = Wall;
					}
					//�߽紦��
					for (j = 0; j <= Width + 1; ++j)
					{
						Map[0][j] = Wall;
						Map[Height + 1][j] = Wall;
					}
					//�Թ����������
					Map[2][1] = Start;
					Map[Height - 1][Width] = End;
					for (i = 1; i <= Height; i++)
						for (j = 1; j <= Width; j++) //�����Թ�
							paint(Map, i, j);
					gotoxy(0, 1);
					printf("��");
					gotoxy(Width * 2 - 2, Height - 2);
					printf("��");
					printf("\n\n��������ص��˵�");
					getch();

		}
		else if (choose == 2)
		{
			void hidden();
			int i = 0, j = 0;
			srand((unsigned)time(NULL));
			//�����к���
			int Height = 0, Width = 0;
			system("CLS");
			printf("�����������������Կո���������û��س�,ֻ׼����������\n");
			scanf("%d %d", &Height, &Width);
			system("CLS");
			//���ɴ����Թ�������
			int ** Map = createMap(Width, Height);
			//��ʼ���Թ�
			for (i = 0; i <= Height + 1; ++i)
				for (j = 0; j <= Width + 1; ++j)
					if (i == 0 || i == Height + 1 || j == 0 || j == Width + 1)
						Map[i][j] = Road;
					else Map[i][j] = Wall;
					//�����Թ�
					create2(Map, 2 * (rand() % (Height / 2) + 1), 2 * (rand() % (Width / 2) + 1), Height, Width);
					//�߽紦��
					for (i = 0; i <= Height + 1; ++i)
					{
						Map[i][0] = Wall;
						Map[i][Width + 1] = Wall;
					}
					//�߽紦��
					for (j = 0; j <= Width + 1; ++j)
					{
						Map[0][j] = Wall;
						Map[Height + 1][j] = Wall;
					}
					//�Թ����������
					Map[2][1] = Start;
					Map[Height - 1][Width] = End;
					Sleep(500);
					for (i = 1; i <= Height; i++)
						for (j = 1; j <= Width; j++) //�����Թ�
							paint(Map, i, j);
					gotoxy(0, 1);
					printf("��");
					gotoxy(Width * 2 - 2, Height - 2);
					printf("��");
					gotoxy(Width * 2 - 2, Height);
					printf("\n\n");
					printf("�������Ҽ��ٿ�*�ţ���ESC����·��\n���������ʼ(ESCû����ఴ���ξ���)");
					getch();
					game(Map, Height, Width);
		}
		else if (choose == 3)
		{
			void hidden();
			int i = 0, j = 0;
			srand((unsigned)time(NULL));
			//�����к���
			int Height = 0, Width = 0;
			system("CLS");
			printf("�����������������Կո���������û��س�,ֻ׼����������\n");
			scanf("%d%d", &Height, &Width);
			system("CLS");
			//���ɴ����Թ�������
			int ** Map = createMap(Width, Height);
			//��ʼ���Թ�
			for (i = 0; i <= Height + 1; ++i)
				for (j = 0; j <= Width + 1; ++j)
					if (i == 0 || i == Height + 1 || j == 0 || j == Width + 1)
						Map[i][j] = Road;
					else Map[i][j] = Wall;
					//�����Թ�
					create2(Map, 2 * (rand() % (Height / 2) + 1), 2 * (rand() % (Width / 2) + 1), Height, Width);
					//�߽紦��
					for (i = 0; i <= Height + 1; ++i)
					{
						Map[i][0] = Wall;
						Map[i][Width + 1] = Wall;
					}
					//�߽紦��
					for (j = 0; j <= Width + 1; ++j)
					{
						Map[0][j] = Wall;
						Map[Height + 1][j] = Wall;
					}
					//�Թ����������
					Map[2][1] = Start;
					Map[Height - 1][Width] = End;
					Sleep(500);
					for (i = 1; i <= Height; i++)
						for (j = 1; j <= Width; j++) //�����Թ�
							paint(Map, i, j);
					gotoxy(0, 1);
					printf("��");
					gotoxy(Width * 2 - 2, Height - 2);
					printf("��");
					gotoxy(Width * 2 + 3, Height);
					printf("\n\n");
					printf("�������Ҽ��ٿ��ʺţ���ESC���ֽ���ָ\n���������ʼ(ESCû����ఴ���ξ���)");
					getch();
					game2(Map, Height, Width);

		}
		else if (choose == 4) exit(0);
		else if ((choose != 1) && (choose != 2) && (choose != 3) && (choose != 4))
		{
			printf("\n������1-4֮�������");
		}
	}
	return 0;
}


////////////////////////////////////////////////////////////////
/**************************************************************/
////////////////////////////////////////////////////////////////
//����Ϊ�����Ķ���
void printM()
{
	//gotoxy(32, 64);
	printf(" *************************************************\n");
	printf(" * �����Թ�                                      *\n");

	printf(" * By Jason_Lee  ���ϿƼ���ѧ��ϢѧԺ            *\n");
	printf(" *************************************************\n");
	printf("   1. �Թ�������ʾ                                \n");
	printf("   2. ��������������Թ�                          \n");
	printf("   3. ��������������Թ�                          \n");
	printf("   4. �˳�                                        \n");
	printf("   Please Choose 1-4 :\n");
	printf(" *************************************************\n");
}
void gotoxy(int x, int y)//���λ��
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void paint(int **Map, int x, int y)
{
	gotoxy(2 * y - 2, x - 1);//ʹ�õ�unicode�ַ���ռ2���ַ�λ�����������2.
	switch (Map[x][y])		 //����Ϊ��ԭ�㿪ʼ���ʺ��������һ��2*(y-1)��
	{

	case Wall:
		printf("��"); break; //��ǽ
	case Road:
		printf("��"); break; //��·
	}
}
void paint2(int **Map, int x, int y)
{
	gotoxy(2 * y - 2, x - 1);
	printf("��"); //��·
}

int ** createMap(int Width, int Height)//����(width+2)*(height+2)�Ķ�ά����
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
void create1(int ** MAP, int x, int y, int Height, int Width, int speed)//�����Թ�·������
{
	int c[4][2] = { 0,1,1,0,0,-1,-1,0 };
	int i, j, t;
	for (i = 0; i < 4; i++)//���������ķ���
	{
		j = rand() % 4;
		t = c[i][0]; c[i][0] = c[j][0]; c[j][0] = t;
		t = c[i][1]; c[i][1] = c[j][1]; c[j][1] = t;
	}
	MAP[x][y] = Road;
	Sleep(speed);
	paint(MAP, x, y);
	for (i = 0; i < 4; i++)
		if (MAP[x + 2 * c[i][0]][y + 2 * c[i][1]] == Wall)//(x,y)����һ����������һ���򣬲�����ʹ�(x,y)����
		{
			MAP[x + c[i][0]][y + c[i][1]] = Road;
			Sleep(speed);
			paint(MAP, x + c[i][0], y + c[i][1]);
			create1(MAP, x + 2 * c[i][0], y + 2 * c[i][1], Height, Width, speed);//(x,y)����һ����������һ�����������
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
int get_key() //���հ���
{
	char c;
	while (c = getch())
	{
		if (c == 27) return Esc; //Esc
								 //if (c != -32)continue;
		c = getch();
		if (c == 72) return Up; //��
		if (c == 80) return Down; //��
		if (c == 75) return Left; //��
		if (c == 77) return Right; //��
	}
	return 0;
}
void game(int **Map, int Height, int Width)
{
	int x = 2, y = 1;		//��ʼλ������ڴ�
	int c;				//������հ���
	while (TRUE)
	{
		gotoxy(2 * y - 2, x - 1);
		printf("*");
		if ((x == Height - 1) && (y == Width))
		{
			system("CLS");
			gotoxy(2 * Width - 1, Height - 2);
			printf("Game Over �����Թ�������������أ�");
			getch();
			break;
		}
		c = get_key();
		if (c == Esc)
		{
			gotoxy(Width + 3, Height + 3);
			printf("\n\n");
			printf("                                    \n");
			printf("������Ҳ����˼���ҡ������س����������޳ܵ���Ϊ��");
			getch();
			Point startP(x, y);
			Point endP(Height - 1, Width);
			stack<Point>  pointStack;
			mazePath(&Map[0][0], Height + 2, Width + 2, startP, endP, pointStack);

			//û���ҵ����н�
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
			printf("\n\nGame Over ����Թ��ˣ����س����֣�");
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
	int x = 2, y = 1;		//��ʼλ������ڴ�
	int c;				//������հ���
	while (TRUE)
	{
		gotoxy(2 * y - 2, x - 1);
		printf("*");
		if ((x == Height - 1) && (y == Width))
		{
			system("CLS");
			gotoxy(2 * Width - 1, Height - 2);
			printf("Game Over ����Թ��ˣ�����������֣�");
			getch();
			break;
		}
		c = get_key();
		if (c == Esc)
		{
			gotoxy(Width + 3, Height + 3);
			printf("\n\n");
			printf("                                                                        \n");
			printf("������Ҳ����˼���ҡ������س����������޳ܵ���Ϊ��");
			getch();
			int dx[] = { 0,1,0,-1 };//����ƫ����
			int dy[] = { 1,0,-1,0 };
			int direction; //���ڱ�־
			int flag = FALSE;
			int now_x, now_y;
			int next_x, next_y;
			SqQueue sqq;
			SqStack sqs, sqsout;
			ElemType start, et;


			InitQueue(&sqq); //��ʼ������sqq
			InitStack(&sqs); //��ʼ��ջsqs
			InitStack(&sqsout); //��ʼ��ջsqsout

			start.x = y;
			start.y = x;
			start.parent_x = -1;
			start.parent_y = -1;

			EnQueue(&sqq, start); //���

			for (; (flag != TRUE) && (!QueueEmpty(sqq));)
			{
				GetHead(sqq, &et); //��ȡȡ����Ԫ��
				now_x = et.x;
				now_y = et.y;
				for (direction = 0; direction < 4; direction++)
				{
					next_x = now_x + dx[direction];
					next_y = now_y + dy[direction];

					if (Map[next_y][next_x] == 0 || Map[next_y][next_x] == 3) //��һ���ͨ��
					{
						et.x = next_x;
						et.y = next_y;
						et.parent_x = now_x; //��һ���·���ϵ�ǰ���ǵ�ǰ��
						et.parent_y = now_y;
						EnQueue(&sqq, et); //����һ�����

						if (Map[next_y][next_x] != 3)
						{
							Map[next_y][next_x] = STEPPED;
						}
					}

					if (Map[next_y][next_x] == 3) //�����һ�����ǳ���
					{
						flag = TRUE; //��־λ��TRUE
						break; //·���ҵ��˳�ѭ��
					}
				}
				DeQueue(&sqq, &et);//����
				Push(&sqs, et);//�����г��ӵ�Ԫ�ض�����ѹ��ջsqs
			}

			if (QueueEmpty(sqq)) //����ÿ��·���������޷�ͨ��������Ϊ��
			{
				printf("���Թ��޷�ͨ��!!!\n");
			}

			if (flag == TRUE) //�ҵ�·��
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
				printf("\n\nGame Over ����Թ��ˣ����س����֣�");
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
void hidden()//���ع�꺯��
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = 1;
	SetConsoleCursorInfo(hOut, &cci);
}
Point getAdjacentNotVisitedNode(bool** mark, Point point, int m, int n) {
	Point resP(-1, -1);
	if (point.row - 1 >= 0 && mark[point.row - 1][point.col] == false) {    //�Ͻڵ�δ������
		resP.row = point.row - 1;
		resP.col = point.col;
		return resP;
	}
	if (point.col + 1<n&&mark[point.row][point.col + 1] == false) {         //�ҽڵ�δ������
		resP.row = point.row;
		resP.col = point.col + 1;
		return resP;
	}
	if (point.row + 1<m&&mark[point.row + 1][point.col] == false) {         //�½ڵ�δ������
		resP.row = point.row + 1;
		resP.col = point.col;
		return resP;
	}
	if (point.col - 1 >= 0 && mark[point.row][point.col - 1] == false) {     //��ڵ�δ������
		resP.row = point.row;
		resP.col = point.col - 1;
		return resP;
	}
	return resP;
}
void mazePath(void* maze, int m, int n, const Point& startP, Point endP, stack<Point>& pointStack) {
	//�����������������Ķ�ά���黹ԭΪָ�����飬��֧���±����
	int** maze2d = new int*[m];
	for (int i = 0; i<m; ++i) {
		maze2d[i] = (int*)maze + i*n;
	}

	if (maze2d[startP.row][startP.col] == 1 || maze2d[endP.row][endP.col] == 1)
		return;                    //�������

								   //���������ڵ���ʱ��
	bool** mark = new bool*[m];
	for (int i = 0; i<m; ++i) {
		mark[i] = new bool[n];
	}
	for (int i = 0; i<m; ++i) {
		for (int j = 0; j<n; ++j) {
			mark[i][j] = *((int*)maze + i*n + j);//����maze[][]�����ֵ�ж���false����true
		}										 //maze[][]��ԭ����Map[][],��������·������Ϊfalse(0)
	}

	//�������ջ
	pointStack.push(startP);
	mark[startP.row][startP.col] = true;

	//ջ���ղ���ջ��Ԫ�ز�Ϊ�����ڵ�
	while (pointStack.empty() == false && pointStack.top() != endP) {
		Point adjacentNotVisitedNode = getAdjacentNotVisitedNode(mark, pointStack.top(), m, n);
		if (adjacentNotVisitedNode.row == -1) {         //û��δ�����ʵ����ڽڵ�
			pointStack.pop();                           //���ݵ���һ���ڵ�
			continue;
		}

		//��ջ�����÷��ʱ�־Ϊtrue
		mark[adjacentNotVisitedNode.row][adjacentNotVisitedNode.col] = true;
		pointStack.push(adjacentNotVisitedNode);
	}
}//mazePath�������������Map[][]�Ŀո�·��false(0)���ҵ�����һ������ͨ��endP��·�����������pointStack�С�
void print(int x, int y)
{
	gotoxy(2 * y - 2, x - 1);
	printf("*");
}



Status InitQueue(SqQueue *Q)//��ʼ������
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
	if (Q->rear>MAX - 1)//������
	{
		return ERROR;
	}
	Q->base[Q->rear] = e;
	(Q->rear)++;
	return TRUE;
}
Status DeQueue(SqQueue *Q, ElemType *e)
{
	if (Q->front == Q->rear)  //���п�                                                                                                              
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