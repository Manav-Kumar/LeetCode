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
#define vmpii vector<map<int,int> >
#define vvmpii vector<vmpii>
#define vvb vector<vector<bool> >

ll mod = pow(10,9) + 7;

int numOfArrays(int n,int m,int k,ll ***dp,int maxEle = 0,int index = 0)
{
	if(index == n)
	{
		if(k == 0) return 1;
		return 0;
	}
	ll &ans = dp[index][k][maxEle];
	if(ans != -1) return ans;
	ans = 0;
	for(int val = 1;val<=m;val++)
	{
		if(val > maxEle && k > 0) ans = (ans + numOfArrays(n,m,k-1,dp,val,index+1))%mod;
		if(val <= maxEle) ans = (ans + numOfArrays(n,m,k,dp,maxEle,index+1))%mod;
	}
	return ans%mod;
}

//	Number Of Submatrices That Sum To Target

class triplet
{
public:
	int total, upward, left;
	triplet(int total = 0,int upward = 0,int left = 0): total(total), upward(upward), left(left) {} 
};


//	O(n^4)
int numSubmatrixSumTarget(vvi &matrix,int target)
{
	int count = 0, n = matrix.size(), m = matrix[0].size();
	vector<vector<triplet> > dp = vector<vector<triplet> >(n, vector<triplet>(m));
	dp[0][0] = triplet(matrix[0][0], matrix[0][0], matrix[0][0]);
	rep(i,1,n) dp[i][0] = triplet(dp[i-1][0].total + matrix[i][0], dp[i-1][0].upward + matrix[i][0], matrix[i][0]);
	rep(j,1,m) dp[0][j] = triplet(dp[0][j-1].total + matrix[0][j], matrix[0][j], dp[0][j-1].left + matrix[0][j]);
	for(int i=1;i<n;i++)
	{
		for(int j=1;j<m;j++)
		{
			dp[i][j] = triplet(dp[i-1][j-1].total + dp[i-1][j].upward + dp[i][j-1].left + matrix[i][j], 
							dp[i-1][j].upward + matrix[i][j], dp[i][j-1].left + matrix[i][j]);
		}
	}

	rep(i,0,n)
	{
		rep(j,0,m)
		{
			for(int l=i;l>=0;l--)
			{
				for(int m=j;m>=0;m--)
				{
					int currSum = dp[i][j].total;
					if(l > 0 && m > 0)
					{
						currSum = currSum - dp[l-1][j].total - dp[i][m-1].total + dp[l-1][m-1].total;
					}
					else if(l > 0) currSum -= dp[l-1][j].total;
					else if(m > 0) currSum -= dp[i][m-1].total;
					if(currSum == target) count++;
				}
			}
		}
	}
	return count;
}


//	O(n^3)
int numSubmatrixSumTarget2(vvi &matrix,int target)
{
	int n = matrix.size(), m = matrix[0].size(), ret = 0;

	for(int l=0;l<m;l++)
	{
		vector<int> row(n, 0);
		for(int r=l;r<m;r++)
		{
			unordered_map<int,int> hash;
			int sum = 0;
			hash[0] = 1;
			for(int i=0;i<n;i++)
			{
				row[i] += matrix[i][r];
				sum += row[i];
				if(hash.count(sum - target) > 0) ret += hash[sum - target];
				hash[sum]++;
			}
		}
	}
	return ret;
}

int main()
{
	int n,m,target;
	cin >> n >> m;
	vvi matrix(n, vi(m));
	for(vi &a: matrix)
	{
		for(int &b: a) cin >> b;
	}
	cout << "Enter Target" << "\n";
	cin >> target;
	cout << numSubmatrixSumTarget(matrix, target) << "\n";
	return 0;
}





