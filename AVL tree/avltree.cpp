#include<bits/stdc++.h>

using namespace std;

class Node {
private:
    int key;
    Node *left;
    Node *right;
    int height;

public:
    Node(int key) {
        this->key = key;
        this->left = NULL;
        this->right = NULL;
        this->height = 0;
    }

    void setKey(int key) {
        this->key = key;
    }

    void setLeft(Node *left) {
        this->left = left;
    }

    void setRight(Node *right) {
        this->right = right;
    }

    void setHeight(int height) {
        this->height = height;
    }

    int getKey() {
        return key;
    }

    Node *getLeft() {
        return left;
    }

    Node *getRight() {
        return right;
    }

    int getHeight() {
        return height;
    }
};

class AVLTree {
private:
    Node *root;
    bool isHeightInvariantViolated;

    int maxChildHeight(Node *left, Node *right) {
        if(left == NULL && right == NULL) {
            return -1;
        } else if(left == NULL) {
            return right->getHeight();
        } else if(right == NULL) {
            return left->getHeight();
        }
        int leftH = left->getHeight();
        int rightH = right->getHeight();
        return leftH > rightH ? leftH : rightH;
    }

    // 0 -> none
    // 1 -> zig
    // 2 -> zag
    int isZigZag(Node *node) {
        if(node->getRight() == NULL && node->getLeft() == NULL)
            return 0;
        else if(node->getRight() == NULL)
            return 1;
        else if(node->getLeft() == NULL)
            return 2;

        return node->getLeft()->getHeight() >= node->getRight()->getHeight() ? 1 : 2;
    }

    Node* rightRotate(Node *node) {


        Node *newRoot = node->getLeft();
        Node *temp = newRoot->getRight();

        newRoot->setRight(node);
        node->setLeft(temp);

        node->setHeight(1 + maxChildHeight(node->getLeft(), node->getRight()));
        newRoot->setHeight(1 + maxChildHeight(newRoot->getLeft(), newRoot->getRight()));

        return newRoot;
    }

    Node* leftRotate(Node *node) {
        Node *newRoot = node->getRight();
        Node *temp = newRoot->getLeft();

        newRoot->setLeft(node);
        node->setRight(temp);


        node->setHeight(1 + maxChildHeight(node->getLeft(), node->getRight()));
        newRoot->setHeight(1 + maxChildHeight(newRoot->getLeft(), newRoot->getRight()));

        return newRoot;
    }

    Node* balance(Node *node) {

        if (isZigZag(node) == 1 && isZigZag(node->getLeft()) == 1)
        {
            return rightRotate(node);
        }
        if (isZigZag(node) == 2 && isZigZag(node->getRight()) == 2)
        {
            return leftRotate(node);
        }
        if (isZigZag(node) == 1 && isZigZag(node->getLeft()) == 2)
        {
            node->setLeft(leftRotate(node->getLeft()));
            return rightRotate(node);
        }
        if (isZigZag(node) == 2 && isZigZag(node->getRight()) == 1)
        {
            node->setRight(rightRotate(node->getRight()));
            return leftRotate(node);
        }

        node->setHeight(1 + maxChildHeight(node->getLeft(), node->getRight()));
        return node;
    }

    int getBalanceFactor(Node *node) {
        Node *left = node->getLeft();
        Node *right = node->getRight();

        if(left == NULL && right == NULL) {
            return 0;
        } else if(right == NULL) {
            return left->getHeight() + 1;
        } else if(left == NULL) {
            return -right->getHeight() - 1;
        }

        return left->getHeight() - right->getHeight();
    }

    Node* insert(Node *node, int key) {
        if(node == NULL) {
            return new Node(key);
        }

        if(key > node->getKey()){
            node->setRight(insert(node->getRight(), key));
        }
        else if(key < node->getKey()) {
            node->setLeft(insert(node->getLeft(), key));
        }
        else
            return node;

        int maxHeight = maxChildHeight(node->getLeft(), node->getRight());
        node->setHeight(1 + maxHeight);

        int balanceFactor = getBalanceFactor(node);

        if(abs(balanceFactor) > 1) {
            isHeightInvariantViolated = true;
            return balance(node);
        }

        return node;
    }

    Node* minInSubTree(Node *node)
    {
        Node *current = node;

        while (current->getLeft() != NULL)
            current = current->getLeft();

        return current;
    }

    Node* deleteNode(Node *node, int key) {
        if(node == NULL)
            return node;

        if(key < node->getKey()) {
            node->setLeft(deleteNode(node->getLeft(), key));
        } else if (key > node->getKey()) {
            node->setRight(deleteNode(node->getRight(), key));
        } else {
            if(node->getLeft() == NULL || node->getRight() == NULL) {
                Node *temp = node->getLeft() ? node->getLeft() : node->getRight();

                if(temp == NULL) {
                    temp = node;
                    node = NULL;
                } else {
                    *node = *temp;
                }

                free(temp);
            } else {
                Node *temp = minInSubTree(node->getRight());
                node->setKey(temp->getKey());

                node->setRight(deleteNode(node->getRight(), temp->getKey()));
            }
        }

        if(node == NULL)
            return node;

        node->setHeight(1 + maxChildHeight(node->getLeft(), node->getRight()));

        int balanceFactor = getBalanceFactor(node);

        if(abs(balanceFactor) > 1) {
            isHeightInvariantViolated = true;
            return balance(node);
        }

        return node;
    }

    bool find(Node *node, int key) {
        if(node == NULL) {
            return false;
        }

        int currentKey = node->getKey();
        if (key == currentKey) {
            return true;
        } else if(key > currentKey) {
            return find(node->getRight(), key);
        } else {
            return find(node->getLeft(), key);
        }
    }

public:
    AVLTree() {
        root = NULL;
        isHeightInvariantViolated = false;
    }

    AVLTree (int key) : AVLTree() {
        root = new Node(key);
    }

    void printTree(Node *root) {
        if(root != NULL) {
            cout << root->getKey();
            if(root->getLeft() == NULL && root->getRight() == NULL) {
                return;
            }
            cout << '(';
            printTree(root->getLeft());
            cout << ")(";
            printTree(root->getRight());
            cout << ')';
        }
    }

    void insert(int key) {
        root = insert(root, key);

        if(isHeightInvariantViolated) {
            cout << "Height invariant violated." << endl;
            isHeightInvariantViolated = false;
            cout << "After rebalancing: ";
        }

        printTree(root);
        cout << endl;
    }

    void deleteKey(int key) {
        root = deleteNode(root, key);

        if (isHeightInvariantViolated)
        {
            cout << "Height invariant violated." << endl;
            isHeightInvariantViolated = false;
            cout << "After rebalancing: ";
        }

        printTree(root);
        cout << endl;
    }

    bool find(int key) {
        return find(root, key);
    }
};

int main() {
    AVLTree bst;

    char c;
    int n;

    freopen("tree.in", "r", stdin);

    while(!feof(stdin)) {
        cin >> c >> n;
        switch(c) {
            case 'F':
                if(bst.find(n))
                    cout << "True" << endl;
                else
                    cout << "False" << endl;
                break;
            case 'I':
                bst.insert(n);
                break;
            case 'D':
                bst.deleteKey(n);
                break;
            default:
                break;
        }
    }
    return 0;
}
