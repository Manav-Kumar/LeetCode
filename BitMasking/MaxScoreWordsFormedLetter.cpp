#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <cmath>
#include <math.h>
#include <unordered_set>
#include <string>
using namespace std;

#define ll long long
#define vl vector<ll>
#define vll vector<vl>
#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>
#define vvb vector<vb>

int helper(vector<string> &words,map<char,int> count,vector<int> &score,vvi &dp,int index = 0,int mask = 0){

	if(index == words.size()) return 0;
	if(dp[index][mask] != -1) return dp[index][mask];
	int a1 = helper(words, count, score, dp, index + 1, mask);
	int a2 = 0, value = 0;
	bool check = true;
	for(char &c: words[index]){
		if(count[c] > 0){
			value += score[c - 'a'];
			count[c]--;
		}
		else{
			check = false;
			break;
		}
	}
	if(check){
		a2 = helper(words, count, score, dp, index + 1, mask | (1<<index)) + value;
	}
	dp[index][mask] =  max(a1, a2);
	return dp[index][mask];
}

int maxScoreWords(vector<string> &words, vector<char>& letters,vector<int> &score)
{
	map<char,int> count;
	for(char &c: letters) count[c]++;
	int n = words.size();
	vvi dp(n, vi(1<<n, -1));
	return helper(words, count, score, dp);
}


int longestAwesome(string s)
{
	int currParity = 0,best = 1;
	vector<int>  mp(1024, s.size());
	mp[currParity] = -1;
	for(int i=0;i<s.size();i++){

		currParity ^= 1 << (s[i] - '0');

		if(mp[currParity] != s.size()){
			best = max(best, i - mp[currParity]);
		}

		for(int d=0;d<10;d++){
			int new_mask = (currParity ^ (1<<d));
			best = max(best, i - mp[new_mask]);
		}

		mp[currParity] = min(mp[currParity], i);
	}

	return best;
}

int subarraySum(vector<int> &nums,int k)
{
	int ans = 0, sum = 0;
	map<int,int> mp;
	mp[0] = 1;
	for(int i=0;i<nums.size();i++){
		sum += nums[i];
		if(mp.count(sum - k) > 0) ans += mp[sum - k];
		mp[sum]++;
	}
	return ans;
}

ll mod = 1e9 + 7;

int numberWaysHelper(vvi &hatsLabels,int n, vvi &dp, int mask = 0,int index = 1){

	if(index > 40){
		if(mask == ((1<<n)-1)) return 1;
		return 0;
	}
	if(dp[index][mask] != -1) return dp[index][mask];
	ll ans = 0;
	for(int &person: hatsLabels[index]){
		if(((mask>>person)&1) == 0){
			ans = (ans + numberWaysHelper(hatsLabels, n, dp, mask | (1<<person), index + 1))%mod;
		}
	}
	ans = (ans + numberWaysHelper(hatsLabels, n, dp, mask, index + 1))%mod;
	dp[index][mask] = ans;
	return ans;
}

int numberWays(vvi &hats){
	int n = hats.size();
	vvi hatsLabels(41);
	for(int i=0;i<n;i++){
		for(int &a: hats[i]){
			hatsLabels[a].push_back(i);
		}
	}
	vvi dp(41, vi((1<<n), -1));
	return numberWaysHelper(hatsLabels, n, dp);
}

int rangeBitwiseAnd(int m,int n){
	int len = n - m, prev = 0, last = 0;
	for(int i=0;i<31;i++){
		int bit = (m>>i)&1;
		if(bit){
			int count = ((1<<i)-1) - last;
			if(count >= len){
				cout << count << " " << prev << "\n";
				return m&(~prev);
			}
		}
		prev |= (1<<i);
		last |= bit*(1<<i);
	}
	return 0;
}

class trieNode{
public:
	bool isTerminal;
	trieNode* left;
	trieNode* right;
	trieNode(): left(NULL), right(NULL), isTerminal(false) {}
	~trieNode(){
		delete left;
		delete right;
	}
};

void insert(trieNode *root,int& value,int& k)
{
	for(int i=k-1;i>=0;i--){
		int bit = (value>>i)&1;
		if(bit){
			if(!root->right) root->right = new trieNode();
			root = root->right;
		}
		else{
			if(!root->left) root->left = new trieNode();
			root = root->left;
		}
	}
	root->isTerminal = true;
}

bool search(trieNode *root, int& value,int& k)
{
	for(int i=k-1;i>=0;i--){
		int bit = (value>>i)&1;
		if((bit && root->right == NULL) || (!bit && root->left == NULL)) return false;
		if(bit) root = root->right;
		else root = root->left;
	}
	return root->isTerminal;
}

bool hasAllCodes(string s,int k){
	trieNode *root = new trieNode();
	int i = 0, curr = 0, mask = ((1<<k) - 1);
	for(;i<k && i < s.size();i++){
		int bit = s[i] - '0';
		curr = (curr << 1);
		if(bit){
			curr |= 1;
		}
	}
	insert(root, curr, k);
	while(i < s.size()){
		int bit = s[i++] - '0';
		curr = (curr<<1)&mask;
		if(bit){
			curr |= 1;
		}
		insert(root, curr, k);
	}

	for(int mask = 0;mask < (1<<k);mask++){
		if(!search(root, mask, k)){
			delete root;
			return false;
		}
	}
	delete root;
	return true;

}


int maxFreq(string s,int maxLetters, int minSize,int maxSize){
	
	int len = minSize, i = 0, best = 0, count, unique = 0;
	unordered_map<string,int> mp;
	string curr = "";
	for(;i < minSize && i < s.size();i++) curr += s[i];
	mp[curr] += 1;
	while(i < s.size()){
		curr = curr.substr(1);
		curr += s[i++];
		mp[curr] += 1;
	}

	for(auto it = mp.begin();it != mp.end();it++){
		string s = it->first;
		count = 0, unique = 0;
		for(char &c: s){
			count = count | (1 << (c - 'a'));
		}
		for(int i=0;i<26;i++) if((count>>i)&1) unique++;
		if(unique <= maxLetters) best = max(best, it->second);
	}

	return best;
}



int main(){
	string s;
	int k;
	cin >> s >> k;
	cout << hasAllCodes(s, k) << "\n";
	return 0;
}



