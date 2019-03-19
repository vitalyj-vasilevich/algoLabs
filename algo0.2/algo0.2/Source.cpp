#include <iostream>
#include <fstream>

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
		Node(int val = 0) : left(nullptr), right(nullptr), parent(nullptr)
		{
			value = val;
		}
	} *root = nullptr;

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
};


int main()
{
	Tree tree;
	ifstream fin("input.txt");
	long long int a = 0;
	long long int suicide = 0;
	if (!fin.eof())
	{
		fin >> suicide;
	}
	else
	{
		fin.close();
		return 0;
	}
	while (!fin.eof())
	{
		fin >> a;
		tree.AddValue(a);
	}
	fin.close();
	tree.PerformRemove(suicide);
	ofstream fout("output.txt");
	tree.Print(fout);
	fout.close();
	system("pause");
	return 0;
}