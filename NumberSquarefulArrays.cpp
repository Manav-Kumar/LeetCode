#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>

using namespace std;

#define rep(i,a,b) for(int i = a;i<b;i++)

bool isPerfect(long long num)
{
	long double sr = sqrt(num);
	return (sr == floor(sr));
}
int getFact(int count)
{
	int ans = 1;
	for(int c = 1;c <= count;c++) ans *= c;
	return ans;
}

int helper(vector<int>& A,int prev,int used, int **dp)
{
	if(used == (1<<A.size())-1) return 1;
	int total = 0;
	if(dp[prev][used] != -1) return dp[prev][used];
	for(int i = 0;i < A.size();i++)
	{
		if((used&(1<<i)) == 0 && (prev == -1 || isPerfect(A[prev]+A[i])))
		{
			used |= 1<<i;
			total += helper(A, i, used, dp);
			used &= ~(1<<i);
		}
	}
	dp[prev][used] = total;
	return total;
}


int numSquarefulPerms(vector<int>& A)
{
	int n = A.size();
	int **dp = new int*[n];
	for(int i=0;i<n;i++)
	{
		dp[i] = new int[(1<<n)];
		fill(dp[i], dp[i] + (1<<n), -1);
	}

	int ans=0, used = 0;
	for(int i = 0;i<n;i++)
	{
		used |= (1<<i);
		ans += helper(A, i, used, dp);
		used &= ~(1<<i);
	}



	for(int i=0;i<n;i++) delete []dp[i];
	delete []dp;
	map<int,int> sim;
	for(int &a: A) sim[a] += 1;
	cout << ans << endl;
	for(auto it = sim.begin();it!=sim.end();it++) ans /= getFact(it->second);

	return ans;
}

// Return all unique permutations

void helper2(map<int,int> count,vector<int> ans, vector<vector<int> >&ret)
{
	if(count.empty())
	{
		ret.push_back(ans);
		return;
	}

	for(auto it = count.begin();it != count.end();++it)
	{
		map<int,int> temp = count;
		int key = it->first;
		ans.push_back(key);
		temp[key] -= 1;
		if(!temp[key]) temp.erase(key);
		helper2(temp, ans, ret);
		ans.pop_back();
	}
}

vector<vector<int> > permuteUnique(vector<int>& nums)
{
	map<int,int> count;
	for(int n: nums) count[n] += 1;
	vector<vector<int> > ret;
	helper2(count, vector<int>(),ret);
	return ret;
}


int main()
{
	vector<int> nums;
	int n;
	cin >> n;
	nums.resize(n);
	for(int &a: nums) cin >> a;
	cout << "Stop inputting " << endl;
	vector<vector<int> > ans = permuteUnique(nums);
	rep(i,0,ans.size())
	{
		rep(j,0,n) cout << ans[i][j] << " ";
		cout << "\n";
	}
	return 0;
}


