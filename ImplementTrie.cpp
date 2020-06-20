#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <unordered_set>

using namespace std;


class Trie{
public:
	class node
	{
	public:
		bool isTerm;
		vector<node*> next;
		node(bool k = false)
		{
			isTerm = k;
			next.resize(26, NULL);
		}
	};
	node *root;
	Trie()
	{
		root = new node(true);
	}

	void insert(string word)
	{
		node* temp = root;
		for(int i = 0;i < word.size();i++)
		{
			int c = word[i] - 'a';
			if(temp->next[c] == NULL) temp->next[c] = new node();
			temp = temp->next[c];
		}
		temp->isTerm = true;
	}

	bool search(string word)
	{
		node* temp = root;
		for(int i = 0;i < word.size();i++)
		{
			int c = word[i] - 'a';
			if(temp->next[c] == NULL) return false;
			temp = temp->next[c];
		}
		return temp->isTerm;
	}

	bool startsWith(string word)
	{
		node* temp = root;
		for(int i = 0;i < word.size();i++)
		{
			int c = word[i] - 'a';
			if(temp->next[c] == NULL) return false;
			temp = temp->next[c];
		}
		return true;
	}
};

int main()
{
	
}