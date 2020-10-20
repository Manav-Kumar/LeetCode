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
int N, L, K;

int numMusicPlayLists(int len,int num){

	if(len == L){
		return num == N;
	}
	if(num > N) return 0;
	int ans = numMusicPlayLists(len + 1, num) * max(0, num - K);
	ans += numMusicPlayLists(len + 1, num + 1) * (N - num);
	return ans;
}

int helper(vvi &A,int r,int c,vector<int> arr)
{
	if(r == A.size()){
		int ans = 0;
		for(int &a: arr){
			cout << a << " ";
			ans += a;
		}
		cout << ": " << ans << "\n";
		return 0;
	}
	if(c < 0 || c >= A[0].size()) return 100000;

	arr.push_back(A[r][c]);

	int a1 = helper(A, r + 1, c, arr);
	int a2 = helper(A, r + 1, c - 1, arr);
	int a3 = helper(A, r + 1, c + 1, arr);

	return min(a1, min(a2, a3)) + A[r][c];
}

int minFallingPathSum(vector<vector<int> > &A)
{
	int n = A.size(), m = A[0].size();
	// int ans = INT_MAX;
	// for(int i = 0;i < A[0].size();i++){
	// 	ans = min(ans, helper(A, 0, i, vector<int> ()));
	// }


	int dp[2][m];
	for(int j = 0;j<m;j++) dp[1][j] = A[n-1][j];
	int curr = 0;

	for(int i = n-2;i >= 0;i--){

		for(int j = 0;j < m;j++){
			dp[curr][j] = dp[curr^1][j];
			if(j - 1 >= 0) dp[curr][j] = min(dp[curr][j], dp[curr^1][j-1]);
			if(j + 1 < m) dp[curr][j] = min(dp[curr][j], dp[curr^1][j+1]);

			dp[curr][j] += A[i][j]; 
		}
		curr ^= 1;
	}

	curr ^= 1;
	int ans = INT_MAX;
	for(int j=0;j<m;j++) ans = min(ans, dp[curr][j]);
	return ans;
}

int main(){
	int n, m;
	cin >> n >> m;
	vvi A(n, vi(m));
	for(vi &a: A){
		for(int &b: a) cin >> b;
	}
	cout << minFallingPathSum(A) << "\n";
	return 0;
}



