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

vs wordBreakHelper(string &s, unordered_set<string> &exists,unordered_map<int, vs> &dp,  int idx = 0){

    if(idx == s.size()){
        return vs{""};
    }
    if(dp.count(idx) > 0) return dp[idx];
    vs ans;
    
    string temp = "";
    for(int i = idx;i < s.size();i++){
        temp += s[i];
        if(exists.count(temp) > 0){
            vs a1 = wordBreakHelper(s, exists, dp, i + 1);
            for(string k: a1){
            	if(k == "") k = temp;
                else k = temp + " " + k;
                ans.push_back(k);
            }
        }
    }

    dp[idx] = ans;
    return ans;
    
}

vs wordBreak(string s, vs &wordDict){
    unordered_set<string> exists;
    for(string &s: wordDict) exists.insert(s);
    unordered_map<int, vs> dp;
    return wordBreakHelper(s, exists, dp);
}

int main(){
	int n; string s;
	cin >> n;
	vs wordDict(n);
	for(string &k: wordDict) cin >> k;
	cin >> s;
	vs ans = wordBreak(s, wordDict);
	for(string k: ans) cout << k << "\n";
	return 0;
}





