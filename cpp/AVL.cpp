#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
    int balanceFactor;

    Node(int value) : data(value), left(nullptr), right(nullptr), height(1), balanceFactor(0) {};

    ~Node() {}
};

struct myAVL {
    Node* root = nullptr;
};

int maxValue(int a, int b) {
    return a > b ? a : b;
}

int getHeight(Node* node) {
    return node ? node->height : 0;
}

int getBalanceFactor(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Node* createNode(int value) {
    return new Node(value);
}

Node* leftRotate(Node* node) {

    if (!node || !node->right)
    {
        return node;
    }

    Node* rightChild = node->right;
    Node* tmpTree = rightChild->left;

    rightChild->left = node;
    node->right = tmpTree;

    node->height = 1 + maxValue(getHeight(node->left), getHeight(node->right));
    rightChild->height = 1 + maxValue(getHeight(rightChild->left), getHeight(rightChild->right));

    node->balanceFactor = getBalanceFactor(node);
    rightChild->balanceFactor = getBalanceFactor(rightChild);

    return rightChild;
}

Node* rightRotate(Node* node) {

    if (!node || !node->left)
    {
        return node;
    } 

    Node* leftChild = node->left;
    Node* tmpTree = leftChild->right;

    leftChild->right = node;
    node->left = tmpTree;

    node->height = 1 + maxValue(getHeight(node->left), getHeight(node->right));
    leftChild->height = 1 + maxValue(getHeight(leftChild->left), getHeight(leftChild->right));

    node->balanceFactor = getBalanceFactor(node);
    leftChild->balanceFactor = getBalanceFactor(leftChild);

    return leftChild;
}

Node* balance(Node* root) {
    if (!root)
    {
        return root;
    }

    root->height = 1 + maxValue(getHeight(root->left), getHeight(root->right));
    root->balanceFactor = getBalanceFactor(root);

    if (root->balanceFactor > 1 && getBalanceFactor(root->left) >= 0)
    {
        return rightRotate(root);
    }
        
    if (root->balanceFactor > 1 && getBalanceFactor(root->left) < 0) 
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    if (root->balanceFactor < -1 && getBalanceFactor(root->right) <= 0)
    {
        return leftRotate(root);
    }
        
    if (root->balanceFactor < -1 && getBalanceFactor(root->right) > 0) 
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


Node* insert(Node* root, int value) {
    if(!root)
    {
        return createNode(value);
    }

    if(value < root->data)
    {
        root->left = insert(root->left, value);
    }
    else if(value > root->data)
    {
        root->right = insert(root->right, value);
    }
    else
    {
        return root;
    }

    return balance(root);
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while(current && current->left)
    {
        current = current->left;
    }

    return current;
}

Node* deleteNode(Node* root, int value) {
    if(!root)
    {
        return root;
    }

    if(value < root->data)
    {
        root->left = deleteNode(root->left, value);
    }
    else if(value > root->data)
    {
        root->right = deleteNode(root->right, value);
    }
    else
    {
        if(!root->left || !root->right)
        {
            Node* tmp = root->left ? root->left : root->right;
            
            if(!tmp)
            {
                tmp = root;
                root = nullptr;
            }
            else
            {
                *root = *tmp;
            }
            delete tmp;
        }
        else
        {
            Node* tmp = minValueNode(root->right);
            root->data = tmp->data;
            root->right = deleteNode(root->right, tmp->data);
        }
    }

    if(!root)
    {
        return nullptr;
    }

    return balance(root);
}

Node* search(Node* root, int value) {
    if(!root || root->data == value)
    {
        return root;
    }

    if(value < root->data)
    {
        return search(root->left, value);
    }
    else
    {
        return search(root->right, value);
    }
}

void inOrderPrint(Node* root) {
    if(!root)
    {
        return;
    }

    inOrderPrint(root->left);
    cout << root->data << " ";
    inOrderPrint(root->right);
}

void clean(Node* root) {
    
    if(root == nullptr)
    {
        return;
    }
    clean(root->left);
    clean(root->right);
    delete root;
}

int main() {
    myAVL tree;
    tree.root = insert(tree.root, 10);
    tree.root = insert(tree.root, 20);
    tree.root = insert(tree.root, 5);
    tree.root = insert(tree.root, 6);
    tree.root = insert(tree.root, 15);
    inOrderPrint(tree.root);
    cout << endl;

    tree.root = deleteNode(tree.root, 20);
    cout << "After deletion (in-order): ";
    inOrderPrint(tree.root);

    Node* found = search(tree.root, 15);
    if (found)
        cout << "Found: " << found->data << "\n";
    else
        cout << "Not found\n";

    clean(tree.root); // очистка памяти
    tree.root = nullptr;

    return 0;
}