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
#include <list>
#include <climits>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vll vector<ll>
#define vi vector<int>
#define vvi vector<vi >
#define vvvi vector<vvi>
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>

bool isInterleave(string s1, string s2, string s3,int i,int j,vvi &dp){
	int n = s1.size(), m = s2.size(), p = s3.size();
	if((i + j) == p) return i == n && j == m;
	if(dp[i][j] != -1) return dp[i][j];
	bool a1, a2;
	if(i < n && s1[i] == s3[i + j]){
		a1 = isInterleave(s1, s2, s3, i + 1,j,dp);
		if(a1) return dp[i][j] = true;
	}

	if(j < m && s2[j] == s3[i + j]){
		a2 = isInterleave(s1, s2, s3, i, j + 1,dp);
		if(a2) return dp[i][j] = true;
	}
	return dp[i][j] = false;
}

bool isInterleave(string s1, string s2, string s3){
	int n = s1.size(), m = s2.size(), p = s3.size(), i = 0, j = 0,k = i + j;
	if(n + m != p) return false;
	vvb dp(n + 1, vb(m + 1, false));
	dp[n][m] = true;
	j = m;
	for(int i = n-1;i >= 0;i--){
		if(s1[i] == s3[i + j]) dp[i][j] = dp[i + 1][j];
		else dp[i][j] = false;
	}
	i = n;
	for(int j = m - 1;j >= 0;j--){
		if(s2[j] == s3[i + j]) dp[i][j] = dp[i][j + 1];
		else dp[i][j] = false;
	}
	for(int i = n-1;i >= 0;i--){
		for(int j = m-1;j >= 0;j--){
			bool a1, a2;
			if(s1[i] == s3[i + j]) dp[i][j] = dp[i][j]||dp[i + 1][j];
			if(s2[j] == s3[i + j]) dp[i][j] = dp[i][j]||dp[i][j + 1];
		}
	}
	return dp[0][0];
}

//	Scramble Strings
int hashValue(string s){

}

bool isScramble(string s1, string s2){
	int n = s2.size();
	if(n == 0) return false;
	if(n == 1){
		return s1[0] == s2[0];
	}
	string temp = s1;
	reverse(temp.begin(), temp.end());
	bool ans;
	rep(i, 0, n - 1){

		unordered_map<string,bool> mp;
		mp[s2.substr(0,i + 1)] = true, mp[s2.substr(i + 1)] = true;

		if(mp.count(s1.substr(0, i + 1)) > 0 && mp.count(s1.substr(i + 1))){
			ans = isScramble(s1.substr(0,i+1), s2.substr(0,i+1))&&isScramble(s1.substr(i+1),s2.substr(i+1));
			if(ans) return true;
		}

		if(mp.count(temp.substr(0, i + 1)) > 0 && mp.count(temp.substr(i + 1))){
			ans = isScramble(temp.substr(0,i+1), s2.substr(0,i+1))&&isScramble(temp.substr(i+1),s2.substr(i+1));
			if(ans) return true;
		}
	}
	return false;
}


bool shouldMatch(string s1, string s2){
	int arr1[26] = {0};
	int arr2[26] = {0};
	int n = s1.size();
	rep(i, 0, n) arr1[s1[i] - 'a'] += 1, arr2[s2[i] - 'a'] += 1;
	rep(i, 0, 26){
		if(arr1[i] != arr2[i]) return false;
	}
	return true;
}

bool isScramble2(string s1, string s2){
	if(s1 == s2) return true;
	if(!shouldMatch(s1, s2)) return false;
	int n = s1.size();
	string temp = s1;
	reverse(temp.begin(), temp.end());
	rep(i, 0, n - 1){
		if(isScramble2(s1.substr(0,i+1),s2.substr(0,i+1))&&isScramble2(s1.substr(i+1),s2.substr(i+1))) return true;

		if(isScramble2(temp.substr(0,i+1),s2.substr(0,i+1))&&isScramble2(temp.substr(i+1),s2.substr(i+1))) return true;
	}
	return false;
}


int main(){
	string s1, s2;
	cin >> s1 >> s2;
	cout << isScramble(s1, s2) << "\n";
	cout << (1<<5) << "\n";
	return 0;
}



