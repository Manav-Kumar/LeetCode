#include <iostream>
#include <vector>
#include <queue>

#define rep(i,a,b) for(int i = a;i<b;i++)
#define revI(i,b,a) for(int i = b;i >= a;i--)

using namesapce std;

bool helper(vector<int>& nums,int start,bool *reached = NULL)
{
	if(start < 0 || start >= nums.size() || reached[start]) return false;
	if(nums[start] == 0) return true;
	reached[start] =  true;
	bool a1 = helper(nums, start - nums[start], reached);
	bool a2 = helper(nums, start + nums[start], reached);
	return a1||a2;
}

bool canReach(vector<int>& nums,int start)
{
	int n = nums.size();
	queue<int> pending;
	bool *visited = new bool[n]();
	fill(visited, visited + n, false);
	pending.push(start);
	visited[start] = true;
	while(!pending.empty())
	{
		int index = pending.front();
		pending.pop();
		if(nums[index] == 0) return true;
		int left = index - nums[index];
		if(left >= 0 && !visited[left]) visited[left] = true, pending.push(left);
		int right = index + nums[index];
		if(right < n && !visited[right]) visited[right] = true, pending.push(right);
	}
	return false;
}

int main()
{

}