#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>

int maxUniqueSplit(string s,unordered_set<string> &visited, int idx = 0){

	string curr = "";
	int ans = 0;
	for(int i = idx;i < s.size();i++){
		curr += s[i];
		if(visited.count(curr) == 0){
			visited.insert(curr);
			ans = max(ans, maxUniqueSplit(s, visited, i + 1) + 1);
			visited.erase(curr);
		}
	}
	return ans;
}


void maxUniqueSplit(string s,unordered_set<string> &visited, int currMax,int &gMax,int idx = 0){

	if(idx == s.size()){
		gMax = max(gMax, currMax);
		return ;
	}

	string curr = "";
	for(int i = idx;i < s.size();i++){
		curr += s[i];
		if(visited.count(curr) == 0 && gMax < (currMax + s.size() - i)){
			visited.insert(curr);
			maxUniqueSplit(s, visited, currMax + 1,gMax, i + 1);
			visited.erase(curr);
		}
	}
}

int maxUniqueSplit(string s){
	unordered_set<string> visited;
	int gMax = 0;
	maxUniqueSplit(s, visited, 0, gMax);
	return gMax;
}

//	Subsets 2
void backtracking(unordered_map<int,int> &count, unordered_map<int,int>::iterator it, vi temp, vvi &ans){

	if(it == count.end()){
		ans.push_back(temp);
		return;
	}
	auto jt = it;
	backtracking(count, ++jt, temp, ans);
	for(int i = 1;i <= it->second;i++){
		temp.push_back(it->first);
		backtracking(count, jt, temp, ans);
	}
}

vector<vector<int> > SubsetsWithDup(vector<int> &nums){
	unordered_map<int,int> count;
	for(int &a: nums) count[a] += 1;
	vvi ans;
	vi temp;
	backtracking(count, count.begin(), temp, ans);
	return ans;
}



int main(){
	int n;
	cin >> n;
	vi nums(n);
	for(int &a: nums) cin >> a;
	vvi ans = SubsetsWithDup(nums);
	for(vi &a: ans){
		for(int &p: a) cout << p << " ";
		cout << "\n";
	}
	return 0;
}




