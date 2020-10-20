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
#define vs vector<string>
#define N 1000000


int integerReplacement(int n)
{
	int count = 0, temp = n;
	while(n > 1)
	{
		int firstBit = (n&1);
		if(firstBit == 0) n = n>>1;
		else
		{
			if(((n>>1)&1) == 1 && n != 3) n += 1;
			else n -= 1;
		}
		count += 1;
	}
	return count;
}

string findAns(int sol)
{
    int min = 0, hrs = 0;
    for(int i = 0;i<6;i++) if(((sol>>i)&1)) min += (1<<i);
    for(int j = 0;j < 4;j++)
    {
        if(((sol>>(j+6))&1) == 1) hrs += (1<<j);
    }
    string ans = "";
    if(hrs/10) ans += char((hrs/10) + '0');
    ans += char((hrs%10) + '0');
    ans += ":";
    ans += char((min/10) + '0');
    ans += char((min%10) + '0');
    return ans;
}
void helper(int num,vector<string>& ans,int sol = 0,int index = 0)
{
    if(index == 10)
    {
        if(num == 0) ans.push_back(findAns(sol));
        return ;
    }
    if(num > 0) helper(num-1, ans,sol | (1<<index),index + 1);
    helper(num, ans, sol, index+1);
}

vector<string> readBinaryWatch(int num) {
    vector<string> ans;
    helper(num, ans);
    return ans;
}

//Bit Array BitWise OR
int subarrayBitWiseOR(vector<int> &A)
{
	set<int> ans, curr, curr2;
	for(int &a: arr)
	{
		curr2 = {a};
		for(int &c: curr)
		{
			curr2.insert(c|a);
		}
		curr = curr2;
		ans.insert(curr.begin(), curr.end());
	}
	return ans.size();
}

int totalHammingDistance(vector<int>& nums)
{
	vector<int> ones(32,0);
	for(int &a: nums)
	{
		for(int i=0;i<32;i++)
		{
			ones[i] += ((a>>i)&1);
		}
	}

	int sum = 0;
	for(int &l: ones)
	{
		sum += l*(nums.size() - l);
	}
	return sum;
}

int main()
{
	int n;
	cin >> n;
	std::vector<string> v = readBinaryWatch(3);
	string arr[] = {"0:03","0:05","0:06","0:09","0:10","0:12","0:17","0:18","0:20","0:24","0:33","0:34","0:36","0:40","0:48","1:01","1:02","1:04","1:08","1:16","1:32","2:01","2:02","2:04","2:08","2:16","2:32","3:00","4:01","4:02","4:04","4:08","4:16","4:32","5:00","6:00","8:01","8:02","8:04","8:08","8:16","8:32","9:00","10:00"};
	cout << v.size() << "\n";
	rep(i,0,v.size())
	{
		bool ok = true;
		for(int j = 0;j < 45;j++) if(v[i] == arr[j]) ok = false;
		if(ok) cout << v[i] << " ";
	}
	return 0;
}


