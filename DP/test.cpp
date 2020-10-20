#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <map>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define ll long long

//	Padding Concept
class temp{
public:
	long b;
	char c;
	int a;
};

ll mod = 1e9 + 7;

int solve2(string a,string c, bool check)
{
	if(c.empty()) return check == true;
	if(a.empty()) return 0;
	int a1 = 0, a2 = 0;
	if(a[0] == c[0]){
		a1 = solve2(a.substr(1), c.substr(1), true);
	}
	a2 = solve2(a.substr(1), c, check);
	return a1 + a2;
}

int solve(string a,string b,string c, bool checkA, bool checkB){
	if(c.empty()){
		cout << a << " " << b << "\n";
		return checkA && checkB;
	}
	if(a.empty() || b.empty()){
		return 0;
		int a1 = 0, a2 = 0;
		a1 = solve2(a, c, checkA);
		a2 = solve2(b, c, checkB);
		return a1 + a2;
	}
	int a1 = 0, a2 = 0, a3 = 0, a4 = 0;
	if(a[0] == c[0]) a1 = solve(a.substr(1), b, c.substr(1), true, checkB);
	else a3 = solve(a.substr(1), b, c, checkA, checkB);
	if(b[0] == c[0]) a2 = solve(a, b.substr(1), c.substr(1), checkA, true);
	else a4 = solve(a, b.substr(1), c, checkA, checkB);

	return a1 + a2 + a3 + a4;
}

void solve(string a,string b,string ans, vvvb &visited){
	int n = a.size(), m = b.size(), z = ans.size();
	if(visited[n][m][z]){

		return ;
	}
	//visited[n][m][z] = true;
	if(a.empty() && b.empty()){
		cout << ans << "\n";
		return;
	}
	if(!a.empty()) solve(a.substr(1), b, ans + a[0], visited);
	if(!b.empty()) solve(a, b.substr(1), ans + b[0], visited);
	if(!a.empty()) solve(a.substr(1), b, ans, visited);
	if(!b.empty()) solve(a, b.substr(1), ans, visited);
	
}


int countPairs(int numCount,vector<int> ratingValues,int target)
{
	sort(ratingValues.begin(), ratingValues.end());
	map<int,bool> visited;
	int ans = 0, a, b;
	for(int i = 0;i < numCount;i++){
		if(visited.count(ratingValues[i]) > 0) continue;
		a = ratingValues[i], b = target - a;
		if(a <= b){
			int st = i + 1, en = numCount - 1;
			bool check = false;
			while(st <= en){
				int mid = (st + en)/2;
				if(ratingValues[mid] == b){
					visited[b] = true;
					check = true;
					break;
				}
				else if(b < ratingValues[mid]){
					en = mid - 1;
				}
				else{
					st = mid + 1;
				}
			}
			if(check) ans++;
		}
		visited[a] = true;
	}
	return ans;
}

class ALNode{
public:
	int value;
	ALNode *next;
	ALNode *arbitrary;

	ALNode(int val): value(val), next(NULL), arbitrary(NULL){}
	ALNode(): value(-1), next(NULL), arbitrary(NULL) {}
};


ALNode *deepCopy(ALNode* head)
{
	map<ALNode*, ALNode*> mp;
	ALNode *temp = head;
	ALNode *root = NULL;
	ALNode *tail = NULL;
	while(temp){
		if(!root){
			root = new ALNode(temp->value);
			tail = root;
		}
		else{
			tail->next = new ALNode(temp->value);
			tail = tail->next;
		}
		mp[temp] = tail;
		temp = temp->next;
	}

	ALNode *temp2 = root;
	temp = head;
	while(temp2){
		if(mp.find(temp->arbitrary) != mp.end()) temp2->arbitrary = mp[temp->arbitrary];
		temp2 = temp2->next;
		temp = temp->next;
	}

	return root;
}


int main(){
	
	
	return 0;
}

