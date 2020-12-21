#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>

pair<int,int> longestDist(vector<vector<pair<int,int> > > &adj, int st = 1,int last = -1){

	int fmax = 0, smax = 0, prevmaxHt = 0;
	for(pair<int,int> &next: adj[st]){
		if(next.first == last) continue;
		pair<int,int> smallAns = longestDist(adj, next.first, st);
		smallAns.first += next.second;
		prevmaxHt = max(prevmaxHt, smallAns.second);
		if(smallAns.first > fmax) smax = fmax, fmax = smallAns.first;
		else if(smallAns.first > smax) smax = smallAns.first;
	}

	return pair<int,int> (fmax, max(prevmaxHt, fmax + smax));
}

int main(){
	int n, a, b, c;
	cin >> n;
	vector<vector<pair<int,int> > > adj(n);
	for(int i=0;i<n-1;i++){
		cin >> a >> b >> c;
		a--, b--;
		adj[a].push_back({b, c});
		adj[b].push_back({a, c});
	}
	cout << longestDist(adj).second << "\n";
	return 0;
}

