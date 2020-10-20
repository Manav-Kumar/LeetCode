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
#include <algorithm>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vvi vector<vector<int> >
#define vvb vector<vector<bool> >

void forwardPass(vvi &edges,vb &visited,stack<int> &s,int ele)
{
	visited[ele] = true;
	for(int &id: edges[ele]) if(!visited[id]) forwardPass(edges, visited, s, id);
	s.push(ele);
}

void backwardPass(vvi &edgesT,vb &visited,int ele,map<int,int> &mp,map<int,set<int> > &mpT,int count)
{
	visited[ele] = true;
	mp[ele] = count;
	mpT[count].insert(ele);
	for(int &id: edgesT[ele]) if(!visited[id]) backwardPass(edgesT,visited,id,mp,mpT,count);
}

set<int> helper(vvi &edges,vvi &edgesT)
{
	stack<int> s;
	int n = edges.size(), count = 0;
	vb visited(n, false);
	rep(i,1,n)
	{
		if(!visited[i]) forwardPass(edges, visited, s, i);
	}
	visited.assign(n, false);
	map<int,int> mp;
	map<int,set<int> >mpT;
	while(!s.empty())
	{
		if(!visited[s.top()]) backwardPass(edgesT, visited, s.top(), mp, mpT,count++);
		else s.pop();
	}
	vector<unordered_set<int> > newEdges(count, unordered_set<int>());
	rep(i,1,n)
	{
		for(int &id: edges[i])
		{
			if(mp[i] == mp[id]) continue;
			newEdges[mp[i]].insert(mp[id]);
		}
	}
	set<int> ans;
	rep(i,0,count) if(newEdges[i].empty()) for(auto it = mpT[i].begin();it!=mpT[i].end();it++) ans.insert(*it);
	return ans;
}


//	Bipartite Graph
bool Bipartite(vvi &edges)
{
	set<int> s1, s2;
	queue<pair<int,int> > pendingNodes;
	vb visited(n, false);
	int n = edges.size();
	s1.insert(1);
	pendingNodes.push(pair<int,int>(1,0));
	while(!pendingNodes.empty())
	{
		pair<int,int> ft = pendingNodes.front();
		pendingNodes.pop();
		for(int &id: edges[ft.first])
		{
			if((ft.second == 0 && s1.find(id) != s1.end()) || (ft.second == 1 && s2.find(id) != s2.end())) return false;
			pendingNodes.push(pair<int,int>(id, (ft.second+1)%2)); 
		}
	}
	return true;
}

int main()
{
	int n,e,f,s;
	vvi edges, edgesT;
	while(1)
	{
		cin >> n;
		if(n == 0) break;
		cin >> e;
		edges.assign(n+1, vi());
		edgesT.assign(n+1, vi());
		while(e--)
		{
			cin >> f >> s;
			edges[f].pb(s);
			edgesT[s].pb(f);
		}

		set<int> sol = helper(edges, edgesT);
		for(auto it = sol.begin();it != sol.end();it++) cout << (*it) << " ";
		cout << "\n";
	}
	return 0;
}

