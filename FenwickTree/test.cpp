#include <iostream>
#include <queue>
using namespace std;


int minHeight(int *inorder,int *level,int n)
{
	queue<pair<int,int> > q;
	// map<int,int> mp;
	// for(int i=0;i<n;i++){
	// 	for(int j=0;j<n;j++){
	// 		if(level[i] == inorder[j]){
	// 			mp[i] = j;
	// 			break;
	// 		}
	// 	}
	// }
	q.push(pair<int,int> (0, n-1));
	q.push(pair<int,int> (-1, -1));
	int idx = 0, ht = 0;
	while(!q.empty())
	{
		if(idx == n) break;
		pair<int,int> front = q.front();
		q.pop();
		if(front.first == -1 && front.second == -1){
			ht++;
			if(q.size() == 0) break;
			q.push(pair<int,int> (-1, -1));
			continue;
		}

		for(int i = front.first;i <= front.second;i++){
			if(inorder[i] == level[idx]){
				idx++;
				if((i-1) >= front.first) q.push(pair<int,int> (front.first, i-1));
				if((i+1) <= front.second) q.push(pair<int,int> (i+1, front.second));
				break;
			}
		}

	}

	return ht + 1;
}



int main(){
	int n;
	cout << "ok";
	cin >> n;
	int *inorder = new int[n];
	int *level = new int[n];
	for(int i=0;i<n;i++){
		cin >> inorder[i];
	}
	for(int i=0;i<n;i++){
		cin >> level[i];
	}
	cout << "done\n";
	cout << minHeight(inorder, level, n) << "\n";
	delete []inorder;
	delete []level;
	return 0;
}