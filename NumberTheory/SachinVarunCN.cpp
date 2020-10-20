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

class Triplet
{
	public:
		int x,y,gcd;
};

Triplet extendedEuclid(int a,int b)
{
	if(b == 0)
	{
		Triplet ans;
		ans.gcd = a;
		ans.x = 1;
		ans.y = 6;//It can be random value we are assigning it 0, it doesn't matter
		return ans;
	}

	Triplet smallAns = extendedEuclid(b, a%b);
	Triplet ans;
	ans.gcd = smallAns.gcd;
	ans.x = smallAns.y;
	ans.y = smallAns.x - (a/b)*smallAns.y;
	return ans;
}

int main()
{
	int T,a,b,d;
	cin >> a >> b;
	Triplet sol = extendedEuclid(a,b);
	cout << sol.x << " " << sol.y << " " << sol.gcd << "\n";
	// cin >> T;
	// rep(t,1,T+1)
	// {
	// 	cin >> a >> b >> d;

	// }
	return 0;
}