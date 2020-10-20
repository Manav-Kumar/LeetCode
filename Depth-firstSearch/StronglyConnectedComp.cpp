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

//	Connected Components in Case of Directed Graph



void forwardPass(vvi &edges,vb &visited,stack<int> &s,int ele)
{
	visited[ele] = true;
	for(int &id: edges[ele]) if(!visited[id]) forwardPass(edges, visited, s, id);
	s.push(ele);
}

void backwardPass(vvi &edgesT,vb &visited,int ele,unordered_set<int>* sol)
{
	visited[ele] = true;
	sol->insert(ele);
	for(int &id: edgesT[ele]) if(!visited[id]) backwardPass(edgesT,visited,id,sol);
}

unordered_set<unordered_set<int>*> * ConnectedComp(vvi &edges,vvi& InverseEdges)
{
	//	0 based indexing
	unordered_set<unordered_set<int>*> *finalAns = new unordered_set<unordered_set<int>*>();
	int n = edges.size();
	stack<int> s;
	vb visited(n, false);
	rep(i,0,n)
	{
		if(!visited[i]) forwardPass(edges, visited,s, i);
	}
	visited.assign(n, false);
	while(!s.empty())
	{
		if(!visited[s.top()])
		{
			unordered_set<int>* sol = new unordered_set<int>();
			backwardPass(InverseEdges, visited, s.top(), sol);
			finalAns->insert(sol);
		}
		else s.pop();
	}
	return finalAns;
}

int main()
{
	int n,m,f,s;
	cin >> n >> m;
	vvi edges(n, vi());
	vvi InverseEdges(n, vi());
	rep(i,0,m)
	{
		cin >> f >> s;
		edges[f].pb(s);
		InverseEdges[s].pb(f);
	}
	unordered_set<unordered_set<int>*> *components =  ConnectedComp(edges, InverseEdges);
	for(auto it = components->begin();it != components->end();it++)
	{
		for(auto it2 = (*it)->begin();it2 != (*it)->end();it2++) cout << *it2 << " ";
		cout << "\n";
	}
	return 0;
}



