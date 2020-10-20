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

int* makeSeive(int n)
{
	int *lpd = new int[n +1];
	rep(i,1,n+1) lpd[i] = i;
	for(int i=2;i*i<=n;i++)
	{
		if(lpd[i] == i)
		{
			for(int j=i*i;j<=n;j+=i)
			{
				if(lpd[j] == j) lpd[j] = i;
			}
		}
	}
	return lpd;
}

void helper(vb &marked,int start,int factor,vi &finalAns)
{
	for(int i=start;i >= 1;i -= factor)
	{
		if(marked[i]) continue;
		marked[i] = true;
		finalAns.pb(i);
	}
}

int main()
{
	int n,x;
	cin >> n;
	int *lpd = makeSeive(n);
	vb marked(n+1, false);
	repR(i,n,1)
	{
		if(marked[i]) continue;
		x = i;
		vi finalAns;
		while(x != 1)
		{
			ll num = lpd[x];
			while(x%num == 0) x /= num;
			helper(marked, i, num, finalAns);
		}
		sort(finalAns.begin(), finalAns.end(), greater<int>());
		rep(i,0,finalAns.size()) cout << finalAns[i] << " ";
	}
	cout << 1;
	delete []lpd;
	return 0;
}
