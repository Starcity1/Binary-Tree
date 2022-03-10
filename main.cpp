#include <iostream>

using namespace std;

//Defining classs node.

template<typename T>
struct TreeNode{
    TreeNode<T> *Left;
    TreeNode<T> *Right;
    T val;
};

template<typename U>
class Tree {

private:
    TreeNode<U> *Root;
public:

    Tree(U value) {
        //Initializing Root node and all its variables.
        Root = new TreeNode<U>;
        Root->val = value;
        Root->Left = NULL;
        Root->Right = NULL;
    }

    void PrintRoot() {
        cout << Root->val << endl;
    }

    void PrintTree() {
        cout << Root->val << endl;

        TreeNode<U> *tmp_ptr = Root->Left;

        if(tmp_ptr != nullptr) {
            cout << tmp_ptr->val << endl;
        } else {
            cout << "Left children of parent is not initialized!." << endl;
        }

        tmp_ptr = Root->Right;

        if(tmp_ptr != nullptr) {
            cout << tmp_ptr->val << endl;
        } else {
            cout << "Right children of parent is not initialized!." << endl;
        }
        
    }

    void CreateChildren(U right_value, U left_value) {
        //Creating pointers for left and right nodes.
        TreeNode<U> *Right_Node, *Left_Node;
        Right_Node = new TreeNode<U>;
        Left_Node = new TreeNode<U>;

        Right_Node->val = right_value;
        Left_Node->val = left_value;

        Right_Node->Right = Right_Node->Left = Left_Node->Left = Left_Node->Right = nullptr;

        Root->Right = Right_Node;
        Root->Left = Left_Node;
    }
};

int main() {
    int root_value = 10;
    Tree<int> Test(root_value);

    Test.PrintRoot();
    Test.PrintTree();
    Test.CreateChildren(30, 20);
    Test.PrintTree();
}