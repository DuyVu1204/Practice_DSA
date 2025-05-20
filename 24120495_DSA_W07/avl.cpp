#include <iostream>
#include <algorithm>

using namespace std;

struct NODE;
NODE* createNode(int data);
int getHeight(NODE* node);
int getBalance(NODE* node);
NODE* rotateRight(NODE* Y);
NODE* rotateLeft(NODE* X);
NODE* insert(NODE*& pRoot, int x);
void Insert(NODE*& pRoot, int x);
NODE* minValueNode(NODE* pRoot);
NODE* remove(NODE*& pRoot, int x);
void  Remove(NODE*& pRoot, int x);
bool isAVL(NODE* pRoot);//AVL tree check


struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};

NODE* createNode(int data) {
    NODE* newNode = new NODE();
    newNode->key = data;
    newNode->p_left = nullptr;
    newNode->p_right = nullptr;
    newNode->height = 0;
    return newNode;
}

int getHeight(NODE* node) {
    return node ? node->height : -1;
}

int getBalance(NODE* node) {
    if (!node)
        return -1;
    return getHeight(node->p_left) - getHeight(node->p_right);// height left - height right
}

NODE* rotateRight(NODE* Y) {
    NODE* X = Y->p_left;
    NODE* Z = X->p_right;

    X->p_right = Y;
    Y->p_left = Z;

    Y->height = 1 + max(getHeight(Y->p_left), getHeight(Y->p_right));
    X->height = 1 + max(getHeight(X->p_left), getHeight(X->p_right));
    return X;
}

NODE* rotateLeft(NODE* X) {
    NODE* Y = X->p_right;
    NODE* Z = Y->p_left;

    Y->p_left = X;
    X->p_right = Z;

    X->height = 1 + max(getHeight(X->p_left), getHeight(X->p_right));
    Y->height = 1 + max(getHeight(Y->p_left), getHeight(Y->p_right));
    return Y;
}

NODE* insert(NODE*& pRoot, int x) {
    if (pRoot == nullptr)
        return createNode(x);

    if (x < pRoot->key)
        pRoot->p_left = insert(pRoot->p_left, x);
    else if (x > pRoot->key)
        pRoot->p_right = insert(pRoot->p_right, x);
    else
        return pRoot;

    pRoot->height = 1 + max(getHeight(pRoot->p_left), getHeight(pRoot->p_right));
    int balance = getBalance(pRoot);
    
    //rotate right
    if (balance >1 && getBalance(pRoot->p_left) >= 0)
        return rotateRight(pRoot);

    //rotate left
    if (balance < -1 && getBalance(pRoot->p_right) <= 0)
        return rotateLeft(pRoot);

    //rotate left right
    if (balance > 1 && getBalance(pRoot->p_left) < 0)
    {
        pRoot->p_left = rotateLeft(pRoot->p_left);
        return rotateRight(pRoot);
    }

    //rotate right left
    if (balance < -1 && getBalance(pRoot->p_right) > 0)
    {
        pRoot->p_right = rotateRight(pRoot->p_right);
        return rotateLeft(pRoot);
    }
    return pRoot;
}

void Insert(NODE*& pRoot, int x) {
    pRoot=insert(pRoot, x);
}

NODE* minValueNode(NODE* pRoot) {
    while (pRoot->p_left != nullptr)
        pRoot = pRoot->p_left;
    return pRoot;
}

NODE* remove(NODE*& pRoot, int x) {
    if (pRoot == nullptr)
        return pRoot;

    if (x < pRoot->key)
        pRoot->p_left = remove(pRoot->p_left, x);
    else if (x > pRoot->key)
        pRoot->p_right = remove(pRoot->p_right, x);
    else
    {
        if (pRoot->p_left == nullptr && pRoot->p_right == nullptr)
        {
            delete pRoot;
            return nullptr;
        }
        if (pRoot->p_left != nullptr && pRoot->p_right == nullptr)
        {
            NODE* tmp = pRoot->p_left;
            delete pRoot;
            return tmp;
        }
        if (pRoot->p_left == nullptr && pRoot->p_right != nullptr)
        {
            NODE* tmp = pRoot->p_right;
            delete pRoot;
            return tmp;

        }
        NODE* tmp = minValueNode(pRoot->p_right);
        pRoot->key = tmp->key;
        pRoot->p_right = remove(pRoot->p_right, tmp->key);
    }
    if (pRoot == nullptr)
        return pRoot;

    pRoot->height = 1 + max(getHeight(pRoot->p_left), getHeight(pRoot->p_right));
    int balance = getBalance(pRoot);

    if (balance > 1 && getBalance(pRoot->p_left) >= 0)
        return rotateRight(pRoot);

    if (balance > 1 && getBalance(pRoot->p_left) < 0)
    {
        pRoot->p_left = rotateLeft(pRoot->p_left);
        return rotateRight(pRoot);
    }

    if (balance < -1 && getBalance(pRoot->p_right) <= 0)
        return rotateLeft(pRoot);

    if (balance < -1 && getBalance(pRoot->p_right) > 0)
    {
        pRoot->p_right = rotateRight(pRoot->p_right);
        return rotateLeft(pRoot);
    }
    return pRoot;
}

void  Remove(NODE*& pRoot, int x) {
    pRoot=remove(pRoot, x);
}

bool isAVL(NODE* pRoot) {
    if (pRoot == nullptr)
        return true;
    int balance = getBalance(pRoot);

    if (balance < -1 || balance>1)// check height left right
        return false;
    return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}
