#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <cmath>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back

ll mod = pow(10,9) + 7;

//	Coordinate Compression
int rectangleArea(vector<vector<int> >& rectangles)
{
	set<int> xvalues, yvalues;	
	rep(i,0,rectangles.size())
	{
		xvalues.insert(rectangles[i][0]), xvalues.insert(rectangles[i][2]);
		yvalues.insert(rectangles[i][1]), yvalues.insert(rectangles[i][3]);
	}
	map<int,int> xmp, ymp, xremp, yremp;
	int k = 0;
	for(auto it1 = xvalues.begin(), it2 = yvalues.begin();it1 != xvalues.end() || it2 != yvalues.end();k++)
	{
		if(it1 != xvalues.end())
		{
			xmp[*it1] = k;
			xremp[k] = *it1;
			it1++;
		}
		if(it2 != yvalues.end())
		{
			ymp[*it2] = k;
			yremp[k] = *it2;
			it2++;
		}
	}
	bool grid[xvalues.size()][yvalues.size()];
	rep(i,0,xvalues.size()) rep(j,0,yvalues.size()) grid[i][j] = false;
	rep(i,0,rectangles.size())
	{
		rep(x, xmp[rectangles[i][0]], xmp[rectangles[i][2]])
		{
			rep(y, ymp[rectangles[i][1]], ymp[rectangles[i][3]]) grid[x][y] = true;
		}
	}

	ll result = 0;
	rep(x,0,xvalues.size()-1)
	{
		rep(y,0,yvalues.size()-1)
		{
			if(!grid[x][y]) continue;
			result += (ll)((ll)xremp[x+1] - xremp[x])*(ll)((ll)yremp[y+1] - yremp[y]);
			result %= mod;
		}
	}
	return int(result%mod);
}

int main()
{
	vector<vector<int> > rectangles;
	int n;
	cin >> n;
	rectangles.resize(n);
	for(vector<int>& v: rectangles)
	{
		v.resize(4);
		for(int &a: v) cin >> a;
	}
	cout << rectangleArea(rectangles) << endl;
	return 0;
}

