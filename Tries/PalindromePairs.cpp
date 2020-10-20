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
//     bool ending;
//     trieNode *children[26];
//     trieNode(){
//         ending = false;
//         for(int i=0;i<26;i++) children[i] = NULL;
//     }
// };

// class Solution {
// public:
    

//     void insert(trieNode *head,string &s){

//         trieNode *curr = head;
//         for(int i=0;i<s.size();i++)
//         {
//             int idx = s[i] - 'a';
//             if(curr->children[idx] == NULL) curr->children[idx] = new trieNode();
//             curr = curr->children[idx];
//         }
//         curr->ending = true;
//     }

//     bool search(trieNode *head,string &s)
//     {
//         trieNode *curr = head;
//         for(int i=0;i<s.size();i++)
//         {
//             int idx = s[i] - 'a';
//             if(curr->children[idx] == NULL) return false;
//             curr = curr->children[idx];
//         }
//         return curr->ending == true;
//     }

//     bool isPalindrome(string &t){
//         int i = 0, j = t.size() - 1;
//         while(i<j)
//         {
//             if(t[i++] != t[j--]) return false;
//         }
//         return true;
//     }

//     vector<vector<int> > palindromePairs(vector<string> &words)
//     {
//         vector<vector<int> > ans;
//         map<string,int> mp;
//         trieNode *head = new trieNode();
//         for(int i=0;i<words.size();i++){

//             string s = words[i];
//             reverse(s.begin(), s.end());
//             insert(head, s);
//             mp[s] = i + 1;
//         }

//         if(mp.count("") > 0){
//             for(int i=0;i<words.size();i++)
//             {
//                 if(words[i] != "" && isPalindrome(words[i])){
//                     ans.push_back({mp[""] - 1, i});
//                 }
//             }
//         }

//         for(int i=0;i<words.size();i++){

//             for(int j=0;j<words[i].size();j++){
//                 string left = words[i].substr(0,j), right = words[i].substr(j);
//                 // if(mp.count(left) > 0 && isPalindrome(right) && mp[left] != i+1){
//                 // 	ans.push_back({i, mp[left] - 1});
//                 // }
//                 // if(mp.count(right) > 0 && isPalindrome(left) && mp[right] != i+1){
//                 // 	ans.push_back({mp[right] - 1, i});
//                 // }
//                 // In above case mp.count(s) will take more time to look for the string than our trie
//                 // 	data structure

//                 if(search(head, left) && isPalindrome(right) && mp[left] != i+1){
//                     ans.push_back({i, mp[left] - 1});
//                 }
//                 if(search(head, right) && isPalindrome(left) && mp[right] != i+1){
//                     ans.push_back({mp[right] - 1, i});
//                 }
//             }
//         }
//         return ans;
//     }
// };

//	OR

bool isPalindrome(string t){
    int i = 0, j = t.size() - 1;
    while(i<j)
    {
        if(t[i++] != t[j--]) return false;
    }
    return true;
}

class trieNode{
public:
	int ending;
	trieNode *children[26];
	trieNode(){
		ending = -1;
		for(int i=0;i<26;i++) children[i] = NULL;
	}
};

void insert(trieNode *head,string &s,int i)
{
	trieNode *curr = head;
	for(int i=0;i<s.size();i++)
	{
		int idx = s[i] - 'a';
		if(curr->children[idx] == NULL) curr->children[idx] = new trieNode();
		curr = curr->children[idx];
	}
	curr->ending = i;
}

void search(trieNode *head,string &s,set<pair<int,int> > &ans,int index,bool isPrefix)
{
	trieNode *curr = head;
	if(curr->ending != -1 && isPalindrome(s.substr(0)) && index != curr->ending){
		if(isPrefix) ans.insert({index, curr->ending});
		else ans.insert({curr->ending, index});
	}
	for(int i=0;i<s.size();i++)
	{
		int idx = s[i] - 'a';
		if(curr->children[idx] == NULL) return;
		curr = curr->children[idx];
		if(curr->ending != -1 && isPalindrome(s.substr(i+1)) && index != curr->ending){
			if(isPrefix) ans.insert({index, curr->ending});
			else ans.insert({curr->ending, index});
		}
	}

}


void printTrie(trieNode *head,string s = "")
{
	if(!head) return;
	if(head->ending != -1) cout << s << "\n";
	for(int i=0;i<26;i++)
	{
		if(head->children[i] == NULL) continue;
		printTrie(head->children[i], s + char(i + 'a'));
	}
}

vector<vector<int> > palindromePairs(vector<string> &words)
{
	string s;
	trieNode *head = new trieNode();
	trieNode *Rhead = new trieNode();
	for(int i=0;i<words.size();i++)
	{
		s = words[i];
		insert(head, s, i);
		reverse(s.begin(), s.end());
		insert(Rhead, s, i);
	}
	printTrie(Rhead);
	set<pair<int,int> > ans;
	for(int i=0;i<words.size();i++){
		s = words[i];
		search(Rhead, s, ans, i, true);
		reverse(s.begin(), s.end());
		search(head, s, ans, i, false);
	}
	vector<vector<int> > final;
	for(pair<int,int> a: ans) final.push_back({a.first, a.second});
	return final;
}




int main()
{
	int n;
	cin >> n;
	vector<string> words(n);
	for(string &s: words) cin >> s;
	words.push_back("");
	//Solution final;
	vector<vector<int> > ans = palindromePairs(words);
	for(vector<int> &a: ans) cout << a[0] << " " << a[1] << "\n";
	return 0;
}




