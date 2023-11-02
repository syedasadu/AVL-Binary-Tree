#include<iostream>
using namespace std;


class Node 
{
public:
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree 
{
private:
    Node* root;

    int getHeight(Node* node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int getBalanceFactor(Node* node)
    {
        if (node == nullptr) 
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(Node* node) 
    {
        if (node)
        {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }

    Node* rotateRight(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* insert(Node* node, int key)
    {
        if (node == nullptr) 
            return new Node(key);

        if (key < node->key)
        {
            node->left = insert(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = insert(node->right, key);
        }
        else 
        {
            // Duplicate keys are not allowed in this example.
            return node;
        }

        updateHeight(node);

        int balance = getBalanceFactor(node);

        // Left-Left case
        if (balance == 2 && key < node->left->key)
        {
            return rotateRight(node);
        }
        // Right-Right case
        if (balance == -2 && key > node->right->key)
        {
            return rotateLeft(node);
        }
        // Left-Right case
        if (balance == 2 && key > node->left->key) 
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // Right-Left case
        if (balance == -2 && key < node->right->key)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* minValueNode(Node* node)
    {
        Node* current = node;
        while (current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }

    Node* deleteNode(Node* node, int key)
    {
        if (node == nullptr) return node;

        if (key < node->key)
        {
            node->left = deleteNode(node->left, key);
        }
        else if (key > node->key) 
        {
            node->right = deleteNode(node->right, key);
        }
        else 
        {
            if ((node->left == nullptr) || (node->right == nullptr)) 
            {
                Node* temp = (node->left) ? node->left : node->right;

                if (temp == nullptr) 
                {
                    temp = node;
                    node = nullptr;
                }
                else 
                {
                    *node = *temp;
                }

                delete temp;
            }
            else 
            {
                Node* temp = minValueNode(node->right);
                node->key = temp->key;
                node->right = deleteNode(node->right, temp->key);
            }
        }

        if (node == nullptr) 
            return node;

        updateHeight(node);

        int balance = getBalanceFactor(node);

        // Left-Left case
        if (balance == 2 && getBalanceFactor(node->left) >= 0)
        {
            return rotateRight(node);
        }
        // Right-Right case
        if (balance == -2 && getBalanceFactor(node->right) <= 0) 
        {
            return rotateLeft(node);
        }
        // Left-Right case
        if (balance == 2 && getBalanceFactor(node->left) < 0) 
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // Right-Left case
        if (balance == -2 && getBalanceFactor(node->right) > 0) 
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inorderTraversal(Node* node) 
    {
        if (node == nullptr) return;
        inorderTraversal(node->left);
        std::cout << node->key << " ";
        inorderTraversal(node->right);
    }
    void print2D(Node* r, int space = 0)
    {
        if (r == NULL)
            return;
        space += 5; // Increase the spacing

        // Recursively print the right child with increased spacing
        print2D(r->right, space);

        // Print the current node with the appropriate spacing
        cout << endl;
        for (int i = 5; i < space; i++)
            cout << " ";
        cout << r->key << "\n";

        // Recursively print the left child with increased spacing
        print2D(r->left, space);
    }
public:
    AVLTree() : root(nullptr) {}

    void insert(int key) 
    {
        root = insert(root, key);
    }

    void remove(int key)
    {
        root = deleteNode(root, key);
    }
    

    void printInorder()
    {
        print2D(root);
    }
};

int main() {
    AVLTree avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25); // Unbalanced insert

    cout << "Inorder traversal of the AVL tree: ";
    avl.printInorder();
    cout << endl;

    avl.remove(30);

    cout << "Inorder traversal after deleting 30: ";
    avl.printInorder();
    cout << endl;
    avl.remove(40);

    cout << "Inorder traversal after deleting 30: ";
    avl.printInorder();
    cout << endl;

    return 0;
}
