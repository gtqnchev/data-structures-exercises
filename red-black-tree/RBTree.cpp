#include <iostream>
using namespace std;

template <typename T = int>
struct RBNode
{
    T value;
    bool color;
    RBNode<T> *left;
    RBNode<T> *right;
    RBNode(T v, bool c, RBNode *l = NULL, RBNode *r = NULL): value(v), color(v), left(l), right(r)
    {}
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
private:
    bool Insert(T value, Node*
};

int main ()
{
    cout << "Testing a red-black tree." << endl;
    RBTree<> tree;
    cout << "Test if a new Tree is empty:" << tree.Empty() << endl;
    
    return 0;
}
