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


//	Kruskal's Alg -> Find the Minimum Spanning Tree
bool compare(vi &a, vi &b){
	return a[2] <= b[2];
}

bool detectCycle(vi &ParentComponent,int a,int b){

	while(ParentComponent[a] != a) a = ParentComponent[a];
	while(ParentComponent[b] != b) b = ParentComponent[b];

	return a == b;
}

vvi MST(int n, vvi &edges){
	sort(edges.begin(), edges.end(), compare);
	vvi ans;
	vi ParentComponent;
	for(int i = 0;i < n;i++) ParentComponent.push_back(i);

	int idx = 0;
	while(ans.size() < n - 1){
		vi e = edges[idx++];
		if(detectCycle(ParentComponent, e[0], e[1])) continue;
		ans.push_back(e);
		int a = e[0], b = e[1];
		while(ParentComponent[a] != a) a = ParentComponent[a];
		while(ParentComponent[b] != b) b = ParentComponent[b];
		ParentComponent[b] = a;
	}
	return ans;
}


int main(){
	int n, m;
	cin >> n >> m;
	vvi edges(m, vi(3));
	for(vi &a: edges) cin >> a[0] >> a[1] >> a[2];
	vvi ans = MST(n, edges);
	for(vi &a: ans) cout << a[0] << " " << a[1] << " " << a[2] << "\n";
	return 0;
}

