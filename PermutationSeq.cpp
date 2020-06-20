#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define rep(i,a,b) for(int i = a;i<b;i++)

int getFact(int n)
{
	if(n == 0) return 1;
	int ans = 1;
	for(int i = 1;i<=n;i++) ans *= i;
	return ans;
}

string getPermutation(int n,int k)
{
	set<int> remaining;
	for(int i=1;i<=n;i++) remaining.insert(i);
	k--;
	string ans = "";
	while(n)
	{
		auto it = remaining.begin();
		if(n == 1)
		{
			int val = *it;
			ans += char(val + '0');
			break;
		}
		int nm1 = getFact(n-1);
		int idx = k/nm1;
		it = next(it, idx);
		ans += char(*it + '0');
		remaining.erase(it);
		k = k%nm1;
		n--;
	}
	return ans;
}

int main()
{
	cout << getPermutation(4,6) << endl;
	return 0;
}