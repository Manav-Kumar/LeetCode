#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>

typedef long long ll;

ll mod = 1e6 + 3;

int dp[101][2];

bool FirstWins(int n,bool turn = true){

	if(n < 2) return !turn;

	if(dp[n][turn] != -1) return dp[n][turn];
	if(turn){
		bool ans = false;
		if(n >= 2) ans = FirstWins(n - 2, !turn);
		if(n >= 3) ans = ans || FirstWins(n - 3, !turn);
		if(n >= 5) ans = ans || FirstWins(n - 5, !turn);
		return dp[n][turn] = ans;
	}
	else{
		bool ans = true;
		if(n >= 2) ans = FirstWins(n - 2, !turn);
		if(n >= 3) ans = ans && FirstWins(n - 3, !turn);
		if(n >= 5) ans = ans && FirstWins(n - 5, !turn);
		return dp[n][turn] = ans;	
	}
}

int main(){
	for(int i=0;i<101;i++) dp[i][0] = -1, dp[i][1] = -1;
	int t, n;
	cin >> t;
	while(t--){
		cin >> n;
		if(FirstWins(n)) cout << "First\n";
		else cout << "Second\n";
	}
	return 0;	
}
