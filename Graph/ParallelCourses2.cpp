#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>


//	Here in each semester we can take maximum K courses
class Solution{
public:
	int n, k;
	vector<int> graph[15];
	vector<int> dp;

	int req_sem(int mask){

		if(mask == ((1<<n) - 1)) return dp[mask] = 0;

		if(dp[mask] != -1) return dp[mask];

		vector<int> indeg(n, 0);
		for(int i=0;i<n;i++){
			if(mask&(1<<i)) continue;
			for(int &next: graph[i]){
				indeg[next]++;
			}
		}

		int avail_mask = 0;
		for(int i=0;i<n;i++) if(indeg[i] == 0 && !(mask&(1<<i))) avail_mask |= (1<<i);

		int num_avail = __builtin_popcount(avail_mask);
		int taken = n + 1;

		if(num_avail <= k) taken = 1 + req_sem(mask | avail_mask);
		else{
			for(int s = avail_mask;s > 0;s = (s - 1)&avail_mask){
				if(__builtin_popcount(s) == k){
					taken = min(taken, 1 + req_sem(mask | s));
				}
			}
		}

		return dp[mask] = taken;
	}

	int minNumberOfSemesters(int N, vvi &dependencies, int K){
		n = N, k = K;
		dp.assign((1<<n), -1);
		for(vi &a: dependencies){
			a[0]--, a[1]--;
			graph[a[0]].push_back(a[1]);
		}

		int ans = req_sem(0);
		return ans;
	}
};

//	Here in each semester we can take as many course as wanted
class Solution2{
	int n;
	vector<vector<int> >graph;
public:


	int minSemesters(int N,vector<vector<int> > &dependencies){ 
		n = N;
		vi indeg(n, 0);
		for(vi &a: dependencies){
			indeg[a[1]]++;
		}
		int count = 0, semester = 0;
		queue<int> q;
		for(int i=0;i<n;i++) if(indeg[i] == 0) q.push(i), count++;

		while(!q.empty()){
			int sz = q.size();
			while(sz--){
				int top = q.front(); q.pop();
				for(int &next: graph[top]){
					indeg[next] --;
					if(indeg[next] == 0) q.push(next), count++;
				}
			}
			semester++;
		}

		return count != n?-1: semester;
	}
};

int main(){
	int n, k, m;
	cin >> n >> k >> m;
	vvi dependencies(m, vi(2));
	for(vi &a: dependencies) cin >> a[0] >> a[1];
	//cout << minNumberOfSemesters(n, dependencies, k) << "\n";
	return 0;
}

