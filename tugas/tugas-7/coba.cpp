#include <bits/stdc++.h>
using namespace std;

struct BSTNode
{
    BSTNode *left, *right;
    int key;
};

/* uniqueBST */

struct BST
{
    // Member
    BSTNode *_root;
    unsigned int _size;

    // Function
    void init()
    {
        _root = NULL;
        _size = 0u;
    }

    bool isEmpty()
    {
        return _root == NULL;
    }

    bool find(int value)
    {
        BSTNode *temp = __search(_root, value);
        if (!temp)
            return false;

        if (temp->key == value)
            return true;
        else
            return false;
    }

    void insert(int value)
    {
        if (!find(value))
        {
            _root = __insert(_root, value);
            _size++;
        }
    }

    void remove(int value)
    {
        if (find(value))
        {
            _root = __remove(_root, value);
            _size++;
        }
    }

    void traverseInorder()
    {
        __inorder(_root);
    }

    void traversePreorder()
    {
        __preorder(_root);
    }

    void traversePostorder()
    {
        __postorder(_root);
    }

private:
    // Utility Function
    BSTNode *__createNode(int value)
    {
        BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
        newNode->key = value;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    BSTNode *__search(BSTNode *root, int value)
    {
        while (root != NULL)
        {
            if (value < root->key)
                root = root->left;
            else if (value > root->key)
                root = root->right;
            else
                return root;
        }
        return root;
    }

    BSTNode *__insert(BSTNode *root, int value)
    {
        if (root == NULL)
            return __createNode(value);

        if (value < root->key)
            root->left = __insert(root->left, value);
        else if (value > root->key)
            root->right = __insert(root->right, value);

        return root;
    }

    BSTNode *__findMinNode(BSTNode *node)
    {
        BSTNode *currNode = node;
        while (currNode && currNode->left != NULL)
            currNode = currNode->left;

        return currNode;
    }

    BSTNode *__remove(BSTNode *root, int value)
    {
        if (root == NULL)
            return NULL;

        if (value > root->key)
            root->right = __remove(root->right, value);
        else if (value < root->key)
            root->left = __remove(root->left, value);
        else
        {

            if (root->left == NULL)
            {
                BSTNode *rightChild = root->right;
                free(root);
                return rightChild;
            }
            else if (root->right == NULL)
            {
                BSTNode *leftChild = root->left;
                free(root);
                return leftChild;
            }

            BSTNode *temp = __findMinNode(root->right);
            root->key = temp->key;
            root->right = __remove(root->right, temp->key);
        }
        return root;
    }

    void __inorder(BSTNode *root)
    {
        if (root)
        {
            __inorder(root->left);
            printf("%d ", root->key);
            __inorder(root->right);
        }
    }

    void __postorder(BSTNode *root)
    {
        if (root)
        {
            __postorder(root->left);
            __postorder(root->right);
            printf("%d ", root->key);
        }
    }

    void __preorder(BSTNode *root)
    {
        if (root)
        {
            printf("%d ", root->key);
            __preorder(root->left);
            __preorder(root->right);
        }
    }
};

int sum = 0;

void internalNode(BSTNode *root, int level)
{
    if (root == NULL)
    {
        return;
    }

    sum += level;
    internalNode(root->left, level + 1);
    internalNode(root->right, level + 1);
}

int internalNode2(BSTNode *root)
{
    queue<BSTNode *> arr;

    int sumInternal = 0;
    int level = 0;

    arr.push(root);

    while (!arr.empty())
    {
        int len = arr.size();
        for (int i = 0; i < len; i++)
        {
            BSTNode *curr = arr.front();
            arr.pop();

            sumInternal += level;

            if (curr->left != NULL)

                arr.push(curr->left);

            if (curr->right != NULL)

                arr.push(curr->right);
        }
        level++;
    }

    return sumInternal;
}

int searchGreater(BSTNode *root, int key)
{
    if (root == NULL)
        return -1;

    if (root->key > key)
    {
        int leftResult = searchGreater(root->left, key);
        if (leftResult != -1)
            return leftResult;

        return root->key;
    }
    else

        return searchGreater(root->right, key);
}

int main()
{
    int count = 0;

    BST tree;

    tree.init();

    tree.insert(56);
    tree.insert(30);
    tree.insert(61);
    tree.insert(13);
    tree.insert(39);

    internalNode(tree._root, 0);

    int result = searchGreater(tree._root, 35);

    cout << result << endl;
}