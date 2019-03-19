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
		long long int value;
		Node(int val = 0) : left(NULL), right(NULL)
		{
			value = val;
		}
	} *root = NULL;	
	void Insert(Node* head, long long int x)
	{
		if (x == head->value) return;
		if (x < head->value	)
		{
			if (head->left != NULL)
			{
				Insert(head->left, x);
			}
			else
			{				
				head->left = GetNewNode(x);
			}
		}
		else
		{
			if (head->right != NULL)
			{
				Insert(head->right, x);
			}
			else
			{				
				head->right = GetNewNode(x);
			}
		}
	}

	void PrintLeftTrayverse(Node* head, ostream& out)
	{
		out << head->value << endl;		
		if (head->left != NULL)
		{
			PrintLeftTrayverse(head->left, out);
		}
		if (head->right != NULL)
		{
			PrintLeftTrayverse(head->right, out);
		}
	}

	void AddValue(long long int x)
	{
		if (root == NULL)
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
		PrintLeftTrayverse(root, out);
	}

	Node* GetNewNode(long long int x)
	{
		Node* temp = new Node(x);
		return temp;
	}
};


int main()
{
	Tree tree;
	ifstream fin("input.txt");
	long long int a = 0;
	while (!fin.eof())
	{
		fin >> a;
		tree.AddValue(a);
	}
	fin.close();
	ofstream fout("output.txt");
	tree.Print(fout);
	fout.close();
	system("pause");
	return 0;
}