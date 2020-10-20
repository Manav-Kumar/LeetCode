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


int getIndex(unordered_set<int> &visited, vi &weight){
	int idx = -1, value = INT_MAX, n = weight.size();
	for(int i = 0;i < n;i++){
		if(visited.count(i) == 0 && weight[i] <= value){
			value = weight[i], idx = i;
		}
	}
	return idx;
}

vi djkastra(int src,vvi &connections){
	int n = connections.size();
	vi weight(n, INT_MAX);
	weight[src] = 0;
	unordered_set<int> visited;
	while(visited.size() < n){
		int node = getIndex(visited, weight);
		visited.insert(node);
		if(weight[node] == INT_MAX) break;//	Means the smallest dst between src and curr node is infinity i.e not reachable
		for(int i = 0;i < n;i++){
			if(connections[node][i] > 0 && node != i && visited.count(i) == 0){
				weight[i] = min(weight[i], weight[node] + connections[node][i]);
			}
		}
	}
	return weight;
}



vi djkastra2(int src, vvi &connections){
	int n = connections.size();
	vi weight(n, INT_MAX);
	weight[src] = 0;
	unordered_set<int> visited;
	priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > pq;
	pq.push({0,src});
	while(!pq.empty()){
		int node = pq.top().second, wt = pq.top().first; pq.pop();
		if(visited.count(node) > 0) continue;
		visited.insert(node);
		if(wt == INT_MAX) break;
		for(int i = 0;i < n;i++){
			if(connections[node][i] > 0 && node != i && visited.count(i) == 0){
				if(weight[i] > weight[node] + connections[node][i]){
					weight[i] = weight[node] + connections[node][i];
					pq.push({weight[i], i});
				}
			}
		}
	}
	return weight;
}

int findTheCity(int n,vvi &edges, int distanceThreshold){

	vvi connections(n, vi(n, 0));
	for(vi &a: edges){
		connections[a[0]][a[1]] = a[2];
		connections[a[1]][a[0]] = a[2];
	}

	int minCount = INT_MAX, ans = -1;
	vvi distances(n);
	rep(i, 0, n){
		distances[i] = djkastra2(i, connections);
		int ct = 0;
		for(int j = 0;j < n;j++){
			if(i != j && distances[i][j] <= distanceThreshold) ct++;
		}
		if(ct <= minCount){
			minCount = ct, ans = i;
		}
	}
	return ans;
}


int main(){
	int n, m, a, b, c, distanceThreshold;
	cin >> n >> m;
	vvi edges(m, vi(3));
	for(int i = 0;i < m;i++){
		cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
	}
	cin >> distanceThreshold;
	cout << findTheCity(n, edges, distanceThreshold) << "\n";
	return 0;
}