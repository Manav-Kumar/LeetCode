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
#define vi vector<int>
#define vvi vector<vi >
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>

void ForwardPass(vvi &connections,int idx,vb &visited, stack<int> &s){

	visited[idx] = true;
	for(int &next: connections[idx]){
		if(!visited[next]) ForwardPass(connections, next, visited, s);
	}
	s.push(idx);
}

void reversePass(vvi &tranConnections, int idx,vb &visited, unordered_set<int> *t){

	visited[idx] = true;
	t->insert(idx);
	for(int &next: tranConnections[idx]){
		if(!visited[next]) reversePass(tranConnections, next, visited, t);
	}
}

unordered_set<unordered_set<int>* >* ssc(vvi &adj)
{
	int n = adj.size();
	vvi connections(n), tranConnections(n);
	for(int i = 0;i < n;i++){
		for(int &next: adj[i]){
			connections[i].push_back(next);
			tranConnections[next].push_back(i);
		}
	}
	vb visited(n, false);
	stack<int> s;
	for(int i = 0;i < n;i++){
		if(!visited[i]) ForwardPass(connections, i, visited, s);
	}
	visited.clear(), visited.resize(n, false);
	unordered_set<unordered_set<int>* >* ans = new unordered_set<unordered_set<int>* >();
	while(!s.empty()){
		int val = s.top(); s.pop();
		if(visited[val]) continue;
		unordered_set<int> *t = new unordered_set<int>();
		reversePass(tranConnections, val, visited, t);
		ans->insert(t);
	}

	return ans;
}

int main(){
	int n, m, a, b;
	cin >> n >> m;
	vvi adj(n);
	while(m--){
		cin >> a >> b;
		adj[a].push_back(b);
	}
	unordered_set<unordered_set<int>* > * ans = ssc(adj);
	for(auto it = ans->begin();it != ans->end();it++){
		unordered_set<int> *t = *it;
		for(auto t2 = t->begin();t2 != t->end();t2++) cout << *t2 << " ";
		cout << "\n";
	}
	return 0;
}

