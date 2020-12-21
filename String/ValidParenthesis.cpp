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

int dp[10][10];

bool checkValidString(string s,int count = 0,int idx = 0){
	if(idx == s.size()) return count == 0;

	if(dp[idx][count] != -1) return dp[idx][count];
	bool ans = false;

	if(s[idx] == '('){
		ans = checkValidString(s, count + 1, idx + 1);
	}
	else if(s[idx] == ')'){
		if(count == 0) ans = false;
		else ans = checkValidString(s, count - 1, idx + 1);
	}
	else if(s[idx] == '*'){

		if(checkValidString(s, count + 1, idx + 1)) ans = true;
		else if(count > 0 && checkValidString(s, count - 1, idx + 1)) ans = true;
		else ans = checkValidString(s, count, idx + 1);
	}
	if(ans) dp[idx][count] = 1;
	else dp[idx][count] = 0;

	return ans;
}

//	Greedy
bool checkValidStringGreedy(string s){
	int count = 0, starcount = 0;
	for(char &c: s){
		if(c == '(') count++;
		else if(c == ')'){
			count--;
			if(count < 0){
				if(starcount == 0) return false;
				count++, starcount--;
			}
		}
		else if(c == '*'){
			if(count > 0) count -= 1;
			starcount += 2;
		}
	}

	return count == 0;

}

int main(){
	for(int i=0;i<10;i++) for(int j=0;j<10;j++) dp[i][j] = -1;
	string s;
	cin >> s;
	cout << checkValidStringGreedy(s) << "\n";
	return 0;
}

