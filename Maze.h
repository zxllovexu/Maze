#ifndef  _MAZE_H
#define _MAZE_H

#include <iostream>
using namespace std;

const int RIGHT = 0;
const int DOWN = 1;
const int LEFT = 2;
const int UP = 3;
const int WAY_NUM = 4;


const int YES = 5;
const int NO = 6;

class  MazeNode
{
public:
	MazeNode()
	{
		for (int i = 0; i < WAY_NUM; ++i)
		{
			mstate[i] = YES;//将所有迷宫节点的状态都初始化为可通行
		}
	}
	~MazeNode()
	{

	}
	void setNode(int val, int x, int y)
	{
		mval = val;
		mx = x;
		my = y;
	}
	void setWayState(int way, int state)
	{
		mstate[way] = state;
	}
	int getWayState(int way)
	{
		return mstate[way];
	}
	int getVal() { return mval; }
	void setVal(int val) { mval = val; }
	int getX() { return mx; }
	int getY() { return my; }
private:
	int mval;
	int mx;//节点的坐标
	int my;
	int mstate[WAY_NUM];//记录该节点的状态
};

class CStack
{
public:
	// 高内聚  低耦合
	CStack(int size = 100):mtop(-1), msize(size)
	{
		mpstack = new MazeNode[msize];
	}
	~CStack()
	{
		delete[]mpstack;
		mpstack = nullptr;
	}

	void push(MazeNode &m);
	void pop();
	MazeNode top()
	{
		return mpstack[mtop];
	}

	bool Is_full()
	{
		return mtop == msize - 1 ;
	}
	bool Is_empty()
	{
		return mtop == -1;
	}
private:
	MazeNode *mpstack;
	int mtop;
	int msize;//栈的最大容量，如果栈满，要对栈进行扩容

	void resize()
	{
		MazeNode *ptmp = new MazeNode[2 * msize];
		for (int i = 0; i < msize; ++i)
		{
			ptmp[i] = mpstack[i];
		}
		delete[]mpstack;
		mpstack = ptmp;
		msize = msize * 2;
	}
};

void CStack::push(MazeNode &m)
{
	if (Is_full())
	{
		resize();
	}
	mpstack[++mtop] = m;//会不会调用赋值运算符重载函数？
}

void CStack::pop()
{
	if (Is_empty())
	{
		return;
	}
	mtop--;
}


class Maze
{ 
public:
	Maze(int row, int col):mrow(row),mcol(col)
	{
		mpMaze = new MazeNode* [row];
		for (int i = 0; i < row; ++i)
		{
			mpMaze[i] = new MazeNode[col];
		}
	}

	~Maze()
	{
		for (int i = 0; i < mrow; ++i)
		{
			delete []mpMaze[i];
		}
		delete []mpMaze;
		mpMaze = nullptr;
	}

	//初始化迷宫节点
	void initMazeNode(int val,int x,int y);//void setMazeMap(MazeNode *mmap,int row,int col);
   
	// 调整迷宫所有节点的方向的行走状态
	void adjustMaze();
	// 寻找迷宫路径
	void findMazePath();
	// 打印寻找结构
	void showResult();
private:
	int mrow;
	int mcol;
	MazeNode **mpMaze;
	CStack mstack;

	Maze(const Maze &);
	void operator=(const Maze &src);
};

/*void Maze::setMazeMap(MazeNode *mmap, int row, int col)
{
	mpMaze = new MazeNode* [row];
	for (int i=0; i<row; ++i)
	{
		mpMaze[i] = new MazeNode[col];
	}
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			mpMaze[i][j] = *mmap;
			mmap++;
		}
	}
}*/

