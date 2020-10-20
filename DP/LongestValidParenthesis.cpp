#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>

int longestValidParentheses(string s,vvi &visited, int op = 0,int cl = 0,int idx = 0,int start = -1)
{
	if(idx == s.size()) return 0;

	if(s[idx] == '(') ++op;
	else ++cl;

	if(visited[start + 1][idx + 1] != -1) return visited[start + 1][idx + 1];

	int a1 = 0;
	if(op >= cl){
		a1 = longestValidParentheses(s, visited, op, cl, idx + 1, start != -1?start:idx);
	}

	int a2 = longestValidParentheses(s, visited, 0, 0, idx + 1);

	int ans = max(a1, a2);
	if(op == cl) ans = max(ans, idx - start + 1);
	visited[start + 1][idx + 1] = ans;
	return ans;
}


int longestValidParentheses2(string s){
	s = 'a' + s;
	int best = 0, n = s.size();
	vector<int> ans(n, 0);
	stack<int> idx;
	for(int i=1;i<s.size();i++){
		if(s[i] == '(') idx.push(i);
		else if(idx.size() > 0){
			cout << i << " " << idx.top() << "\n";
			best = max(best, i - idx.top() + 1 + ans[idx.top() - 1]);
			ans[i] = i - idx.top() + 1 + ans[idx.top() - 1];
			idx.pop();
		}
	}
	for(int i=1;i<ans.size();i++) cout << ans[i] << " ";
	cout << "\n";
	return best;
}

int longestValidParentheses3(string s)
{
	stack<int> idx;
	stack<char> characters;
	int best = 0;
	idx.push(-1);
	for(int i = 0;i < s.size();i++){
		if(s[i] == '('){
			idx.push(i);
			characters.push('(');
		}
		else{
			if(!characters.empty()){
				idx.pop();
				characters.pop();
				best = max(best, i - idx.top());
			}
			else{
				idx.push(i);
			}
		}
	}
	return best;
}


int main(){
	string s;
	cin >> s;
	int n = s.size();
	vvi visited(n + 1, vi(n + 1, -1));
	cout << longestValidParentheses2(s) << "\n";
	return 0;
}