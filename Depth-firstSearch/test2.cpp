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
#include <climits>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vvi vector<vi >
#define vvvi vector<vvi>
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>

bool helper(string s,string t, int k,vvvi &dp, int i = 0,int j = 0, bool erase = false)
{
	if(k >= (t.size() - j) || j == t.size()) return true;

	if(i == s.size()) return false;

	bool check = (s[i] == t[j]) || ((s[i] == 'o' || s[i] == 'a') && (t[j] == 'o' || t[j] == 'a')) || 
			((s[i] == 't' || s[i] == 'l') && (t[j] == 't' || t[j] == 'l'));

	if(check) return helper(s, t, k, dp, i + 1, j + 1, erase);
	if(k > 0) check = helper(s, t, k - 1, dp, i + 1, j, erase);
	if(check) return true;
	if(!erase) check = helper(s, t, k, dp, i, j + 1, true);
	return check;
}

int totalWins(int n, string drawString, vector<string> tickets, int k){
	int count = 0;
	for(int i = 0;i < n;i++){
		bool check = false;
		int s1 = drawString.size(), s2 = tickets[i].size();
		vvvi dp(s1, vvi(s2, vi(k, -1)));
		for(int j = 0;j < drawString.size();j++){
			check = helper(drawString, tickets[i], k, dp, j);
			if(check){
				cout << i << "\n";
				count++;
				break;
			}
		}
	}
	return count;
}

int longestConsec(int n,int k,string s)
{
	return 0;
}

int getans(string s,int idx)
{
	
}

int correctAns(string s,vector<int> answers)
{
	int score = 0, n = answers.size();
	int crt = 0;
	for(int i = 0;i < s.size() - 1;i += 2){
		
		if(s[i - 1] == '*'){

		}
	}
	return score;
}

int main(){
	int a = 2 - 3 + 4 - 5;
	cout << a << "\n";
	return 0;
}

