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
#define vll vector<ll>
#define vi vector<int>
#define vvi vector<vi >
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>

double euclideanDist(pair<int,int> a,pair<int,int> b){
    return (double)sqrt( (double)pow((a.first - b.first), 2) + (double)pow((a.second - b.second), 2) );
}

pair<int,int> bestCoordinate(vvi &towers, int radius){

	int ans = 0;
	pair<int,int> point(-1, -1);

	for(int x = 0;x <= 150;x++){
		for(int y = 0;y <= 150;y++){
			int netQSum = 0;
			for(vi &t: towers){
				double d = euclideanDist({t[0] + 50, t[1] + 50}, {x, y});
				if(d <= radius){
					netQSum += (t[2]/(1 + d));
				}
			}
			if(netQSum > ans){
				ans = netQSum, point = {x - 50, y - 50};
			}
		}
	}

	return point;
}

//	Cinema Seat Allocation

int maximumNumberOfFamilies(int n, vvi &reservedSeats){
	vvb seats(n + 1, vb(11, false));
	for(vi &a: reservedSeats) seats[a[0]][a[1]] = true;

	int ans = 0;
	for(int i = 1;i <= n;i++){
		bool c1 = true, c2 = true, c = true;
		for(int j = 2;j <= 5;j++){
			if(seats[i][j]){
				c1 = false; break;
			}
		}
		if(c1) ans++;
		for(int j = 6;j <= 9;j++){
			if(seats[i][j]){
				c2 = false; break;
			}
		}
		if(c2) ans++;

		if(!c1 && !c2){
			for(int j = 4;j <= 7;j++){
				if(seats[i][j]){
					c = false; break;
				}
			}
			if(c) ans++;
		}

	}
	return ans;
}


int maximumNumberOfFamilies2(int n, vvi &reservedSeats){
	map<int,vb > mp;
	for(vi &a: reservedSeats){
		int row = a[0], idx = a[1];
		if(mp.count(row) == 0){
			mp[row] = vb(3, true);
		}
		if(idx == 2 || idx == 3){
			mp[row][0] = false;
		}
		else if(idx == 4 || idx == 5){
			mp[row][0] = false, mp[row][1] = false;
		}
		else if(idx == 6 || idx == 7){
			mp[row][1] = false, mp[row][2] = false;
		}
		else if(idx == 8 || idx == 9){
			mp[row][2] = false;
		}
	}
	int ans = (n - mp.size())*2;
	for(auto it = mp.begin();it != mp.end();it++){
		vb t = it->second;
		if(t[0] || t[2]) ans += (t[0]?1:0) + (t[2]?1:0);
		else if(t[1]) ans += 1;
	}
	return ans;
}


//	Maximum Profit Of Operating A Centennial Wheel
int minOperationsMaxProfit(vector<int>& customers, int boardingCost, int runningCost){

	queue<int> q;
	rep(i, 0, 4) q.push(0);
	int persons = 0, rotations = 0, profit = 0, waiting = 0, maxProfit = 0, ansRotations = 0;
	for(int i = 0;i < customers.size() || waiting > 0;){

		if(i < customers.size()) waiting += customers[i++];

		int people = min(waiting, 4);
		persons += people - q.front(), rotations += 1;
		q.pop(); q.push(people);
		profit += boardingCost*people - runningCost;
		if(profit > maxProfit){
			maxProfit = profit, ansRotations = rotations;
		}

		waiting -= people;
	}

	return ansRotations == 0?-1:ansRotations;
}


int minOperationsMaxProfit2(vector<int>& customers, int boardingCost, int runningCost){

	int rotations = 0, profit = 0, waiting = 0, maxProfit = 0, ansRotations = 0;
	for(int i = 0;i < customers.size() || waiting > 0;){

		if(i < customers.size()) waiting += customers[i++];

		int people = min(waiting, 4);
		rotations += 1;
		profit += boardingCost*people - runningCost;
		if(profit > maxProfit){
			maxProfit = profit, ansRotations = rotations;
		}

		waiting -= people;
	}

	return ansRotations == 0?-1:ansRotations;
}

int main(){
	int n, boardingCost, runningCost;
	cin >> n >> boardingCost >> runningCost;
	vi customers(n);
	for(int &a: customers) cin >> a;
	cout << minOperationsMaxProfit(customers, boardingCost, runningCost) << "\n";
	return 0;
}











