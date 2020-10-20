#include <iostream>
#include <vector>
#include <queue>
#include <map>
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
#define vi vector<int>
#define vvi vector<vector<int> >
#define vvb vector<vector<bool> >

int n;
void helper(vvi &edges,int index,vector<bool>& visited,set<int>& sol)
{
	sol.insert(index);
	visited[index] = true;
	rep(i,0,n)
	{
		if(i!=index && !visited[i] && edges[index][i]) helper(edges, i, visited, sol);
	}
}

void connectedComponents(vvi &edges)
{
	unordered_set<int> finalAns;
	n = edges.size();
	vector<bool> visited(n, false);
	rep(i,0,n)
	{
		if(!visited[i])
		{
			set<int> sol;
			helper(edges, i, visited,sol);
			for(auto it = sol.begin();it != sol.end();it++) cout << *it << " ";
			cout << "\n";
		}
	}
	return ;
}


//	Largest Piece of Cake
int largestPiece(char cake[10][10],int i,int j,int n,vvb &visited)
{
	if(i < 0 || j < 0 || i >= n || j >= n || visited[i][j] || cake[i][j] != '1') return 0;
	visited[i][j] = true;
	int ans = 1;
	ans += largestPiece(cake, i+1,j,n,visited) + largestPiece(cake,i,j+1,n,visited) + 
			largestPiece(cake, i-1, j, n, visited) + largestPiece(cake, i, j -1, n, visited);

	return ans;
}


int solve(int n,char cake[10][10])
{
	int best = 0;
	vector<vector<bool> > visited(n, vector<bool>(n, false));
	rep(i,0,n)
	{
		rep(j,0,n)
		{
			if(!visited[i][j] && cake[i][j] == '1')
			{
				best = max(best, largestPiece(cake, i,j, n, visited));
			}
		}
	}
	return 0;
}

//	Find Coding Ninja
int xDir[] = {0, -1, 0, 1};
int yDir[] = {-1, 0, 1, 0};
bool isString(char Graph[][MAXN],int i,int j,int n,int m,string s,vvb &visited)
{
	if(s.empty()) return true;
	if(i < 0 || j < 0 || i >= n || j >= m || visited[i][j] || Graph[i][j] != s[0]) return false;
	visited[i][j] = true;
	rep(k,0,8)
	{
		if(isString(Graph, i+xDir[k], j+yDir[k], n, m, s.substr(1), visited)) return true;
	}
	visited[i][j] = false;
	return false;
}

int solveR(char Graph[][MAXN], int n,int m)
{
	string s = "CODINGNINJA";
	vvb visited(n, vb(m, false));
	rep(i,0,n)
	{
		rep(j,0,m)
		{
			if(Graph[i][j] == 'C' && isString(Graph, i,j,n,m, s, visited)) return true;
			else visited.assign(n, vb(m, false));
		}
	}
	return false;
}

//	Connecting Dots

bool ConnectingDots(char board[][MAXN],int n,int m,char color,int i,int j,int x,int y,int count = 0)
{
	if(count >= 4 && (i == x && j == y)) return true;
	if(i < 0 || j < 0 || i >= n || j >= m || color != board[i][j]) return false;
	board[i][j] = '\0';
	rep(k,0,4)
	{
		if(ConnectingDots(board, n,m, color,i+xDir[k],j+yDir[k],x,y,count+1)) return true;
	}
	board[i][j] = color;
	return false;
}

int solveBoard(char board[][MAXN],int n,int m)
{
	rep(i,0,n)
	{
		rep(j,0,m)
		{
			if(ConnectingDots(board, n, m, board[i][j] - 'A', i,j,i,j)) return true;
		}
	}
	return false;
}


int main()
{
	int V,E,f,s;
	cin >> V >> E;
	vvi edges(V, vector<int>(V));
	for(int i = 0;i < E;i++)
	{
		cin >> f >> s;
		edges[f][s] = 1;
		edges[s][f] = 1;
	}
	connectedComponents(edges);
	return 0;
}