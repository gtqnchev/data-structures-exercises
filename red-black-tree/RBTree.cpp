#include <iostream>
#include <iomanip>
using namespace std;

template <typename T = int>
struct RBNode
{
    T value;
    bool color; // 0 for black
    RBNode<T> *parent, *left, *right;
    RBNode(T v, bool c = 1, RBNode *p = NULL, RBNode *l = NULL, RBNode *r = NULL) : value(v), color(c), parent(p), left(l), right(r)
    {}
    RBNode()
    {}
    void PrintTree(int offset)
    {
        if(parent != NULL)
        {
            if(right) right->PrintTree(offset + 5);

            cout << setw(offset) << value << endl;

            if(left) left->PrintTree(offset + 5);
        }
    }

    void Print()
    {
        if(parent != NULL)
            cout << value << " ";
    }
};

template <typename T = int >
class RBTree
{
    RBNode<T> *root;
    RBNode<T> *nil;
    void InsertFixup(RBNode<T> *node)
    {
        while(node->parent->color == 1)
        {
            RBNode<T> *y;
            if(node->parent->parent->left == node->parent)
            {
                y = node->parent->parent->right;                  // y is the uncle of node
                if (y->color == 1)                                // CASE 1
                {
                    y->color = 0;
                    node->parent->color = 0;
                    y->parent->color = 1;
                }
                else if (node->parent->right == node)             // CASE 2
                {
                    node = node->parent;
                    LeftRotate(node);
                }
                else                                              // CASE 3 
                {
                    RightRotate(node->parent->parent);
                    node = node->parent;
                    node->color = 0;
                    node->right->color = 1;
                }
            }
            else  //It's symetric to the first block
            {
                y = node->parent->parent->left;                  // y is the uncle of node
                if (y->color == 1)                                // CASE 1
                {
                    y->color = 0;
                    node->parent->color = 0;
                    y->parent->color = 1;
                }
                else if (node->parent->left == node)             // CASE 2
                {
                    node = node->parent;
                    RightRotate(node);
                }
                else                                              // CASE 3 
                {
                    LeftRotate(node->parent->parent);
                    node = node->parent;
                    node->color = 0;
                    node->left->color = 1;
                }
            }
        }
        root->color = 0;
    }
public:
    RBTree()
    {
        nil = new RBNode<T>;
        nil->color = 0;
        nil->left = nil->right = nil->parent = NULL;
        root = nil;
    }
   
    RBNode<T>* Root()
    {
	return root;
    }
   
    void Insert(T value)
    {
        RBNode<T> *parent = nil;
        RBNode<T> **current = &root;
        while(*current != nil)
        {
            parent = *current;
            if(value < (*current)->value)
                current = &((*current)->left);
            else
                current = &((*current)->right);
        }
        *current = new RBNode<T>(value, 1, parent, nil, nil);
        InsertFixup(*current);
    }

    void InorderTreeWalk(RBNode<T>* node)
    {
        if(node != nil)
        {
            InorderTreeWalk(node->left);
            node->Print();
            InorderTreeWalk(node->right);
        }
    }

    RBNode<T>* Search(T value)
    {
	RBNode<T>* current = root;
	while(current != nil && current->value != value)
        {
            if(value > current->value)
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }
        return current;
    }

    RBNode<T>* Minimum(RBNode<T>* node)
    {
        while(node->left != nil)
        {
            node = node->left;
        }
        return node;
    }

    RBNode<T>* Maximum(RBNode<T>* node)
    {
        while(node->right != nil)
        {
            node = node->right;
        }
        return node;
    }
    
