#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <unordered_map>
#include <set>
#include <cmath>
#include <math.h>
#include <unordered_set>
#include <climits>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vvi vector<vi >
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>

bool compare(vi &a, vi &b){
	return a[1] < b[1];
}

int maxCourses(vvi &courses,vvi &dp, int idx = 0,int d = 0){

	if(idx == courses.size()) return 0;
	//if(dp[idx][d] != -1) return dp[idx][d];

	int a1 = maxCourses(courses, dp, idx + 1, d);
	int a2 = 0;
	if(d + courses[idx][0] <= courses[idx][1]){
		a2 = maxCourses(courses, dp, idx + 1, d + courses[idx][0]) + 1;
	}
	dp[idx][d] = max(a1, a2);
	return dp[idx][d];
}

int scheduleCourse(vvi &courses){
	sort(courses.begin(), courses.end(), compare);
	vvi dp(10001, vi(10001, -1));
	//	Here memory creation will take a lot of time
	return maxCourses(courses, dp);
}



int scheduleCourse2(vvi &courses){
	sort(courses.begin(), courses.end(), compare);
	priority_queue<int> q;
	int ans = 0, d = 0, n = courses.size();
	for(int i = 0;i < n;i++){

		if(d + courses[i][0] <= courses[i][1]){
			d += courses[i][0], ans++;
			q.push(courses[i][0]);
		}
		else if(!q.empty() && q.top() > courses[i][0]){
			d = d - q.top() + courses[i][0]; 
			q.pop();
			q.push(courses[i][0]);
		}
	}

	return ans;
}


int main(){
	int n;
	cin >> n;
	vvi courses(n, vi(2));
	for(vi &a: courses){
		cin >> a[0] >> a[1];
	}
	cout << scheduleCourse(courses) << "\n";
	return 0;
}








