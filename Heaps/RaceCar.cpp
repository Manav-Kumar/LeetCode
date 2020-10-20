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
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vl vector<long>
#define vll vector<long long>
#define vc vector<char>
#define vs vector<string>
#define vvc vector<vc>
#define vvi vector<vector<int> >
#define vvl vector<vl>
#define vvll vector<vll>
#define vvb vector<vector<bool> >

//	Maximum #Steps it can take is taking 3instructions cause 1 increment
class node
{
public:
	double pos, speed, steps;
	node(double p,double sp,double st): pos(p), speed(sp), steps(st) {}
};

int raceCar(int target)
{
	queue<node> q;
	q.push({0, 1, 0});
	while(!q.empty())
	{
		node t = q.front();
		q.pop();
		double steps = t.steps, pos = t.pos, speed = t.speed;
		if(target == pos) return steps;
		q.push({pos + speed, speed*2, steps + 1});
		if(speed > 0 && (pos + speed) > target){
			q.push({pos, -1, steps + 1});
		}
		else if(speed <= 0 && (pos + speed) < target){
			q.push({pos, 1, steps + 1});
		}
	}
	return 0;
}


class MedianFinder{
	vector<int> v;
	priority_queue<int> leftMax;
	priority_queue<int, vector<int>, greater<int> > rightMin;
public:
	MedianFinder() {}

	void addNum(int num)
	{
		if(rightMin.size() == 0 && leftMax.size() == 0){
			rightMin.push(num);
			return ;
		}
		if(num < rightMin.top()) leftMax.push(num);
		else rightMin.push(num);

		if(int(leftMax.size() - rightMin.size()) > 1){
			rightMin.push(leftMax.top());
			leftMax.pop();
		}

		if(int(rightMin.size() - leftMax.size()) > 1){
			leftMax.push(rightMin.top());
			rightMin.pop();
		}
	}
	
	double findMedian(){
		if(leftMax.size() == rightMin.size()){
			return (leftMax.top() + rightMin.top())/2;
		}
		return leftMax.size() > rightMin.size()?leftMax.top():rightMin.top();
	}
};

int main()
{
	map<triplet, int> dp;
	int target;
	cin >> target;
	cout << raceCar(0,1,target,0,dp) << "\n";
	return 0;
}