    RBNode<T>* Succesor(RBNode<T>* node)
    {
        if(node->right != nil)
        {
            return Minimum(node->right);
        }
       
        RBNode<T>* parent = node->parent;
        while(parent != nil && parent->right == node)
        {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    RBNode<T>* Predecessor(RBNode<T>* node)
    {
        if(node->left != nil)
        {
            return Maximum(node->left);
        }
       
        RBNode<T>* parent = node->parent;
        while(parent != nil && parent->left == node)
        {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    void Print()
    {
        if(root == nil)
            cout << "Tree is empty!" << endl;
        else
            root->PrintTree(0);
    }
 
    void Delete(RBNode<T> *node)
    {
        RBNode<T>  *to_remove = nil, *to_save = nil;
        
        if(node->left == nil || node->right == nil) // Mark the node to be removed 
        {
            to_remove = node;
        }
        else
        {
            to_remove = Succesor(node);
        }
        
        if(to_remove->left != nil)   // Mark the succesor of that node
        {
            to_save = to_remove->left;
        }
        else
        {
            to_save = to_remove->right;
        }
    
        if(to_save != nil)                       // If there is a succesor, 
        {                                         // change the succesor parent 
            to_save->parent = to_remove->parent;  // to the parent of the node to be removed
        }
        
        if(to_remove->parent == nil)             // If the node to be removed is the root,
        {                                         // set the new root
            root = to_save;
        }
        else if(to_remove == to_remove->parent->left) // Else, set the parent of the node to be removed
        {                                             // to point at the new node
            to_remove->parent->left = to_save;
        }
        else
        {
            to_remove->parent->right = to_save;
        }

        if(to_remove->value != node->value)
        {
            node->value = to_remove->value;
        }
        
        delete to_remove;
    }
   
    void LeftRotate(RBNode<T> *node)
    {
        RBNode<T>* y = node->right;
        if (y == nil) return;
        
        node->right = y->left;                          // Turn y's left subtree into x's right subtree
        if(y->left != nil) y->left->parent = node;
        
        if (node->parent == nil)                        // Link x's parent to y
        {
            root = y;
            y->parent = nil;
        }
        else  if (node->parent->left == node) node->parent->left = y;
        else node->parent->right = y;
        y->parent = node->parent;
        
        node->parent = y;
        y->left = node;                                 // Put x on y's left
    }
    
    void RightRotate(RBNode<T> *node)
    {
        RBNode<T>* y = node->left;
        if (y == nil) return;
        
        node->left = y->right;                          // Turn y's right subtree into x's left subtree
        if(y->right != nil) y->right->parent = node;
        
        if (node->parent == nil)                        // Link x's parent to y
        {
            root = y;              
            y->parent = nil;
        }
        else  if (node->parent->left == node) node->parent->left = y;
        else node->parent->right = y;
        y->parent = node->parent;
        
        node->parent = y;
        y->right = node;                                 // Put x on y's right
    }
};


int main ()
{
    cout << "Testing an red-black tree." << endl;
    RBTree<> tree;

    cout << "Test if we can add elements:" << endl;
    tree.Insert(5); tree.Insert(10); tree.Insert(8); tree.Insert(7); tree.Insert(6); tree.Insert(3); tree.Insert(4); tree.Insert(2);

    cout << "Test if we can print the tree:" << endl;
    tree.Print();

    cout << "Inorder tree walk:"<<endl;
    tree.InorderTreeWalk(tree.Root());

    cout << endl << "Test if we can search the tree: " <<  tree.Search(10) << " " << tree.Search(22) << endl;
    cout << "Test tree minimun function: " << tree.Minimum(tree.Root())->value << endl
         << "Test tree maximum function: " << tree.Maximum(tree.Root())->value << endl;
    
    cout << "Test tree succesort function at root " << tree.Succesor(tree.Root())->value << endl
         << "Test tree predecessor fucntion at root " << tree.Predecessor(tree.Root())->value << endl;
    
    cout << "Left rotate at root:" << endl;
    tree.LeftRotate(tree.Root());
    tree.Print();

    cout << endl << "Left rotate at 3 :" << endl;
    tree.LeftRotate(tree.Search(3));
    tree.Print();
    
    cout << endl << "Right rotate at root :" << endl;
    tree.RightRotate(tree.Root());
    tree.Print();

    cout << endl << "Right rotate at 10 and then right rotate at 8 :" << endl;
    tree.RightRotate(tree.Search(10));
    tree.RightRotate(tree.Search(8));
    tree.Print();
    cout << "Test deletion at the root "<< endl;
    tree.Delete(tree.Root());
    tree.Print();
    
    cout << "Test deletion at 7" << endl;
    tree.Delete(tree.Search(7));
    tree.Print();

    cout << "Test deletion at 10" << endl;
    tree.Delete(tree.Search(10));
    tree.Print();

    cout << "Test deletion at 3" << endl;
    tree.Delete(tree.Search(3));
    tree.Print();    

    cout << "Test deletion at 6" << endl;
    tree.Delete(tree.Search(6));
    tree.Print();
    return 0;
}
