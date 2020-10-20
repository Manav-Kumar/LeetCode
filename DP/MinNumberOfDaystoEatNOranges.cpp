#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define ll long long

//	Using Recursive Approach would fill the memory due to calls stack
int minDays2(int n){
	vector<int> dp(max(4,n + 1), 0);
    dp[1] = 1, dp[2] = 2, dp[3] = 2;
    for(int i = 4;i <= n;i++){
        dp[i] = dp[i-1];
        if(i%2 == 0) dp[i] = min(dp[i], dp[i/2]);
        if(i%3 == 0) dp[i] = min(dp[i], dp[i/3]);
        dp[i] += 1;
    }
    return dp[n];
}


int minDays(int n)
{
	int level = 0;
	queue<int> days;
	unordered_map<int,bool> visisted;
	days.push(n);
	visisted[n] = true;
	days.push(-1);
	while(!days.empty()){
		int curr = days.front();
		days.pop();
		if(curr == 0) return level;
		if(curr == -1){
			days.push(-1);
			level++;
			continue;
		}
		if(visisted.count(curr - 1) == 0 && (curr%2 != 0 || curr%3 != 0)){
			if(curr - 1 == 0) return level + 1;
			visisted[curr - 1] = true;
			days.push(curr - 1);
		}
		if(curr%2 == 0 && visisted.count(curr/2) == 0){
			if(curr/2 == 0) return level + 1;
			visisted[curr/2] = true;
			days.push(curr/2);
		}
		if(curr%3 == 0 && visisted.count(curr/3) == 0){
			if(curr/3 == 0) return level + 1;
			visisted[curr/3] = true;
			days.push(curr/3);
		}
	}
	return level;

	// int up = 0, down = 0;
	// queue<int> forward;
	// queue<int> backward;
	// forward.push(n), forward.push(-1);
	// backward.push(0), backward.push(-1);

	// while(!forward.empty() && !backward.empty())
	// {
	// 	int cforw = forward.front(), cback = backward.front();

	// 	if(cforw == 0) return up;
	// 	if(cback == n) return down;

	// 	if(cforw == cback){
	// 		return up + down;
	// 	}
	// 	if(cforw == -1){
	// 		forward.push(-1);
	// 		forward.pop();
	// 		up++;
	// 		continue;
	// 	}

	// 	if(cback == -1){
	// 		backward.push(-1);
	// 		backward.pop();
	// 		down++;
	// 		continue;
	// 	}

	// 	forward.pop(), backward.pop();
	// 	forward.push(cforw - 1);
	// 	if(cforw%2 == 0) forward.push(cforw/2);
	// 	if(cforw%3 == 0) forward.push(cback/3);

	// 	if(cback > cforw) continue;
	// 	backward.push(cback + 1);
	// 	backward.push(2*cback);
	// 	backward.push(3*cback);		
	// }
	// return up + down;
}

int main(){
	ll n;
	cin >> n;
	cout << minDays(n) << "\n";
	return 0;
}