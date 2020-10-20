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
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vl vector<long>
#define vll vector<long long>
#define vc vector<char>
#define vs vector<string>
#define vvc vector<vc>
#define vvi vector<vector<int> >
#define vvl vector<vl>
#define vvll vector<vll>
#define vvb vector<vector<bool> >


double helper(vector<double> &ratios,vector<int> &wage,double ***dp,int k,int idx,int i = 0)
{
	if(k == 0) return 0;
	if(i == wage.size()) return -1;
	if(dp[idx][i][k] != -1) return dp[idx][i][k];
	if(i == idx) return helper(ratios, wage, dp, k, idx, i+1);
	double a1 = helper(ratios, wage, dp, k, idx, i + 1);
	double a2 = INT_MAX;
	if(ratios[i] >= ratios[idx]){
		a2 = helper(ratios, wage, dp, k - 1, idx, i + 1);
		if(a2 != -1) a2 += (ratios[i]/ratios[idx])*wage[i];
	}
	if(a1 == -1 || a2 == -1) return fmax(a1, a2);
	return fmin(a1, a2);
}

double minCostHireKWorkers(vector<int> &quality,vector<int> &wage,int k){
	int n = quality.size();
	vector<double> ratios(n);
	for(int i=0;i<n;i++){
		ratios[i] = ((double)quality[i])/wage[i];
	}
	double ***dp = new double**[n];
	for(int i=0;i<n;i++){
		dp[i] = new double*[n];
		for(int j=0;j<n;j++)
		{
			dp[i][j] = new double[k+1]();
			fill(dp[i][j], dp[i][j] + k + 1, -1);
		}
	}
	double ans = INT_MAX;
	for(int i=0;i<n;i++){
		ans = min(ans, helper(ratios, wage, dp, k - 1, i) + wage[i]);
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++) delete []dp[i][j];
		delete []dp[i];
	}
	delete []dp;
	return ans;
}


class comparator
{
public:
	comparator() {}

	bool operator() (const pair<double,int> &a, const pair<double,int> &b){
		return a.first > b.first;
	}
	
};

class node{
public:
	double quality,wage;
	node(double q = 0, double w = 0): quality(q), wage(w) {}
};

bool compare(const node &a, const node &b){
	return a.quality < b.quality;
}

double minCostHireKWorkers2(vector<int> &quality, vector<int> &wage,int k)
{
	int n = quality.size(), j = 0;
	vector<node> vn(n);
	for(int i=0;i<n;i++) vn[i] = node(quality[i], wage[i]);
	sort(vn.begin(), vn.end(), compare);

	priority_queue<pair<double,int>, vector<pair<double,int> >, comparator> q;

	vector<double> ratios(n);
	for(int i=0;i<n;i++)
	{
		ratios[i] = vn[i].quality/vn[i].wage;
		q.push(pair<double,int> (ratios[i], i));
	}

	vector<bool> visited(n, false);
	double ans = 100123, sum = 0;
	for(;j<k&&j<n;j++)
	{
		visited[j] = true;
		sum += vn[j].quality;
	}

	while(!q.empty() && j <= n)
	{
		pair<double,int> top = q.top();
		q.pop();
		ans = fmin(ans, (double)(sum/top.first));
		if(top.second >= j){
			visited[top.second] = true;
		}
		else{
			sum -= vn[top.second].quality;
			while(j < n && visited[j]) j++;
			if(j != n){
				sum += vn[j].quality;
				j++;
			}
			else break;
		}
	}

	return ans;

}


int main()
{
	int n,k;
	cin >> n;
	vi quality(n), wage(n);
	for(int &a: quality) cin >> a;
	for(int &a: wage) cin >> a;
	cin >> k;
	cout << minCostHireKWorkers2(quality, wage, k) << "\n";
	return 0;
}


