#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>

class trienode{
public:
	vector<trienode*> next;
	trienode(): next(26, NULL) {}
};

int insertFirst(string a, trienode* root){
	trienode* curr = root;
	for(char c: a){
		int idx = c - 'a';
		if(curr->next[idx] == NULL) curr->next[idx] = new trienode();
		curr = curr->next[idx];
	}
	return a.size();
}

int insert(string a,trienode* root){
	trienode* curr = root;
	int count = 0;
	for(int i=0;i<a.size();i++){
		int idx = a[i] - 'a';
		if(curr->next[idx] == NULL){
			return i;
		}
		else curr = curr->next[idx];
	}
	return a.size();
}

int main(){
	trienode* root = new trienode();
	int n, len = 0;
	string ans = "";
	cin >> n;
	string a;
	for(int i=0;i<n;i++){
		cin >> a;
		if(i == 0){
			len = insertFirst(a, root);
		}
		else len = min(len, insert(a, root));

		if(i == n - 1) ans = a.substr(0, len);
	}

	cout << ans << "\n";
	return 0;
}



