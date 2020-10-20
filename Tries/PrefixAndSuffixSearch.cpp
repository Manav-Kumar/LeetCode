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
#include <deque>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vl vector<long>
#define vll vector<long long>
#define vc vector<char>
#define vs vector<string>
#define vvc vector<vc>
#define vvi vector<vector<int> >
#define vvvi vector<vvi>
#define vvl vector<vl>
#define vvll vector<vll>
#define vvb vector<vector<bool> >
#define vvvb vector<vvb>

// class trieNode{
// public:
// 	int count;
// 	trieNode** children;
// 	trieNode(int ct = 0){
// 		count = ct;
// 		children = new trieNode*[26];
// 		for(int i=0;i<26;i++) children[i] = NULL;
// 	}
// };


// void insert(trieNode *head,string s,int pr)
// {
// 	trieNode *curr = head;
// 	while(!s.empty())
// 	{
// 		curr->count = max(curr->count,pr);
// 		int idx = s[0] - 'a';
// 		if(curr->children[idx] == NULL) curr->children[idx] = new trieNode(pr);
// 		curr = curr->children[idx];
// 		s = s.substr(1);
// 	}
// 	curr->count = max(curr->count, pr);
// }

// int query(trieNode *head,string s)
// {
// 	trieNode *curr = head;
// 	while(!s.empty()){
// 		int idx = s[0] - 'a';
// 		if(curr->children[idx] == NULL) return -1;
// 		curr = curr->children[idx];
// 		s = s.substr(1);
// 	}
// 	return curr->count;
// }




// class WordFilter{
// public:
// 	trieNode *headPre;
// 	trieNode *headSuf;
// 	WordFilter(vector<string> &words){
// 		headPre = new trieNode();
// 		headSuf = new trieNode();
// 		for(int i=0;i<words.size();i++){
// 			string s = words[i];
// 			insert(headPre, s, i);
// 			reverse(s.begin(), s.end());
// 			insert(headSuf, s, i);
// 		}
// 	}

// 	int f(string prefix,string suffix){
// 		set<int> p = query(headPre, prefix);
// 		reverse(suffix.begin(), suffix.end());
// 		set<int> s = query(headSuf, suffix);
// 		auto it1 = s.begin();
// 		auto it2 = p.begin();
// 		int ans = -1;
// 		while(it1 != s.end() && it2 != p.end()){
// 			if(*it1 < *it2) it1++;
// 			else if(*it1 > *it2) it2++;
// 			else{
// 				ans = *it1;
// 				it1++, it2++;
// 			}
// 		}
// 		return ans;
// 	}
// };



class trieNode
{
public:
	int prt;
	trieNode* children[27];
	trieNode(int ct = 0){
		prt = ct;
		for(int i=0;i<27;i++) children[i] = NULL;
	}
};

void insert(trieNode *head,string s,int prt)
{
	trieNode *curr = head;
	while(!s.empty()){
		curr->prt = max(curr->prt, prt);
		int idx = (s[0] == '#')?26:(s[0] - 'a');
		if(curr->children[idx] == NULL) curr->children[idx] = new trieNode(prt);
		curr = curr->children[idx];
		s = s.substr(1);
	}
	curr->prt = max(curr->prt, prt);
}

int query(trieNode *head,string s){

	trieNode *curr = head;
	while(!s.empty()){
		int idx = (s[0] == '#')?26:(s[0] - 'a');
		if(curr->children[idx] == NULL) return -1;
		curr = curr->children[idx];
		s = s.substr(1);
	}
	return curr->prt;
}

void deleteMem(trieNode *head)
{
	if(!head) return;
	for(int i=0;i<27;i++) deleteMem(head->children[i]);
	delete []head;
	return;
}

class WordFilter{
public:
	trieNode *head;
	WordFilter(vector<string> &words){
		head = new trieNode();
		for(int i=0;i<words.size();i++){
			string s = words[i], k = "#" + words[i];
			insert(head, k, i);
			for(int j=s.size()-1;j >= 0;j--){
				k = s[j] + k;
				insert(head, k, i);
			}
		}
	}

	int f(string prefix,string suffix)
	{
		string s = suffix + '#' + prefix;
		return query(head, s);
	}

	~WordFilter(){
		deleteMem(head);
	}
};



//	Pair Trie 
// class trieNode{
// public:
// 	int prt;
// 	trieNode **children;
// 	trieNode(int ct = 0){
// 		prt = ct;
// 		children = new trieNode*[26*26]();
// 		for(int i=0;i<26*26;i++) children[i] = NULL;
// 	}
// };

// void insert(trieNode *head,string prefix,string suffix,int prt)
// {
// 	trieNode *curr = head;
// 	while(!prefix.empty())
// 	{
// 		curr->prt = max(curr->prt, prt);
// 		int idx = int(prefix[0] - 'a')*26 + int(suffix[0] - 'a');
// 		if(curr->children[idx] == NULL) curr->children[idx] = new trieNode(prt);
// 		curr = curr->children[idx];
// 		prefix = prefix.substr(1), suffix = suffix.substr(1); 
// 	}
// 	curr->prt = max(curr->prt, prt);
// }

// int helper1(trieNode *head,string prefix)
// {
// 	if(prefix.empty()) return head->prt;
// 	int ans = -1;
// 	for(int i=0;i<26;i++){
// 		int idx = int(prefix[0] - 'a')*26 + i;
// 		if(head->children[idx]) ans = max(ans, helper1(head->children[idx], prefix.substr(1)));
// 	}
// 	return ans;
// }

// int helper2(trieNode *head,string suffix)
// {
// 	if(suffix.empty()) return head->prt;
// 	int ans = -1;
// 	for(int i=0;i<26;i++){
// 		int idx = i*26 + (suffix[0] - 'a');
// 		if(head->children[idx]) ans = max(ans, helper2(head->children[idx], suffix.substr(1)));
// 	}
// 	return ans;
// }

// int query(trieNode *head,string prefix,string suffix)
// {
// 	trieNode *curr = head;
// 	while(!prefix.empty() || !suffix.empty())
// 	{
// 		int idx;
// 		if(!prefix.empty() && !suffix.empty()){
// 			idx = int(prefix[0] - 'a')*26 + int(suffix[0] - 'a');
// 			if(curr->children[idx] == NULL) return -1;
// 			curr = curr->children[idx];
// 			prefix = prefix.substr(1), suffix = suffix.substr(1);
// 		}
// 		else if(!prefix.empty()){
// 			return helper1(curr, prefix);
// 		}
// 		else if(!suffix.empty()){
// 			return helper2(curr, suffix);
// 		}
// 	}
// 	return curr->prt;
// }

// class WordFilter{
// public:
// 	trieNode *head;
// 	WordFilter(vector<string> &words)
// 	{
// 		head = new trieNode();
// 		for(int i=0;i<words.size();i++){
// 			string prefix = words[i], suffix = words[i];
// 			reverse(suffix.begin(), suffix.end());
// 			insert(head, prefix, suffix, i);
// 		}
// 	}

// 	int f(string prefix,string suffix)
// 	{
// 		return query(head, prefix, suffix);
// 	}
// };


int main(){
	int n, q;
	string prefix, suffix;
	cin >> n >> q;
	vector<string> words(n);
	for(string &s: words) cin >> s;
	WordFilter wf(words);
	while(q--){
		cin >> prefix >> suffix;
		cout << wf.f(prefix, suffix) << "\n";
	}
	return 0;
}




