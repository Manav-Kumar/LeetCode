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

bool ispath(vvi &edges,int st,int en,vb &visited)
{
	if(st == en) return true;
	visited[st] = true;
	for(int &id: edges[st])
	{
		if(!visited[id] && ispath(edges, id, en, visited)) return true;
	}
	return false;
}

bool helper(vector<int> &p, vector<int> &q,vvi& edges,map<int,int> &mp,int index = 1)
{
	if(index == p.size()) return true;
	if(p[index] == q[index]) return helper(p,q,edges,mp,index+1);

	int next = mp[q[index]];
	vector<bool> visited(p.size(), false);
	if(ispath(edges, index, next, visited))
	{
		swap(p[index], p[next]);
		if(helper(p,q,edges,mp,index+1)) return true;
	}

	return false;
}


void PermutationSwaps()
{
	int t,n,m,f,s;
	map<int,int> mp;
	vvi edges;
	cin >> t;
	rep(T,1,t+1)
	{
		cin >> n >> m;
		edges.assign(n+1, vi());
		vvi edges(n+1, vi());
		vector<int> p(n+1), q(n+1);
		rep(i,1,n+1)
		{
			cin >> p[i];
			mp[p[i]] = i;
		}
		rep(i,1,n+1) cin >> q[i];
		rep(i,0,m)
		{
			cin >> f >> s;
			edges[f].pb(s);
			edges[s].pb(f);
		}
		if(helper(p,q,edges,mp)) cout << "YES" << "\n";
		else cout << "NO" << "\n";
		mp.clear();
		edges.assign(n+1, vi());
	}
}

int main()
{
	PermutationSwaps();
}