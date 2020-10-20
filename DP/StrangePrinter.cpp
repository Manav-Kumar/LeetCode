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


int helper(string t,int st,int en, vvi &dp)
{
	if(st > en) return 0;
	int &finalAns = dp[st][en];
	if(finalAns != -1) return finalAns;
	int ans = helper(t, st + 1, en,dp) + 1;
	for(int k = st + 1;k <= en;k++){
		if(t[k] == t[st]){
			ans = min(ans, helper(t, st + 1, k - 1, dp) + 1 + helper(t, k + 1, en, dp));
		}
	}
	finalAns = ans;
	return ans;
}

int strangePrinter(string s){
	string t = "";
	int i = 0;
	while(i < s.size()){
		char c = s[i];
		t += c;
		while(i < s.size() && s[i] == c) i++;
	}
	int n = t.size();
	vvi dp(n, vi(n, -1));
	int ans = helper(t, 0 ,n - 1, dp);
	return ans;
}

int main(){
	string s;
	cin >> s;
	cout << strangePrinter(s) << "\n";
	return 0;
}

