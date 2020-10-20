#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long

/*
Below Approach Worst Case Complexity is O(N^2) in case tree is skewed.
*/

class node
{
public:
	node *left,*right;
	ll count, value, smallerCount;
	node(ll c,ll n,ll sc): count(c), value(n), smallerCount(sc), left(NULL), right(NULL)
	{}
};

void Query(node* root,ll& value,ll& count,ll& result)
{
	if(!root)
	{
		result += count;
		return;
	}

	if(value >= root->value)
	{
		count += root->smallerCount;
		if(value != root->value) count += root->count;
		Query(root->right, value, count, result);
	}
	else Query(root->left, value, count, result);
}

node* insertBIT(node* root,ll& value)
{
	if(!root) return new node(1, value, 0);
	if(value == root->value)
	{
		root->count++;
		return root;
	}
	if(value < root->value)
	{
		root->smallerCount++;
		root->left = insertBIT(root->left, value);
	}
	else root->right = insertBIT(root->right, value);
	return root;
}


int reversePairs(vector<int>& nums)
{
	ll result = 0;
	int n = nums.size();
	node* root = NULL;
	repR(i, n-1, 0)
	{
		ll value = nums[i], count = 0;
		Query(root, value, count, result);
		value *= 2;
		root = insertBIT(root, value);
	}
	return int(result);
}

void insert_sorted(vector<ll> &forwarded,const ll &value)
{
	forwarded.insert(
		upper_bound(forwarded.begin(), forwarded.end(), value), value
	);
}

int reversePairs2(vector<int>& nums)
{
	ll n = nums.size(), result = 0;
	vector<ll> forwarded;

	repR(i, n-1, 0)
	{
		ll value = nums[i];
		result += lower_bound(forwarded.begin(), forwarded.end(), value) - forwarded.begin();
		value *= 2;
		insert_sorted(forwarded, value);
	}
	return int(result);
}


//	Going to use Fenwick Tree or BIT to avoid the problem of skewness


//	DIVIDE & CONQUER

void merge(vector<int> &nums,int start,int end)
{
	int mid = (start + end)/2;
	int i = start, j = mid+1,k = 0;
	int arr[end - start + 1];
	while(i <= mid && j <= end)
	{
		if(nums[i] < nums[j])
		{
			arr[k] = nums[i];
			i++;
		}
		else
		{
			arr[k] = nums[j];
			j++;
		}
		k++;
	}
	while(i <= mid)
	{
		arr[k] = nums[i];
		i++, k++;
	}
	while(j <= end)
	{
		arr[k] = nums[j];
		k++, j++;
	}
	rep(i,start,end+1)
	{
		nums[i] = arr[i - start];
	}
}

int calc_func(vector<int>& nums,int start,int end)
{
	if(start >= end) return 0;
	int mid = (start + end)/2;
	int count = calc_func(nums, start,mid) + calc_func(nums,mid+1,end);
	int k = 0;
	rep(i,start,mid+1)
	{
		rep(j,mid+1+k,end+1)
		{
			if((long)nums[i] > (long)2*nums[j]) k++;
			else break;
		}
		count += k;
	}
	merge(nums,start, end);
	return count;
}



int main()
{
	std::vector<int> v;
	int n;
	cin >> n;
	v.assign(n, 0);
	for(int &a: v) cin >> a;
	cout << reversePairs2(v) << endl;
	cout << calc_func(v,0,v.size()-1) << endl;
	return 0;
}

