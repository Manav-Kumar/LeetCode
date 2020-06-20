#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <set>
#include <unordered_map>

using namespace std;


vector<string> letterCombinations2(string digit)
{
	if(digit.empty()) return vector<string>();
	map<int,vector<char> > vivc;
	int count = 0;
	for(int i=2;i<=9;i++)
	{
		int num=3;
		if(i == 7 || i == 9) num = 4;
		vector<char> vec;
		for(int j=0;j<num;j++)
		{
			char c = 'a' + count;
			vec.push_back(c);
			count++;
		}
		vivc[i] = vec;
	}
	vector<string> ans;
	ans.push_back("");
	for(char c: digit)
	{
		int val=c-'0';
		vector<char> vec = vivc[val];
		vector<string> temp;
		for(int i=0;i<ans.size();i++) for(char z: vec) temp.push_back(ans[i] + z);
		ans = temp;
	}

	return ans;
}

class node
{
public:
	string s;
	int op, cl;
	node(string s,int op = 0, int cl = 0): s(s), op(op), cl(cl) {}
};

vector<string> generateParenthesis(int n)
{
	vector<string> ret;
	queue<node> q;
	q.push(node("(",1,0));
	while(!q.empty())
	{
		node curr = q.front(); q.pop();

		if(curr.op == n && curr.cl == n)
		{
			ret.push_back(curr.s); 
			continue;
		}
		string temp = curr.s + ')';
		if(curr.op > curr.cl) q.push(node(temp, curr.op, curr.cl+1));
		temp = curr.s + '(';
		if(curr.op != n) q.push(node(temp, curr.op+1,curr.cl));

	}
	return ret;
}

int main()
{
	vector<string> ans = generateParenthesis(3);
	for(string s: ans) cout << s << endl;
	return 0;
}

