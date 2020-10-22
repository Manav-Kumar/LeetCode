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
#define vvvi vector<vvi>
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>


string intToRoman(int num){
	string ans = "";
	map<int,char> mp;
	int count = 0;
	while(num > 0){
		int v = num%10;
		string t = "";
		if(v == 4){
			if(count == 0) t += "IV";
			else if(count == 1) t += "XL";
			else if(count == 2) t += "CD";
			v -= 4;
		}
		else if(v == 9){
			if(count == 0) t += "IX";
			else if(count == 1) t += "XC";
			else if(count == 2) t += "CM";
			v -= 9;
		}
		else if(v >= 5){
			if(count == 0) t += 'V';
			else if(count == 1) t += 'L';
			else if(count == 2) t += 'D';
			v -= 5;
		}

		while(v--){
			if(count == 0) t += 'I';
			else if(count == 1) t += 'X';
			else if(count == 2) t += 'C';
			else if(count == 3) t += 'M';
		}

		ans = t + ans;
		num /= 10, count++;
	}

	return ans;
}

//	Doubly Link List Forming MultiLevel Data Structure
class Node{
public:
	int val;
	Node *prev;
	Node *next;
	Node *child;
};

Node* flatten(Node* head, Node* prev = NULL){
	if(!head) return NULL;
	head->prev = prev;
	if(!head->child) head->next = flatten(head->next, head);
	else{
		Node* nt = head->next;
		head->next = flatten(head->child, head);
		head->child = NULL;
		Node* tail = head;
		while(tail->next) tail = tail->next;
		tail->next = flatten(nt, tail);
	}
	return head;
}

//	Clone a link list in O(1)
class singlenode{
public:
	int val;
	singlenode* next;
	singlenode* random;
	singlenode(int d): val(d), next(NULL), random(NULL) {}
};

singlenode* CloneLinkList(singlenode* head){

	//	Creating a copy of each node after each original node
	singlenode* temp = head;
	while(!temp){
		singlenode* t = new singlenode(temp->val);
		singlenode* nt = temp->next;
		temp->next = t, t->next = nt, temp = nt;
	}

	//	Assigning the random pointers to clone nodes
	temp = head;
	while(!temp){
		singlenode* clonnode = temp->next;
		if(temp->random) clonnode->random = temp->random->next;
		temp = clonnode->next;
	}

	//	Separating the clones nodes from original link list
	singlenode* newhead = NULL;
	singlenode* tail = NULL;
	temp = head;
	while(!temp){
		singlenode* clonnode = temp->next;
		if(newhead == NULL && tail == NULL) newhead = clonnode, tail = clonnode;
		else tail->next = clonnode, tail = clonnode;
		temp->next = clonnode->next;
		temp = temp->next;
	}

	return newhead;
}


//	2 City Scheduling
int CitySchedHelper(vvi &costs,vvi &dp,int cta = 0,int ctb = 0, int idx = 0){
	if(idx == costs.size()) return 0;
	int &ans = dp[cta][ctb];
	if(ans != -1) return ans;
	int n = costs.size()/2, a1 = INT_MAX, a2 = INT_MAX;
	if(cta < n) a1 = CitySchedHelper(costs, dp, cta + 1, ctb, idx + 1) + costs[idx][0];
	if(ctb < n) a2 = CitySchedHelper(costs, dp, cta, ctb + 1, idx + 1) + costs[idx][1];

	ans = min(a1, a2);
	return ans;
}

int twoCitySchedCost(vvi &costs){
	int n = costs.size()/2;
	vvi dp(n + 1, vi(n + 1, -1));
	return CitySchedHelper(costs, dp);
}

bool comparator(vi &a, vi &b){
	return a[1] - a[0] > b[1] - b[0]; 
}

int twoCitySchedCost2(vvi &costs){
	//	How much profit will i make by going to city A rather than B
	sort(costs.begin(), costs.end(), comparator);
	int ans = 0, n = costs.size();
	for(int i = 0;i < n;i++){
		if(i < n/2) ans += costs[i][0];
		else ans += costs[i][1];
	}
	return ans;
}

bool comparator2(vi &a, vi &b){
	return abs(a[0] - a[1]) > abs(b[0] - b[1]);
}

int twoCitySchedCost3(vvi &costs){
	sort(costs.begin(), costs.end(), comparator2);
	int ans = 0, cta = 0, ctb = 0, n = costs.size()/2;
	for(int i = 0;i < 2*n;i++){
		if(costs[i][0] < costs[i][1]){
			if(cta < n) ans += costs[i][0], cta++;
			else ans += costs[i][1], ctb++;
		}
		else{
			if(ctb < n) ans += costs[i][1], ctb++;
			else ans += costs[i][0], cta++;
		}
	}
	return ans;
}


int numRescueBoats(vi &people,int limits){
	sort(people.begin(), people.end());
	int i = 0, j = people.size() - 1, ans = 0;
	while(i <= j){
		if(people[i] + people[j] <= limits) ans += 1, i++, j--;
		else ans += 1, j--;
	}
	return ans;
}

//	Non Overlapping Intervals
int eraseOverlapIntervals(vvi &intervals){
	//	Sorting on the basis of start point
	sort(intervals.begin(), intervals.end());
	int ans = 0, st = -1, en = INT_MIN, n = intervals.size();
	rep(i, 0, n){
		if(en <= intervals[i][0]) st = intervals[i][0], en = intervals[i][1];
		else{
			ans += 1;
			en = min(en, intervals[i][1]);
		}
	}
	return ans;
}

bool comparator3(vi &a, vi &b){
	return a[1] < b[1];
}

int eraseOverlapIntervals(vvi &intervals){
	sort(intervals.begin(), intervals.end(), comparator3);
	int ans = 0, n = intervals.size(), prev = 0;
	rep(i, 1, n){
		if(intervals[prev][1] <= intervals[i][0]) prev = i;
		else ans++;
	}
	return ans;
}

//	Removed Covered Intervals
bool comp(vi &a, vi &b){
	if(a[0] == b[0]) return a[1] > b[1];
	return a[0] < b[0];
}
int removeCoveredIntervals(vvi &intervals){
	sort(intervals.begin(), intervals.end(), comp);
	int ans = 0, en = intervals[0][1], n = intervals.size();
	rep(i, 1, n){
		if(intervals[i][0] >= en || intervals[i][1] > en){
			en = intervals[i][1];
		}
		else if(intervals[i][1] <= en){
			ans++;
		}
	}
	return ans;
}

int main(){
	int n;
	cin >> n;
	vvi costs(n, vi(2));
	for(vi &a: costs) cin >> a[0] >> a[1];
	cout << twoCitySchedCost3(costs) << "\n"; 
	return 0;
}





