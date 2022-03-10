#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
How indexing will work:
User will input a vector {a, b} where a represents the 'level' the node trying to be accessed is relative to the root node.
Example: Consider the tree
        A
    B       C
D     E   F    G

Node D will be index {2, 0} because is the 0th index in the 2nd level relative to the root node (Note: We say that the level where the Root node is is 0)
With this clarification, we can now say that the root node A is in index {0, 0}. What I will now call the origin position.

With this, we can also say that for any level a => b = 2^a. Thus, if the user inputs a value such that c > 2^a, we can return an error.
*/

// Defining classs node.

template <typename T>
struct TreeNode {
    TreeNode<T> *Left;
    TreeNode<T> *Right;
    T val;
};

template <typename U>
class Tree {
private:
    TreeNode<U> *Root;

    vector<int> CreatePath(vector<int>& position) {
        //to find the position for the parent node, we notice that its position is the quotiend of the child's position divided by 2.
        vector<int> parent_position{position[1]};
        int tmp_pos = position[1];

        for(int level = position[0]; level > 0; level--) {
            parent_position.push_back(tmp_pos / 2);
            tmp_pos /= 2;
        }

        return parent_position;
    }

    TreeNode<U> *FindNode(vector<int> &index)
    {
        // Check if b >= 2^a.
        if (index[1] >= pow(2, index[0]))
        {
            cout << "Error: Index out of bounds.";
            return nullptr;
        }

        // To actually find the index, we just need to create the path from the root to the node to find it.
        // To create this path we recursively ask who is the parent of this child until arriving to the root.
        // This path will tell you the index of each parent node relative to its level. It is nice to say that by using this index system
        // a side effect is that any right node will have an odd index and any left node an even index. We can use this logic to find the next node.

        vector<int> Path = CreatePath(index);

        // Finding if we need to go to the left or right according to this path.

        TreeNode<U> *follow_ptr;
        follow_ptr = Root;

        for (int level = Path.size() - 1; level > 0; level--)
        {

            if (Path[level] % 2 == 1 && follow_ptr->Left != nullptr)
            {
                follow_ptr = follow_ptr->Left;
            }
            else if (Path[level] % 2 == 0 && follow_ptr->Right != nullptr)
            {
                follow_ptr = follow_ptr->Right;
            }
            else
            {
                cout << "Error: Parent node has not been created." << endl;
                return nullptr;
            }
        }

        return follow_ptr;
    }
public:
    Tree(U value) {
        // Initializing Root node and all its variables.
        Root = new TreeNode<U>;
        Root->val = value;
        Root->Left = nullptr;
        Root->Right = nullptr;
    }

    void PrintNode(vector<int> &index) {
        TreeNode<U> *ptr;
        ptr = FindNode(index);

        if(ptr == nullptr) {
            return;
        }

        cout << ptr->val << endl;
    }

    void ChangeValue(vector<int> &index, int value) {
        TreeNode<U> *ptr;
        ptr = FindNode(index);

        if (ptr == nullptr)
        {
            return;
        }

        ptr->val = value;
    }

};

int main() {
    int root_value = 10;
    int level, index;

    cout << "Enter level: ";
    cin >> level;
    cout << "Enter index: ";
    cin >> index;
    cout << endl;

    vector<int> Nodeindex{level, index};
    Tree<int> Test(root_value);
    Test.PrintNode(Nodeindex);
    Test.ChangeValue(Nodeindex, 23);
    Test.PrintNode(Nodeindex);
}