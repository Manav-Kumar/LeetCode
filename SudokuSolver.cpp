#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <set>
#include <unordered_map>

using namespace std;

#define n 9
#define rep(i,a,b) for(int i=a;i<b;i++)
#define vvb vector<vector<bool> > 
#define vvvb vector<vector<vector<bool> > >
#define vvc vector<vector<char> > 


// TRY TO PASS MOST OF THE TIME BY REFERENCE AS IT WASTES ALOT OF TIME WHILE COPYING

bool helper2(bool rows[][9],bool cols[][9],bool boxes[][9],
 					vvc& board,vector<pair<int,int> >& emptySpots, int pos = 0)
{
	if(pos == emptySpots.size()) return true;
	int i = emptySpots[pos].second/9, j = emptySpots[pos].second%9;
	rep(k,0,9)
	{
		if(cols[j][k] || rows[i][k] || boxes[(i/3)*3 + j/3][k]) continue;
		cols[j][k] = rows[i][k] = boxes[(i/3)*3 + j/3][k] = true;
		board[i][j] = char('1' + k);
		if(helper2(rows, cols, boxes, board, emptySpots, pos+1)) return true;
		cols[j][k] = rows[i][k] = boxes[(i/3)*3 + j/3][k] = false;
		board[i][j] = '.';
	}
	return false;
}

void solveSudoku2(vector<vector<char> >& board)
{
	bool rows[9][9] = {}, cols[9][9] = {}, boxes[9][9] = {};

	rep(i,0,9)
	{
		rep(j,0,9)
		{
			if(board[i][j] == '.') continue;
			rows[i][board[i][j] - '1'] = true;
			boxes[(i/3)*3 + j/3][board[i][j] - '1'] = true;
			cols[j][board[i][j] - '1'] = true;
		}
	}
	vector<pair<int,int> > emptySpots;
	rep(i,0,n)
	{
		rep(j,0,n)
		{
			if(board[i][j] != '.') continue;
			int nums = 0;
			rep(k,0,9) nums += !rows[i][k] && !cols[j][k] && !boxes[(i/3)*3 + j/3][k];
			emptySpots.push_back(pair<int,int> (nums, i*9+j));
		}
	}
	// Sorting on the basis of 1st number
	sort(emptySpots.begin(), emptySpots.end());
	helper2(rows, cols, boxes, board, emptySpots);
}



bool helper(vvb &cols, vvb &rows, vvvb &boxes, vvc& board,vector<pair<int,int> >& emptySpots,
					int pos = 0)
{
    if(pos == emptySpots.size()) return true;
    int i = emptySpots[pos].second/9, j = emptySpots[pos].second%9;
    rep(k,1,10)
    {
        if(cols[j][k] || rows[i][k] || boxes[i/3][j/3][k]) continue;
        cols[j][k] = rows[i][k] = boxes[i/3][j/3][k] = true;
        board[i][j] = char('0' + k);
        if(helper(cols, rows, boxes, board, emptySpots, pos+1)) return true;
        cols[j][k] = rows[i][k] = boxes[i/3][j/3][k] = false;
        board[i][j] = '.';
    }
    return false;
}
void solveSudoku(vector<vector<char> >& board)
{
    vvb cols(board.size(), vector<bool>(10 ,false));
    vvb rows(board.size(), vector<bool>(10 ,false));
    vvvb boxes(3, vector<vector<bool> >(3, vector<bool>(10, false)));


    rep(i,0,n)
    {
        rep(j,0,n)
        {
            if(board[i][j] == '.') continue;
            int val = board[i][j] - '0';
            rows[i][val] = true;
            boxes[i/3][j/3][val] = true;
            cols[j][val] = true;
        }
    }
    vector<pair<int,int> > emptySpots;
    rep(i,0,n)
    {
        rep(j,0,n)
        {
            if(board[i][j] != '.') continue;
            int nums = 0;
            rep(k,1,10) nums += !rows[i][k] && !cols[j][k] && !boxes[i/3][j/3][k];
            emptySpots.push_back(pair<int,int> (nums, i*9+j));
        }
    }
    // Sorting on the basis of 1st number
    sort(emptySpots.begin(), emptySpots.end());
    helper(cols, rows, boxes, board, emptySpots);
}


int main()
{
	vvc board;
	board.resize(n);
	for(vector<char> &z: board)
	{
		z.resize(n);
		rep(i,0,n) cin >> z[i];
	}
	solveSudoku2(board);
	rep(i,0,n)
	{
		rep(j,0,n) cout << board[i][j];
		cout << "\n";
	}
	return 0;
}

