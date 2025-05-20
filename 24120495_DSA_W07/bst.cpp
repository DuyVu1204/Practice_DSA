#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct NODE;
NODE* Search(NODE* pRoot, int x);//find node
void Insert(NODE*& pRoot, int x);// add node into tree
NODE* findMinNode(NODE* pRoot);// find the smallest node on the right
NODE* removeNode(NODE*& pRoot, int x);// delete node in tree rrturn root tree
void Remove(NODE*& pRoot, int x);// delete node in tree 
NODE* createTree(int a[], int n); // create tree based array
void removeTree(NODE*& pRoot); // remove tree
int Height(NODE* pRoot);// height tree
int countLess(NODE* pRoot, int x);// sum of elements with value less than that node
int countGreater(NODE* pRoot, int x);// sum of elements with value greater than that node
bool checkisBST(NODE* pRoot, NODE*& prev);// check tree is binary search tree
bool isBST(NODE* pRoot);// check tree is binary search tree
bool isFullBST(NODE* pRoot);// check tree is full binary search tree

struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
};

NODE* Search(NODE* pRoot, int x)
{
    if (pRoot == nullptr)
        return nullptr;
    if (pRoot->key == x)
        return pRoot;
    if (x < pRoot->key)
        return Search(pRoot->p_left, x);
    else
        return Search(pRoot->p_right, x);
}

void Insert(NODE*& pRoot, int x)
{
    if (pRoot == nullptr)
    {
        NODE* newNode = new NODE();
        newNode->key = x;
        newNode->p_left = nullptr;
        newNode->p_right = nullptr;
        pRoot = newNode;
    }
    else
    {
        if (x < pRoot->key)// x < value pRoot then add recursive left
        {
            Insert(pRoot->p_left, x);
        }
        else if (x>pRoot->key)// x > pRoot->key then add to right
        {
            Insert(pRoot->p_right, x);
        }
        // else x==value pRoot then skip
    }
}

NODE* findMinNode(NODE* pRoot) {
    if (pRoot == nullptr)
        return nullptr;
    while (pRoot->p_left != nullptr)
        pRoot = pRoot->p_left;//run to the left node
    return pRoot;
}

NODE* removeNode(NODE*& pRoot, int x) {
    if (pRoot == nullptr)
        return nullptr;
    if (x < pRoot->key)// if x < value root
        pRoot->p_left = removeNode(pRoot->p_left, x);//pointer recursive root left
    else if (x > pRoot->key)// if x > value root
        pRoot->p_right = removeNode(pRoot->p_right, x);// pointer recursive root right
    else
    {
        // case 1: node leaf
        if (pRoot->p_left == nullptr && pRoot->p_right == nullptr)
        {
            delete pRoot;
            return nullptr;
        }
        // case 2: node 1 child
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
        // case 3: node 2 chile
        NODE* tmp = findMinNode(pRoot->p_right);// Find the leftmost right node
        pRoot->key = tmp->key;// The node to be deleted has the same value as the node just found.
        pRoot->p_right = removeNode(pRoot->p_right, tmp->key);// delete the leftmost node
    }
    return pRoot;
}

void Remove(NODE*& pRoot, int x)
{
    pRoot = removeNode(pRoot, x);// call function  removeNode
}

NODE* createTree(int a[], int n) {
    NODE* pRoot = nullptr;// create node pRoot
    for (int i = 0; i < n; i++)
    {
        Insert(pRoot, a[i]);// use loop insert node
    }
    return pRoot;
}

void removeTree(NODE*& pRoot) {
    // Browse post-order delete each node
    if (pRoot == nullptr)
        return;
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);

    delete pRoot;// delete each node
    pRoot = nullptr;// avoid junk node
}

int Height(NODE* pRoot)
{
    if (pRoot == nullptr)
        return -1;
    return 1 + max(Height(pRoot->p_left), Height(pRoot->p_right));
}

int countLess(NODE* pRoot, int x)
{
    // Browse breath first search 
    if (pRoot == nullptr) 
    return 0;

    int count = 0;
    queue<NODE*> q;
    q.push(pRoot);
    while (!q.empty()) 
    {
        NODE* cur = q.front(); 
        q.pop();

        if (cur->key < x) 
        count++;// check condition
        if (cur->p_left) q.push(cur->p_left);
        if (cur->p_right) q.push(cur->p_right);
    }
    return count;
}

int countGreater(NODE* pRoot, int x)
{
    // Browse breath first search 
    if (pRoot == nullptr) 
    return 0;

    int count = 0;
    queue<NODE*> q;
    q.push(pRoot);
    while (!q.empty()) 
    {
        NODE* cur = q.front(); 
        q.pop();

        if (cur->key > x) 
        count++;// check condition
        if (cur->p_left) q.push(cur->p_left);
        if (cur->p_right) q.push(cur->p_right);
    }
    return count;
}

bool checkisBST(NODE* pRoot, NODE*& prev) {
    if (pRoot == nullptr)
        return true;
    if (!checkisBST(pRoot->p_left, prev))// left branch test
        return false;
    if (prev != nullptr && pRoot->key <= prev->key)// If the previous node is smaller than the left node, return false.
        return false;
    prev = pRoot;// for the following node
    return checkisBST(pRoot->p_right, prev);// check right branch test
}

bool isBST(NODE* pRoot)
{
    NODE* prev = nullptr;// create node nullptr
    return checkisBST(pRoot, prev);
}

bool isFullBST(NODE* pRoot)
{
    if (pRoot == nullptr)
        return true;
    if (pRoot->p_left == nullptr && pRoot->p_right == nullptr)// if node 2 child return true
        return true;
    if (pRoot->p_left != nullptr && pRoot->p_right != nullptr)
        return isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);// call recursive root left and right
    return false;
}
