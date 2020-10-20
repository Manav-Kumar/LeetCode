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


int findMaximizedCapital(int k,int w,vi &profits, vi &capital){
	int n = profits.size();
	vb visited(n, false);
	for(int it = 0;it < min(n, k);it++){
		int p = -1, idx = -1;
		for(int i = 0;i < n;i++){
			if(!visited[i] && w >= capital[i] && p < profits[i]){
				p = profits[i], idx = i;
			}
		}
		if(idx == -1) return w;
		w += p, visited[idx] = true;
	}

	return w;
}

bool compare(pair<int,int> &a, pair<int,int> &b){
	return a.second < b.second;
}



int findMaximizedCapital2(int k,int w,vi &profits,vi &capital)
{
	int n = profits.size();
	vpii arr(n);
	rep(i, 0, n){
		arr[i] = {profits[i], capital[i]};
	}
	sort(arr.begin(), arr.end(), compare);
	int idx = 0;
	if(arr[idx].second > w) return w;
	priority_queue<int> q;

	for(int it = 0;it < min(n, k);it++){

		while(idx < n && arr[idx].second <= w){
			q.push(arr[idx].first), idx++;
		}

		if(q.empty()) return w;

		int v = q.top(); q.pop();
		w += v;
	}

	return w;

}


int main(){
	int k, w, n;
	cin >> k >> w >> n;
	vi profits(n), capital(n);
	for(int &a: profits) cin >> a;
	for(int &a: capital) cin >> a;
	cout << findMaximizedCapital(k, w, profits, capital) << "\n";
	return 0;
}


