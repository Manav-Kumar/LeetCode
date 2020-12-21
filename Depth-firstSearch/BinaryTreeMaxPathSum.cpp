#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>

class TreeNode{
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int v): val(v), left(NULL), right(NULL) {}
};


class Solution1{
public:
	pair<int,int> maxPathSum2(TreeNode* root){
		if(!root) return pair<int,int> (INT_MIN, 0);
		pair<int,int> ans;
		pair<int,int> a1 = maxPathSum2(root->left);
		pair<int,int> a2 = maxPathSum2(root->right);
		ans.second = root->val + (max(a1.second, a2.second) > 0?max(a1.second, a2.second):0);
		ans.first = max({ max(a1.first, a2.first), ans.second, a1.second + root->val + a2.second });
		return ans;
	}


	int maxPathSum(TreeNode* root){
		return maxPathSum2(root).first;
	}
};

class Solution2{
	TreeNode* first;
	TreeNode* second;
	TreeNode* prev;
public:
	void inorder(TreeNode* root){
		if(!root) return;
		inorder(root->left);
		if(!first && prev->val > root->val) first = prev;
		if(first && prev->val > root->val) second = root;
		prev = root;
		inorder(root->right);
	}
	void recoverTree(TreeNode* root){
		prev = new TreeNode(INT_MIN);
		inorder(root);
	}
};


//	Remove Boxes
class Solution3{
	//int dp[101][101][101];
public:
	//	Implement using Segment Tree
	int solve(vector<int>& boxes, int l,int r,int k){
		if(l > r) return 0;
		for(;l+1 <= r && boxes[l] == boxes[l + 1];++l,++k) {}
		int ans = k*k + solve(boxes, l + 1, r, 1);
		for(int x = l + 1;x <= r;x++){
			if(boxes[x] == boxes[l]){
				ans = max(ans, solve(boxes, l + 1, x - 1, 1) + solve(boxes, x, r, k + 1));
			}
		}
		return ans;
	}
	int removeBoxes(vector<int> &boxes){
		int n = boxes.size();
		//cout << sizeof(dp) << "\n";
		//memset(dp, -1, sizeof(dp));
		return solve(boxes, 0, n - 1,1);
	}
};

//	Strange Printer
class Solution4{
public:
	int dp[100][100];
	int solve(string s,int l,int r){
		if(l > r) return 0;
		int &ans = dp[l][r];
		if(ans != -1) return ans;
		for(;l + 1 <= r && s[l] == s[l + 1];++l) {}
		ans = 1 + solve(s, l + 1, r);
		for(int x = l + 1;x <= r;x++){
			if(s[x] == s[l]){
				ans = min(ans, solve(s, l + 1, x - 1) + solve(s, x, r));
			}
		}
		return ans;
	}

	int strangePrinter(string s){
		string t = "";
		int i = 0;
		while(i < s.size()){
			char c = s[i];
			t += c;
			while(i < s.size() && c == s[i]) {++i;}
		}
		int n = t.size();
		memset(dp, -1, sizeof(dp));
		return solve(t, 0, n - 1);
	}

};



// class Solution{
// public:
// 	vector<vector<int> > adj;
// 	vector<int> colors;

// 	bool isCycle(int v){
// 		colors[v] = 1;
// 		for(int &next: adj[v]){
// 			if(colors[next] == 1 || isCycle(next)) return true;
// 		}
// 		colors[v] = 2;
// 		return false;
// 	}

// 	bool isPrintable(vvi &targetGrid){
// 		vector<int> top(61, 100), bottom(61, -1), left(61, 100), right(61, -1);
// 		int m = targetGrid.size(), n = targetGrid[0].size();
// 		adj = vector<vector<int> > (61, vector<int> ());
// 		colors = vector<int> (61, 0);
// 		for(int i=0;i<m;i++){
// 			for(int j=0;j<n;j++){
// 				int v = targetGrid[i][j];
// 				top[v] = min(top[v], i), left[v] = min(left[v], j);
// 				bottom[v] = max(bottom[v], i), right[v] = max(right[v], j);
// 			}
// 		}
// 		for(int i=1;i<=60;i++){
// 			if(top[i] == 100) continue;
// 			for(int x = top[i];x <= bottom[i];x++){
// 				for(int y = left[i];y <= right[i];y++){
// 					if(i != targetGrid[x][y]) adj[i].push_back(targetGrid[x][y]);
// 				}
// 			}
// 		}

// 		for(int i=1;i <= 60;i++){
// 			if(top[i] == 100) continue;
// 			if(colors[i] == 0 && isCycle(i)) return false;
// 		}
// 		return true;
// 	}
// };



class Solution{	
public:
	vector<vector<int> > adj;
	vector<int> colors;

	bool isCycle(int v){
		colors[v] = 1;
		for(int &next: adj[v]){
			if(colors[next] == 1) return true;
			else if(colors[next] == 0 && isCycle(next)) return true;
		}
		colors[v] = 2;
		return false;
	}

	bool isPrintable(vvi &targetGrid){
		vector<int> top(61, 100), left(61, 100), bottom(61, -1), right(61, -1);
		int m = targetGrid.size(), n = targetGrid[0].size();
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				int v = targetGrid[i][j];
				top[v] = min(top[v], i), left[v] = min(left[v], j);
				bottom[v] = max(bottom[v], i), right[v] = max(right[v], j);
			}
		}
		adj = vector<vector<int> > (61, vector<int> ());
		colors = vector<int> (61, 0);

		for(int i=1;i<=60;i++){
			if(top[i] == 100) continue;
			for(int x = top[i];x <= bottom[i];x++){
				for(int y = left[i];y <= right[i];y++){
					if(i != targetGrid[x][y]) adj[i].push_back(targetGrid[x][y]);
				}
			}
		}

		for(int i=1;i<=60;i++){
			if(top[i] == 100) continue;
			if(colors[i] == 0 && isCycle(i)) return false;
		}
		return true;
	}
};


int main(){
	int n, m;
	cin >> m >> n;
	vector<vector<int> > targetGrid(m, vector<int> (n));
	for(vector<int> &a: targetGrid) for(int &b: a) cin >> b; 
	cout << Solution().isPrintable(targetGrid) << "\n";
	return 0;
}




