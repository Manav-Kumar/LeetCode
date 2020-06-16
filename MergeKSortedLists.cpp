#include <iostream>
#include <vector>
using namespace std;

struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x): val(x), next(NULL) {}
	ListNode(int x,ListNode *next): val(x), next(next) {}
};

ListNode* mergeKLists(vector<ListNode*> lists)
{
	ListNode* head = NULL;
	ListNode* tail = NULL;
	while(1)
	{
		int Min = INT_MAX, index = -1;
		for(int i = 0;i < lists.size();i++)
		{
			if(lists[i] && lists[i]->val < Min)
			{
				Min = min(Min, lists[i]->val);
				index = i;
			}
		}
		if(index == -1) return head;
		if(!head)
		{
			head = new ListNode(Min);
			tail = head;
		}
		else
		{
			tail->next = new ListNode(Min);
			tail = tail->next;
		}
		lists[index] = lists[index]->next;
	}
}

ListNode* takeInput()
{
	ListNode* head = NULL;
	ListNode* tail = NULL;
	int data;
	cin >> data;
	while(data != -1)
	{
		if(!head)
		{
			head = new ListNode(data);
			tail = head;
		}
		else
		{
			tail->next = new ListNode(data);
			tail = tail->next;
		}
		cin >> data;
	}
	return head;
}

void PRINT(ListNode* head)
{
	while(head)
	{
		cout << head->val << " ";
		head = head->next;
	}
	return;
}

int main()
{
	int k;
	cin >> k;
	vector<ListNode*> lists;
	while(k--)
	{
		ListNode* head = takeInput();
		lists.push_back(head);
	}
	ListNode* head = mergeKLists(lists);
	PRINT(head);
	return 0;

}

