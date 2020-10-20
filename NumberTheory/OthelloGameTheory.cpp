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


int **makeMove(int **board,int player,int x,int y,bool isCheck)
{
	if(x < 0 || x >= 4 || y < 0 || y >= 4 || board[x][y] != 0) return NULL;
	int **newBoard;
	if(isCheck) newBoard = board;
	else
	{
		newBoard = new int*[4];
		rep(i,0,4)
		{
			newBoard[i] = new int[4];
			rep(j,0,4) newBoard[i][j] = board[i][j];
		}
	}
	bool movePossibe = false;
	int xDir[] = {-1, -1, -1, 0, 1, 1, 1, 0};
	int yDir[] = {-1, 0, 1, 1, 1, 0, -1, -1};
	for(int i=0;i<8;i++)
	{
		int currX = x + xDir[i];
		int currY = y + yDir[i];
		int count = 0;
		while(currX >= 0 && currX < 4 && currY >= 0 && currY < 4)
		{
			if(board[currX][currY] == 0) break;
			else if(board[currX][currY] != player)
			{
				count++;
				currX += xDir[i];
				currY += yDir[i];
			}
			else if(board[currX][currY] == player)
			{
				if(count > 0)
				{
					movePossibe = true;
					if(isCheck) return newBoard;
					while(currX != x || currY != y)
					{
						newBoard[currX][currY] = player;
						currX -= xDir[i];
						currY -= yDir[i];
					}
					newBoard[x][y] = player;
				}
				break;
			}
		}
	}

	if(movePossibe) return newBoard;
	else return NULL;
}


vector<pair<int,int>*>* PossibeMoves(int **board,int player)
{
	vector<pair<int,int>*>* output = new vector<pair<int,int>*>();
	rep(i,0,4)
	{
		rep(j,0,4)
		{
			if(board[i][j] == 0)
			{
				if(makeMove(board, player, i,j, true))
				{
					pair<int,int>* p = new pair<int,int>(i,j);
					output->pb(p);
				}
			}
		}
	}
	return output;
}

//	Evaluate Function, 1 is Maximizer and 2 is Minimizer
int evaluateBoard(int **board,bool& iscompleted)
{
	if(PossibeMoves(board, 1)->size() != 0 || PossibeMoves(board, 2)->size() != 0)
	{
		iscompleted = false;
		return 0;
	}
	int count[3] = {};
	rep(i,0,4) rep(j,0,4) count[board[i][j]]++;
	return count[1] - count[2];
}

void printBoard(int **board)
{
	rep(i,0,4)
	{
		rep(j,0,4) cout << board[i][j] << " ";
		cout << "\n";
	}
}

int findNextSteps(int **board,bool maximizerTurn,int &x,int &y)
{
	bool iscompleted;
	int score = evaluateBoard(board, iscompleted);
	printBoard(board);
	cout << "\n";
	if(iscompleted) return score;
	int player = maximizerTurn? 1: 2;
	vector<pair<int,int>*>* options = PossibeMoves(board, player);
	if(options->size() == 0)
	{
		x = -1, y = -1;
		int dummyX, dummyY;
		return findNextSteps(board, !maximizerTurn, dummyX, dummyY);
	}
	int best;
	if(maximizerTurn) best = INT_MIN;
	else best = INT_MAX;

	for(int i = 0;i < options->size();i++)
	{
		int currX = options->at(i)->first, currY = options->at(i)->second;
		int **newBoard = makeMove(board, player, currX, currY, false);
		//	Make recursive Call
		int dummyX, dummyY;
		int score = findNextSteps(newBoard, !maximizerTurn, dummyX, dummyY);

		if(maximizerTurn) best = max(best, score);
		else best = min(best, score);

		if(best == score)
		{
			//	Means best is updated
			x = currX, y = currY;
		}
		//	Undo the move. We will have to maintain the copy of the board for this
		rep(i,0,4) delete []newBoard[i];
		delete []newBoard;
	}
	return best;
}


int main()
{
	int **a = new int*[4];
	rep(i,0,4)
	{
		a[i] = new int[4]();
		rep(j,0,4) a[i][j] = 0;
	}
	a[1][1] = 1;
	a[1][2] = 2;
	a[2][0] = 2;
	a[2][2] = 1;
	int x,y;
	cout << findNextSteps(a, true, x,y) << "\n";
	cout << x << " " << y << "\n";
	return 0;
}

