#include<iostream>
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
				maze.initMazeNode(data, i, j);
			}
		}

		// �����Թ����нڵ�ķ��������״̬
		maze.adjustMaze();
		
		// Ѱ���Թ�·��
		maze.findMazePath();

		//maze.showMaze();

		cout << "Ѱ�ҵ����Թ�·������ ��" << endl;
		
		// ��ӡѰ�ҽṹ
		maze.showResult();
		
		return 0;
}

