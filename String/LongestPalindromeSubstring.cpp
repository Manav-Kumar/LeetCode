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

//	Expand from Middle -> O(N^2), Space O(1)

int expandFromMiddle(string s,int left,int right){
	int n = s.size();
	while(left >= 0 && right < n && s[left] == s[right]) left--, right++;
	return right - left - 1;
}

string LongestPalindromSubstr(string &s){
	int n = s.size(), st = 0, en = 0, len;
	rep(i, 0, n){
		int len1 = expandFromMiddle(s, i, i);
		int len2 = expandFromMiddle(s, i, i + 1);
		len = max(len1, len2);
		if(len > (en - st + 1)){
			st = i - (len - 1)/2, en = i + len/2;
		}
	}
	return s.substr(st, en - st + 1);
}


//	Dynamic Programming - > O(N^2), Space O(N^2)

string LongestPalindromSubstr2(string s){
	int n = s.size();
	vvb dp(n, vb(n, false));
	//	1Len Palindromic Substrings
	rep(i, 0, n) dp[i][i] = true;

	//	2Len Palindromic Substrings
	rep(i, 0, n - 1) if(s[i] == s[i + 1]) dp[i][i + 1] = true;

	rep(counter, 2, n){
		int i = 0, j = i + counter;
		while(i < n && j < n){
			if(s[i] == s[j]) dp[i][j] = dp[i + 1][j - 1];
			else dp[i][j] = false;
			i++, j++;
		}
	}

	int ans = 0, st, en;
	rep(i, 0, n){
		rep(j, i, n){
			if(dp[i][j] && (j - i + 1 > ans)) ans = j - i + 1, st = i, en = j;
		}
	}
	return s.substr(st, en - st + 1);
}


 
string LongestPalindromSubstr3(string s){
	int n = s.size(), start = 0, maxLen = 1;
    for(int i = 0; i < n;) {
        int x = i-1, y = i+1;
        while(y < n && s[y] == s[i]) y++;
        i = y;
        while(x >= 0 && y < n && s[x] == s[y]) {x--;y++;}
        if(y-x-1 > maxLen) {start = x+1; maxLen = y-x-1;}
    }
    return s.substr(start, maxLen);
}

int main(){
	string s;
	cin >> s;
	cout << LongestPalindromSubstr2(s) << "\n";
	return 0;
}






