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

class node{
public:
	int key, val;
	node* next;
	node* prev;
	node(int k,int v): key(k), val(v), next(NULL), prev(NULL) {}
};

class LRUCache{
	node* head;
	node* tail;
	int count, capacity;
	map<int,node*> mp;

	void moveToFront(node* temp){
		if(head == temp) return;
		if(tail == temp){
			temp->next = head, head->prev = temp;
			tail = tail->prev, tail->next = NULL, temp->prev = NULL;
			head = temp;
			return;
		}

		node* p = temp->prev;
		node* nt = temp->next;
		p->next = nt, nt->prev = p;
		temp->next = head, head->prev = temp, temp->prev = NULL;
		head = temp;
		return;
	}

public:
	LRUCache(int capacity): capacity(capacity){
		head = NULL, tail = NULL, count = 0;
	}
	int get(int key){
		node* temp = head;
		//	Optimize this operation
		if(mp.count(key) > 0) temp = mp[key];
		else temp = NULL;
		//while(temp && temp->key != key) temp = temp->next;
		if(!temp) return -1;
		int v = temp->val;
		moveToFront(temp);
		return v;
	}
	void put(int key,int value){
		node* temp = head;
		//	Optimize This operation
		if(mp.count(key) > 0) temp = mp[key];
		else temp = NULL;
		//while(temp && temp->key != key) temp = temp->next;
		if(!temp){//	Not Found
			node* t = new node(key, value);
			if(head == NULL && tail == NULL) head = t, tail = t;
			else{
				t->next = head, head->prev = t;
				head = t;
			}
			mp[key] = t;
			count++;
			if(count > capacity){
				node* curr = tail;
				tail = tail->prev, tail->next = NULL, curr->prev = NULL;
				mp.erase(curr->key);
				delete curr;
				count--;
			}
		}
		else{
			temp->val = value;
			moveToFront(temp);
		}
	}
};


int main(){
	
	return 0;
}





