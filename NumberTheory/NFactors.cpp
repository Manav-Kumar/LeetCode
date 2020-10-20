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

vector<vector<int> > makeSeive()
{
	int *seive = new int[N+1]();
	fill(seive, seive + N+1, 0);
	//	Handling only even prime 2
	for(int j=2;j<=N;j+=2) seive[j] += 1;
	//	Handling rest of Odd numbers
	for(int i = 3;i<=N;i += 2)
	{
		if(seive[i] == 0)
		{
			for(int j=i;j<=N;j+=i) seive[j] += 1;
		}
	}

	vector<vector<int> >vmp(11, vector<int>(N+1,0));
	for(int ct=0;ct<=10;ct++)
	{ 
		int count = 0;
		rep(i,1,N+1)
		{
			if(seive[i] == ct) vmp[ct][i] = ++count;
			else vmp[ct][i] = count;
		}
	}
	delete []seive;
	return vmp;
}

int main()
{
	//	Precomputation
	vector<vector<int> > seive = makeSeive();
	int T,a,b,n;
	cin >> T;
	rep(t,1,T+1)
	{
		cin >> a >> b >> n;
		cout << seive[n][b] - seive[n][a-1] << "\n";
	}
	return 0;
}