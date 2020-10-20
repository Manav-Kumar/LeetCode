#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <list>
#include <queue>
using namespace std;

#define vb vector<bool>
#define vi vector<int>
#define vvb vector<vb>
#define vvi vector<vi>
#define rep(i,a,b) for(int i=a;i<b;i++)


int calculateMinimumHP(vvi &dungeon)
{
	int n = dungeon.size(), m = dungeon[0].size();
	vvi dp(n, vi(m,0));
	int initalHealth = 1;
	for(int i = m-1;i >= 0;i--){
		dp[n-1][i] = max(initalHealth - dungeon[n-1][i], 1);//At evert step minHealth Would should
		initalHealth = dp[n-1][i];
	}
	initalHealth = 1;
	for(int i = n-1;i >= 0;i--){
		dp[i][m-1] = max(initalHealth - dungeon[i][m-1], 1);//At evert step minHealth Would should
		initalHealth = dp[i][m-1];
	}

	for(int i=n-2;i>=0;i--){
		for(int j=m-2;j>=0;j--){
			dp[i][j] = min(dp[i+1][j] - dungeon[i][j], dp[i][j+1] - dungeon[i][j]);
			dp[i][j] = max(dp[i][j], 1);
		}
	}
	rep(i,0,n){
		rep(j,0,m) cout << dp[i][j] << " ";
		cout << "\n";
	}
	return dp[0][0];
}


//	Ugly Number
int nthUglyNumber(int n){
	int N = 10000;
	bool *visited = new bool[N + 1]();
	visited[1] = true;
	for(int p = 2;p < (N + 1);p++){
		if(!visited[p]){
			for(int i=p;i<=N;i += p){
				if(p == 2 || p == 3 || p == 5) visited[i] = true;
				else visited[i] = false;
			}
		}
	}
	int count = 0;
	for(int i=1;i<=N;i++){
		if(visited[i]) ++count;
		if(count == n){
			delete []visited;
			return i;
		}
	}
	delete []visited;
	return -1;
}

bool isUgly(int n){

	while(n%2 == 0){
		n /= 2;
	}
	while(n%3 == 0){
		n /= 3;
	}
	while(n%5 == 0){
		n /= 5;
	}

	return n == 1;
}

int nthUglyNumber2(int n)
{
	int N = 1000000, count = 0;
	for(int i=1;i<N;i++){
		if(isUgly(i)) count++;
		if(count == n) return i;
	}
	return -1;
}


int nthUglyNumber3(int n){
	vector<int> arr;
	arr.push_back(1);
	int i = 0, j = 0, k = 0;
	while(arr.size() < n){
		int a1 = 2*arr[i], a2 = 3*arr[j], a3 = 5*arr[k];
		if(a1 <= min(a2,a3)){
			if(arr.back() < a1){
				arr.push_back(a1);
			}
			i++;
		}
		else if(a2 <= min(a1, a3)){
			if(arr.back() < a2){
				arr.push_back(a2);
			}
			j++;
		}
		else if(a3 <= min(a1, a2)){
			if(arr.back() < a3){
				arr.push_back(a3);
			}
			k++;
		}
	}

	return arr.back();
}

int nthUglyNumberGen(int n,int a,int b,int c)
{
	vi arr1(1,0), arr2(1,0), arr3(1,0);

	int count = 0;
	while(count < n){
		int a1 = a + arr1.back(), a2 = b + arr2.back(), a3 = c + arr3.back();
		if(a1 <= min(a2,a3)){
			if(a1 > max(arr2.back(), arr3.back())){
				count++;
			}
			arr1.push_back(a1);
		}
		else if(a2 <= min(a1, a3)){
			if(a2 > max(arr1.back(), arr3.back())){
				count++;
			}
			arr2.push_back(a2);
		}
		else if(a3 <= min(a1, a2)){
			if(a3 > max(arr1.back(), arr2.back())){
				count++;
			}
			arr3.push_back(a3);
		}
	}

	return max(arr1.back(), max(arr2.back(), arr3.back()) );
}

int gcd(int a,int b){
	if(b > a) return gcd(b, a);
	if(b == 0) return a;
	return gcd(b, a%b);
}

int lcm(int a,int b){
	return (a*b)/gcd(a,b);
}

int getNumberEle(int value,int a,int b,int c){
	return value/a + value/b + value/c - value/lcm(a,b) - value/lcm(b,c) - value/lcm(a,c) + 
				value/(lcm(a, lcm(b,c)));
}

int nthUglyNumberGen2(int n,int a,int b,int c)
{
	int lo = 1, hi = 12334, ans = -1;
	while(lo < hi){
		int mid = (lo + hi)/2;
		int count = getNumberEle(mid, a, b, c);
		if(count == n && getNumberEle(mid - 1, a, b, c) != count) return mid;
		if(n <= count) hi = mid;
		else lo = mid;
	}
	return lo;
}

int main(){
	int n, a, b, c;
	cin >> n >> a >> b >> c;
	cout << nthUglyNumberGen2(n, a, b, c) << "\n";
	return 0;
}

