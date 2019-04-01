
#ifndef MAZE_H
#define MAZE_H
#include<iostream>

using namespace std;
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int WAY_NUM = 4;
const int YES = 5;
const int NO = 6;
class MazeNode
{
public:
	MazeNode()
	{
		for (int i = 0; i < WAY_NUM; i++)
		{
			mstate[i] = NO;
		}
	}
	void SetNode(int i,int j,int data)
	{
		mx = i;
		my = j;
		mval = data;
	}
	void SetState(int dir,int way)
	{
		mstate[dir] = way;
	}

	int GetVal()
	{
		return mval;
	}

	int GetX()
	{
		return mx;
	}

	int GetY()
	{
		return my;
	}

	int GetState(int dir)
	{
		return mstate[dir];
	}

	void SetVal(int data)
	{
		mval = data;
	}
private:
	int mval;
	int mx;
	int my;
	int mstate[WAY_NUM];
};

class CStack
{
public:
	CStack(int size = 30)
	{
		msize = size;
		mtop = -1;
		mpstack = new MazeNode[msize];
	}

	~CStack()
	{
		delete[]mpstack;
	}

	void Push(MazeNode &src)
	{
		if (Full())
		{
			Resize();
		}
		mpstack[++mtop] = src;
	}

	void Pop()
	{
		mtop--;
	}
	
	bool Full()
	{
		return mtop == msize - 1;
	}

	bool Empty()
	{
		return mtop == -1;
	}

	MazeNode GetTop()
	{
		return mpstack[mtop];
    }



private:
	int mtop;
	int msize;
	MazeNode *mpstack;
	void Resize()
	{
		
	}
};
class Maze
{
public:
	Maze(int row,int col)
	{
		mrow = row;
		mcol = col;
		mpMaze = new MazeNode*[mrow];
		for (int i = 0; i < mcol; i++)
		{
			mpMaze[i] = new MazeNode[mcol];
		}
	}

	~Maze()
	{
		for (int i = 0; i < mcol; i++)
		{
			delete[]mpMaze[i];
		}
		delete[]mpMaze;
		mpMaze = nullptr;
	}

	void initMazeNode(int i, int j,int data)
	{
		mpMaze[i][j].SetNode(i, j, data);
	 }

	void adjustMaze()
	{
		for (int i = 0; i < mrow; i++)
		{
			for (int j = 0; j < mcol; j++)
			{
				if (i != 0 && mpMaze[i-1][j].GetVal() == 0)
				{
					mpMaze[i][j].SetState(UP,YES);
				}
				if (j != 0 && mpMaze[i][j - 1].GetVal() == 0)
				{
					mpMaze[i][j].SetState(LEFT,YES);
				}
				if (i != mrow - 1 && mpMaze[i+1][j].GetVal() == 0)
				{
					mpMaze[i][j].SetState(DOWN, YES);
				}
				if (j != mcol - 1 && mpMaze[i][j + 1].GetVal() == 0)
				{
					mpMaze[i][j].SetState(RIGHT, YES);
				}
			}
		}
	}

	void findMazePath()
	{
		mystack.Push(mpMaze[0][0]);
		while (!mystack.Empty())
		{
			MazeNode node = mystack.GetTop();

			int i = node.GetX();
			int j = node.GetY();

			if (j == mrow - 1 && i == mcol - 1)
			{
				break;
			}
			if (mpMaze[i][j].GetState(RIGHT) == YES)
			{
				mpMaze[i][j].SetState(RIGHT, NO);
				mpMaze[i][j + 1].SetState(LEFT, NO);
				mystack.Push(mpMaze[i][j+1]);
				continue;
			}

			if (mpMaze[i][j].GetState(DOWN) == YES)
			{
				mpMaze[i][j].SetState(DOWN,NO);
				mpMaze[i + 1][j].SetState(UP,NO);
				mystack.Push(mpMaze[i+1][j]);
				continue;
			}

			if (mpMaze[i][j].GetState(LEFT) == YES)
			{
				mpMaze[i][j].SetState(LEFT, NO);
				mpMaze[i][j - 1].SetState(RIGHT, NO);
				mystack.Push(mpMaze[i][j-1]);
				continue;
			}

			if (mpMaze[i][j].GetState(UP) == YES)
			{
				mpMaze[i][j].SetState(UP, NO);
				mpMaze[i - 1][j].SetState(DOWN, NO);
				mystack.Push(mpMaze[i-1][j]);
				continue;
			}

			mystack.Pop();
		}
	}

	void showResult()
	{
		if (mystack.Empty())
		{
			cout << "此迷宫不存在可通行路径" << endl;
		}
		else
		{
			while (!mystack.Empty())
			{
				MazeNode node = mystack.GetTop();
				int i = node.GetX();
				int j = node.GetY();
				mpMaze[i][j].SetVal('*');
				mystack.Pop();
			}

			for (int i = 0; i < mrow; i++)
			{
				for (int j = 0; j < mcol; j++)
				{
					if (mpMaze[i][j].GetVal() == '*')
					{
						cout << "* ";
					}
					else
					{
						cout << mpMaze[i][j].GetVal() << " ";
					}
				}
				cout << endl;
			}
		}
     }

private:
	int mrow;
	int mcol;
	MazeNode **mpMaze;
	Maze(const Maze &src);
	void operator=(const Maze &src);
	CStack mystack;
}; 
#endif
