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
#include <cmath>
using namespace std;

#define ll long long
#define vl vector<ll>
#define vll vector<vl>
#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>
#define vvb vector<vb>


bool isNumber(string s) {
   int i = 0, dot = 0, exp = 0;
   while(s[i] == ' ' && i < s.size()) i++;
   while(s.size() > 0 && s[s.size()-1] == ' ') s = s.substr(0, s.size() - 1);
   if(s.size() == 0) return 0;

   if(s[i] == '+' || s[i] == '-') i++;
    
    while(i < s.size()){
        if((s[i] >= '0' && s[i] <= '9') || (s[i] == 'e' && exp == 0) || (s[i] == '.' && dot == 0)) i = i;
        else return 0;

        if(s[i] == '.'){
        	if(i-1 >= 0 && s[i-1] >= '0' && s[i-1] <= '9') i = i;
        	else if(i+1 < s.size() && s[i+1] >= '0' && s[i+1] <= '9') i = i;
        	else return 0;
            dot = 1, i++;
        }
        else if(s[i] == 'e'){
        	if(i-1 >= 0 && ((s[i-1] >= '0' && s[i-1] <= '9') || s[i-1] == '.')) i = i;
        	else return 0;
            i++;
            if(i == s.size()) return 0;
            if(s[i] == '+' || s[i] == '-') i++;
            if(i == s.size()) return 0;
            if(s[i] >= '0' && s[i] <= '9') i++;
            else return 0;
            dot = 1, exp = 1;
        }
        else{
        	i++;
        }
    }
    return 1;
}

//	Find the Closest Palindrome
//	stol() -> Converts String into integer
//	to_string() -> Converts integer to String
string nearestPalindromic(string s){
	int midIdx = s.size()%2? s.size()/2:(s.size()-1)/2;
	long prefix = stol(s.substr(0, midIdx + 1));

	vector<long> candidates {prefix - 1, prefix, prefix + 1};
	for(long &prefix: candidates){
		string n = to_string(prefix), temp = n;
		reverse(temp.begin(), temp.end());
		string ans;
		if(s.size()%2 == 0){
			ans = n + temp;
		}
		else{
			ans = n + temp.substr(1);
		}
		prefix = stol(ans);
	}

	candidates.push_back(pow(10,s.size()-1) - 1);
	candidates.push_back(pow(10, s.size()) + 1);

	long ans = INT_MAX, diff = INT_MAX;
	for(int i=0;i<candidates.size();i++){
		cout << candidates[i] << " " << stol(s) << "\n";
		if(candidates[i] == stol(s)) continue;

		if(abs(candidates[i] - stol(s)) < diff){
			ans = candidates[i], diff = abs(candidates[i] - stol(s));
		}
		else if(abs(candidates[i] - stol(s)) == diff && candidates[i] < ans){
			ans = candidates[i];
		}
	}

	return to_string(ans);
}

//	Substring with Concatenation of All words

class trieNode{
public:
	int isTerminal, count;
	vector<trieNode*> children;
	trieNode(): children(26, NULL), isTerminal(0), count(0) {}
};

void insert(trieNode *root,string &s)
{
	for(int i=0;i<s.size();i++){
		int idx = s[i] - 'a';
		if(!root->children[idx]) root->children[idx] = new trieNode();
		root = root->children[idx];
	}
	root->isTerminal += 1;
	root->count += 1;
}

int Search(trieNode *root,string s)
{

	for(int i=0;i<s.size();i++){
		int idx = s[i] - 'a';
		if(root->children[idx] == NULL) return -1;
		root = root->children[idx];
	}
	return root->count;
}

bool findSubstringHelper(trieNode *root,string& s,int Start,int total,int wordLen)
{
	// bool ans = true;
	// int stop = total - 1;
	// string curr = "";
	// map<string, int> mp;
	// for(int i=0;i<total;i++){
	// 	string curr = s.substr(Start + i*wordLen, wordLen);
	// 	int value = Search(root, curr, false);
	// 	if(value < 0){
	// 		ans = false;
	// 		stop = i;
	// 		break;
	// 	}
	// }

	// for(int i=0;i<=stop;i++){
	// 	string curr = "";
	// 	for(int j=0;j<wordLen;j++){
	// 		curr += s[Start + i*wordLen + j];
	// 	}
	// 	int value = Search(root, curr, true);
	// }



	// return ans;


	string curr = "";
	map<string, int> mp;
	for(int i=0;i<total;i++){
		string curr = s.substr(Start + i*wordLen, wordLen);
		if(mp.find(curr) != mp.end()){
			mp[curr]--;
			if(mp[curr] < 0) return false;
		}
		else{
			int value = Search(root, curr);//	Here make sure in search function just return roo->count
			if(value <= 0) return false;
			mp[curr] = --value;
		}
	}
	return true;
}




vector<int> findSubstring(string& s,vector<string> &words)
{
	trieNode *root = new trieNode();
	int len = words[0].size()*words.size(), total = words.size(), wordLen = words[0].size();
	for(string &s: words){
		insert(root, s);
	}

	vector<int> ans;
	for(int i = 0;i <= int(s.size() - len);i++){
		if(findSubstringHelper(root, s, i, total, wordLen)) ans.push_back(i);
	}
	
	// for(int i=0;i<=int(s.size() - len);i++){
	// 	if(findSubstringHelper2(s, i, total, wordLen, mp)) ans.push_back(i);
	// }

	return ans;
}


bool findSubstringHelper2(string s, int Start, int total, int wordLen, map<string,int> mp)
{
	int count = 0;
	for(int i=0;i<total;i++){
		string curr = s.substr(Start + i*wordLen, wordLen);
		if(mp.find(curr) == mp.end() || mp[curr] <= 0) return false;
		mp[curr]--;
		if(mp[curr] == 0) count++;
	}

	return count == mp.size();

}

void update(string curr,int number,map<string,int> &mp)
{
	mp[curr] += number;
	if(mp[curr] == 0) mp.erase(curr);
}

vector<int> findSubstring2(string s,vector<string> &words)
{
	int wordCount = words.size(), wordLen = words[0].size(), N = s.size();
	vector<int> ans;
	for(int start = 0;start < wordLen;start++){
		int curr = start;
		if(curr + wordCount*wordLen > N) continue;

		map<string,int> mp;
		for(string &s: words) mp[s] += 1;

		for(int i=0;i<wordCount;i++){
			update(s.substr(curr, wordLen), -1, mp);
			curr += wordLen;
		}

		if(mp.size() == 0){
			ans.push_back(curr - wordCount*wordLen);
		}

		while((curr + wordLen) <= N){
			update(s.substr(curr, wordLen), -1, mp);
			update(s.substr(curr - wordCount*wordLen, wordLen), 1, mp);
			curr += wordLen;
			if(mp.size() == 0){
				ans.push_back(curr - wordLen*wordCount);
			}
		}

	}
	return ans;
}


int main(){
	string s;
	cin >> s;
	int n;
	cin >> n;
	vector<string> words(n);
	for(string &s: words) cin >> s;
	vector<int> ans = findSubstring2(s, words);
	for(int &a: ans) cout << a << "\n";
	return 0;
}







