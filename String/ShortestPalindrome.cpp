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

bool isPalindrom(string s,int st,int en){
	while(st <= en){
		if(s[st++] != s[en--]) return false;
	}
	return true;
}

string shortestPalindrome(string s){

	int st = 0, en;
	rep(i, 0, s.size()){
		if(isPalindrom(s,0,i)) en = i;
	}
	string rem = s.substr(en + 1), ans = s;
	reverse(rem.begin(), rem.end());
	ans = rem + ans;
	return ans;
}

vi getLPS(string pattern){
	int j = 0, i = 1, n = pattern.size();
	vi lps(n, 0);
	rep(i, 1, n){
		int j = lps[i - 1];
		while(j > 0 && pattern[i] != pattern[j]) j = lps[j - 1];
		if(pattern[i] == pattern[j]) lps[i] = j + 1;
	}
	
	for(int &a: lps) cout << a << " ";
	cout << "\n";
	return lps;
}

vi getLPS2(string pattern){
	int n = pattern.size(), j = 0, i = 1;
	vi lps(n, 0);
	while(i < n){
		if(pattern[i] == pattern[j]) lps[i++] = ++j;
		else if(j > 0){
			while(j > 0 && pattern[i] != pattern[j]) j = lps[j - 1];
		}
		else i++;
	}
	return lps;
}

string shortestPalindrome2(string s){
	if(isPalindrom(s, 0, s.size() - 1)) return s;
	string k = s;
	reverse(k.begin(), k.end());
	string l = s + "#" + k;
	vi lps = getLPS2(l);
	cout << lps[l.size() - 1] << "\n";
	return k.substr(0, s.size() - lps[l.size() - 1]) + s;
}

int main(){
	string s;
	cin >> s;
	string ans = "";
	cout << shortestPalindrome2(s) << "\n";
	return 0;
}

