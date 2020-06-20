#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <unordered_set>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)

bool canPlace(vector<string> ans, int x,int y)
{
	//Check Vertically
	int tempx = x, tempy = y;
	while(tempx >= 0)
	{
		if(ans[tempx][tempy] == 'Q') return false;
		tempx--;
	}
	tempx = x;
	//Check Left Diagnol
	while(tempx >= 0 && tempy >= 0)
	{
		if(ans[tempx][tempy] == 'Q') return false;
		tempx--, tempy--;
	}
	tempx = x, tempy = y;
	//Check Right Diagnol
	while(tempx >= 0 && tempy < ans.size())
	{
		if(ans[tempx][tempy] == 'Q') return false;
		tempx--, tempy++;
	}
	return true;
}

void helper(int n,vector<string> ans,vector<vector<string> > &sol,int idx = 0)
{
	if(idx == n)
	{
		sol.push_back(ans);
		return;
	}

	for(int i=0;i<n;i++)
	{
		if(canPlace(ans,idx,i))
		{
			ans[idx][i] = 'Q';
			helper(n, ans, sol, idx+1);
			ans[idx][i] = '.';
		}
	}

}

vector<vector<string> > solveNQueens(int n)
{
	vector<vector<string> > sol;
	vector<string> ans(n, string(n,'.'));
	helper(n, ans, sol);
	return sol;
}

void helper2(int n,bool *col, bool *digLeft,bool *digRight,int &ans,int idx = 0)
{
	if(idx == n)
	{
		ans++;
		return;
	}
	for(int i=0;i<n;i++)
	{
		if(col[i] || digLeft[idx - i + n] || digRight[idx + i]) continue;
		col[i] = digLeft[idx - i + n] = digRight[idx + i] = true;
		helper2(n, col, digLeft, digRight, ans, idx+1);
		col[i] = digLeft[idx - i + n] = digRight[idx + i] = false;
	}
}

int solveNQueensGetCount(int n)
{
	bool *col = new bool[n]();
	bool *digLeft = new bool[2*n]();
	bool *digRight = new bool[2*n]();
	int ans = 0;
	helper2(n, col, digLeft, digRight, ans);
	return ans;
}

int main()
{
	vector<vector<string> > ans = solveNQueens(4);
	rep(i,0,ans.size())
	{
		rep(j,0,4) cout << ans[i][j] << endl;
		cout << "\n\n";
	}
	cout << "Total count is " << solveNQueensGetCount(4) << endl;
	return 0;
}