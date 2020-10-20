#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>
#define ll long long

class node{
public:
	int value, idx, arnumber;
	node(int a = 0,int b = -1, int c = -1): value(a), idx(b), arnumber(c) {}
};

class comparator{
public:
	bool operator() (node &a, node &b){
		if(a.value == b.value) return a.idx > b.idx;
		return a.value < b.value;
	}
};

vector<int> maxNumber(vector<int>& nums1, vector<int> &nums2,int k,int i,int j){
	vector<int> ans(k);
	int n = nums1.size(), m = nums2.size();
	// while(ct < k - 1){
	// 	if(i >= 0 && nums1[i] <= nums2[j]) i--;
	// 	else if(j >= 0) j--;
	// 	else{
	// 		if(i < 0) j--;
	// 		else if(j < 0) i--;
	// 	}

	// 	ct++;
	// }
	cout << i << " " << j << "\n";
	priority_queue<node, vector<node>, comparator> pq; 
	for(int x = 0;x < i;x++) pq.push(node(nums1[x], x, 1));
	for(int x = 0;x < j;x++) pq.push(node(nums2[x], x, 2));

	
	int counter = 0, curi = -1, curj = -1, remainCount = k;
	while(counter < k){

		if(remainCount == (n - (curi + 1) + m - (curj + 1))){
			curi++, curj++;
			while(curi < n && curj < m && counter < k){
				if(nums1[curi] >= nums2[curj]) ans[counter++] = nums1[curi++];
				else ans[counter++] = nums2[curj++];
			}
			while(curi < n && counter < k) ans[counter++] = nums1[curi++];
			while(curj < m && counter < k) ans[counter++] = nums2[curj++];
			break;
		}

		node a = pq.top();
		cout << a.value << " " << a.idx << " " << a.arnumber << "\n";
		pq.pop();
		if(a.arnumber == 1 && a.idx > curi){
			curi = a.idx;
			ans[counter++] = a.value;
			remainCount--;
		}
		if(a.arnumber == 2 && a.idx > curj){
			curj = a.idx;
			ans[counter++] = a.value;
			remainCount--;
		}
		a.idx++;
		if((i< n) && (j< m)){
			if(nums1[i+1] >= nums2[j]){
				pq.push(node(nums1[i], i, 1));
				i++;
			}
			else{
				pq.push(node(nums2[j],j, 2));
				j++;
			}
		}
		else if(i < n){
			pq.push(node(nums1[i], i, 1));
			i++;
		}
		else if(j < m){
			pq.push(node(nums2[j], j, 2));
			j++;
		}
		else{
			return vector<int> ();
		}


	}
	cout << "ok";
	return ans;
}

bool compare2vecs(vector<int> &a,vector<int> &b)
{
	int k = a.size();
	for(int i=0;i<k;i++){
		if(a[i] > b[i]) return true;
		else if(a[i] < b[i]) return false;
	}
	return false;
}

vector<int> maxNumber(vector<int> &nums1, vector<int> &nums2,int k)
{
	//	Need to remove K elements
	vector<int> ans(k);
	int n = nums1.size(), m = nums2.size(), i = n, j = m - (k - 1);
	while(j < 0) i--, j++;
	while(i >= 0 && n - i <= k-1){
		vector<int> temp = maxNumber(nums1, nums2, k, i, j);
		cout << "ok";
		if(temp.size() > 0 && compare2vecs(temp, ans)) ans = temp;
		i--, j++;
	}
	return ans;
}


int main(){
	int n, m, k;
	cin >> n;
	vector<int> nums1(n);
	for(int &a: nums1) cin >> a;
	cin >> m;
	vector<int> nums2(m);
	for(int &a: nums2) cin >> a;
	cin >> k;
	vector<int> ans = maxNumber(nums1, nums2, k);
	for(int &a: ans) cout << a << " ";
	return 0;
}


