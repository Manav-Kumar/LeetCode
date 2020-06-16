#include <iostream>
#include <vector>
using namespace std;


double findMedianSortedArrays(vector<int> nums1, vector<int> nums2) {
	int m = nums1.size(), n = nums2.size();
	int size = n+m;
	if(m > n)
	{
		vector<int> temp = nums2;
		nums2 = nums1;
		nums1 = temp;
		m = nums1.size(), n = nums2.size();
	}
	if(m == 0)
	{
		if(n%2) return nums2[n/2];
		return double(nums2[n/2] + nums2[(n-1)/2])/2.0;
	}
	int st = 0, en = m;
	int halfLen = (n+m+1)/2;
	while(st <= en)
	{
		int i = (st+en)/2;
		int j = halfLen - i;//j is always going to divide the same elements between the sets
		if(i >  st && nums1[i-1] > nums2[j]) en = i-1;
		else if(i < en && nums2[j-1] > nums1[i]) st = i+1;
		else
		{
			//i is perfect
			int leftPart = 0;
			if(i == 0) leftPart = nums2[j-1];
			else if(j == 0) leftPart = nums1[i-1];
			else leftPart = max(nums1[i-1], nums2[j-1]);

			if((n+m)%2 == 1) return leftPart;
			int rightPart = 0;
			if(i == m) rightPart = nums2[j];
			else if(j == n) rightPart = nums1[i];
			else rightPart = min(nums1[i], nums2[j]);

			return (leftPart + rightPart)/2.0;
		}
	}

}

int main()
{
	vector<int> nums1, nums2;
	int n,m;
	cin >> n >> m;
	nums1.resize(n);
	nums2.resize(m);
	for(int &a: nums1) cin >> a;
	for(int &a: nums2) cin >> a;
	cout << "Input completed " << endl;
	cout << findMedianSortedArrays(nums1, nums2) << endl;
	return 0;
}