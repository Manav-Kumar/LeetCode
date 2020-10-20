#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <cmath>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define ll long long

#define MAXR 5005
#define inf 1<<28


int helper(vi &rods,vvi &dp,int idx,int leftSum,int rightSum)
{
	if(idx == rods.size()){
		if(leftSum == rightSum) return 0;
		return -(1<<28);
	}
	int &ans = dp[idx][leftSum - rightSum + MAXR];
	if(ans != INT_MIN) return ans;

	int best = helper(rods, dp, idx + 1, leftSum, rightSum);
	best = max(best, helper(rods, dp, idx + 1, leftSum + rods[idx], rightSum) + rods[idx]);
	best = max(best, helper(rods, dp, idx + 1, leftSum, rightSum + rods[idx]));

	ans = best;
	return best;
}

int tallestBillBoard(vi &rods){
	int n = rods.size();
	vvi dp(n, vi(2*MAXR, INT_MIN));
	return helper(rods, dp, 0, 0, 0);
}


pair<int,int> moveClockWise(string ring,int idx,char c){
	int len = ring.size(), count = 0;
	while(ring[idx] != c){
		idx = (idx + 1)%len;
		count++;
	}

	return pair<int,int> (idx, count);
}

pair<int,int> moveAntiClockWise(string ring,int idx,char c){
	int len = ring.size(), count = 0;
	while(ring[idx] != c){
		idx = (idx - 1 + len)%len;
		count++;
	}
	return pair<int,int> (idx, count);
}


int helper2(string ring,int ri,string key,int kidx)
{
	if(kidx == key.size()) return 0;

	char c = key[kidx];
	if(c == ring[ri]) return helper2(ring, ri, key, kidx + 1) + 1;

	pair<int,int> temp = moveClockWise(ring, ri, c);
	int a1 = helper2(ring, temp.first, key, kidx + 1) + temp.second + 1;

	temp = moveAntiClockWise(ring, ri, c);
	int a2 = helper2(ring, temp.first, key, kidx + 1) + temp.second + 1;

	return min(a1, a2);
}

pair<int,int> moveClockWise2(int ringSz, vi pos, int ri){
	int st = 0, en = pos.size() - 1, ansIdx = -1, count = 0;
	while(st <= en){
		int mid = (st + en)/2;
		if(pos[mid] == ri){
			ansIdx = pos[mid];
			break;
		}
		if(ri > pos[mid]) st = mid + 1;
		else if(ri < pos[mid]) {
			ansIdx = pos[mid];
			en = mid - 1;
		}
	}

	if(ansIdx != -1){
		count = ansIdx - ri;
		return pair<int,int> (ansIdx, count);
	}
	else{
		ansIdx = pos[0];
		count = ringSz - ri  + ansIdx;
		return pair<int,int> (ansIdx, count);
	}

}

pair<int,int> moveAntiClockWise2(int ringSz,vi pos, int ri){
	int st = 0, en = pos.size() - 1, count = 0, ansIdx = -1;
	while(st <= en){
		int mid = (st + en)/2;
		if(pos[mid] == ri){
			ansIdx = pos[mid];
			break;
		}
		if(ri > pos[mid]){
			ansIdx = pos[mid];
			st = mid + 1;
		}
		else if(ri < pos[mid]) en = mid - 1;
	}

	if(ansIdx != -1){
		count = ri - ansIdx;
		return pair<int,int> (ansIdx, count);
	}
	else{
		ansIdx = pos[pos.size() - 1];
		count = ri + ringSz - ansIdx;
		return pair<int,int> (ansIdx, count);
	}
}



int findRotateSteps(string ring, string key, map<char, vi> &pos,int ri = 0,int kidx = 0){

	if(kidx == key.size()) return 0;

	char c = key[kidx];

	if(c == ring[ri]) return findRotateSteps(ring, key, pos, ri, kidx + 1) + 1; 

	pair<int,int> temp = moveClockWise2(ring.size(), pos[c], ri);
	int a1 = findRotateSteps(ring, key, pos, temp.first, kidx + 1) + temp.second + 1;
	temp = moveAntiClockWise2(ring.size(), pos[c], ri);
	int a2 = findRotateSteps(ring, key, pos, temp.first, kidx + 1) + temp.second + 1;
	return min(a1, a2);
}


int get(string &ring, string &key, int i,int j,vvi &pos, vvi &dp){

	if(j == key.size()) return dp[i][j] = 0;

	if(dp[i][j] != -1) return dp[i][j];
	int ans = INT_MAX;
	char c = key[j];
	if(ring[i] == c) ans = 1 + get(ring, key, i, j + 1, pos, dp);
	else{
		for(int p: pos[c - 'a']){
			int cost = 1 + min(max(i,p) - min(i,p), min(i, p) + ringSz - max(i, p));
			ans = min(ans, cost + get(ring, key, p, j + 1, pos, dp));
		}
	}

	dp[i][j] = ans;

	return ans;

}

int findRotateSteps2(string ring,string key){
	int ringSz = ring.size(), keySz = key.size();
	vvi pos(26, vi());
	for(int i = 0;i < ringSz;i++){
		pos[ring[i] - 'a'].push_back(i);
	}
	vvi dp(ringSz, vi(keySz + 1, -1));
	return get(ring, key, 0, 0, pos, dp);

}

int main(){
	string ring, key;
	cin >> ring >> key;
	map<char,vector<int> > pos;
	for(int i=0;i<ring.size();i++) pos[ring[i]].push_back(i);
	cout << findRotateSteps(ring, key, pos) << "\n";
	return 0;
}








