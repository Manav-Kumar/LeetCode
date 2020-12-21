#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>

using namespace std;



// class Solution{

// 	int largestRectangleInStack(vector<int> &heights){
// 		int n = heights.size(), ans = 0;
// 		vector<int> left(n, -1), right(n, -1);

// 		stack<pair<int,int> > s;
// 		for(int i=0;i<n;i++){
// 			pair<int,int> curr(i, heights[i]);
// 			while(s.size()){
// 				if(s.top().second >= curr.second) s.pop();
// 				else{
// 					left[i] = s.top().first + 1;
// 					break;
// 				}
// 			}
// 			if(left[i] == -1) left[i] = 0;
// 			s.push(curr);
// 		}

// 		stack<pair<int,int> > k;
// 		for(int i=n-1;i>=0;i--){
// 			pair<int,int> curr(i, heights[i]);
// 			while(k.size()){
// 				if(k.top().second >= curr.second) k.pop();
// 				else{
// 					right[i] = k.top().first - 1;
// 					break;
// 				}
// 			}
// 			if(right[i] == -1) right[i] = n - 1;
// 			k.push(curr);
// 		}

// 		for(int i=0;i<n;i++) ans = max(ans, heights[i]*(right[i] - left[i] + 1));
// 		return ans;
// 	}

// public:
// 	//	Find the largest Rectangle Containing Only 1s

// 	int maximumRectangle(vector<vector<char> > &matrix){
// 		if(matrix.empty()) return 0;
// 		int m = matrix.size(), n = matrix[0].size(), ans = 0;
// 		vector<int> prev(n, 0), curr(n, 0);
// 		for(int i=0;i<m;i++){

// 			for(int j = 0;j<n;j++){
// 				if(matrix[i][j] == '0') curr[j] = 0;
// 				else curr[j] = prev[j] + 1;
// 			}
// 			ans = max(ans, largestRectangleInStack(curr));
// 			prev = curr;
// 		}

// 		return ans;
// 	}
// };


// int largestRectangleInStack(vector<int> &heights){
// 	int n = heights.size(), ans = 0;
// 	vector<int> left(n, -1), right(n, n - 1);
	
// 	stack<pair<int,int> > s;
// 	for(int i=0;i<n;i++){
// 		pair<int,int> curr(i, heights[i]);
// 		while(s.size()){
// 			if(s.top().second >= curr.second) s.pop();
// 			else{
// 				left[i] = s.top().first + 1;
// 				break;
// 			}
// 		}
// 		if(left[i] == -1) left[i] = 0;
// 		s.push(curr);
// 	}

// 	//	Clearing the stack
// 	while(s.size()) s.pop();

// 	for(int i = n-1;i >= 0;i--){
// 		pair<int,int> curr(i, heights[i]);
// 		while(s.size()){
// 			if(s.top().second >= curr.second) s.pop();
// 			else{
// 				right[i] = s.top().first - 1;
// 				break;
// 			}
// 		}
// 		if(right[i] == -1) right[i] = n - 1;
// 		s.push(curr);
// 	}


// 	for(int i=0;i<n;i++){
// 		ans = max(ans, heights[i]*(right[i] - left[i] + 1));
// 	}
// 	return ans;
// }

// class Solution{
// public:
// 	int maximalSquare(vector<vector<char> > &matrix){
// 		if(matrix.empty()) return 0;
// 		int m = matrix.size(), n = matrix[0].size(), ans = 0;
// 		vector<int> prev(n, 0), curr(n, 0);
// 		for(int i=0;i<m;i++){
// 			curr.clear(); curr.resize(n, 0);
// 			for(int j=0;j<n;j++){
// 				if(matrix[i][j] == '0') continue;
// 				if(j == 0 || i == 0) curr[j] = 1;
// 				else curr[j] = min({prev[j], prev[j - 1], curr[j - 1]}) + 1;
// 				ans = max(ans, curr[j]);
// 			}
// 			prev = curr;
// 		}
// 		return ans*ans;
// 	}
// }

int main(){
	string num;
	cin >> num;
	int k;
	cin >> k;
	cout << Solution().minInteger(num, k) << "\n";
	return 0;
}





