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

int helper(vi &a,int k,int ***dp,bool active = false,int index = 0)
{
	if(index == a.size()) return 0;
	int &ans = dp[index][k][active];
	if(ans != -1) return ans;
	//	Can Only Buy
	if(!active) ans = helper(a,k,dp,!active,index+1) - a[index];
	else if(k > 0) ans = helper(a,k-1,dp,false,index+1) + a[index];

	ans = max(ans, helper(a, k, dp, active, index+1));
	return ans;

}

int MaxTraderProfit(vi &a,int k)
{
	int ***dp = new int**[a.size()];
	for(int i=0;i<a.size();i++)
	{
		dp[i] = new int*[k+1];
		for(int j=0;j<=k;j++)
		{
			dp[i][j] = new int[2];
			fill(dp[i][j], dp[i][j] + 2,-1);
		}
	}
	int ans = helper(a,k,dp);
	for(int i=0;i<a.size();i++)
	{
		for(int j=0;j<=k;j++) delete []dp[i][j];
		delete []dp[i];
	}
	delete []dp;
	return ans;
}

//	Charlie And Pilots
long long CharlieHelper(int *captain,int *assistant,int n,long long **dp,int index = 0,int capCount = 0,int asstCount = 0)
{
	if(index == n) return 0;
	long long &ans = dp[index][capCount];
	if(ans != INT_MAX) return ans;
	if(asstCount < n/2)
		ans = CharlieHelper(captain, assistant,n,dp,index+1,capCount,asstCount+1) + assistant[index];

	if(asstCount > capCount)
		ans = min(ans, CharlieHelper(captain,assistant,n,dp,index+1,capCount+1,asstCount) + captain[index]);

	return ans;
}

int CharliePilots()
{
	int n;
	cin >> n;
	int *captain = new int[n];
	int *assistant = new int[n];
	for(int i=0;i<n;i++) cin >> captain[i] >> assistant[i];
	long long **dp = new long long*[n];
	for(int i=0;i<n;i++)
	{
		dp[i] = new long long[n/2+1];
		fill(dp[i], dp[i] + n/2+1, INT_MAX);
	}
	long long ans = CharlieHelper(captain, assistant, n,dp);
	for(int i=0;i<n;i++) delete []dp[i];
	delete []dp;
	return ans;
}

//	Sqaure Brackets
int SqaureBracketsHelper(bool* OpenBrack ,int n,int **dp,int opCount = 0,int clCount = 0,int index = 1)
{
	if(opCount > n || clCount > n) return 0;
	if((opCount == n && clCount == n) || index > (2*n)) return 1;
	int &ans = dp[index][opCount];
	if(ans != -1) return ans;
	ans = 0;
	if((opCount == clCount) || OpenBrack[index])
		ans = SqaureBracketsHelper(OpenBrack,n,dp,opCount+1,clCount,index+1);
	else if(opCount == n)
		ans = SqaureBracketsHelper(OpenBrack,n,dp,opCount,clCount+1,index+1);
	else
	{
		ans  = SqaureBracketsHelper(OpenBrack,n,dp,opCount+1,clCount,index+1) + 
					SqaureBracketsHelper(OpenBrack,n,dp,opCount,clCount+1,index+1);
	}

	return ans;
}

void SqaureBrackets()
{
	int d,n,k,a;
	vector<int> OpenBrack;
	cin >> d;
	while(d--)
	{
		cin >> n >> k;
		bool *OpenBrack = new bool[2*n+1];
		fill(OpenBrack, OpenBrack + 2*n+1,false);
		while(k--)
		{
			cin >> a;
			OpenBrack[a] = true;
		}
		int **dp = new int*[2*n+1];
		for(int i=0;i<=2*n;i++)
		{
			dp[i] = new int[n+1];
			fill(dp[i], dp[i] + n+1, -1);
		}
		cout << SqaureBracketsHelper(OpenBrack,n,dp) << "\n";
		for(int i=0;i<=2*n;i++) delete []dp[i];
		delete []dp;
	}
	return ;
}

int SqaureBracketsHelper2(vi OpenBrack,int n,int **dp,int opCount = 0,int clCount = 0,int index = 1)
{
	if((opCount == n && clCount == n) || index > (2*n)) return 1;
	int &ans = dp[index][opCount];
	if(ans != -1) return ans;
	ans = 0;
	if(!OpenBrack.empty() && OpenBrack[0] == index)//At these indexes only opening can come not closing
	{
		OpenBrack.erase(OpenBrack.begin());
		ans = SqaureBracketsHelper2(OpenBrack,n,dp,opCount+1,clCount,index+1);
	}
	else
	{
		if(opCount > clCount) ans = SqaureBracketsHelper2(OpenBrack,n,dp,opCount,clCount+1,index+1);

		if(OpenBrack.size() < (n - opCount))
			ans += SqaureBracketsHelper2(OpenBrack,n,dp,opCount+1,clCount,index+1);
	}
	
	return ans;
}

