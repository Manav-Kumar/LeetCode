#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>

class Solution{
public:
	unordered_map<string, vector<string> > g;
	unordered_map<string, int> out; 
	vector<string> allCombinations;
	void makeCombinations(int n,int k,string num = ""){
		if(n == 0){
			allCombinations.push_back(num); return;
		}
		for(int j = 0;j < k;j++){
			makeCombinations(n - 1, k, num + char(j + '0'));
		}
	}

	vector<string> generateStrings(int n,int k){
		vector<string> res;
		if(n == 0){
			for(int i=0;i<k;i++){
				string s = ""; s += char(i + '0');
				res.push_back(s);
			}
			return res;
		}
		vector<string> minus1 = generateStrings(n - 1, k);

		for(int i = 0;i < k;i++){
			for(string &str: minus1){
				res.push_back(str + char(i + '0'));
			}
		}
		return res;
	}

	void buildGraph(int n,int k){
		// allCombinations.clear();
		// makeCombinations(n, k);
		vector<string> allCombinations = generateStrings(n, k);
		for(string &start: allCombinations){
			cout << start << "\n";
			for(int i=0;i<k;i++){
				string to = start + char(i + '0');
				to = to.substr(1);
				g[start].push_back(to), out[start] += 1;
			}
		}
	}

	//	Traversing all edges exactly once
	string res = "";
	string dfs(string at){
		if(out[at] == 0) return res;

		while(out[at]){
			out[at] -= 1;
			res += g[at][out[at]].back(); 
			dfs(g[at][out[at]]);
		}
		return res;
	}

	string crackSafe(int n,int k){
		if(n == 1){
			string res = "";
			for(int i=0;i<k;i++) res += char(i + '0');
			return res;
		}
		//	Here we need to return a min len string such that it contains every possible combination
		makeCombinations(n, k);
		string ans = "";

		//	Make Graph such that each node is going to have k-1 edges out indicating on chaning 
		//		only last digit we are going to land on other combination of sequence therefore 
		//		by keeping last n-1 digits of sequence to be same as previous one, and hence traversing
		//		the euler path(i.e visiting each edge exactly one time).
		buildGraph(n - 2, k);
		string start(n - 1, '0');
		dfs(start);
		return start + res;
	}
};

int main(){
	int n, k;
	cin >> n >> k;
	cout << Solution().crackSafe(n, k) << "\n";
	return 0;
}




