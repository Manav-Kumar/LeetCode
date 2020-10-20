#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stack>
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
#define vl vector<long>
#define vll vector<long long>
#define vc vector<char>
#define vs vector<string>
#define vvc vector<vc>
#define vvi vector<vector<int> >
#define vvl vector<vl>
#define vvll vector<vll>
#define vvb vector<vector<bool> >

int getRmoveTop(stack<int> &s)
{
	int ans = s.top();
	s.pop();
	return ans;
}

int evalRPN(vector<string>& tokens)
{
	stack<int> s;
	int ans = 0, value;
	for(int i=0;i<tokens.size();i++)
	{
		string str = tokens[i];

		if(str == "*") value = getRmoveTop(s) * getRmoveTop(s);
		else if(str == "/")
		{
			int a1 = getRmoveTop(s), a2 = getRmoveTop(s);
			value = a2/a1;
		}
		else if(str == "-")
		{
			int a1 = getRmoveTop(s), a2 = getRmoveTop(s);
            value = a2 - a1;
		}
		else if(str == "+") value = getRmoveTop(s) + getRmoveTop(s);
		else
		{
			value = 0;
			for(int i= (str[0] == '-'?1:0);i<str.size();i++) value = value*10 + (str[i] - '0');
			if(str[0] == '-') value *= -1;
			cout << value << " ";
		}
		s.push(value);
	}
	return s.top();
}


//	Remove K Digits
string remveKDigits(string num,int k)
{
	int req = num.size() - k, value,idx = -1,temp;
	string ans;
	for(int i=req;i>=1;i--)
	{
		value = 9, temp = idx;
		for(int j=num.size() - i;j > temp;j--)
		{
			if(value >= int(num[j] - '0'))
			{
				value = num[j] - '0';
				idx = j;
			}
		}
		if(ans != "" || value != 0) ans += char(value + '0');
	}
	return ans == ""?"0":ans;
}

//Using Stack
string remveKDigits2(string num,int k)
{
	stack<char> s;
	for(int i=0;i<num.size();i++)
	{
		char c = num[i];
		while(!s.empty() && k > 0 && s.top() > c)
		{
			s.pop();
			k--;
		}
		s.push(c);
	}
	string ans = "";
	while(!s.empty())
	{
		ans = s.top() + ans;
		s.pop();
	}

	ans = ans.substr(0, ans.size() - k);

	//Removing leading zeros
	int i=0;
	while(ans[i] == '0') i++;
	ans = ans.substr(i);
	return ans == ""?"0":ans;

}

//	132 Pattern
bool find132pattern(vector<int> &nums)
{
	stack<int> s;
	for(int i=2;i<nums.size();i++)
	{
		int ok = -1;
		for(int j=i-1;j>0;j--)
		{
			if(nums[i] < nums[j])
			{
				ok = j;
				break;
			}
		}
		if(ok == -1) continue;
		for(int j=ok-1;j>=0;j--)
		{
			if(nums[i] > nums[j]) return true;
		}
	}

	return false;
}

bool find132pattern2(vector<int> &nums)
{
	int n = nums.size();
    if(n <= 2) return false;
    vector<int> minValues(n,0);
    minValues[0] = nums[0];
    for(int i=1;i<n;i++)
    {
        if(nums[i] >= minValues[i-1]) minValues[i] = minValues[i-1];
        else minValues[i] = nums[i];
    }

    stack<int> s;
    for(int j=n-1;j>=0;j--)
    {
        if(!s.empty())
        {
            if(nums[j] <= s.top()) s.push(nums[j]);
            else
            {
                while(!s.empty())
                {
                    if(s.top() >= nums[j]) break;
                    if(minValues[j] < s.top()) return true;
                    s.pop();
                }
                s.push(nums[j]);
            }
        }
        else s.push(nums[j]);
    }

    return false;
}

int main()
{
	int n;
	cin >> n;
	vi nums;
	nums.resize(n);
	for(int &a: nums) cin >> a;
	cout << find132pattern2(nums) << "\n";
	return 0;
}

