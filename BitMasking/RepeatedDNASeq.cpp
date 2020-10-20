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

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vvi vector<vector<int> >
#define vvb vector<vector<bool> >
#define vs vector<string>
#define vvs vector<vs>
#define ull unsigned long long
#define vull vector<ull> 
#define vvull vector<vull>
#define vp vector<pair<int,ull> >
#define vvp vector<vp>


vector<string> findRepeatedDNASequences(string s){
	vector<string> ans;
	map<char,int> indexing;
	indexing['A'] = 0, indexing['C'] = 1, indexing['G'] = 2, indexing['T'] = 3;
	int curr = 0;
	for(int i=0;i<10 && i < s.size();i++){
		int value = indexing[s[i]];
		curr |= (value << (2*i));
	}
	
	map<int,int> mp;
	mp[curr]++;
	for(int i=10;i < s.size();i++){

		int value = indexing[s[i]];

		curr = (curr>>2) | (value<<18);

		if(mp[curr] == 1){
			ans.push_back(s.substr(i-9, 10));
		}

		mp[curr]++;
	}

	return ans;
	// vector<string> ret;
	// for(int& s: ans){
	// 	string k = "";
	// 	for(int i=0;i<10;i++){
	// 		int temp = s&(3);
	// 		if(temp == 0) k += 'A';
	// 		else if(temp == 1) k += 'C';
	// 		else if(temp == 2) k += 'G';
	// 		else if(temp == 3) k += 'T';
	// 		s = (s>>2);
	// 	}
	// 	ret.push_back(k);
	// }
	// return ret;
}


//	Number of Steps
int numSteps(string s){
	int ans = 0, i = s.size()-1;
	while(i >= 0){
		if(s[i] == '0'){
			ans++, i--;
		}
		else if(s[i] == '1' && i == 0){
			return ans;
		}
		else if(s[i] == '1'){
			++ans;
			while(i >= 0 && s[i] != '0'){
				ans++, i--;
			}
			if(i < 0) return  ans;
			s[i] = '1';
		}
	}
	return ans;
}


//	Sum of 2 Integers
int getSum(int a, int b) {
    int carry = 0, idx = 0,ans = 0;
    for(int i=0;i<32;i++){
    	int bit = ((a>>i)&1)^((b>>i)&1)^carry;
    	if(bit) ans |= (1<<i);
    	if(!carry) carry = ((a>>i)&1)&((b>>i)&1);
    	else{
    		if(((a>>i)&1) || ((b>>i)&1)) carry = 1;
    		else carry = 0;
    	}
    }
    return ans;
}

//	Maximum XOR of 2Numbers in array
class node{
public:
	node* left;
	node* right;
	node(): left(NULL), right(NULL) {}
};

void insert(node* root,int value)
{
	for(int i=31;i>=0;i--){
		int bit = (value>>i)&1;
		if(bit){
			if(!root->right) root->right = new node();
			root = root->right;
		}
		else{
			if(!root->left) root->left = new node();
			root = root->left;
		}
	}
}

int maxXOR(node *root,int value)
{
	int ans = 0;
	for(int i=31;i>=0;i--){
		int bit = (value>>i)&1;
		if(bit){
			if(root->left){
				root = root->left;
				ans |= (1<<i);
			}
			else root = root->right;
		}
		else{
			if(root->right){
				root = root->right;
				ans |= (1<<i);
			}
			else root = root->left;
		}
	}
	return ans;
}

int findMaximumXOR(vector<int> &nums)
{
	int best = 0;
	node* root = new node();
	for(int &value: nums){
		insert(root, value);
		best = max(best, maxXOR(root, value));
	}
	return best;
}

bool helper(int mask,map<int,vector<int> > &allowedTrans,int totalLen,int len,map<int,char> &op,int newmask = 0)
{
	if(mask <= 7) return true;
	if(len < 0) return helper(newmask, allowedTrans, totalLen - 1, totalLen - 2, op);
	int v1 = ((mask>>(3*len))&7), v2 = (mask>>(3*(len+1)))&7;
	cout << op[v1] << " " << op[v2] << "\n"; 
	v1 = (v2 << 3) | (v1&7);
	for(int &a: allowedTrans[v1]){
		if(helper(mask, allowedTrans, totalLen, len - 1, op, (newmask << 3) | a)){
			return true;
		} 
	}

	return false;
}

bool pyramidTransition(string bottom, vector<string>& all){
	map<char,int> indexing;
	map<int, char> op;
	for(int i=0;i<7;i++){
		indexing[char(i + 'A')] = i + 1;
		op[i+1] = char(i + 'A');
	}

	map<int,vector<int> > allowedTrans;
	for(string &s: all){
		int v1 = indexing[s[0]], v2 = indexing[s[1]], v3 = indexing[s[2]];
		v1 = (v1 << 3) | v2;
		allowedTrans[v1].push_back(v3);
	}

	int mask = 0;
	for(int i=0;i<bottom.size();i++){
		int value = indexing[bottom[i]];
		mask = (mask << 3) | (value&7);
	}

	return helper(mask, allowedTrans, bottom.size() - 1, bottom.size() - 2, op);

}

int main(){
	string bottom;
	cin >> bottom;
	int n;
	cin >> n;
	vector<string> all(n);
	for(string &s: all) cin >> s;
	cout << pyramidTransition(bottom, all) << "\n";
	return 0;
}





