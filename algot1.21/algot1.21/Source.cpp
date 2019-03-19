#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Tree
{
public:
	struct Node
	{
		Node* left;
		Node* right;
		Node* parent;
		long long int value;
		short height;
		short leftDescendants;
		short rightDescendants;
		Node(int val = 0) : left(nullptr), right(nullptr), parent(nullptr), height(0), leftDescendants(0), rightDescendants(0)
		{
			value = val;
		}
	} *root = nullptr;
	vector<long long int> select;
	void Insert(Node* head, long long int x)
	{
		if (x == head->value) return;
		if (x < head->value)
		{
			if (head->left)
			{
				Insert(head->left, x);
			}
			else
			{
				head->left = GetNewNode(x);
				head->left->parent = head;
			}
		}
		else
		{
			if (head->right)
			{
				Insert(head->right, x);
			}
			else
			{
				head->right = GetNewNode(x);
				head->right->parent = head;
			}
		}
	}

	void PrintLeftTrayverse(Node* head, ostream& out)
	{
		out << head->value << endl;
		if (head->left)
		{
			PrintLeftTrayverse(head->left, out);
		}
		if (head->right)
		{
			PrintLeftTrayverse(head->right, out);
		}
	}

	Node* Search(Node* head, long long int x)
	{
		if (!root) return nullptr;
		if (x == head->value) return head;
		if (x > head->value)
		{
			if (head->right)
			{
				return Search(head->right, x);
			}
			else
			{
				return nullptr;
			}
		}
		if (x < head->value)
		{
			if (head->left)
			{
				return Search(head->left, x);
			}
			else
			{
				return nullptr;
			}
		}
	}

	void AddValue(long long int x)
	{
		if (root == nullptr)
		{
			root = GetNewNode(x);
		}
		else
		{
			Insert(root, x);
		}
	}

	void Print(ostream& out)
	{
		if (!root) return;
		PrintLeftTrayverse(root, out);
	}

	Node* GetNewNode(long long int x)
	{
		Node* temp = new Node(x);
		return temp;
	}

	void RightRemove(long long int x, Node* key)
	{
		if (key->left && key->right)
		{
			Node* tmp = key->right;
			while (tmp->left)
			{
				tmp = tmp->left;
			}
			key->value = tmp->value;
			tmp->value = x;
			RightRemove(x, tmp);
			return;
		}
		if (!key->left)
		{
			if (!key->right)
			{
				if (!key->parent)
				{
					root = nullptr;
					return;
				}
				if (key->parent->left && key->parent->left->value == key->value)
				{
					key->parent->left = nullptr;
				}
				else
				{
					key->parent->right = nullptr;
				}
				return;
			}
			else
			{
				if (!key->parent)
				{
					root = (key->right ? key->right : nullptr);
					return;
				}
				Node* tmp = key->right;
				key->parent->left == key ? key->parent->left = tmp : key->parent->right = tmp;
				tmp->parent = key->parent;
				return;
			}
		}
		else if (!key->right)
		{
			if (!key->parent)
			{
				root = key->left;
				return;
			}
			Node* tmp = key->left;
			key->parent->left == key ? key->parent->left = tmp : key->parent->right = tmp;
			tmp->parent = key->parent;
			return;
		}
	}

	void PerformRemove(long long int x)
	{
		Node* key = Search(root, x);
		if (key)
		{
			RightRemove(x, key);
		}
	}

	void DoHeights(Node* root)
	{		
		if (root->left)
		{
			DoHeights(root->left);
			root->leftDescendants = root->left->leftDescendants + root->left->rightDescendants + 1;
			root->height = root->left->height + 1;
		}
		if (root->right)
		{
			DoHeights(root->right);
			root->rightDescendants = root->right->leftDescendants + root->right->rightDescendants + 1;
			if (root->right->height > root->height - 1)
			{
				root->height = root->right->height + 1;
			}
		}
		if (root->left == root->right)
		{
			root->leftDescendants = 0;
			root->rightDescendants = 0;
			root->height = 0;
		}

	}

	void Chooseselectisfying(Node* head)
	{
		if (head->left)
		{
			Chooseselectisfying(head->left);
		}
		if (head->right && head->left)
		{
			if (head->right->height == head->left->height && head->leftDescendants != head->rightDescendants)
			{
				select.push_back(head->value);
			}
		}
		if (head->right)
		{
			Chooseselectisfying(head->right);
		}
	}
};

int main()
{
	Tree tree;
	ifstream fin("in.txt");
	long long int a = 0;
	while (!fin.eof())
	{
		fin >> a;
		tree.AddValue(a);
	}
	fin.close();
	tree.DoHeights(tree.root);
	tree.Chooseselectisfying(tree.root);
	if (tree.select.size() == 1)
	{
		a = tree.select[0];
		tree.PerformRemove(a);

	}
	else if (tree.select.size() % 2 == 1)
	{
		//sort(tree.select.begin(), tree.select.end());
		a = tree.select[(tree.select.size() / 2)];
		tree.PerformRemove(a);
	}
	ofstream fout("out.txt");
	tree.Print(fout);	
	fout.close();
	system("pause");
}