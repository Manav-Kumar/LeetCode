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
#define N 750000

ll mod = pow(10,9) + 7;

class duplet
{
public:
	map<ll,ll> mp;
	ll sum;
	duplet(): sum(0) {}
};

int goodSets(vector<int>& a)
{
	ll *seive = new ll[N+1]();
	fill(seive, seive + N + 1, 0);
	for(int &b: a) seive[b] = 1;
	for(int i=1;2*i<=N;i++)
	{
		if(seive[i] > 0){
			for(int j = 2*i;j<=N;j+=i) if(seive[j] > 0) seive[j] = (seive[j] + seive[i])%mod; 
		}
	}
	ll ans = 0;
	for(int i=1;i<=N;i++)
	{
		if(seive[i] > 0) ans = (ans + seive[i]%mod)%mod;
	}
	delete []seive;
	return int(ans);
}

//	Card Game(CN)
bool isDivisible(vector<pair<int,int> > &vp,vector<pair<int,int> > &vq)
{
	rep(i,0,vp.size()) if(vq[i].second < vp[i].second) return false;
	return true;
}

vector<pair<int,int> > generateVecPrime(ll n)
{
	vector<pair<int,int> > v;
	ll x = n;
	for(int i=2;i*i<=x;i++)
	{
		int count = 0;
		while(n%i == 0)
		{
			n /= i;
			count += 1;
		}
		if(count == 0) continue;
		v.push_back(pair<int,int>(i, count));
	}
	if(n != 1) v.push_back(pair<int,int>(n,1));
	return v;
}

void modify(vector<pair<int,int> > &vq,ll num,bool add = true)
{
	rep(i,0,vq.size())
	{
		int count = 0;
		while(num%vq[i].first == 0)
		{
			num /= vq[i].first;
			count += 1;
		}
		if(add) vq[i].second += count;
		else vq[i].second -= count;
	}
}

int CardGame()
{
	int n,k,i = 0,j = 0;
	cin >> n >> k;
	vector<pair<int,int> > vp = generateVecPrime(k);
	vector<pair<int,int> > vq(vp);
	rep(i,0,vq.size()) vq[i].second = 0;
	vector<int> a;
	a.resize(n);
	for(int &b: a) cin >> b;
	ll ans = 0;
	j = 0;
	rep(i,0,n)
	{
		modify(vq, a[i], true);
		while(j<=i)
		{
			if(isDivisible(vp, vq))
			{
				ans += (n-i);
				modify(vq, a[j], false);
				j++;
			}
			else break;
		}
	}
	return ans;
}


int main()
{
	cout << CardGame() << "\n";
	return 0;
}