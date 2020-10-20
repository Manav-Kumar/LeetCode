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
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>


int candy(vi &ratings){
	int n = ratings.size();
	vi ans(n, 0);
	ans[0] = 1;
	for(int i = 1;i < n;i++){
		if(ratings[i] <= ratings[i - 1]) ans[i] = 1;
		else ans[i] = ans[i - 1] + 1;
	}
	for(int i = n-2;i >= 0;i--){
		if(ratings[i] > ratings[i + 1] && ans[i] <= ans[i + 1]) ans[i] = ans[i + 1] + 1;
	}
	int count = 0;
	for(int &a: ans) count += a;
	return count;
}

//	Construct target Array with Multiple Sums
bool isPossible(vi &target){
	ll totalSum = 0;
	priority_queue<ll> q;
	for(int &a: target){
		totalSum += a, q.push((ll)a);
	}

	while(q.top() > 1){
		ll sum = q.top();
		ll remSum = totalSum - sum;
		ll v = sum - remSum;
		if(v < 1 || remSum < 1) return false;
		q.pop();
		totalSum -= sum;
		totalSum += sum%remSum;
		q.push(sum%remSum);
	}

	return true;
}


int main(){
	int n;
	cin >> n;
	vi ratings(n);
	for(int &a: ratings) cin >> a;
	cout << isPossible(ratings) << "\n";
	return 0;
}




