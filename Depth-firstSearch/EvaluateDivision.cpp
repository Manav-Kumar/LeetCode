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
#define vd vector<double>

double dfs(unordered_map<string, vector<pair<double,string> > > adj, string src, string dst,unordered_set<string> &visited){

	if(src == dst) return 1;

	visited.insert(src);
	double a1, a2;
	string k;
	for(pair<double,string> &a: adj[src]){
		a2 = a.first, k = a.second;
		if(visited.count(k) > 0) continue;
		a1 = dfs(adj, k, dst, visited);
		if(a1 != -1) return a2*a1;
	}
	return -1;
}

vd calcEquation(vvs &equations, vd &values, vvs &queries){
	int n = values.size();
	unordered_map<string, vector<pair<double,string> > > adj;
	unordered_set<string> isPresent;
	for(int i = 0;i < n;i++){
		vs s = equations[i];
		adj[s[0]].push_back({values[i], s[1]});
		isPresent.insert(s[0]), isPresent.insert(s[1]);
	}
	vd ans;
	for(vs &s: queries){
		unordered_set<string> visited;
		if(isPresent.count(s[0]) == 0 || isPresent.count(s[1]) == 0) ans.push_back(-1);
		else ans.push_back(dfs(adj, s[0], s[1], visited));
	}
	return ans;
}




int main(){
	int m;
	cin >> m;
	vvi edges(m, vi(2));
	for(vi &a: edges) cin >> a[0] >> a[1];
	cout << "done\n";
	vi ans = findRedundantDirectedConnection(edges);
	cout << ans[0] << " " << ans[1] << "\n";
	return 0;
}




