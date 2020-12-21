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



bool helper(vvi &edges,vb &visited,int &count,int &forbiddenEdge,int idx = 1,int parent = -1){

	if(visited[idx] == true) return false;
	int m = edges.size();
	visited[idx] = true, count++;
	for(int j = 0;j < m;j++){
		if(forbiddenEdge == j) continue;
		vi e = edges[j];
		bool check = true;
		if(e[0] == idx && e[1] != parent){
			check = helper(edges, visited, count, forbiddenEdge, e[1], idx);
		}
		else if(e[1] == idx && e[0] != parent){
			check = helper(edges, visited, count, forbiddenEdge, e[0], idx);
		}
		if(!check) return false;
	}

	return true;
}


vi findRedundantConnection(vvi &edges){
	int n = 0, m = int(edges.size());
	for(vi &a: edges) n = max({n, a[0], a[1]});
	for(int i = m - 1;i >= 0;i--){
		int count = 0;
		vb visited(n + 1, false);
		bool check = helper(edges, visited, count, i);
		if(check && count == n){
			return edges[i];
		}
	}
	
	return vi();
}


bool helper2(vvi &edges, vb &visited, int &ans, vpii &Parents, int index = -1, int vertex = 1,int parent = 0){

	if(visited[vertex]){
		ans = index;
		while(parent != vertex){
			ans = max(ans, Parents[parent].second);
			parent = Parents[parent].first;
		}
		return false;
	}
	int m = edges.size();
	visited[vertex] = true;
	Parents[vertex] = {parent, index};
	for(int j = m - 1;j >= 0;j--){
		bool check = true;
		vi e = edges[j];
		if(e[0] == vertex && e[1] != parent){
			check = helper2(edges, visited, ans, Parents, j, e[1], vertex);
		}
		else if(e[1] == vertex && e[0] != parent){
			check = helper2(edges, visited, ans, Parents, j, e[0], vertex);
		}
		if(!check){
			return false;
		}
	}

	return true;
}

vi findRedundantConnection2(vvi &edges){
	int n = edges.size(), ans = -1;
	vb visited(n + 1, false);
	vpii Parents(n + 1, {-1, -1});
	helper2(edges, visited, ans, Parents);
	return edges[ans];
}


//	Union Find Alg

bool detectCycle(vi &Components, int &a, int &b){

	while(Components[a] != a) a = Components[a];
	while(Components[b] != b) b = Components[b];
	return a == b;
}

vi findRedundantConnection3(vvi &edges){
	int n = edges.size();//It has got 1 redundant edge
	//	Edges Consist of number from 1 to N
	vi Components(1, 0) , Parents(n + 1, -1);
	rep(i, 1, n + 1) Components.push_back(i);
	for(int i = 0;i < n;i++){
		vi e = edges[i];
		int a = e[0], b = e[1];
		if(detectCycle(Components, a, b)){
			return e;
		}
		else Components[b] = a;
	}
	return vi();
}



int main(){
	int m;
	cin >> m;
	vvi edges(m, vi(2));
	for(vi &a: edges) cin >> a[0] >> a[1];
	vi ans = findRedundantConnection2(edges);
	for(int &a: ans) cout << a << " ";
	cout << "\n";
	return 0;
}