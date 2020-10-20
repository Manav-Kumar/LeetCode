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
#include <string>
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
// 	int isending;
// 	trieNode *children[26];
// 	trieNode(int ct = -1): isending(ct){
// 		for(int i=0;i<26;i++) children[i] = NULL;
// 	}
// };

// void insert(trieNode *head,string s,int index)
// {
// 	trieNode *curr = head;
// 	for(int i=0;i<s.size();i++){
// 		int idx = s[i] - 'a';
// 		if(curr->children[idx] == NULL) curr->children[idx] = new trieNode();
// 		curr = curr->children[idx];
// 	}
// 	curr->isending = index;
// }

// void deleteMem(trieNode *head)
// {
// 	if(!head) return;
// 	for(int i=0;i<26;i++) deleteMem(head->children[i]);
// 	delete head;
// }

// bool isAvailable(trieNode* head,trieNode *curr, int index,string s,set<int> occured,string prev= "")
// {
// 	if(index == s.size()){
// 		if(curr->isending == -1) return false;
// 		occured.insert(curr->isending);
// 		//return s.size() != prev.size();
// 		return occured.size() >= 2;
// 	}
// 	int idx = s[index] - 'a';
// 	bool ans = false;
// 	if(curr->children[idx] != NULL) ans = isAvailable(head, curr->children[idx], index + 1, s,
// 			occured, prev + s[index]);
// 	if(ans) return true;
// 	if(curr->isending != -1)
// 	{
// 		occured.insert(curr->isending);
// 		ans = isAvailable(head, head, index, s, occured, "");
// 	}
// 	return ans;
// }


// vector<string> findAllConcatenatedWordsInADict(vector<string> &words){
// 	trieNode *head = new trieNode();
// 	int emptyString = -1;
// 	for(int i=0;i<words.size();i++){
// 		if(words[i] != "") insert(head, words[i], i);
// 		else emptyString = i;
// 	}
// 	vector<string> ans;
// 	set<int> occured;
// 	if(emptyString != -1) occured.insert(emptyString);
// 	for(int i=0;i<words.size();i++)
// 	{
// 		if(words[i] == "") continue;
// 		if(isAvailable(head, head, 0, words[i], occured)) ans.push_back(words[i]);
// 	}

// 	deleteMem(head);
// 	return ans;
// }


class trieNode{
public:
	int isending;
	trieNode *children[26];
	trieNode(int ct = -1): isending(ct){
		for(int i=0;i<26;i++) children[i] = NULL;
	}
};

void insert(trieNode *head,string s,int i)
{
	trieNode *curr = head;
	for(int i=0;i<s.size();i++){
		int idx = s[i] - 'a';
		if(curr->children[idx] == NULL) curr->children[idx] = new trieNode();
		curr = curr->children[idx];
	}
	curr->isending = i;
}

int startsWith(trieNode *head,string s)
{
	trieNode *curr = head;
	for(int i=0;i<s.size();i++){
		int idx = s[i] - 'a';
		if(curr->children[idx] == NULL) return -1;
		curr = curr->children[idx]; 
	}
	return curr->isending;
}

bool isConcatenated(trieNode *head,int start,string s, string chunk = "")
{
	if(start == s.size()){
		return s.size() != chunk.size();
	}
	string newChunk = "";
	for(int i = start;i < s.size();i++){
		newChunk += s[i];
		int t = startsWith(head, newChunk);
		if(t == -1) continue;
		if(isConcatenated(head, i + 1, s,  newChunk)) return true;
	}

	return false;
}


vector<string> findAllConcatenatedWordsInADict(vector<string> &words)
{
	trieNode *head = new trieNode();
	bool emptyString = false;
	for(int i=0;i<words.size();i++){
		if(words[i] != "") insert(head, words[i], i);
		else emptyString = true;
	}
	vector<string> ans;
	for(int i=0;i<words.size();i++){

		if(words[i] == "") continue;
		if(isConcatenated(head, 0, words[i])) ans.push_back(words[i]);
	}
	return ans;
}



// class trieNode{
// public:
// 	int isending;
// 	trieNode *children[26];
// 	trieNode(int ct = -1): isending(ct){
// 		for(int i=0;i<26;i++) children[i] = NULL;
// 	}
// };

// void insert(trieNode *head,string s,int i)
// {
// 	trieNode *curr = head;
// 	for(int i=0;i<s.size();i++){
// 		int idx = s[i] - 'a';
// 		if(curr->children[idx] == NULL) curr->children[idx] = new trieNode();
// 		curr = curr->children[idx];
// 	}
// 	curr->isending = i;
// }

// int startsWith(trieNode *head,string s)
// {
// 	trieNode *curr = head;
// 	for(int i=0;i<s.size();i++){
// 		int idx = s[i] - 'a';
// 		if(curr->children[idx] == NULL) return -1;
// 		curr = curr->children[idx]; 
// 	}
// 	return curr->isending;
// }



// bool isConcatenated(trieNode *head,trieNode *curr,int start,string s, set<int> occured)
// {
// 	if(start == s.size()){
// 		if(curr->isending == -1) return false;
// 		occured.insert(curr->isending);
// 		return occured.size() >= 2;
// 	}
	
// 	bool ans = false;

// 	int idx = s[start] - 'a';
// 	if(curr->children[idx] != NULL) ans = isConcatenated(head, curr->children[idx], start+1, s,
// 			occured);
// 	if(ans) return true;
// 	if(curr->isending != -1)
// 	{
// 		occured.insert(curr->isending);
// 		ans = isConcatenated(head, head, start, s, occured);
// 	}
// 	return ans;
// }

// bool compare(string &a, string &b){
// 	return a.size() < b.size();
// }

// vector<string> findAllConcatenatedWordsInADict(vector<string> &words)
// {
// 	sort(words.begin(), words.end(), compare);
// 	int emptyString = -1;
// 	if(words[0] == "")
// 	{
// 		emptyString = 0;
// 		words.erase(words.begin());
// 	}
// 	set<int> occured;
// 	if(emptyString != -1) occured.insert(0);
// 	vector<string> ans;
// 	trieNode *head = new trieNode();
// 	insert(head, words[0], 0);
// 	for(int i=1;i<words.size();i++){
// 		if(isConcatenated(head, head, 0, words[i], occured)) ans.push_back(words[i]);
// 		insert(head, words[i], i);
// 	}
// 	return ans;
// }




int main()
{
	int n;
	cin >> n;
	vector<string> words(n);
	for(string &s: words) cin >> s;
	vector<string> ans = findAllConcatenatedWordsInADict(words);
	for(string &a: ans) cout << a << "\n";
	return 0;
}



