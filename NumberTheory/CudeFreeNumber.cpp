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

int main()
{
	//	Precomputation
	vector<int> cubeFree(N, 0);
	cubeFree[0] = -1;
	for(int i = 2;i*i*i<=N;i++)
	{
		if(cubeFree[i] == 0)
		{
			for(int j = i*i*i;j<=N;j += (i*i*i)) cubeFree[j] = -1;
		}
	}
	int count = 0;
	rep(i,1,N+1)
	{
		if(cubeFree[i] == 0) cubeFree[i] = ++count;
	}
	int T,n;
	cin >> T;
	rep(t,1,T+1)
	{
		cin >> n;
		cout << "Case " << t << ": ";
		if(cubeFree[n] == -1) cout << "Not Cube Free\n";
		else cout << cubeFree[n] << "\n"; 
	}
	return 0;
}