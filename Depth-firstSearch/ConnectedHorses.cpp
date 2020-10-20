#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <cmath>
#include <math.h>
#include <unordered_set>
#include <stack>
#include <queue>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vvi vector<vector<int> >
#define vvb vector<vector<bool> >
#define vvl vector<vector<ll> >

ll mod = pow(10,9) + 7;

int xDir[] = {-2, -2, -1, 1, 2, 2, 1, -1};
int yDir[] = {-1, 1, 2, 2, 1, -1, -2, -2};

void dfs(vvi &edges,int ele,ll &count,vb &visited)
{
	visited[ele] = true;
	for(int &id: edges[ele])
	{
		if(!visited[id]) dfs(edges, id, ++count, visited);
 	}
}

ll getFact(ll num)
{
	if(num <= 1) return 1;
	return (num * (getFact(num-1)%mod))%mod;
}

int CountPhoto(vvi &edges)
{
	int n = edges.size();
	ll ans = 1, count = 1;
	vb visited(n, false);
	rep(i,1,n)
	{
		if(!visited[i])
		{
			dfs(edges, i, count, visited);
			ans = (ans * (getFact(count)%mod))%mod;
		}
		count = 1;
	}
	return int(ans);
}

bool isValid(vvi &board,int x,int y,int n,int m)
{
	if(x < 0 || y < 0 || x >= n || y >= m || board[x][y] == 0) return false;
	else return true;
}

int main()
{
	int t,n,m,q,f,s, horseNum;
	vvi board;
	cin >> t;
	rep(T,1,t+1)
	{
		cin >> n >> m >> q;
		board.assign(n, vi(m, 0));
		horseNum = 1;
		rep(i,0,q)
		{
			cin >> f >> s;
			board[f-1][s-1] = horseNum++;
		}
		vvi edges(horseNum, vi());
		rep(x,0,n)
		{
			rep(y,0,m)
			{
				if(board[x][y] == 0) continue;
				rep(k,0,8) if(isValid(board,x + xDir[k], y + yDir[k],n,m)) edges[board[x][y]].pb(board[x+xDir[k]][y+yDir[k]]);
			}
		}
		cout << CountPhoto(edges) << "\n";
	}
	return 0;
}

