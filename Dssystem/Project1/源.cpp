#include<iostream>
using namespace std;


int findValuePath(int arr[],int  b, int c)
{
	for (int i = 0; i < b; i++)
	{
		if (arr[i] == c)
		{
			return i;
		}
	}
	return -1;
}

int main()
{
	int arr[6] = { 5,12,14,16,18,86 };
	int t = findValuePath(arr, 6, 12);
	cout << t << endl;
	return 0;
}