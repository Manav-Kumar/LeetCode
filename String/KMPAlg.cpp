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

vi getLPS(string pattern){
	int j = 0, i = 1, n = pattern.size();
	vi lps(n, 0);
	while(i < n){
		if(pattern[j] == pattern[i]) lps[i++] = ++j;
		else if(j > 0){
			while(j > 0 && pattern[i] != pattern[j]) j = lps[j - 1];
		}
		else i++;
	}
	for(int &a: lps) cout << a << " ";
	cout << "\n";
	return lps;
}

vi getOccurances(string text, string pattern){
	vi lps = getLPS(pattern);
	cout << "done\n";
	vi ans;
	int i = 0, j = 0;
	while(i < text.size()){
		if(j < pattern.size() && pattern[j] == text[i]) i++, j++;
		else{
			if(j == pattern.size()) ans.push_back(i - pattern.size());
			if(j != 0) j = lps[j - 1];
			else i++;
		}
	}
	if(j == pattern.size()) ans.push_back(i - pattern.size());
	return ans;
}

int main(){
	string text, pattern;
	cin >> text >> pattern;
	vi ans = getOccurances(text, pattern);
	for(int &a: ans) cout << a << " ";
	return 0;
}




