#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


#define vvi vector<vector<int> > 
#define vi vector<int>


vvi intervalIntersection(vvi& A, vvi& B) {

    int i = 0, j = 0;
    vvi res;
    while(i < A.size() && j < B.size())
    {
        int m = max(A[i][0], B[j][0]);
        int M = min(A[i][1], B[j][1]);
        
        if(m <= M)
        {
            res.push_back(vector<int> {m,M});
            int k = (M == A[i][1]?++i: ++j);
        }
        else if(A[i][1] < B[j][0]) i++;
        else if(A[i][0] > B[j][1]) j++;
    }
    
    return res;
}

bool isMatch(string s,string p,int **dp)
{
	if(p == "*" || (p.empty() && s.empty())) return true;
	if(p.empty() && !s.empty()) return false;
	int n = s.size(), m = p.size();
	if(dp[n][m] != -1) return dp[n][m];
	if(s.empty())
	{
		if(p[0] == '*') dp[n][m] = isMatch(s, p.substr(1), dp);
		else dp[n][m] = false;
		return dp[n][m];
	}
	bool firt_match = (p[0] == '?' || p[0] == s[0]);
	bool ans = false;
	if(firt_match) ans = isMatch(s.substr(1), p.substr(1), dp);
	else if(p[0] == '*') ans = (isMatch(s, p.substr(1), dp) || isMatch(s.substr(1), p, dp));
	dp[n][m] = ans;
	return ans;
}

//Memoization
bool isMatchMem(string s,string p)
{
	int n = s.size(), m = p.size();
	bool **dp = new bool*[n+1];
	for(int i = 0;i <= n;i++) dp[i] = new bool[m+1];
	for(int i = 1;i <= n;i++) dp[i][0] = false;
	fill(dp[0], dp[0] + m+1, false);
	for(int j = 1;j <= m;j++)
	{
		if(p[m-j] == '*') dp[0][j] = true;
		else break;
	}
	dp[0][0] = true;
	for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j <= m;j++)
		{
			dp[i][j] = false;
			int ni = n-i, mj = m-j;
			bool firt_match = (p[mj] == '?' || p[mj] == s[ni]);
			if(firt_match) dp[i][j] = dp[i-1][j-1];
			else if(p[mj] == '*') dp[i][j] = dp[i][j-1] || dp[i-1][j];
		}
	}

	bool ans = dp[n][m];
	for(int i = 0;i <= n;i++) delete []dp[i];
	delete []dp;
	return ans;
}

//Faster Solution
bool isMatchIterative(string s,string p)
{
	string star = "", ss = "";
	while(!s.empty())
	{
		if(s[0] == p[0] || p[0] == '?')
		{
			s = s.substr(1);
			p = p.substr(1);
			continue;
		}
		if(p[0] == '*')
		{
			star = p, p = p.substr(1);
			ss = s;
			continue;
		}
		if(!star.empty())
		{
			p = star.substr(1);
			ss = ss.substr(1);
			s = ss;
			continue;
		}

		return false;
	}

	while(!p.empty() && p[0] == '*') p = p.substr(1);
	return p.empty(); 
}

int main()
{
	string s,p;
	cin >> s >> p;
	int n = s.size(), m = p.size();
	int **dp = new int*[n+1];
	for(int i = 0;i <= n;i++)
	{
		dp[i] = new int[m+1];
		fill(dp[i], dp[i]+m+1,-1);
	}
	bool ans = isMatchMem(s, p);
	for(int i = 0;i <= n;i++) delete []dp[i];
	delete []dp;
	cout << ans << endl;
	return 0;
}


