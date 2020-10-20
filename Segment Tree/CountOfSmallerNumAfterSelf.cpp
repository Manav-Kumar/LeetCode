#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long

void insert_sorted(vector<int> &forwarded,const int &value)
{
	forwarded.insert(
		upper_bound(forwarded.begin(), forwarded.end(), value), value
	);
}

vector<int> countSmaller(vector<int>& nums)
{
	int n = nums.size();
	vector<int> forwarded, result;

	repR(i, n-1, 0)
	{
		result.push_back(lower_bound(forwarded.begin(), forwarded.end(), nums[i]) - forwarded.begin());
		insert_sorted(forwarded, nums[i]);
	}
	reverse(result.begin(), result.end());
	return result;
}

class node
{
public:
	node *left,*right;
	int count, value, smallerCount;
	node(int c,int n,int sc): count(c), value(n), smallerCount(sc), left(NULL), right(NULL)
	{}
};

node* insertBIT(node* root,int& value,int& count,vector<int>& result)
{
	if(!root)
	{
		result.push_back(count);
		return new node(1, value, 0);
	}
	if(value == root->value)
	{
		root->count++;
		count += root->smallerCount;
		result.push_back(count);
		return root;
	}
	if(value < root->value)
	{
		root->smallerCount++;
		root->left = insertBIT(root->left, value, count, result);
	}
	else
	{
		count += root->smallerCount + root->count;
		root->right = insertBIT(root->right, value, count, result);
	}
	return root;
}

vector<int> countSmaller2(vector<int>& nums)
{
	vector<int> result;
	int n = nums.size();
	node* root = NULL;
	repR(i, n-1, 0)
	{
		int count = 0;
		root = insertBIT(root, nums[i], count, result);
	}
	reverse(result.begin(), result.end());
	return result;
}

int main()
{
	vector<int> v {10, 20, 30, 30, 30, 40, 50};
	cout << "Experimenting on Lower Bounds" << endl;
	cout << (lower_bound(v.begin(), v.end(), 30) - v.begin()) << endl;
	cout << (lower_bound(v.begin(), v.end(), 35) - v.begin()) << endl;
	cout << (lower_bound(v.begin(), v.end(), 55) - v.begin()) << endl;
	cout << "Experimenting on Upper Bounds" << endl;
	cout << (upper_bound(v.begin(), v.end(), 30) - v.begin()) << endl;
	cout << (upper_bound(v.begin(), v.end(), 35) - v.begin()) << endl;
	cout << (upper_bound(v.begin(), v.end(), 45) - v.begin()) << endl;
	cout << (upper_bound(v.begin(), v.end(), 55) - v.begin()) << endl;
	v.insert(v.end(),90);
	rep(i,0,v.size()) cout << v[i] << " ";
	cout << "\n";
	int n;
	cin >> n;
	v.assign(n, 0);
	for(int &a: v) cin >> a;
	vector<int> ans = countSmaller(v);
	rep(i,0, v.size()) cout << ans[i] << " ";
	cout << "\n";
	ans = countSmaller2(v);
	rep(i,0, v.size()) cout << ans[i] << " ";
	cout << "\n";
	return 0;
}