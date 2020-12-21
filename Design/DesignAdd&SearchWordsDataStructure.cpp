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


class Trienode{
public:
	vector<Trienode*> children;
	bool isword;
	Trienode(): children(26, NULL), isword(false) {}

	~Trienode(){
		for(int i = 0;i < 26;i++) delete children[i];
	}
};


class WordDictionary{
	Trienode* head;

	bool dfs(string word,Trienode* curr,int idx = 0){

		if(idx == word.size()) return curr && curr->isword;
		if(!curr) return false;

		if(word[idx] != '.'){
			int childidx = word[idx] - 'a';
			return dfs(word, curr->children[childidx], idx + 1);
		}
		else{
			for(int i = 0;i < 26;i++){
				if(!curr->children[i]) continue;
				if(dfs(word, curr->children[i], idx + 1)) return true;
			}
		}
		return false;
	}

	bool bfs(string word){
		int counter = 0;
		queue<Trienode*> q;
		q.push(head);
		while(!q.empty()){
			if(counter == word.size()){
				while(!q.empty()){
					if(q.front()->isword) return true;
				}
				return false;
			}
			int size = q.size();
			for(int turn = 0;turn < size;turn++){
				Trienode* curr = q.front(); q.pop();
				if(word[counter] != '.'){
					int childidx = word[counter] - 'a';
					if(curr->children[childidx]){
						if(counter == word.size() - 1){
							if(curr->children[childidx]->isword) return true;
						}
						else q.push(curr->children[childidx]);
					}
				}
				else{
					for(int i = 0;i < 26;i++){
						if(!curr->children[i]) continue;
						if(counter == word.size() - 1){
							if(curr->children[i]->isword) return true;
						}
						else q.push(curr->children[i]);
					}
				}
			}
			counter++;
		}
		return false;
	}

public:
	WordDictionary(){
		head = new Trienode();
	}

	void addWord(string word){
		Trienode* temp = head;
		for(int i = 0;i < word.size();i++){
			int childidx = word[i] - 'a';
			if(temp->children[childidx] == NULL) temp->children[childidx] = new Trienode();
			temp = temp->children[childidx];
		}
		temp->isword = true;
	}

	bool search(string word){
		return dfs(word, head);
	}

	~WordDictionary(){
		delete head;
	}
};


// class WordDictionary{
// 	unordered_map<int, vector<string> > mp;
// 	bool isSame(string s, string word){
// 		int n = word.size();
// 		for(int i = 0;i < n;i++){
// 			if(word[i] == '.') continue;
// 			if(s[i] != word[i]) return false;
// 		}
// 		return true;
// 	}
// public:
// 	WordDictionary(){
// 		mp.clear();
// 	}

// 	void addWord(string word){
// 		mp[word.size()].push_back(word);
// 	}

// 	bool search(string word){
// 		int n = word.size();
// 		if(mp.find(n) == mp.end()) return false;
// 		for(string s: mp[n]){
// 			if(isSame(s, word)) return true;
// 		}
// 		return false;
// 	}

// };



int main(){

	return 0;
}






