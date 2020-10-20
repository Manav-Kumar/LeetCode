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


//	Finding the shortest distance between every pair
int findTheCity(int n,vvi &edges, int distanceThreshold){

	vvi dp(n, vi(n, INT_MAX));
	for(vi &a: edges){
		dp[a[0]][a[1]] = a[2];
		dp[a[1]][a[0]] = a[2];
	}

	for(int k = 0;k < n;k++){
		rep(i, 0, n){
			rep(j, 0, n){
				dp[i][j] = min((long)dp[i][j], (long)dp[i][k] + (long)dp[k][j]);
			}
		}
	}
	int ans = -1, count = INT_MAX;
	for(int i = 0;i < n;i++){
		int ct = 0;
		for(int j = 0;j < n;j++){
			if(i!=j && dp[i][j] <= distanceThreshold) ct++;
		}
		if(ct <= count){
			count = ct, ans = i;
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