void Maze::initMazeNode(int val, int x, int y)
{
	mpMaze[x][y].setNode(val, x, y);
}
/*
0 0 1 0 0
0 0 0 0 0
1 0 0 1 1
0 1 0 1 0
1 0 0 0 0
开始寻找迷宫路径...

没找到，打印提示信息“迷宫不存在可通行的路径”
找到了，把迷宫路径打印一遍
* * 1 0 0
0 * * 1 0
1 0 * 0 1
0 1 * 1 0
1 0 * * *
*/
void Maze::adjustMaze()
{
	for (int j = 0; j < mcol; ++j)
	{
		//mpMaze[0][j].mstate[UP] = NO;
		mpMaze[0][j].setWayState(UP, NO);
		//mpMaze[mrow - 1][j].mstate[DOWN] = NO;
		mpMaze[mrow - 1][j].setWayState(DOWN, NO);
	}
	for (int i = 0; i < mrow; ++i)
	{
		//mpMaze[i][0].mstate[LEFT] = NO;
		mpMaze[i][0].setWayState(LEFT, NO);
		//mpMaze[i][mcol - 1].mstate[RIGHT] = NO;
		mpMaze[i][mcol - 1].setWayState(RIGHT, NO);
	}

	for (int i = 0; i < mrow; ++i)
	{    
		for (int j = 0; j < mcol; ++j)
		{
#if 0
			if (mpMaze[i][j].getVal() == 1)
			{
				continue;
			}
			if (i == 0)
			{
				mpMaze[i][j].setWayState(UP, NO);
			}
			if (j == 0)
			{
				mpMaze[i][j].setWayState(LEFT, NO);
			}
			if (i == mrow - 1)
			{
				mpMaze[i][j].setWayState(DOWN, NO);
			}
			if (j == mcol - 1)
			{
				mpMaze[i][j].setWayState(RIGHT, NO);
			}
			if (j<mcol-1 && mpMaze[i][j + 1].getVal() == 1)
			{
				mpMaze[i][j].setWayState(RIGHT, NO);
			}
			if (mpMaze[i + 1][j].getVal() == 1)
			{
				mpMaze[i][j].setWayState(DOWN, NO);
			}
#endif
			if (1 == mpMaze[i][j].getVal())
			{
				if (j > 0)
					mpMaze[i][j - 1].setWayState(RIGHT, NO);
				if (j < mcol - 1)  
					//mpMaze[i][j + 1].mstate[LEFT] = NO;
					mpMaze[i][j + 1].setWayState(LEFT, NO);

				if (i < mrow - 1) 
					//mpMaze[i + 1][j].mstate[UP] = NO;
					mpMaze[i + 1][j].setWayState(UP, NO);
				if (i > 0)
					//mpMaze[i - 1][j].mstate[DOWN] = NO;
					mpMaze[i - 1][j].setWayState(DOWN, NO);
			}
			else
			{
				continue;
			}
		}
	}
}

void Maze::findMazePath()
{
	    this->mstack.push(mpMaze[0][0]);

		while(!mstack.Is_empty())
		{
			MazeNode node = mstack.top();
			int i = node.getX();
			int j = node.getY();
			
			if (i == mrow - 1 && j == mcol - 1)
			{
				break;
			}

			// 右
			if (mpMaze[i][j].getWayState(RIGHT) == YES)
			{
				mpMaze[i][j].setWayState(RIGHT, NO);
				mpMaze[i][j + 1].setWayState(LEFT, NO);
				mstack.push(mpMaze[i][j+1]);
				continue;
			}
			
			// 下
			if (mpMaze[i][j].getWayState(DOWN) == YES)
			{
				mpMaze[i][j].setWayState(DOWN, NO);
				mpMaze[i+1][j].setWayState(UP, NO);
				mstack.push(mpMaze[i+1][j]);
				continue;
			}
			
			// 左
			if (mpMaze[i][j].getWayState(LEFT) == YES)
			{
				mpMaze[i][j].setWayState(LEFT, NO);
				mpMaze[i][j-1].setWayState(RIGHT, NO); 
				mstack.push(mpMaze[i][j-1]);
				continue;
			}
			
			// 上
			if (mpMaze[i][j].getWayState(UP) == YES)
			{
				mpMaze[i][j].setWayState(UP, NO);
				mpMaze[i-1][j].setWayState(DOWN, NO);
				mstack.push(mpMaze[i-1][j]);
				continue;
			}
		
			mstack.pop( );
		}
}

void Maze::showResult()
{
	if (mstack.Is_empty())
	{
		cout << "该迷宫不存在可同行的路径" << endl;
		return;
	}


	
	/*
	while (mstack.mtop != -1)
	{
		i = mstack.mpstack[mstack.mtop].mx;
		j = mstack.mpstack[mstack.mtop].my;
		mstack.mtop--;
		mpMaze[i][j].mval = '*';
	}
	*/
	while (!mstack.Is_empty())
	{
		MazeNode node = mstack.top();
		int i = node.getX();
		int j = node.getY();
		mpMaze[i][j].setVal('*');
		mstack.pop();
	}

	for (int i = 0; i < mrow; ++i)
	{ 
		for (int j = 0; j < mcol; ++j)
		{
			if (mpMaze[i][j].getVal() == '*')
				cout << "* ";
			else
			{
				cout << mpMaze[i][j].getVal() << " ";
			}
		}
		cout << endl;
	}
}



#endif  
