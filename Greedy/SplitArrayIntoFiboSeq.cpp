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
#define vll vector<ll>
#define vi vector<int>
#define vvi vector<vi >
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>

bool ValidFibo(ll a,ll b,string s,int idx, vll &ans){
    int n = s.size();
    ll c = 0;
    while(idx < n){
        c = c*10 + (s[idx++] - '0');
        if(c > INT_MAX) return false;
        if(c == 0 && (a != 0 || b != 0)) return false;//Will cause leading zeros
        if(c == (a + b)){
            ans.push_back(c);
            a = b, b = c, c = 0;
        }
    }
    return c == 0;
}

vll splitIntoFibonacci(string s){
	int n = s.size();
    vll ans(2);
    ll a = 0, b = 0;
    bool leadingZeros = false;
    for(int i = 0;i <= n-3;i++){
        a = a*10 + (s[i] - '0'), b = 0;
        if(a > INT_MAX) return vll();

        if(a == 0) leadingZeros = true;
        else if(leadingZeros) return vll();

        ans[0] = a;
        bool leadingZeros2 = false;
        for(int j = i + 1;j <= n-2;j++){
            b = b*10 + (s[j] - '0');
            if(b > INT_MAX) break;

            if(b == 0) leadingZeros2 = true;
            else if(leadingZeros2) break;

            ans[1] = b;
            vll finalAns = ans;
            if(ValidFibo(a, b, s, j + 1, finalAns)){
                return finalAns;
            }
        }
    }
    return vll();
}

int main(){
	string s;
	cin >> s;
	vll ans = splitIntoFibonacci(s);
	for(ll &a: ans) cout << a << " ";
	return 0;
}


