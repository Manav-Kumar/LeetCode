#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <list>
using namespace std;

#define vb vector<bool>
#define vi vector<int>
#define vvb vector<vb>
#define vvi vector<vi>



long long getValue(vector<int> &A,int st,int en)
{
	long long sum = 0;
	for(int i=en;i>=st;i--){
		sum += A[i]*pow(2, en - i);
	}
	return sum;
}

void BinarySearch(vector<int>& A,int i,int j,bool &ok,vector<int> &ans,vvb &visited)
{
	if((i + 1 > j - 1) || (i < 0) || (j >= A.size())) return;

	long long v1 = getValue(A, 0, i), v2 = getValue(A, i+1, j-1), v3 = getValue(A, j, A.size() - 1);

	if(visited[i][j]) return;
	visited[i][j] = true;
	if(v1 == v2 && v1 == v3){
		ok = true;
		ans[0] = i, ans[1] = j;
		return;
	}

	if(v1 >= v2 && v1 >= v3){
		BinarySearch(A, --i, j, ok, ans, visited);
	}
	else if(v2 >= v1 && v2 >= v3){

		if(v1 > v3) BinarySearch(A, i, j - 1, ok, ans, visited);
		else BinarySearch(A, i + 1, j, ok, ans, visited);
	}
	else if(v3 >= v1 && v3 >= v2){
		BinarySearch(A, i, ++j, ok, ans, visited);
	}
	//visited[i][j] = true;
}






vector<int> threeEqualParts(vector<int> &A){
	// int n = A.size();
	// vvb visited(n, vb(n, false));
	// int i = 0, j = 2;
	// bool ok = false;
	// vector<int> ans = {-1, -1};
	// BinarySearch(A, i, j, ok, ans, visited);
	// return ans;


	int countOnes = 0;
	for(int i = 0;i < n;i++) if(A[i] == 1) countOnes++;

	if(countOnes%3 != 0) return vector<int>{-1, -1};
	int eachPart = countOnes/3, idx = 0, j = -1, i = -1, k = -1;
	if(eachPart == 0){
		return vector<int> {0, n-1};
	}
	vector<int> pos;
	vector<int> ans(2);
	for(int i = n-1;i >= 0;i--){

		if(A[i] == 1){
			idx++;
		}

		pos.push_back(A[i]);

		if(idx == eachPart){
			break;
		}
	}


	reverse(pos.begin(), pos.end());

	i = 0, k = 0;
	while(i < n && A[i] == 0) i++;

	while(k < pos.size()){

		if(i >= n || A[i] != pos[k]) return vector<int> {-1, -1};
		i++, k++;
	}

	ans[0] = i-1, k = 0;
	while(i < n && A[i] == 0) i++;

	while(k < pos.size()){

		if(i >= n || A[i] != pos[k]) return vector<int> {-1, -1};
		i++, k++;
	}

	ans[1] = i, k = 0;
	while(i < n && A[i] == 0) i++;

	while(k < pos.size()){

		if(i >= n || A[i] != pos[k]) return vector<int> {-1, -1};
		i++, k++;
	}
	

	if(i!=n) return vector<int> {-1, -1};
	return ans;
}


int main(){
	int n;
	cin >> n;
	vector<int> A(n);
	for(int &a: A) cin >> a;
	vector<int> ans = threeEqualParts(A);
	cout << ans[0] << " " << ans[1] << "\n";

	return 0;
}




