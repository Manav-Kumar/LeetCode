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

void helper(vvi &edges,stack<int> &s,int ele,vb &visited)
{
	visited[ele] = true;
	for(int &id: edges[ele])
	{
		if(!visited[id]) helper(edges, s, id, visited);
	}
	s.push(ele);
}

void dfs(vvi &edges,vb &visited,int ele)
{
	visited[ele] = true;
	for(int &id: edges[ele])
	{
		if(!visited[id]) dfs(edges, visited, id);
	}
}

int CountHand(vvi &edges)
{
	int n = edges.size();
	stack<int> s;
	vb visited(n, false);
	rep(i,1,n)
	{
		if(visited[i]) continue;
		helper(edges, s, i, visited);
	}
	int count = 0;
	visited.assign(n, false);
	while(!s.empty())
	{
		if(!visited[s.top()])
		{
			dfs(edges, visited, s.top());
			count++;
		}
		else s.pop();
	}
	return count;
}

int main()
{
	int t,n,m,x,y;
	vvi board;
	cin >> t;
	rep(T,1,t+1)
	{
		cin >> n >> m;
		vvi edges(n+1, vi());
		while(m--)
		{
			cin >> x >> y;
			edges[x].pb(y);
		}
		cout << CountHand(edges) << "\n";
	}
	return 0;
}

