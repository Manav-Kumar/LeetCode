#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> movesToStamp(string stamp, string target)
{
	int m = stamp.size(), n = target.size();
	vector<int> res;
	while(1)
	{
		bool check = false;
		for(int i = 0;i < (n-m+1);i++)
		{
			bool ch = true, isChar = false;
			for(int j = 0;j < m;j++)
			{
				if(target[i+j] == '?' || target[i+j] == stamp[j]) {
					if(target[i+j] == stamp[j]) isChar = true;
				}
				else
				{
					ch = false;
					break;
				}
			}
			if(ch && isChar)
			{
				res.push_back(i);
				for(int j = i;j < (i+m);j++) target[j] = '?';
				check = true;
				break;
			}
		}

		if(check)
		{
			int i = 0;
			for(;i < n;i++) if(target[i] != '?') break;
			if(i == n)
			{
				reverse(begin(res), end(res));
				return res;
			}
		}
		else
		{
			return vector<int>();
		}
	}
}

int n,m;
string target, stamp


int main()
{
	cin >> stamp >> target;
	n = target.size(), m = stamp.size();
	vector<int> ans = movesToStamp(stamp, target);
	for(int a: ans) cout << a << " ";
	return 0;
}




