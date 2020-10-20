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
#define N 1000000

ll mod = pow(10,9) + 7;

int lootHouse(int *arr,int n)
{
	if(n <= 0) return 0; 
	int smallAns = lootHouse(arr, n-2) + arr[n-1];
	int smallAns2 = lootHouse(arr, n-1);
	return max(smallAns2, smallAns);
}

int lootHouseMem(int *arr,int n)
{
	int *dp = new int[n+1];
	dp[0] = 0;
	dp[1] = arr[0];
	for(int i=2;i<=n;i++)
	{
		int smallAns = dp[i-2] + arr[i-1];
		int smallAns2 = dp[i-1];
		dp[i] = max(smallAns2, smallAns);
	}
	int ans = dp[n];
	delete []dp;
	return ans;
}

int findMaxSquareWithAllZeros(int **arr,int row,int col)
{
	int best = 0;
	int **dp = new int*[row];
	for(int i=0;i<row;i++)
	{
		dp[i] = new int[col];
		fill(dp[i], dp[i] + col, 0);
	}
	for(int i=0;i<row;i++) if(arr[i][0] == 0) dp[i][0] = 1;
	for(int j=0;j<col;j++) if(arr[0][j] == 0) dp[0][j] = 1;
	for(int i=1;i<row;i++)
	{
		for(int j=1;j<col;j++)
		{
			if(!arr[i][j]) dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) + 1;
			best = max(best, dp[i][j]);
		}
	}
	for(int i=0;i<row;i++) delete []dp[i];
	delete []dp;
	return best;
}

long long helper(int st,int en,long long *dp)
{
	if(st >= en) return 1;
	if(dp[en - st + 1] != 0) return dp[en - st + 1];
	long long &ans = dp[en - st + 1];
	for(int i=st;i<=en;i++)
	{
		ans = (ans + (helper(st,i-1, dp)*helper(i+1,en, dp))%mod)%mod;
	}
	return ans%mod;
}

int countBST(int n)
{
	long long *dp = new long long[n+1]();
	int ans = helper(1,n,dp);
	delete []dp;
	return ans;
}


int boredom(vector<int>&A,int n)
{
	int *freq = new int[1001]();
	for(int &a: A) freq[a]++;
	int *dp = new int[1001];
	dp[0] = 0;
	dp[1] = freq[1];
	for(int i=2;i<=1000;i++)
	{
		dp[i] = max((i*freq[i]) + dp[i-2], dp[i-1]);
	}
	int ans = dp[1000];
	delete []dp;
	delete []freq;
	return ans;
}

//Minimum Number Of Chocolates

int getMin(int *arr,int n)
{
	//	Forward Pass
	int *dp = new int[n];
	dp[0] = 1;
	for(int i=1;i<n;i++)
	{
		dp[i] = 1;
		if(arr[i] > arr[i-1]) dp[i] += dp[i-1];
	}
	int sum = dp[n-1];
	for(int i=n-2;i>=0;i--)
	{
		if(arr[i] > arr[i+1])
		{
			dp[i] = max(dp[i], dp[i+1] + 1);
		}
		sum += dp[i];
	}

	delete []dp;
	return sum;

}

//Return the minCount of numbers whose squared sum will be n

int helper2(int n,int index,int **dp)
{
	if(n == 0) return 0;
	if(index == 0) return 1000;
	if(dp[n][index] != -1) return dp[n][index];
	int count = 0,ans = INT_MAX;
	while((count*index*index) <= n)
	{
		ans = min(ans,helper2(n - (count*index*index), index-1, dp) + count);
		count++;
	}
	dp[n][index] = ans;
	return ans;
}

int minCount(int n)
{
	int maxele = sqrt(n);
	int **dp = new int*[n+1];
	for(int i=0;i<=n;i++)
	{
		dp[i] = new int[maxele+1];
		fill(dp[i], dp[i] + maxele+1,-1);
	}
	int ans = helper2(n, maxele,dp);
	for(int i=0;i<=n;i++) delete []dp[i];
	return ans;
}

void RoyCoin()
{
	int n,m,q,i,j,x,temp;
	cin >> n >> m;
	int *st = new int[n]();
	int *en = new int[n]();
	int *dp = new int[n]();
	temp = m;
	while(temp--)
	{
		cin >> i >> j;
		i--, j--;
		st[i]++, en[j]++;
	}
	dp[0] = st[0];
	for(int i=1;i<n;i++)
	{
		dp[i] = st[i] - en[i-1] + dp[i-1];
	}
	vector<int> numBoxWithCoin(m+1, 0);
	for(int i=0;i<n;i++) numBoxWithCoin[dp[i]] += 1;
	for(int i=m-1;i>=0;i--) numBoxWithCoin[i] += numBoxWithCoin[i+1];
	cin >> q;
	while(q--)
	{
		cin >> x;
		cout << numBoxWithCoin[x] << "\n";
	}
	delete []st;
	delete []en;
	delete []dp;
	return ;
}




int main()
{
	RoyCoin();
	return 0;
}

