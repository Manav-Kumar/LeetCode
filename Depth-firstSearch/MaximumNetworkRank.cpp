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
#include <algorithm>
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
#define vd vector<double>
#define vvd vector<vd>
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>


int maximaNetworkRank(int n, vvi &roads){
	vi count(n, 0);
	vvi graph(n, vi(n, 0));
	for(vi &edges: roads){
		count[edges[0]]++, count[edges[1]]++;
		graph[edges[0]][edges[1]] = 1, graph[edges[1]][edges[0]] = 1;
	}
	int ans = 0;
	for(int i = 0;i < n;i++){
		for(int j = i + 1;j < n;j++){
			ans = max(ans, count[i] + count[j] -  (graph[i][j] == 1?1:0));
		}
	}
	return ans;
}

//	Path with Maximum Probability
double maxProbability(int n, vvi &edges, vd &succProb, int start, int end){

	priority_queue<pair<double,int>, vector<pair<double,int> > > pq;
	vvi adj(n, vi());
	map<pair<int,int>, double> weights;
	for(int i = 0;i < edges.size();i++){
		vi a = edges[i];
		adj[a[0]].push_back(a[1]), adj[a[1]].push_back(a[0]);
		weights[{a[0], a[1]}] = succProb[i];
		weights[{a[1], a[0]}] = succProb[i];
	}

	vb visited(n, false);
	vd currProb(n, 0.0);
	pq.push({1.0, start});
	while(!pq.empty()){
		int node = pq.top().second;
		double d = pq.top().first; pq.pop();
		if(node == end) return d;
		visited[node] = true;
		for(int &next: adj[node]){
			if(!visited[next] && currProb[next] < (d * weights[{node, next}])){
				currProb[next] = d * weights[{node, next}];
				pq.push({currProb[next], next});
			}
		}
	}
	return 0;
}

pair<double,int> getIdx(int n, vd &currProb, vb &visited){

	pair<double,int> ans(-0.1, -1);
	for(int i = 0;i < n;i++){
		if(!visited[i] && ans.first < currProb[i]){
			ans.first = currProb[i], ans.second = i;
		}
	}
	return ans;
}

double maxProbability2(int n, vvi &edges, vd &succProb, int start, int end){

	vb visited(n, false);
	vd currProb(n, 0.0);
	currProb[start] = 1.0;
	int count = 0;
	while(count < n){
		pair<double,int> pq = getIdx(n, currProb, visited);
		int node = pq.second;
		double d = pq.first;
		if(node == end || d == 0) return d;
		visited[node] = true, count++;
		for(int i = 0;i < edges.size();i++){
			vi a = edges[i];
			if(a[0] == node && !visited[a[1]] && currProb[a[1]] < (d * succProb[i])){
				currProb[a[1]] = d * succProb[i];
			}
			else if(a[1] == node && !visited[a[0]] && currProb[a[0]] < (d * succProb[i])){
				currProb[a[0]] = d * succProb[i];
			}
		}
	}
	return 0;
}


double maxProbability3(int n, vvi &edges, vd &succProb, int start,int end){
	vb visited(n, false);
	vd currProb(n, 0.0);
	currProb[start] = 1;
	vector<vector<pair<int,double> > > adj(n, vector<pair<int,double> >());
	for(int i = 0;i < edges.size();i++){
		vi a = edges[i];
		adj[a[0]].push_back({a[1], succProb[i]});
		adj[a[1]].push_back({a[0], succProb[i]});
	}

	priority_queue<pair<double,int>, vector<pair<double,int> > > pq;

	pq.push({1.0, start});
	while(!pq.empty()){
		int node = pq.top().second;
		double d = pq.top().first; pq.pop();
		if(node == end) return d;
		visited[node] = true;
		for(auto next: adj[node]){
			if(!visited[next.first] && currProb[next.first] < (d * next.second)){
				currProb[next.first] = d * next.second;
				pq.push({currProb[next.first], next.first});
			}
		}
	}
	return 0;

}



int main(){

	return 0;
}



