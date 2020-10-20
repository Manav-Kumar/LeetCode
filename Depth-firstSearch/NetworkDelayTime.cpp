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
#define vvs vector<vs>

//	Djkastra Alg
int getIdx(vi &weight,unordered_set<int> visited){
	int n = weight.size() - 1, value = INT_MAX, idx = -1;
	for(int i = 1;i <= n;i++){
		if(visited.count(i) == 0 && weight[i] <= value){
			value = weight[i], idx = i;
		}
	}
	return idx;
}

int networkDelayTime(vvi &times, int N,int K){
	vi weight(N + 1, INT_MAX);
	weight[K] = 0;
	unordered_set<int> visited;
	while(visited.size() < N){
		int node = getIdx(weight, visited);
		visited.insert(node);
		if(weight[node] == INT_MAX) return -1;
		for(vi &a: times){
			if(node == a[0] && visited.count(a[1]) == 0){
				weight[a[1]] = min(weight[a[1]], weight[node] + a[2]);
			}
		}
	}
	int ans = 0;
	for(int i = 1;i <= N;i++){
		ans = max(ans, weight[i]);
	}
	return ans;
}

int main(){

	return 0;
}


