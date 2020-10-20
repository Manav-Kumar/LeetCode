#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)

#define vi vector<int>
#define ll long long

class node
{
public:
	node *left, *right;
	int count;
	ll min, max;
	node(ll min,ll max): min(min), max(max), left(NULL), right(NULL), count(0) 
	{}
};

node* buildTree(vector<ll>& ssum,int start,int end)
{
	node *root = new node(ssum[start], ssum[end]);
	if(start != end)
	{
		int mid = (start + end)/2;
		root->left = buildTree(ssum, start, mid);
		root->right = buildTree(ssum, mid+1, end);
	}
	return root;
}

void modify(node* root, ll value)
{
	if(root == NULL || value > root->max || value < root->min) return;
	if(root->min <= value && value <= root->max) root->count++;
	modify(root->left, value);
	modify(root->right, value);
}

int query(node* root,ll min, ll max)
{
	if(!root || min > root->max || max < root->min) return 0;
	if(min <= root->min && max >= root->max) return root->count;
	return query(root->left, min, max) + query(root->right, min, max);
}

void deleteBIT(node* root)
{
	if(!root) return;
	deleteBIT(root->left);
	deleteBIT(root->right);
	delete root;
}

int countRangeSum(vector<int>& nums,int lower,int higher)
{
	unordered_set<ll> s;
	ll sum = 0;
	for(int &a: nums)
	{
		sum += a;
		s.insert(sum);
	}
	vector<ll> ssum;
	for(auto it = s.begin();it!=s.end();it++) ssum.push_back(*it);
	sort(ssum.begin(), ssum.end());
	node * root = buildTree(ssum,0, ssum.size()-1);
	int count = 0;
	repR(i,nums.size()-1,0)
	{
		modify(root, sum);
		sum -= nums[i];
		count += query(root, lower + sum, higher + sum);
	}
	deleteBIT(root);
	return count;
}


int main()
{
	vector<int> nums;
	int lower, higher, n;
	cin >> n;
	nums.resize(n);
	for(int &a: nums) cin >> a;
	cin >> lower >> higher;
	cout << countRangeSum(nums, lower, higher) << endl;
	return 0;	
}

