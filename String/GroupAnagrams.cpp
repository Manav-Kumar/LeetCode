#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>

string ConvertStandard(string s){
	vector<int> count(26, 0);
	for(char &c: s) count[c - 'a'] += 1;
	string k = "";
	for(int i=0;i<26;i++){
		while(count[i] > 0){
			k += char(i + 'a'), count[i] -= 1;
		}
	}
	return k;
}

vector<vector<string> > groupAnagrams(vector<string> &strs){
	vector<vector<string> > ans;
	unordered_map<string, int> indexes;
	int count = 0;
	for(string &s: strs){
		string k = ConvertStandard(s);
		if(indexes.count(k) == 0){
			ans.push_back(vector<string> ());
			indexes[k] = count++;
		}
		ans[indexes[k]].push_back(s);
	}
	return ans;
}

int main(){
	int n;
	cin >> n;
	vector<string> strs(n);
	for(string &s: strs) cin >> s;
	vector<vector<string> > ans = groupAnagrams(strs);
	for(vector<string> &s: ans){
		for(string &k: s) cout << k << " ";
		cout << "\n";
	}
	return 0;
}




