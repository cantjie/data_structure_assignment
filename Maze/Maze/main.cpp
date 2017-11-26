#include<stdio.h>
#include<stdlib.h>
#include<stack>
#define MAX_SIZE 100
using namespace std;


/**************************/
/*    Auther Cantjie      */
/*走出迷宫之深度优先搜索版*/
/**************************/

class Node {
private:
	int x;
	int y;
public:
	void setPos(int _x, int _y) {
		x = _x;
		y = _y;
	}
	void incrementX() { x++; }
	void incrementY() { y++; }
	void decrementX() { x--; }
	void decrementY() { y--; }
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	bool operator!=(const Node &another_node) const;
	bool operator==(const Node & another_node) const;
};

bool Node::operator!=(const Node & another_node) const
{
	if (another_node.x == x && another_node.y == y) {
		return false;
	}
	else {
		return true;
	}
}
bool Node::operator==(const Node & another_node) const
{
	if (another_node.x == x && another_node.y == y) {
		return true;
	}
	else {
		return false;
	}
}


class Maze {
private:
	char maze[MAX_SIZE][MAX_SIZE];
	Node endNode;
	Node startNode;
	int row_size;
	int col_size;
	int HasWay(int row, int col);
public:
	Maze() {
		int m, n;
		int i = 0;
		int j = 0;
		scanf("%d %d", &n, &m);
		row_size = n;
		col_size = m;
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				scanf("%c", &maze[i][j]);
				switch (maze[i][j])
				{
				case '\n':
					j--;
					break;
				case 'S':
					startNode.setPos(i, j);
					break;
				case 'T':
					endNode.setPos(i, j);
					break;
				default:
					break;
				}
			}
		}
	}
	int process();
	void PrintMaze();
};

int Maze::HasWay(int row, int col) {
	if (col + 1 < col_size) {
		if (maze[row][col + 1] == '.' || maze[row][col + 1] == 'T')return 6;
	}
	if (row + 1 < row_size) {
		if (maze[row + 1][col] == '.' || maze[row + 1][col] == 'T')return 2;
	}
	if (col - 1 >= 0) {
		if (maze[row][col - 1] == '.' || maze[row][col - 1] == 'T')return 4;
	}
	if (row - 1 >= 0) {
		if (maze[row - 1][col] == '.' || maze[row - 1][col] == 'T')return 8;
	}
	return 0;
}

int Maze::process() {
	stack <Node>MyStack;
	int count = 0;
	Node curr_node;
	int dir;
	curr_node = startNode;

	while (curr_node != endNode) {
		dir = HasWay(curr_node.getX(), curr_node.getY());
		if (dir) {
			maze[curr_node.getX()][curr_node.getY()] = count;
			switch (dir)
			{
			case 2:
				curr_node.incrementX();
				break;
			case 6:
				curr_node.incrementY();
				break;
			case 4:
				curr_node.decrementY();
				break;
			case 8:
				curr_node.decrementX();
				break;
			default:
				break;
			}
			count++;
			MyStack.push(curr_node);
		}
		else {
			curr_node = MyStack.top();
			MyStack.pop();
			while ((dir = HasWay(curr_node.getX(), curr_node.getY())) == 0) {
				maze[curr_node.getX()][curr_node.getY()] = 'X';
				curr_node = MyStack.top();
				MyStack.pop();
				count--;
			}
		}
	}
	//return printf("%d\n", MyStack.size());
	//return MyStack.size();
	return count;
}

void Maze::PrintMaze() {
	int i = 0, j = 0;
	for (i = 0; i < row_size; i++) {
		for (j = 0; j < col_size; j++) {
			//84 35 35  0  1 35
			//	10  9 35 35  2 35
			//	35  8 35  4  3 35
			//	88  7  6  5 35 35
			if (maze[i][j] == 35 || maze[i][j] == 84 || maze[i][j] == 88 || maze[i][j] == 46) {
				printf("%3c", maze[i][j]);
			}
			else {
				printf("%3d", maze[i][j]);
			}
		}
		printf("\n");
	}
}

int main() {
	int count = 0;
	Maze *MyMaze = new Maze();
	count = MyMaze->process();
	MyMaze->PrintMaze();
	printf("%d", count);
	return 0;
}