void SqaureBrackets2()
{
	int d,n,k;
	vector<int> OpenBrack;
	cin >> d;
	while(d--)
	{
		cin >> n >> k;
		OpenBrack.resize(k);
		for(int &a: OpenBrack) cin >> a;
		sort(OpenBrack.begin(), OpenBrack.end());
		int **dp = new int*[2*n+1];
		for(int i=0;i<=2*n;i++)
		{
			dp[i] = new int[n+1];
			fill(dp[i], dp[i] + n+1, -1);
		}
		cout << SqaureBracketsHelper2(OpenBrack,n,dp) << "\n";
		for(int i=0;i<=2*n;i++) delete []dp[i];
		delete []dp;
	}
	return ;
}

ll mod = pow(10,9) + 7;

//	Distinct Subsequences
ll DistinctSubsequencesHelper(string s)
{
	map<char,ll> last;
	ll FinalAns = 1;
	last[s[s.size()-1]] = 1;
	for(int i = s.size()-2;i >= 0;i--)
	{
		ll CurrAns = (FinalAns + 1)%mod;
		FinalAns = (FinalAns + (CurrAns - last[s[i]])%mod + mod)%mod;
		last[s[i]] = CurrAns;
	}
	return FinalAns+1;//plus Empty string
}

void DistinctSubsequences()
{
	int T;
	string s;
	cin >> T;
	while(T--)
	{
		cin >> s;
		cout << DistinctSubsequencesHelper(s) << "\n";
	}
	return ;
}


//	Smallest Super-Sequence
int SmallestSuperSequenceHelper(string s,string t,int **dp,int i=0,int j=0)
{
	if(i == s.size() || j == t.size()) return max(s.size() - i, t.size() - j);
	int &ans = dp[i][j];
	if(ans != -1) return ans;
	if(s[i] == t[j]) ans = 1 + SmallestSuperSequenceHelper(s,t,dp,i+1,j+1);
	else ans = min(SmallestSuperSequenceHelper(s,t,dp,i+1,j), SmallestSuperSequenceHelper(s,t,dp,i,j+1))+1;
	return ans;
}

int SmallestSuperSequenceHelper2(string s,string t)
{
	int **dp = new int*[s.size()+1];
	for(int i=0;i<=s.size();i++) dp[i] = new int[t.size()+1]();

	for(int i=s.size()-1;i>=0;i--) dp[i][t.size()] = s.size() - i;
	for(int j=t.size()-1;j>=0;j--) dp[s.size()][j] = t.size() - j;

	for(int i=s.size()-1;i>=0;i--)
	{
		for(int j=t.size()-1;j>=0;j--)
		{
			if(s[i] == t[j]) dp[i][j] = 1 + dp[i+1][j+1];
			else dp[i][j] = 1 + min(dp[i+1][j], dp[i][j+1]);
		}
	}
	int ans = dp[0][0];
	for(int i=0;i<=s.size();i++) delete []dp[i];
	delete []dp;
	return ans;
}

void SmallestSuperSequence()
{
	string s,t;
	cin >> s >> t;
	int **dp = new int*[s.size()];
	for(int i=0;i<s.size();i++)
	{
		dp[i] = new int[t.size()];
		fill(dp[i], dp[i] + t.size(), -1);
	}
	cout << SmallestSuperSequenceHelper(s,t,dp) << "\n";
	for(int i=0;i<s.size();i++) delete []dp[i];
	delete []dp;
	return;
}


//Shortest Subsequence Present in S NOT IN T
int ShortestSubsequence(string s,string t,map<char,vi> &mpT,int **dp,int i = 0,int j = 0)
{
	if(i < s.size() && j == t.size()) return 1;
	if(i == s.size() && j <= t.size()) return INT_MAX;
	int &ans = dp[i][j];
	if(ans != -1) return ans;
	ans = ShortestSubsequence(s,t,mpT,dp,i+1,j);
	int nextIdx = mpT[s[i]][j];
	if(nextIdx != -1)
	{
		int ans2 = ShortestSubsequence(s,t,mpT,dp,i+1,nextIdx+1);
		if(ans2!= INT_MAX) ans2 += 1;
		ans = min(ans, ans2);
	}
	else//It means we have reached end of the string not able to find it out
		ans = 1;
	return ans;
}

int main()
{
	// int T,k,n;
	// vi a;
	// cin >> T;
	// while(T--)
	// {
	// 	cin >> k >> n;
	// 	a.resize(n);
	// 	for(int &b: a) cin >> b;
	// 	cout << MaxTraderProfit(a,k) << "\n";
	// }
	string s,t;
	cin >> s >> t;
	map<char,vi> mpT;
	for(int i=0;i<26;i++) mpT[char(i + 'a')].resize(t.size(),-1);
	for(int i=t.size()-1;i>=0;i--)
	{
		for(int j=i;j>=0;j--) mpT[t[i]][j] = i;
	}
	int **dp = new int*[s.size()];
	for(int i=0;i<s.size();i++)
	{
		dp[i] = new int[t.size()];
		fill(dp[i], dp[i] + t.size(), -1);
	}
	cout << ShortestSubsequence(s,t,mpT,dp) << "\n";
	for(int i=0;i<s.size();i++) delete []dp[i];
	delete []dp;
	return 0;
}

