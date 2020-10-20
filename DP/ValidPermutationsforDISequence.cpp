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

ll mod = 1e9 + 7;

int numPermsDISequence(string s){
	int n = s.size();
	vector<vector<int64_t> > dp(n + 1, vector<int64_t> (n + 1, 0));
	for(int i = 0;i <= n;i++) dp[0][i] = 1;
	//dp[0][0] = 0;

	for(int s_len = 1;s_len <= n;s_len++){

		for(int rank = 0;rank <= s_len;rank++){
			if(s[s_len - 1] == 'D'){
				for(int k = rank;k < s_len;k++){
					dp[s_len][rank] += dp[s_len - 1][k];
				}
			}
			else if(s[s_len - 1] == 'I'){

				for(int k = 0;k < rank;k++){
					dp[s_len][rank] += dp[s_len - 1][k];
				}
			}
			dp[s_len][rank] %= mod;
		}
	}

	for(int i = 0;i <= n;i++){
		for(int j = 0;j <= n;j++) cout << dp[i][j] << " ";
		cout << "\n";
	}
	int64_t ans = 0;
	for(int64_t &a: dp[n]){
		ans += a;
		ans %= mod;
	}
	return ans;
}


int numPermsDISequence2(string s)
{
	int n = s.size();
	vector<vector<ll> > dp(n + 1, vector<ll> (n + 1, 0));
	for(int i = 0;i <=n;i++) dp[0][i] = 1;

	vector<int> G = {0, 1};

	for(int s_len = 0;s_len < n;s_len++){

		vector<int> ng = {0};

		for(int rank = 0;rank <= s_len + 1;rank++){
			int k;
			if(s[s_len] == 'I'){
				k = G[s_len + 1] - G[rank];
			}
			else{
				k = G[rank];
			}
			ng.push_back(ng.back() + k);
		}

		G.swap(ng);

	}

	return G[n + 1];

}

int main(){
	string s;
	cin >> s;
	cout << numPermsDISequence2(s) << "\n";
	return 0;
}

