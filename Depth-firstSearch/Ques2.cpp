#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>

using namespace std;
#define vi vector<int>
#define vb vector<bool>
#define vvi vector<vi>
#define vvb vector<vb>

int minTimeReq(int n, vector<int> &expertise){
	int m = expertise.size(), time = 0;
	priority_queue<vi, vector<vi>, greater<vi> > pq;
	for(int i=0;i<m;i++){
		pq.push(vi {expertise[i], expertise[i], expertise[i]});//	total_time_taken, last_value, k
	}
	while(n--){
		vi curr = pq.top(); pq.pop();
		time = curr[0];
		curr[0] += curr[1] + curr[2];
		curr[1] += curr[2];
		pq.push(curr);
	}
	return time;
}

void Ques4(){
	int n;
	cin >> n;
	vector<int> f(n), s(n), th(n);
	for(int &a: f) cin >> a;
	for(int &a: s) cin >> a;
	for(int &a: th) cin >> a;
	cout << "Done Inserting\n";
	sort(f.begin(), f.end()); sort(s.begin(), s.end());
	sort(th.begin(), th.end());
	int i = 0, j = 0, k = 0, diff = INT_MAX;
	vector<int> ans(3);
	while(i < n && j < n && k < n){
		int maxval = max({f[i], s[j], th[k]}), minval = min({f[i], s[j], th[k]}), value = maxval - minval;
		if(value < diff){
			ans = {f[i], s[j], th[k]}, diff = value;
		}
		if(minval == f[i]) i++;
		else if(minval == s[j]) j++;
		else if(minval == th[k]) k++;
		else cout << "notok\n";
	}
	sort(ans.begin(), ans.end(), greater<int> ());
	for(int i=0;i<3;i++) cout << ans[i] << " ";
}

int maxCost(vector<int> &cost){
	if(cost.size() == 1) return cost[0];
	int n = cost.size(), prod_val = 0, ans = 0;
	for(int i=0;i<n;i++){
		vector<int> temp = cost;
		if(i == 0) prod_val = cost[i]*cost[i + 1];
		else if(i == n - 1) prod_val = cost[i]*cost[i - 1];
		else prod_val = cost[i - 1]*cost[i]*cost[i + 1];
		temp.erase(temp.begin() + i);
		ans = max(ans, maxCost(temp) + prod_val);
	}
	return ans;
}

int main () {
	int n;
	cin >> n;
	vector<int> cost(n);
	for(int &a: cost) cin >> a;
	cout << maxCost(cost) << "\n";
	return 0;
}





