/*
0 0 0 0 0
0 1 1 0 1
0 0 0 0 1
0 1 0 1 0
1 0 0 0 0
*/
#include<iostream>
#include<stdio.h>
#include"Maze.h"
using namespace std;

int main()
{
	cout << "请输入迷宫路径的行列数：";
	int row, col;
	cin >> row >> col;
	Maze maze(row, col);

	cout << "请输入迷宫的具体路径信息(0表示能走，1表示不能走)：" << endl;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			int data;
			cin >> data;
			maze.initMazeNode(i, j, data);
		}
	}

	// 调整迷宫所有节点的方向的行走状态
	maze.adjustMaze();

	// 寻找迷宫路径
	maze.findMazePath();

	printf("\n");

	// 打印寻找结构
	maze.showResult();

	return 0;
}