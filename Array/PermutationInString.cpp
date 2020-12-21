#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>

bool checkEqual(vi &curr, vi &count){
	for(int i=0;i<26;i++) if(curr[i] != count[i]) return false;
	return true;
}

bool checkInclusion(string s1, string s2){
	if(s2.size() < s1.size()) return false;
	vector<int> count(26, 0);
	for(char c: s1) count[c - 'a'] += 1;

	vector<int> curr(26, 0);
	int i = 0, j = 0, checkbits = 0, validBits = 0;

	for(int z=0;z<26;z++){
		if(count[z] > 0) validBits |= (1<<z);
	}

	for(;i<min(s1.size(), s2.size());i++){
		int curridx = s2[i] - 'a';
		curr[curridx] += 1;

		if(curr[curridx] == count[curridx]) checkbits |= (1<<curridx);
		else checkbits &= ~(1<<curridx);
	}

	while(i < s2.size()){
		// if(checkEqual(curr, count)) return true;
		if(validBits == checkbits) return true;
		int curridx = s2[i] - 'a', previdx = s2[j] - 'a';
		curr[curridx] += 1;
		if(curr[curridx] == count[curridx]) checkbits |= (1<<curridx);
		else checkbits &= ~(1<<curridx);

		curr[previdx] -= 1;
		if(curr[previdx] == count[previdx]) checkbits |= (1<<previdx);
		else  checkbits &= ~(1<<previdx);

		i++, j++;

	}
	// if(checkEqual(curr, count)) return true;
	if(validBits == checkbits) return true;
	return false;
}


bool checkInclusion2(string s1, string s2){
	if(s2.size() < s1.size()) return false;
	vector<int> count(26, 0);
	for(char c: s1) count[c - 'a'] += 1;
	vector<int> curr(26, 0);
	int checkbits = (1<<26) - 1, validBits = (1<<26) - 1;

	
	int i = 0, j = 0;
	for(;i < min(s1.size(), s2.size());i++){
		int curridx = s2[i] - 'a'; 

		curr[curridx] += 1;
		if(curr[curridx] == count[curridx]) checkbits |= (1<<curridx);
		else checkbits &= ~(1<<curridx);
	}

	while(i < s2.size()){

		if(checkbits == validBits) return true;

		int curridx = s2[i++] - 'a', previdx = s2[j++] - 'a';

		curr[curridx] += 1;
		if(curr[curridx] == count[curridx]) checkbits |= (1<<curridx);
		else checkbits &= ~(1<<curridx);

		curr[previdx] -= 1;
		if(curr[previdx] == count[previdx]) checkbits |= (1<<previdx);
		else checkbits &= ~(1<<previdx);
	}
	if(checkbits == validBits) return true;

	return false;

}

int main(){
	string s1, s2;
	cin >> s1 >> s2;
	cout << checkInclusion2(s1, s2) << "\n";
	return 0;
}

