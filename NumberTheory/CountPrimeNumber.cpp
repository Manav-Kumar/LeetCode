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


bool checkPrime(int n)
{
	int countFactors = 0;
	for(int j=1;j*j<=n;j++)
	{
		if(n%j == 0)
		{
			if(j*j == n) countFactors += 1;
			else countFactors += 2;
		}
	}
	if(countFactors == 2) return true;
	else return false;
}

int seive(int n)
{
	vector<bool> isprime(n+1, true);
	isprime[0] = false;
	isprime[1] = false;
	int count = 0;
	for(int i = 2;i*i<=n;i++)
	{
		if(isprime[i])
		{
			for(int j=i*i;j<=n;j+=i) isprime[j] = false;
		}
	}
	rep(i,0,n+1)
	{
		if(isprime[i]) count++;
	}
	return count;
}

//	Find the integral solution for eq: ax + by = gcd(a,b), a,b are integers
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
		ans.y = 0;//It can be random value we are assigning it 0, it doesn't matter
		return ans;
	}

	Triplet smallAns = extendedEuclid(b, a%b);
	Triplet ans;
	ans.gcd = smallAns.gcd;
	ans.x = smallAns.y;
	ans.y = smallAns.x - (a/b)*smallAns.y;
	return ans;
}

//	Applications of Extended Euclid is Finding Inverse Modulo
int findInverseModulo(int a,int m)
{
	//	Find b -->  (a*b)%m = 1
	//	To exist it's sol gcd(a,m) == 1
	if(gcd(a,m) == 1)
	{
		Triplet sol = extendedEuclid(a,m);
		if((a*sol.x)%m == 1) return sol.x;
	} 
	else
	{
		cout << "Sol doesn't exist \n";
		return -1;
	}
}

int main()
{
	int n;
	cin >> n;
	int count = 0;
	for(int i=1;i<=n;i++)
	{
		if(checkPrime(i)) count++;
	}
	cout << count << endl;
}