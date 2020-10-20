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

int helper(vi &stoneValue,int ascore = 0, int bscore = 0, int idx = 0,bool turn = true)
{
	int n = stoneValue.size();
	if(idx >= n){
		if(ascore > bscore) return 10;
		else if(ascore < bscore) return -10;
		else return 0;
	}

	int s1 = stoneValue[idx], s2 = s1 + ((idx + 1) < n?stoneValue[idx + 1]:0);
	int s3 = s2 + ((idx + 2) < n?stoneValue[idx + 2]:0);
	int a1, a2, a3;
	if(turn){
		a1 = helper(stoneValue, ascore + s1, bscore, idx + 1, !turn);
		a2 = helper(stoneValue, ascore + s2, bscore, idx + 2, !turn);
		a3 = helper(stoneValue, ascore + s3, bscore, idx + 3, !turn);
	}
	else{
		a1 = helper(stoneValue, ascore, bscore + s1, idx + 1, !turn);
		a2 = helper(stoneValue, ascore, bscore + s2, idx + 2, !turn);
		a3 = helper(stoneValue, ascore, bscore + s3, idx + 3, !turn);
	}
	
	if(turn) return max({a1, a2, a3});
	else return min({a1, a2, a3});
}


int helper2(vi &stoneValue)
{
	int n = stoneValue.size();
	vpii dp(n, {0, 0});

	int &ans = dp[0].first;

	int s1 = stoneValue[n - 1];
	dp[n-1] = pair<int,int> (s1, -1*s1);
	if(n == 1) return ans;

	int s2 = s1 + stoneValue[n - 2];
	dp[n-2].first = max({s2, stoneValue[n-2] + dp[n-1].second});
	dp[n-2].second = min({-1*s2, -1*stoneValue[n-2] + dp[n-1].first});
	if(n == 2) return ans;

	int s3 = s2 + stoneValue[n - 3];
	dp[n-3].first = max({s3, stoneValue[n-3] + stoneValue[n-2] + dp[n-1].second, stoneValue[n-3] + dp[n-2].second});
	dp[n-3].second = min({-1*s3, -1*stoneValue[n-3] + -1*stoneValue[n-2] + dp[n-1].first, -1*stoneValue[n-3] + dp[n-2].first});
	if(n == 3) return ans;

	for(int i = n-4;i >= 0;i--)
	{
		s1 = stoneValue[i], s2 = s1 + stoneValue[i + 1], s3 = s2 + stoneValue[i + 2];

		dp[i].first = max({s1 + dp[i + 1].second, s2 + dp[i + 2].second, s3 + dp[i + 3].second });
		dp[i].second = min({-1*s1 + dp[i + 1].first, -1*s2 + dp[i + 2].first, -1*s3 + dp[i + 3].first });
	}

	return ans;
}

string stoneGame3(vector<int> &stoneValue){
	int ans = helper2(stoneValue);
	if(ans < 0) return "Bob";
	else if(ans > 0) return "Alice";
	else return "Tie";
}

int main(){
	int n;
	cin >> n;
	vi stoneValue(n);
	for(int &a: stoneValue) cin >> a;
	cout << stoneGame3(stoneValue) << "\n";
	return 0;
}



