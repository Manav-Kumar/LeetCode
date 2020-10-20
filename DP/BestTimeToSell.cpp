#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define ll long long

int maxProfit(vector<int>& prices,vvvi &dp,int idx,int ct,bool transaction = false)
{
	if(idx == prices.size()){
		return 0;
	}
	int &value = dp[idx][ct][transaction];
	if(value != -1) return value;
	int a1 = 0;
	if(!transaction && ct > 0) a1 = maxProfit(prices, dp, idx + 1, ct, true) - prices[idx];
	else if(transaction) a1 = maxProfit(prices, dp, idx + 1, ct - 1) + prices[idx];

	int a2 = maxProfit(prices, dp, idx + 1, ct, transaction);
	value = max(a1, a2);
	return value;
}

int maxProfit2(int k,vector<int> &prices)
{
	int n = prices.size();
	if(n <= 1 || k <= 0) return 0;
	if(k >= (n/2)){
		int profit = 0;
		for(int i = 0;i < n-1;i++){
			if(prices[i] < prices[i+1]) profit += prices[i + 1] - prices[i];
		}
		return profit;
	}

	vector<int> buy(k, INT_MIN);//	On buying maxProfit can go neg
	vector<int> sell(k, 0);//	On selling max profit could be 0

	for(int i = 0;i < n;i++){
		for(int j = 0;j < k;j++){
			buy[j] = max(buy[j], j == 0?0 - prices[i]: sell[j-1] - prices[i]);
			sell[j] = max(sell[j], buy[j] + prices[i]);
		}
	}

	return sell[k-1];

}

//	Maximum 2 transactions are allowed
int maxProfit2Transactions(int k,vector<int> &prices)
{
	int fb = INT_MIN, fs = 0, sb = INT_MIN, ss = 0;
	for(int i = 0;i < prices.size();i++){
		fb = max(fb, -prices[i]);
		fs = max(fs, fb + prices[i]);
		sb = max(sb, fs - prices[i]);
		ss = max(ss, sb + prices[i]);
	}
	return ss;
}


int maxProfit3(int k,vector<int> &prices){
	int n = prices.size();
	if(n <= 1 || k <= 0) return 0;
	if(k >= (n/2)){
		int profit = 0;
		for(int i = 0;i < n-1;i++){
			if(prices[i] < prices[i+1]) profit += prices[i + 1] - prices[i];
		}
		return profit;
	}
	vector<int> preProfit(n, 0);
	vi curProfit(n, 0);
	for(int i = 0;i < n;i++) preProfit[i] = 0;

	for(int l = 1;l <= k;l++){
		for(int i = 0;i < n;i++){
			curProfit[i] = max(curProfit[i], )
		}
	}
}

int main(){
	int n, k;
	cin >> n >> k;
	vector<int> prices(n);
	for(int &a: prices) cin >> a;
	int maxTransaction = min(k, n/2);
	vvvi dp(n, vvi(maxTransaction + 1, vi(2, -1)));
	cout << maxProfit(prices, dp, 0, maxTransaction) << "\n";
	return 0;
}



