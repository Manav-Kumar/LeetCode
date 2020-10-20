#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <cmath>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define ll long long


int helper(int target,vvi &stations, int fuel,int idx = 0)
{
	if(fuel < 0) return 1000;
	if((idx + 1) == stations.size()){
		
		int nextMiledist = target - stations[idx][0];
		if(nextMiledist <= fuel) return 0;
		if(nextMiledist <= (fuel + stations[idx][1])) return 1;
		return 1000;
	}



	int nextMiledist = stations[idx + 1][0] - stations[idx][0];

	int a1 = helper(target, stations, fuel - nextMiledist, idx + 1);
	int a2 = helper(target, stations, fuel + stations[idx][1] - nextMiledist, idx + 1) + 1;

	int ans = min(a1, a2);

	return ans;
}

int minRefuelStops(int target, int startFuel, vvi &stations)
{
	if(stations.size() == 0){
		return startFuel >= target?0:-1;
	}

	int nextMiledist = stations[0][0];
	int ans = helper(target, stations, startFuel - nextMiledist);
	if(ans > stations.size()) return -1;
	return ans;
}

int minRefuelStops2(int target,int startFuel,vvi &stations)
{
	int ans = 0, n = stations.size(), curfuel = startFuel, curmile = 0;
	priority_queue<int> tanks;
	for(int i = 0;i < n;i++){

		int nexdst = stations[i][0] - curmile;
		while(!tanks.empty() && curfuel < nexdst){
			curfuel += tanks.top();
			tanks.pop();
			ans++;
		}
		
		if(curfuel < nexdst) return -1;
		else curfuel -= nexdst;

		curmile += nexdst;
		tanks.push(stations[i][1]);
	}

	int nexdst = target - curmile;

	while(!tanks.empty() && curfuel < nexdst){
		curfuel += tanks.top();
		tanks.pop();
		ans++;
	}

	return curfuel >= nexdst?ans:-1;
}

int minRefuelStops3(int target,int startFuel,vvi &stations)
{
	int n = stations.size();
	vector<ll> dp(n + 1, 0);
	dp[0] = startFuel;

	for(int i = 0;i < n;i++){

		for(int t = i;t >= 0;t--){
			if(dp[t] >= stations[i][0]){
				dp[t + 1] = max(dp[t + 1], dp[t] + (ll)stations[i][1]);
			}
		}
	}

	for(int i = 0;i<=n;i++){
		if(dp[i] >= target) return i;
	}
	return -1;
}



int main(){
	int n, target, startFuel;
	cin >> target >> startFuel >> n;
	vvi stations(n);
	for(vi &a: stations){
		a.resize(2);
		cin >> a[0] >> a[1];
	}
	cout << minRefuelStops2(target, startFuel, stations) << "\n";
	return 0;
}


