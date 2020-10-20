#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <cmath>
#include <math.h>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vvi vector<vector<int> >
int n;

void helper(vvi &edges, int ele,vector<set<int> > &parent,int n,int& count)
{
	rep(i, 0, n)
	{
		if(edges[i][0] != ele) continue;
		int next = edges[i][1];
		if(!parent[next].empty()) parent[next].insert(i);
		else
		{
			parent[next].insert(i);
			helper(edges, next, parent, n, ++count);
		}
	}
	return;
}

vector<int> findRedundantDirectedConnection(vector<vector<int> > edges)
{
	int count = 1,n = edges.size(), ans = -1;
	rep(i,0,n) edges[i][0]--, edges[i][1]--;
	rep(i,0,n)
	{
		int count = 1;
		vector<set<int> > parent(n, set<int>());
		parent[i].insert(-1);
		helper(edges, i, parent, n, count);
		if(count != n) continue;
		rep(j,0,n)
		{
			auto it = parent[j].end();
			if(parent[j].size() > 1)
			{
				--it;
				ans = max(ans, *it);
				cout << j+1 << endl;
			}
		}
	}
	if(ans == -1) return vector<int>();
	return edges[ans];
}


int main()
{
	int n;
	cin >> n;
	vector<vector<int> > edges(n, vector<int>(2,0));
	rep(i,0,n)
	{
		cin >> edges[i][0] >> edges[i][1];
	}
	vector<int> sol = findRedundantDirectedConnection(edges);
	for(int &a: sol) cout << a+1 << " ";
	return 0;
}

