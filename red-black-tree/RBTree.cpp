#include <iostream>
#include <iomanip>
using namespace std;

template <typename T = int>
struct RBNode
{
    T value;
    bool color;
    RBNode<T> *left;
    RBNode<T> *right;
    RBNode(T v, bool c = 1, RBNode *l = NULL, RBNode *r = NULL): value(v), color(v), left(l), right(r)
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
    bool Add(T value)
    {
        return Insert(value, root);
    }
    
    void Print()
    {
        root->Print(0);
    }
    
private:
    bool Insert(T value, RBNode<T> *&node)
    {
        if (node == NULL)
        {
            node = new RBNode<T>(value);
            return true;
        }
        else if (node->value > value)
            return Insert(value, node->left);
        
        else if (node->value < value)
            return Insert(value, node->right);
        
        return false;
    }
};  

int main ()
{
    cout << "Testing a red-black tree." << endl;
    RBTree<> tree;
    
    cout << "Test if a new Tree is empty:" << tree.Empty() << endl;
    
    cout << "Test if we can add elements:" << tree.Add(5) << endl;
    
    cout << "Test if we can print the tree:" <<endl;
        tree.Print();
        
    return 0;
}
