#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <cmath>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define ll long long


int getCount(int len)
{
	return (len*len - 3*len + 2)/2;
}

//	This make sure it is a substring
int numberOfArithmeticSlices(vector<int> &A)
{
	int cd = -1, ans = 0, st = -1, n = A.size();
	for(int i = 1;i < n;i++){

		if(st == -1){
			st = i - 1;
			cd = A[i] - A[i-1];
		}
		else if(cd != A[i] - A[i-1]){
			int len = i - 1 - st + 1;
			if(len >= 3){
				ans += getCount(len);
			}
			st = i - 1;
			cd = A[i] - A[i-1];
		}
	}
	int len = n - 1 - st + 1;
	cout << len << "\n";
	if(len >= 3) ans += getCount(len);
	return ans;
}

//	Here it can be subsequence 
int numberOfArithmeticSlices2(vi &A)
{
	int n = A.size(), ans = 0;
	vector<unordered_map<int,int> > dp(A.size());

	for(int i = 0;i < n;i++){
		for(int j = 0;j < i;j++){
			ll diff = (ll)A[i] - (ll)A[j];
			dp[i][diff] += 1;
			if(dp[j].count(diff) > 0){
				dp[i][diff] += dp[j][diff];
				ans += dp[j][diff];
			}
		}
	}

	return ans;
}

int main(){
	int n;
	cin >> n;
	vector<int> A(n);
	for(int &a: A) cin >> a;
	cout << numberOfArithmeticSlices2(A) << "\n";
	return 0;
}


