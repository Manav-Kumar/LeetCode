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


int minDistance(string w1,string w2,int id1 = 0,int id2 = 0)
{
	if(id1 == w1.size() || id2 == w2.size()){
		return w2.size() - id2 + w1.size() - id1;
	}

	if(w1[id1] == w2[id2]) return minDistance(w1, w2, id1 + 1,id2 + 1);

	int a1 = minDistance(w1, w2, id1, id2 + 1) + 1;//Insert Operation
	int a2 = minDistance(w1, w2, id1 + 1,id2) + 1;//Delete Character
	int a3 = minDistance(w1, w2, id1 + 1,id2 + 1) + 1;//Replace Character

	return min({a1, a2, a3});
}


int minDistance2(string w1, string w2)
{
	int n = w1.size(), m = w2.size();
	vvi dp(n + 1, vi(m + 1,0));
	for(int j = m;j >= 0;j--) dp[n][j] = m - j;
	for(int i = n;i >= 0;i--) dp[i][m] = n - i;

	vvi dp2(2, vi(m + 1, 0));
	int curr = 1;
	for(int j = m;j >= 0;j--) dp2[curr][j] = m - j;
	dp2[0][m] = 1;
	curr ^= 1;
	
	vi lastCol(n + 1);
	for(int i = n;i >= 0;i--) lastCol[i] = n - i;

	for(int i = n-1;i >= 0;i--){
		for(int j = m-1;j >= 0;j--)
		{
			int &ans = dp[i][j];
			ans = INT_MAX;
			if(w1[i] == w2[j]) ans = min(ans, dp[i + 1][j + 1]);
			else{
				ans = min({ans, dp[i][j + 1] + 1, dp[i + 1][j] + 1, dp[i + 1][j + 1] + 1});
			}
		}
	}

	for(int i = n-1; i >= 0;i--){
		for(int j = m-1;j >= 0;j--)
		{
			int &ans = dp2[curr][j];
			ans = INT_MAX;
			int d, r, dr;
			d = dp2[curr^1][j];
			if(j == m - 1){
				r = lastCol[i], dr = lastCol[i + 1];
			}
			else{
				r = dp2[curr][j + 1], dr = dp2[curr^1][j + 1];
			}
			if(w1[i] == w2[j]) ans = min(ans, dr);
			else{
				ans = min({ans, r + 1, d + 1, dr + 1 });
			}
		}
		curr ^= 1;
	}

	return dp2[curr^1][0];
}

int main(){
	string w1, w2;
	cin >> w1 >> w2;
	cout << minDistance2(w1, w2) << "\n";
	return 0;
}

