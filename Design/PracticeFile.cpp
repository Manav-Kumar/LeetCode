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
#include <list>
#include <climits>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vll vector<ll>
#define vi vector<int>
#define vvi vector<vi >
#define vvvi vector<vvi>
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>


//	Merge Intervals
bool comp(vi &a, vi &b){
	if(a[0] == b[0]) return a[1] > b[1];
	return a[0] < b[0];
}
vvi merge(vvi &Intervals){
	sort(Intervals.begin(), Intervals.end(), comp);
	vvi ans;
	int st = -1, en = -1;
	for(vi &a: Intervals){
		if(a[0] > en){
			if(en != -1) ans.push_back({st, en});
			st = a[0], en = a[1];
		}
		else if(a[1] > en) en = a[1];
	}
	if(en != -1) ans.push_back({st, en});
	return ans;
}

//	Solve Above using Connected Components - > O (n^2)
void mergeHelper(vvi &Intervals, vb &visited, int &st,int &en,int idx){

	st = min(st, Intervals[idx][0]), en = max(en, Intervals[idx][1]);
	visited[idx] = true;
	rep(i, 0, visited.size()){
		if(!visited[i] && ((Intervals[i][0] >= st && Intervals[i][0] <= en) || (Intervals[i][1] >= st && Intervals[i][1] <= en) || (Intervals[i][0] <= st && Intervals[i][1] >= en)))
		 mergeHelper(Intervals, visited, st, en, i);
	}
}
vvi merge2(vvi &Intervals){
	int n = Intervals.size(), st, en;
	vb visited(n, false);
	vvi ans;
	rep(i, 0, n){
		if(!visited[i]){
			st = Intervals[i][0], en = Intervals[i][1];
			mergeHelper(Intervals, visited, st, en, i);
			ans.push_back({st, en});
		}
	}
	return ans;
}

//	Longest Substring without Repeating Characters
int lengthOfLongestSubstring(string s){
	if(s.empty()) return 0; 
	//	Rolling Hash , s can consist of lowercase eng, digits, symbols, spaces
	unordered_map<char,int> visited;
	vi Hash(100, -2);
	int ans = 0, t = 0, n = s.size(), last = -1;
	rep(i, 0, n){
		if(Hash[s[i] - ' '] <= last) t += 1, Hash[s[i] - ' '] = i;
		else{
			ans = max(ans, t);
			last = Hash[s[i] - ' '];
			Hash[s[i] - ' '] = i;
			//	Optimize on it
			//for(int j = k + 1;j <= i;j++) visited[s[j]] = j;
			t = i - last;
		}
	}
	ans = max(ans, t);
	return ans;
}


class Node{
public:
	int val;
	Node* prev;
	Node* next;
	Node* child;
};

Node* flatten(Node* head, Node* prev, Node* &tail){
	if(!head) return NULL;
	head->prev = prev;
	if(!head->child){
		head->next = flatten(head->next, head, tail);
		if(head->next == NULL) tail = head;
	}
	else{
		Node* nt = head->next;
		head->next = flatten(head->child, head, tail);
		head->child = NULL;
		// Node* tail = head;
		// while(tail->next) tail = tail->next;
		tail->next = flatten(nt, tail, tail);
	}
	return head;
}


int main(){
	string s;
	cin >> s;
	cout << lengthOfLongestSubstring(s) << "\n";
	return 0;
}





