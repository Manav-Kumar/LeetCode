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

int gcd(int b,int a)
{
	if(b < a) return gcd(a,b);
	if(a == 0) return b;
	return gcd(a, b%a);
}

int CountSubs(vector<int> &arr)
{
	vector<vector<int> > dp(arr.size(),vector<int>(101,0));
	for(int i=0;i<arr.size();i++)
	{
		for(int j=i-1;j>=0;j--)
		{
			if(arr[j] >= arr[i]) continue;
			for(int k=1;k<=arr[i];k++)
			{
				dp[i][gcd(k,arr[i])] += dp[j][k];
			}
		}
		//One subseuqence with itself
		dp[i][arr[i]] += 1;
	}
	int sum = 0;
	for(vector<int>&a: dp) sum += a[1];
	return sum;
}


//	Adjacent Bit Counts

long long helper(int n,int k,bool prev,long long ***dp)
{
	if(n == 0) return int(k == 0);
	if(dp[n][k][prev] != -1) return dp[n][k][prev];
	long long ans = helper(n-1,k, false, dp);
	if(k > 0 && prev) ans = (ans + helper(n-1, k-1, true,dp))%mod;
	if(!prev) ans = (ans + helper(n-1, k, true, dp))%mod;
	dp[n][k][prev] = ans;
	return ans;
}
void AdjacentNBitCount()
{
	int p,n,k,a;
	cin >> p;
	while(p--)
	{
		cin >> a >> n >> k;
		long long ***dp = new long long**[n+1];
		for(int i=0;i<=n;i++)
		{
			dp[i] = new long long*[k+1];
			for(int j=0;j<=k;j++)
			{
				dp[i][j] = new long long[2]();
				fill(dp[i][j], dp[i][j] + 2, -1);
			}
		}
		cout << a << " " << (helper(n-1,k,true,dp) + helper(n-1,k,false,dp))%mod << endl;
		for(int i=0;i<=n;i++)
		{
			for(int j=0;j<=k;j++) delete []dp[i][j];
			delete []dp[i];
		}
		delete []dp;
	}
	return ;
}

//	Jnow Snow And His Favourate Number
void JonSnow()
{
	int n,k,x,temp;
	cin >> n >> k >> x;
	int *dp = new int[1024]();
	int *Updatedp = new int[1024]();
	for(int i=0;i<n;i++)
	{
		cin >> temp;
		dp[temp] += 1;
	}
	while(k--)
	{
		int count = 0;
		for(int i=0;i<=1023;i++)
		{
			if(dp[i] == 0) continue;
			int freq = dp[i];
			if(freq%2 == 0)
			{
				Updatedp[i] += freq/2;
				Updatedp[(i^x)] += freq/2;
			}
			else
			{
				Updatedp[i] += (freq/2 + count%2);
				Updatedp[(i^x)] += (freq/2 + 1 - count%2);
			}
			count += freq;
		}
		for(int i=0;i<=1023;i++)
		{
			dp[i] = Updatedp[i];
			Updatedp[i] = 0;
			if(dp[i] > 0) cout << i << ":" << dp[i] << " , ";
		}
		cout << "\n";
	}
	int maxStrength = -1, minStrength = -1;
	for(int i=0;i<1024;i++)
	{
		if(dp[i] == 0) continue;
		if(minStrength == -1) minStrength = i;
		if(minStrength != -1) maxStrength = i; 
	}
	cout << maxStrength << " " << minStrength << "\n";
	delete []dp;
	delete []Updatedp;
	return ;
}

//	Alyona And SpreadSheet
int* AlyonaHelper(int **arr,int n,int m)
{
	int **dp = new int*[n+1];
	for(int i=1;i<=n;i++) dp[i] = new int[m+1]();
	for(int j=1;j<=m;j++)
	{
		dp[1][j] = 1;
		for(int i=2;i<=n;i++)
		{
			if(arr[i][j] >= arr[i-1][j]) dp[i][j] = dp[i-1][j];
			else dp[i][j] = i;
		}
	}
	int *dp2 = new int[n+1];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(dp2[i] == 0 || dp2[i] > dp[i][j]) dp2[i] = dp[i][j];
		}
		delete []dp[i];
	}
	delete []dp;
	return dp2;
}

int* AlyonaHelper2(int n,int m)
{
	int arr[2][m];
	int **dp = new int*[2];
	for(int i=0;i<2;i++) dp[i] = new int[m]();
	int *finalDp = new int[n]();
	fill(finalDp, finalDp + n, -1);
	for(int j=0;j<m;j++)
	{
		cin >> arr[0][j];
		dp[0][j] = 0;
	}
	finalDp[0] = 0;
	bool prev = true;
	for(int i=1;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cin >> arr[prev][j];
			if(arr[prev][j] >= arr[!prev][j]) dp[prev][j] = dp[!prev][j];
			else dp[prev][j] = i;
			if(finalDp[i] == -1 || finalDp[i] > dp[prev][j]) finalDp[i] = dp[prev][j];
		}
		prev ^= 1;
	}
	for(int i=0;i<2;i++) delete []dp[i];
	delete []dp;
	return finalDp;
}

void AlyonaSpreadSheet()
{
	int n,m,k,l,r;
	cin >> n >> m;
	int *dp = AlyonaHelper2(n,m);
	cin >> k;
	while(k--)
	{
		cin >> l >> r;
		l--, r--;
		if(dp[r] <= l) cout << "Yes" << "\n";
		else cout << "No" << "\n";
	}
	return ;
}

//	Angry Children
int AngryChildren()
{
	int n,k,sum = 0, target = 0;
	cin >> n >> k;
	int *arr = new int[n];
	for(int i=0;i<n;i++) cin >> arr[i];
	sort(arr, arr+n);
	sum = 0;
	for(int i=0;i<k;i++)
	{
		target += i*arr[i] - sum;
		sum += arr[i];
	}
	int best = target;
	for(int i=0,j=k;j < n;i++,j++)
	{
		sum -= arr[i];
		target += (k-1)*arr[j] - 2*sum + (k-1)*arr[i];
		sum += arr[j];
		best = min(target, best);
	}
	delete []arr;
	return best;
}

int main()
{
	// int n;
	// cin >> n;
	// vector<int> a(n);
	// for(int &k: a) cin >> k;
	// cout << CountSubs(a) << "\n";
	cout << AngryChildren() << "\n";
	return 0;
}