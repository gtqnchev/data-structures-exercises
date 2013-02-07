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

    Node<T>* Search(T value)
    {
	Node<T>* current = root;
	while(current != NULL && current->value != value)
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

    Node<T>* Minimum(Node<T>* node)
    {
        while(node->left != NULL)
        {
            node = node->left;
        }
        return node;
    }

    Node<T>* Maximum(Node<T>* node)
    {
        while(node->right != NULL)
        {
            node = node->right;
        }
        return node;
    }
    
    Node<T>* Succesor(Node<T>* node)
    {
        if(node->right != NULL)
        {
            return Minimum(node->right);
        }
       
        Node<T>* parent = node->parent;
        while(parent != NULL && parent->right == node)
        {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }


    Node<T>* Predecessor(Node<T>* node)
    {
        if(node->left != NULL)
        {
            return Maximum(node->left);
        }
       
        Node<T>* parent = node->parent;
        while(parent != NULL && parent->left == node)
        {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    void Print()
    {
        if(root == NULL)
            cout << "Tree is empty!" << endl;
        else
            root->PrintTree(0);
    }
 
    void Delete(Node<T>* node)
    {
        Node<T>  *to_remove = NULL, *to_save = NULL;
  
        if(node->left == NULL || node->right == NULL)
        {
            to_remove = node;
        }
        else
        {
            to_remove = Succesor(node);
        }
        
        if(to_remove->left != NULL)
        {
            to_save = to_remove->left;
        }
        else
        {
            to_save = to_remove->right;
        }
    
        if(to_save != NULL)
        {
            to_save->parent = to_remove->parent;
        }
        
        if(to_remove->parent == NULL)
        {
            root = to_save;
        }
        else if(to_remove == to_remove->parent->left)
        {
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
};


int main ()
{
    cout << "Testing an ordered tree." << endl;
    OrdTree<> tree;

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
