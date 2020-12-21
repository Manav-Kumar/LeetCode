#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <unordered_map>
#include <set>
#include <cmath>
#include <math.h>
#include <unordered_set>
#include <climits>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vll vector<ll>
#define vi vector<int>
#define vvi vector<vi >
#define vvvi vector<vvi>
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>

int x[] = {-1, 0, 1, 0};
int y[] = {0, 1, 0, -1};

void dfs(vvc &board,int i,int j){
	int n = board.size(), m = board[0].size();
	if(i < 0 || j < 0 || i >= n || j >= m || board[i][j] != 'O') return;

	board[i][j] = '@';
	rep(k, 0, 4){
		dfs(board, i + x[k], j + y[k]);
	}
}

void solve(vvc &board){
	int n = board.size(), m = board[0].size();
	//	Border Elements
	rep(i, 0, n) if(board[i][0] == 'O') dfs(board, i, 0);
	rep(j, 0, m) if(board[n-1][j] == 'O') dfs(board, n-1, j);
	rep(i, 0, n) if(board[i][m-1] == 'O') dfs(board, i, m - 1);
	rep(j, 0, m) if(board[0][j] == 'O') dfs(board, 0, j);

	rep(i, 0, n){
		rep(j, 0, m){
			if(board[i][j] == '@') board[i][j] = 'O';
			else if(board[i][j] == 'O') board[i][j] = 'X';
		}
	}
}

void solve2(vvc &board){
	
}

int main(){

	return 0;
}





