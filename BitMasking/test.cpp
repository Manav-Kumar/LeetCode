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

int countPalindrom(string s,int st,int en){
	int op = 0;
	while(st <= en){
		if(s[st++] != s[en--]) op++;
	}
	return op;
}

int helper(string s,string k,int start)
{
	int kst = start, ken = start + k.size() - 1;
	if(ken >= s.size()) return INT_MAX;

	int mid = s.size();
	if(mid > ken){

	}
	else if(mid < kst){

	}
	else{
		
	}
}


int minOp(string s,string k)
{
	int ans = INT_MAX;
	for(int i=0;i<s.size();i++){
		ans = min(ans, helper(s, k, i));
	}
	return ans
}


int main(){
	string a,b;
	cin >> a >> b;
	cout << minOp(a,b);
	return 0;
}