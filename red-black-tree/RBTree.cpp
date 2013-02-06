#include <iostream>
#include <iomanip>
using namespace std;

template <typename T = int>
struct RBNode
{
    T value;
    bool color;
    RBNode<T> *parent, *left, *right;
    RBNode(T v, bool c = 1, RBNode *p = NULL, RBNode *l = NULL, RBNode *r = NULL): value(v), color(v), parent(p), left(l), right(r)
    {}

    void Print(int offset)
	{
        if(right) right->Print(offset + 5);

        cout << setw(offset) << value << endl;

        if(left) left->Print(offset + 5);
	}
};

template <typename T = int>
class RBTree
{
    RBNode<T> *root;

public:
    RBTree() : root(NULL)
    {}

    bool Empty()
    {
        return root == NULL;
    }

    void Add(T value)
    {
        Insert(value, &root);
    }

    void Print()
    {
        if(Empty())
            cout << "Tree is empty!" << endl;
        else
            root->Print(0);
    }

private:

    void Insert(T value, RBNode<T> **node)
    {
        while (*node != NULL)
        {
            if(value < (*node)->value)
                node = &((*node)->left);
            else
                node = &((*node)->right);
        }
        *node = new RBNode<T>(value,);

    }


};

int main ()
{
    cout << "Testing a red-black tree." << endl;
    RBTree<> tree;

    cout << "Test if a new Tree is empty:" << tree.Empty() << endl;

    cout << "Test if we can add elements:" << endl;
    tree.Add(5);
    tree.Add(10);
    tree.Add(8);

    cout << "Test if we can print the tree:" <<endl;
        tree.Print();

    return 0;
}
