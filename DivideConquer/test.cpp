#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <unordered_map>
#include <set>
#include <iomanip>
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


int main(){
	char abc[20];
	strcpy(abc, "manavKuma");
	for(int i = 0;i < 20;i++){
		if(abc[19] == '\0') cout << "ok";
		cout << abc[i];
	}
	cout << "\n";
	char *pt = abc;
	cout << abc << " " << *abc << " " << pt << " " << *pt << " " << &abc << " "  << &pt << "\n";
	return 0;
}






