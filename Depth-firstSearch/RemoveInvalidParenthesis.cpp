#include <iostream>
#include <vector>
#include <queue>
#include <map>
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
#define vvi vector<vector<int> >
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vs vector<string>

pair<int,int> numInvalid(string s, vvpii &dp, int idx = 0, int ct = 0){
	int n = s.size();
	if(ct < 0 || ct > (n - idx)) return pair<int,int> (10000, 1);
	if(idx == s.size()){
		return pair<int,int> (ct, 0);
	}
	if(dp[idx][ct].first != -1) return dp[idx][ct];
	pair<int,int> ans(100000, 1);
	if(s[idx] != ')' && s[idx] != '(') ans = numInvalid(s, dp, idx + 1, ct);
	else{
		pair<int,int> temp = numInvalid(s, dp, idx + 1, ct);

		if(s[idx] == '('){
			temp.first += 1;
			ans = numInvalid(s, dp, idx + 1, ct + 1);
		}
		else if(s[idx] == ')'){
			temp.second += 1;
			ans = numInvalid(s, dp, idx + 1, ct - 1);
		}
		ans = ((ans.first + ans.second) < (temp.first + temp.second))?ans:temp;
	}
	return dp[ct][idx] = ans;
}

void helper(string s,string p,set<string> &ans, int num,int idx = 0,int ct = 0)
{
	if(ct < 0) return ;
	if(idx == s.size()){
		if(ct != 0 || num != 0) return;
		ans.insert(p);
		return;
	}

	if(s[idx] != ')' && s[idx] != '(') helper(s, p + s[idx], ans, num, idx + 1, ct);
	else{
		if(s[idx] == '(') helper(s, p + s[idx], ans, num, idx + 1, ct + 1);
		else if(s[idx] == ')') helper(s, p + s[idx], ans, num, idx + 1, ct - 1);
		if(num > 0){
			helper(s, p, ans, num - 1, idx + 1, ct);
		}
	}

}

bool isValid(string &s){
	int ct = 0, i = 0;
	while(i < s.size()){
		if(s[i] == '(') ct++;
		else if(s[i] == ')') ct--;

		if(ct < 0) return false;
		i++;
	}
	return ct == 0;
}

void backtrack(vs &res,string s,int pos,int move,int &minMove)
{
	if(pos > s.size() || move > minMove) return;
	if(isValid(s)){
		if(move < minMove) res.clear(), res.push_back(s), minMove = move;
		else if(move == minMove && find(res.begin(), res.end(), s) == res.end()) res.push_back(s);
		return;
	}

	while(pos < s.size() && s[pos] != ')' && s[pos] != '(') pos++;
	if(pos >= s.size()) return;

	backtrack(res, s.substr(0, pos) + s.substr(pos + 1), pos, move + 1, minMove);
	backtrack(res, s, pos + 1, move, minMove);

}


vector<string> removeInvalidParentheses(string s) {
    vs res;
    int minMove = INT_MAX;
    backtrack(res, s, 0, 0, minMove);
    return res;
}


vs bfs(string s)
{
	vs res;
	int move = 0;
	queue<string> q;
	unordered_map<string,int> ump;
	bool check = false;
	q.push(s);
	ump[s] = 1;
	q.push("@");
	while(!q.empty())
	{
		string k = q.front();
		q.pop();
		if(k == "@"){
			if(q.empty() || check) break;
			move++;
			q.push("@");
			continue;
		}
		if(isValid(k)){
			check = true;
			if(find(res.begin(), res.end(), k) == res.end()) res.push_back(k);
		}
		if(check) continue;
		for(int j = 0;j < k.size();j++){
			if(k[j] != '(' && k[j] != ')') continue;
			string temp = k.substr(0,j) + k.substr(j + 1);
			if(ump.count(temp) == 0) q.push(temp), ump[temp] = 1;
		}

	}

	return res;
}



char isValid2(string &k)
{
	int count = 0;
	for(char c: k){

		if(c == '(') count++;
		else if(c == ')'){
			if(count > 0) count--;
			else return ')';
		}
	}

	return count == 0?'o':'(';
}

vs bfs2(string s)
{
	vs res;
	bool check = false;
	unordered_set<string> visited;
	queue<string> q;
	q.push(s);
	visited.insert(s);
	q.push("@");
	while(!q.empty())
	{
		string k = q.front();q.pop();
		if(k == "@"){
			if(check || q.empty()) break;
			q.push("@");
			continue;
		}
		char ch = isValid2(k);
		if(ch == 'o'){
			check = true;
			if(find(res.begin(), res.end(), k) == res.end()) res.push_back(k);
		}
		if(check) continue;
		for(int i = 0;i < k.size();i++){
			if(k[i] == ch){
				string temp = k.substr(0, i) + k.substr(i + 1);
				if(visited.count(temp) == 0) visited.insert(temp), q.push(temp);
			}
		}
	}

	return res;
}


vector<string> removeInvalidParentheses2(string s){
	vs res;
	return bfs2(s);
}


int main(){
	string s;
	cin >> s;
	vector<string> sol = removeInvalidParentheses2(s);
	for(string &a: sol) cout << a << "\n";
	return 0;
}

