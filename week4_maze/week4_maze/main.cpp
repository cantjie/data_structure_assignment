#include <cstdio>
#include <iostream>
#include<stdlib.h>
#include<Windows.h>
#define MAZE_SIZE 10
#define SLEEP_TIME 500 //毫秒 1000毫秒=1秒
using namespace std;
//节点的定义
class Node {
public:
	int x;
	int y;
};

//栈的定义
class Stack {
private:
	int top;
	int maxsize;
	Node node[100];
public:
	Stack() {
		maxsize = 100;
		top = 0;
	}
	bool IsEmpty() { return top == 0; }
	bool IsFull() { return top == maxsize - 1; }
	bool Len() { return top; }
	Node GetTop();
	Node Pop();
	bool Push(int x, int y);
	bool Push(Node node);//我应该再定义一个这个函数。
};

//迷宫的定义
class Maze {
private:
	int maze[MAZE_SIZE][MAZE_SIZE];
	Node end_node;//终点
	Node start_node;//起点
public:
	Maze() {

		end_node.x = MAZE_SIZE - 1;
		end_node.y = MAZE_SIZE - 1;
		start_node.x = 0;
		start_node.y = 0;
		//for (int i = 0; i < MAZE_SIZE; i++) {
		//	for (int j = 0; j < MAZE_SIZE; j++) {
		//		maze[i][j] = 1;
		//	}
		//}
		int a[MAZE_SIZE][MAZE_SIZE] = { 
		{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 1, 0, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 1, 0, 1 },
		{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 0, 1, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 } };
		for (int i = 0; i < MAZE_SIZE; i++) {
			for (int j = 0; j < MAZE_SIZE; j++) {
				maze[i][j] = a[i][j];
			}
		}

	}
	bool IsFinished(int row, int col) { return (row == end_node.x && col == end_node.y); }
	bool PrintMaze();
	bool PrintMaze(int row, int col, char w = 0);
	bool ChangeUnit(int row, int col, int w);
	int HasWay(int row, int col);
	void Process();
};

bool Maze::ChangeUnit(int row, int col, int w) {
	if (row<0 || col < 0 || row > MAZE_SIZE - 1 || col>MAZE_SIZE - 1) return false;
	maze[row][col] = w;
	return true;
}
bool Maze::PrintMaze() {
	system("cls");
	for (int i = 0; i < MAZE_SIZE; i++) {
		for (int j = 0; j < MAZE_SIZE; j++) {
			//4← 6→ 8↑ 2↓
			switch (maze[i][j])
			{
			case 2:case 0: printf("  "); break;
			case 1: printf("##"); break;
			//case 2: printf("↓"); break;
			//case 4: printf("←"); break;
			//case 6: printf("→"); break;
			//case 8: printf("↑"); break;
			default:
				break;
			}
		}
		printf("\n");
	}
	return true;
}
bool Maze::PrintMaze(int row, int col, char w) {
	system("cls");
	for (int i = 0; i < MAZE_SIZE; i++) {
		for (int j = 0; j < MAZE_SIZE; j++) {
			if (i == row && j == col) {
				w == 0 ? printf("·") : printf("%c", w);
				continue;
			}
			switch (maze[i][j])
			{
			case 2:case 0: printf("  "); break;
			case 1: printf("##"); break;
			default:
				break;
			}
		}
		printf("\n");
	}
	return true;
}
//判断当前节点是否有路可走， 2468 分别对应下左右上可行，0表示不可行，1表示已到达终点
//以右为第一个节点，顺时针查找可行路径
int Maze::HasWay(int row, int col) {
	if (IsFinished(row,col)) {
		return 1;
	}
	else{
		if (col + 1 < MAZE_SIZE) {
			if (maze[row][col + 1] == 0) return 6;
		}
		if (row + 1 < MAZE_SIZE) {
			if (maze[row + 1][col] == 0)return 2;
		}
		if (col - 1 > 0) {
			if (maze[row][col - 1] == 0)return 4;
		}
		if (row - 1 > 0) {
			if (maze[row - 1][col] == 0)return 8;
		}
		return 0;
	}
}
//核心算法
void Maze::Process() {
	int dir;//direction
	Stack *MyStack = new Stack();
	MyStack->Push(start_node.x, start_node.y);
	Node curr_node = MyStack->GetTop();
	while (!IsFinished(curr_node.x, curr_node.y)) {
		maze[curr_node.x][curr_node.y] = 2;
		if (dir = HasWay(curr_node.x, curr_node.y)) {
			//TODO 这里好像缺少一点防止溢出的处理
			switch (dir)
			{
			case 1: printf("已到达终点"); break;
			case 2:
				curr_node.x += 1;
				break;
			case 4:
				curr_node.y -= 1;
				break;
			case 6:
				curr_node.y += 1;
				break;
			case 8:
				curr_node.x -= 1;
				break;
			default:
				break;
			}
			MyStack->Push(curr_node.x, curr_node.y);
			PrintMaze(curr_node.x, curr_node.y);
			Sleep(SLEEP_TIME);
		}
		else
		{
			while ((dir = HasWay(curr_node.x, curr_node.y) == 0)) {
				curr_node = MyStack->Pop();
				PrintMaze(curr_node.x, curr_node.y);
				Sleep(SLEEP_TIME);
			}
		}
	}
	printf("Finished");
}

Node Stack::GetTop() {
	if (!IsEmpty())
		return node[top-1];
	else {
		printf("这个玩应可能无解");
		exit(0);
	}
}
Node Stack::Pop() {
	if (!IsEmpty()) {
		top--;
		return node[top];
	}
	else{
		printf("这个玩应可能无解");
		exit(0);
	}
}
bool Stack::Push(int x, int y) {
	if (!IsFull()) {
		node[top].x = x;
		node[top].y = y;
		top++;
		return true;
	}
	else{
		printf("空间开辟少了，不足以储存节点数");
		return false;
	}
}

int main()
{
	Maze *MyMaze = new Maze();
	MyMaze->Process();
}