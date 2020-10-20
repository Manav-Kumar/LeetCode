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
#define vc vector<char>
#define vvc vector<vc>
#define vvi vector<vector<int> >
#define vvb vector<vector<bool> >

bool isSafe(vvc &seats,int x,int y)
{
	//Left
	if(y-1 >= 0 && seats[x][y-1] == 'p') return false;
	//Right
	if((y+1) < seats[0].size() && seats[x][y+1] == 'p') return false;
	//Upper Left
	if(x-1 >= 0 && y-1 >= 0 && seats[x-1][y-1] == 'p') return false;
	//Upper Right
	if(x-1 >= 0 && y+1 < seats[0].size() && seats[x-1][y+1] == 'p') return false;
	return true;
}

int helper(vvc &seats,int ***dp,int prev = 0,int mask = 0,int x = 0,int y = 0)
{
	if(x == seats.size()) return 0;
	if(y == seats[0].size()) return helper(seats, dp,mask, 0,x+1,0);
	if(seats[x][y] == '#') return helper(seats, dp, prev,mask,x, y+1);
	if(dp[x][y][prev] != -1) return dp[x][y][prev];
	int ans = 0;
	if(isSafe(seats,x,y))
	{
		seats[x][y] = 'p';
		mask |= (1<<y);
		prev |= (1<<(seats[0].size()+y));
		ans = max(ans, helper(seats, dp, prev,mask,x,y+1) + 1);
		mask &= ~(1<<y);
		prev &= ~(1<<(seats[0].size()+y));
		seats[x][y] = '.';
	}
	ans = max(ans, helper(seats,dp, prev,mask, x, y+1));
	dp[x][y][prev] = ans;
	return ans;
}

int maxStudents(vvc &seats,int x = 0,int y = 0)
{
    int ***dp = new int**[8];
    for(int i=0;i<8;i++)
    {
        dp[i] = new int*[8];
        for(int j=0;j<8;j++)
        {
            dp[i][j] = new int[(1<<17)];
            fill(dp[i][j], dp[i][j] + (1<<17), -1);
        }
    }
    int ans = helper(seats, dp);
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++) delete []dp[i][j];
        delete []dp[i];
    }
    delete []dp;
    return ans;
}


//MaxStudent FASTER APPROACH

bool isValid(int mask,vc &seats)
{
	int n = seats.size();
	for(int i=0;i<n;i++)
	{
		int p = n - 1 - i;
		if(seats[i] == '#' && (mask&(1<<p))) return false;
	}
	return true;
}

bool noConsecutive(int mask)
{
	int p = (mask<<1);
	return (mask&p) == 0;
}

int CountOnes(int mask)
{
	int count = 0;
	while(mask > 0)
	{
		if((mask&1) == 1) count++;
		mask = mask>>1;
	}
	return count;
}

int maxStudents2(vvc &seats)
{
	int n = seats.size(), m = seats[0].size();
	int m1 = (1<<m);
	vvi dp = vvi(n, vi(m1,-1));

	for(int i=0;i<n;i++)
	{
		for(int mask = 0;mask < m1;mask++)
		{
			if(isValid(mask, seats[i]) && noConsecutive(mask))
			{
				int ct = CountOnes(mask);
				if(i == 0)
				{
					dp[i][mask] = ct;
					continue;
				}
				int count = 0;
				for(int temp = 0;temp < m1;temp++)
				{
					int x1 = temp^mask;
					if(dp[i-1][temp] != -1 && noConsecutive(x1))
					{
						count = max(count, ct + dp[i-1][temp]);
					}
				}
				dp[i][mask] = count;
			}
		}
	}

	int ans = 0;
	for(int mask=0;mask<m1;mask++) ans = max(ans, dp[n-1][mask]);
	return ans;
}


int main()
{
	int n,m;
	cin >> n >> m;
	vvc seats = vvc(n, vc(m));
	for(vc &a: seats) for(char &c: a) cin >> c;
	cout << maxStudents2(seats) << "\n";
	return 0;
}

