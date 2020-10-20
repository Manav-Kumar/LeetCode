#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <cmath>
#include <math.h>
#include <unordered_set>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vvi vector<vector<int> >
#define vvb vector<vector<bool> >

bool checkPlayerMakingTriplet(char **board,char player)
{
	//	Checking rows, cols
	bool checkDia1 = true, checkDia2 = true;
	rep(i,0,3)
	{
		bool tr = true, tc = true;
		rep(j,0,3)
		{
			if(board[i][j] != player) tr = false;
			if(board[j][i] != player) tc = false;
		}
		if(tr || tc) return true;
		if(board[i][i] != player) checkDia1 = false;
	}

	int i=0,j=2;
	while(i < 3 && j >= 0)
	{
		if(board[i][j] != player) checkDia2 = false;
		i++, j--;
	}
	return (checkDia1 || checkDia2);
}

int evaluateBoard(char **board,bool &isCompleted,int depth = 0)
{
	bool isDraw = true;
	rep(i,0,3) rep(j,0,3) if(board[i][j] == '\0') isDraw = false;
	bool isXWin = checkPlayerMakingTriplet(board, 'x');
	bool isOWin = checkPlayerMakingTriplet(board, 'o');
	if(isDraw || isXWin || isOWin)
	{
		isCompleted = true;
		int ans = 0;
		if(isXWin) ans = 10 - depth;
		else if(isOWin) ans = -10 + depth;
		else if(isDraw) ans = 0;
		return ans;
	}
	else
	{
		isCompleted = false;
		return -1;
	}
}

void printBoard(char **board)
{
	rep(i,0,3)
	{
		rep(j,0,3) cout << board[i][j] << " ";
		cout << "\n";
	}
}

int findNextStep(char **board,bool maximizerTurn,int &x,int &y,int depth = 0)
{
	//	Evaluation of Board
	bool isCompleted;
	int score = evaluateBoard(board,isCompleted);
	//printBoard(board);
	if(isCompleted) return score;

	char player = maximizerTurn? 'x': 'o';
	int best;
	if(maximizerTurn) best = INT_MIN;
	else
	{
		depth++;
		best = INT_MAX;
	}
	rep(i,0,3)
	{
		rep(j,0,3)
		{
			if(board[i][j] != '\0') continue;
			board[i][j] = player;
			int dummyX,dummY;
			int score = findNextStep(board, !maximizerTurn, dummyX, dummY, depth);
			if(maximizerTurn) best = max(best, score);
			else best = min(best, score);
			if(best == score)
			{
				x = i, y = j;
			}
			board[i][j] = '\0';
		}
	}
	return best;
}

int main()
{
	char **board = new char*[3];
	rep(i,0,3)
	{
		board[i] = new char[3];
		rep(j,0,3) board[i][j] = '\0';
	}
	int n,x,y;
	char c;
	cin >> n;
	while(n--)
	{
		cin >> x >> y >> c;
		board[x][y] = c;
	}
	cout << findNextStep(board, true, x,y) << " row: " << x << " col: " << y << "\n";
	return 0;
}