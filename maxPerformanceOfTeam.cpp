#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

#define MOD 1000000007

long long maxPerformance(int n,vector<int> speed,vector<int> efficiency,int k,
						int index = 0,int minEfi = -1,long long sum = 0)
{
	if(k == 0 || index == n)
	{
		if(minEfi == -1) return 0;
		return ((minEfi%MOD)*sum)%MOD;
	}

	long long a1 = maxPerformance(n, speed, efficiency, k, index+1, minEfi, sum);

	long long newEffi;
	if(minEfi == -1) newEffi = efficiency[index];
	else newEffi = min(minEfi, efficiency[index]);
	long long a2 = maxPerformance(n, speed, efficiency, k-1, index+1,
						newEffi , (sum + (speed[index]%MOD))%MOD);

	long long a3 = 0;
	if(minEfi != -1) a3 = ((minEfi%MOD)*sum)%MOD;
	long long ans = max(max(a1, a2), a3);
	return ans;
}

//IT'S NOT AT ALL A DP PROBLEM, DON'T EVEN TRY TO MAKE IT. IT'S GREEDY PROBLEM

// <-----
// GREEDY PROBLEM
// ------>


int maxPerformance2(int n,vector<int> speed,vector<int> efficiency,int k)
{
	vector<pair<int,int> > res;
	for(int i = 0;i < n;i++) res.emplace_back(efficiency[i], speed[i]);
	sort(res.rbegin(), res.rend());
	priority_queue<int, vector<int>, greater<int> > pq;//min heap
	long long ans = 0, sSum = 0;
	for(auto &[e,s]: res)
	{
		pq.push(s);
		sSum += s;
		if(pq.size() > k)
		{
			sSum -= pq.top();
			pq.pop();
		}
		ans = max(ans, sSum*e);
	}
	return ans%int(1e9+7);
}



int main()
{
	int n,k;
	vector<int> speed, effi;
	cin >> n;
	speed.resize(n), effi.resize(n);
	for(int &a: speed) cin >> a;
	for(int &a: effi) cin >> a;
	cin >> k;
	cout << maxPerformance2(n, speed, effi, k) << endl;
	cout << maxPerformance(n, speed, effi, k) << endl;
	return 0;
}