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
#include <climits>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vvi vector<vi >
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>

void fill(vb &visited, int &lasPos, int counter)
{
	int n = visited.size() - 1, start = counter + lasPos;
	if(start >= n){
		lasPos = n + 1;
		return;
	}
	for(int i = counter + lasPos;i >= 0 && visited[i] == false;){
		if(i <= n) visited[i--] = true;
	}
	lasPos += counter;
}

int minPatches(vi &nums, int n){
	vb visited(n + 1, false);
	int counter = 1, idx = 0, ans = 0, lasPos = 0;
	while(lasPos <= n && counter <= n){

		while(idx < nums.size() && nums[idx] == counter){
			fill(visited, lasPos, counter);
			idx++;
		}

		if(!visited[counter]){
			fill(visited, lasPos, counter);
			ans++;
		}

		counter++;
	}
	return ans;
}


int minPatches2(vi &nums,int n)
{
	int curr = 1, ans = 0, idx = 0;
	while(curr <= n){
		bool check = true;
		int temp = curr;
		while(idx < nums.size() && nums[idx] <= temp){
			curr = (check?temp - 1:curr) + nums[idx];
			idx++, check = false;
		}
		if(check){
			curr = curr + curr - 1;
			ans++;
		}

		curr++;
	}

	return ans;
}


int main(){
	int n, m;
	cin >> n >> m;
	vi nums(m);
	for(int &a: nums) cin >> a;
	cout << minPatches2(nums, n) << "\n";
	return 0;
}


