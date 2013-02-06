#include <iostream>
#include <iomanip>
using namespace std;

template <typename T = int >
struct Node
{
    T value;
    Node *parent, *left, *right;

    Node(T v, Node *p, Node *l = NULL, Node *r = NULL) : value(v), parent(p), left(l), right(r)
    {}

    void PrintTree(int offset)
	{
        if(right) right->PrintTree(offset + 5);

        cout << setw(offset) << value << endl;

        if(left) left->PrintTree(offset + 5);
	}
    void Print()
    {
        cout << value << " ";
    }
};

template <typename T = int >
class OrdTree
{
    Node<T>* root;
public:
    OrdTree()
    {
        root = NULL;
    }
    Node<T>* Root()
    {
	return root;
    }
    void Insert(T value)
    {
        Node<T> *parent = NULL;
        Node<T> **current = &root;
        while(*current != NULL)
        {
            parent = *current;
            if(value < (*current)->value)
                current = &((*current)->left);
            else
                current = &((*current)->right);
        }
        *current = new Node<T>(value, parent);
    }

    void InorderTreeWalk(Node<T>* node)
    {
        if(node != NULL)
        {
            InorderTreeWalk(node->left);
            node->Print();
            InorderTreeWalk(node->right);
        }
    }

    void Print()
    {
        if(root == NULL)
            cout << "Tree is empty!" << endl;
        else
            root->PrintTree(0);
    }
};


int main ()
{
    cout << "Testing an ordered tree." << endl;
    OrdTree<> tree;

    cout << "Test if we can add elements:" << endl;
    tree.Insert(5);
    tree.Insert(10);
    tree.Insert(8);

    cout << "Test if we can print the tree:" <<endl;
    tree.Print();
    cout << "Inorder tree walk:"<<endl;
        tree.InorderTreeWalk(tree.Root());
    return 0;
}
