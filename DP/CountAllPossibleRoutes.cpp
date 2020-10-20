#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <cmath>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vmp vector<map<int,int> >
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvmp vector<vmp>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define ll long long

ll mod = 1e9 + 7;


int countRoutes(vi &locations, int start,int finish, int fuel,vvi &dp)
{
	if(fuel < 0) return 0;
	if(dp[start][fuel] != -1) return dp[start][fuel];
	int n = locations.size(), ans = (start == finish?1:0);
	for(int i = 0;i < n;i++){
		if(i == start) continue;
		ans = (ans + countRoutes(locations, i, finish, fuel - abs(locations[i] - locations[start]), dp))%mod;
	}
	dp[start][fuel] = ans;
	return ans;
}


int main(){
	int n, start, finish, fuel;
	cin >> n;
	vi locations(n);
	for(int &a: locations) cin >> a;
	cin >> start >> finish >> fuel;
	vvi dp(n, vi(fuel + 1, -1));
	cout << countRoutes(locations, start, finish, fuel, dp);
	return 0;
}



