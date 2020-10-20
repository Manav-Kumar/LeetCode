#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>
#define ll long long

ll MOD = 1e9 + 7;

int numDecodingsHelper(string s,vi &dp, int idx = 0)
{
	if(idx == s.size()) return 1;
	if(s[idx] == '0') return 0;
	ll a1 = 0, a2 = 0;
	a1 = numDecodingsHelper(s, dp, idx + 1) * (s[idx] == '*'?9:1);
	if(idx + 1 < s.size()){
		a2 = numDecodingsHelper(s, dp, idx + 2);
		if(s[idx] == '*'){
			if(s[idx + 1] == '*') a2 *= 15;
			else if(s[idx + 1] <= '6') a2 *= 2;
		}
		else{
			if(s[idx + 1] == '*'){
				if(s[idx] <= '1') a2 *= 9;
				else if(s[idx] == '2') a2 *= 6;
				else a2 *= 0; 
			}
			else if((s[idx] - '0')*10 + (s[idx + 1] - '0') > 26){
				a2 *= 0;
			}
		}
	}
	ll ans = (a1%MOD + a2%MOD)%MOD;
	return ans;
}

int numDecodings(string s)
{
	vector<int> dp(s.size(), 0);
	int ans = numDecodingsHelper(s, dp);
	for(int &a: dp) cout << a << " ";
	return ans;
}

int main(){
	string s;
	cin >> s;
	cout << numDecodings(s) << "\n";
	return 0;
}