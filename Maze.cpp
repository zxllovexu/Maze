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
	cout << "�������Թ�·������������";
	int row, col;
	cin >> row >> col;
	Maze maze(row, col);

	cout << "�������Թ��ľ���·����Ϣ(0��ʾ���ߣ�1��ʾ������)��" << endl;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			int data;
			cin >> data;
			maze.initMazeNode(i, j, data);
		}
	}

	// �����Թ����нڵ�ķ��������״̬
	maze.adjustMaze();

	// Ѱ���Թ�·��
	maze.findMazePath();

	printf("\n");

	// ��ӡѰ�ҽṹ
	maze.showResult();

	return 0;
}