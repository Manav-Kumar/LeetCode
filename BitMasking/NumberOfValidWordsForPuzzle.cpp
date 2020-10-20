#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <cmath>
#include <math.h>
#include <unordered_set>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vvi vector<vector<int> >
#define vvb vector<vector<bool> >
#define vs vector<string>
#define N 1000000


vi findNumOfValidWords(vector<string>& words, vector<string> &puzzles){

	unordered_map<int,int> mp;
	for(string &s: words){
		int value = 0;
		for(char c: s){
			value |=  (1<< (c - 'a'));
		}
		mp[value]++;
	}


	vi ans;
	for(string &s: puzzles){
		int count = 0, puzzlBit = 0, firstletter = s[0] - 'a';
		for(char c: s){
			puzzlBit |= (1<< (c - 'a'));
		}

		int temp = puzzlBit;
		while(temp > 0){
			if(((temp >> firstletter)&1) > 0){
				count += mp[temp];
			}
			temp = (temp - 1)&puzzlBit;
		}

		ans.push_back(count);
	}
	return ans;
}

int main(){
	int n, m;
	cin >> n;
	vector<string> words(n);
	for(string &s: words) cin >> s;
	cin >> m;
	vector<string> puzzles(m);
	for(string &p: puzzles) cin >> p;
	vi ans = findNumOfValidWords(words, puzzles);
	for(int &a: ans) cout << a << " ";
	return 0;
}


