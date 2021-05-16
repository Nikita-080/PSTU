#include <iostream>
using namespace std;
int board[8][8];
void SR_queen(int i, int j, int add, int queen)
{
    int foo;
	for (int x = 0; x < 8; x++)
	{
		board[x][j]+=add;
		board[i][x]+=add;
		foo = j - i + x;
		if (foo >= 0 && foo < 8)
			board[x][foo]+=add;
		foo = j + i - x;
		if (foo >= 0 && foo < 8)
			board[x][foo]+=add;
	}
	board[i][j] = queen;
}
bool try_queen(int i)
{
	bool result = false;
	for (int j = 0; j < 8; j++)
	{
		if (board[i][j] == 0)
		{
			SR_queen(i, j, 1, -1);
			if (i == 7)
				result = true;
			else if (!(result = try_queen(i + 1))) SR_queen(i, j, -1, 0);
		}
		if (result) break;
	}
	return result;
}
int main()
{
	for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) board[i][j] = 0;
	try_queen(0);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == -1) cout << "Y";
			else cout <<".";
		}
		cout << endl;
	}
	system("pause");
}
