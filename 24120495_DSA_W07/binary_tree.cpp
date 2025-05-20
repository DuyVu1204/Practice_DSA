#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

struct NODE;
NODE* createNode(int data);//create Node tree
vector<int> NLR(NODE* pRoot);// Browse node left right
vector<int> LNR(NODE* pRoot);// Browse left node right
vector<int> LRN(NODE* pRoot);// Browse left right node
void LevelOrderec(NODE* pRoot, int level, vector<vector<int>>& res);// Helper function to find level of each node using recursion
vector<vector<int>> LevelOrder(NODE* pRoot);//return vector level of tree
int countNode(NODE* pRoot);// count node of tree
int sumNode(NODE* pRoot);// sum of values ​​of nodes of tree
int height(NODE* pRoot);// calculate tree height
NODE* Search(NODE* pRoot, int value);// search node based on the return value of that node pointer
int heightNode(NODE* pRoot, int value);// calculate height of node in tree
int Level(NODE* pRoot, NODE* p);// return value level of node
int countLeaf(NODE* pRoot);// Returns the number of leaf nodes in the tree


struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
};

NODE* createNode(int data)
{
    NODE* newNode = new NODE();
    newNode->key = data;
    newNode->p_left = nullptr;
    newNode->p_right = nullptr;
    return newNode;
}

vector<int> NLR(NODE* pRoot)
{
    vector<int> Browse;// create vector
    if (pRoot == nullptr)// if the tree is hollow 
        return Browse; //return nullptr
    stack<NODE*> s;// create stack
    s.push(pRoot);// push root of tree
    while (!s.empty())// browse until empty stack
    {
        NODE* tmp = s.top();// get top node of stack into tmp
        s.pop();// remove from top of stack

        Browse.push_back(tmp->key);//add value tmp vector
        if (tmp->p_right != nullptr) s.push(tmp->p_right);// add node right tmp into stack
        if (tmp->p_left != nullptr) s.push(tmp->p_left);// add node left tmp into stack
    }
    return Browse;// return vector saved values type node left right
}

vector<int> LNR(NODE* pRoot)
{
    vector<int> Browse;
    if (pRoot == nullptr)
        return Browse;
    stack<NODE*> s;// create stack
    NODE* curr = pRoot;// create node using root of tree
    while (!s.empty() || curr != nullptr)// iterate when stack is not empty or curr is not null
    {
        while (curr != nullptr)
        {
            s.push(curr);// push left to the end
            curr = curr->p_left;
        }

        curr = s.top();
        s.pop();
        Browse.push_back(curr->key);
        curr = curr->p_right;// browse curr right
    }
    return Browse;
}

vector<int> LRN(NODE* pRoot)
{
    vector<int> Browse;
    if (pRoot == nullptr)
        return Browse;
    stack<NODE*> s1, s2;// create two stack
    s1.push(pRoot);
    while (!s1.empty())
    {
        NODE* tmp = s1.top();// create tmp node with stack top
        s1.pop();

        s2.push(tmp);// push top stack2
        if (tmp->p_left != nullptr)//push node left of tmp
            s1.push(tmp->p_left);
        if (tmp->p_right != nullptr)//push node right of tmp
            s1.push(tmp->p_right);
    }

    while (!s2.empty())// browse stack2
    {
        Browse.push_back(s2.top()->key);// push value top of stack2 into vector
        s2.pop();
    }
    return Browse;
}

void LevelOrderec(NODE* pRoot, int level, vector<vector<int>>& res)
{
    if (pRoot == nullptr)
        return;
    if (res.size() <= level)// if size of res <= level then add vector null
        res.push_back({});

    res[level].push_back(pRoot->key);// add node with correct size position

    LevelOrderec(pRoot->p_left, level + 1, res);// recursive node left and level+1
    LevelOrderec(pRoot->p_right, level + 1, res);// recursive node right and level+1
}

vector<vector<int>> LevelOrder(NODE* pRoot)
{
    vector<vector<int>> res;
    LevelOrderec(pRoot, 0, res);// call function recursive level or der ec
    return res;
}

int countNode(NODE* pRoot)
{
    vector<vector<int>> tree = LevelOrder(pRoot);// count element vector level
    int count = 0;
    for (int i = 0; i < tree.size(); i++)
    {
        count += tree[i].size();
    }
    return count;
}

int sumNode(NODE* pRoot)
{
    vector<vector<int>> tree = LevelOrder(pRoot);
    int sum = 0;
    for (int i = 0; i < tree.size(); i++)
    {
        for (int j = 0; j < tree[i].size(); j++)
        {
            sum += tree[i][j];// sum each element of the vector
        }
    }
    return sum;
}

int height(NODE* pRoot) {
    if (pRoot == nullptr)
        return -1;// return -1 if tree empty
    return 1 + max(height(pRoot->p_left), height(pRoot->p_right));// recursive max(letf, right)
}

NODE* Search(NODE* pRoot, int value) {
    if (pRoot == nullptr)
        return nullptr;
    if (pRoot->key == value)
        return pRoot;// return always when node value equals value
    NODE* leftResult = Search(pRoot->p_left, value);//recursive left
    if (leftResult != nullptr)
        return leftResult;// if found return now
    return Search(pRoot->p_right, value);// else recursive right
}

int heightNode(NODE* pRoot, int value)
{
    NODE* tmp = Search(pRoot, value);// search node based on value
    if (tmp == nullptr)
        return -1;
    return height(tmp);// return height that node
}

int Level(NODE* pRoot, NODE* p)
{
    vector<vector<int>> level = LevelOrder(pRoot);
    for (int i = 0; i < level.size(); i++)
    {
        for (int j = 0; j < level[i].size(); j++)
        {
            if (p->key == level[i][j])// node has value equal to node p
                return i;// return index external vector
        }
    }
    return -1;//else ruturn -1
}

int countLeaf(NODE* pRoot)
{
    //Browse NLR
    if (pRoot == nullptr)
        return 0;
    stack<NODE*> s;
    int count = 0;
    s.push(pRoot);
    while (!s.empty())
    {
        NODE* top = s.top();
        s.pop();
        if (!top->p_left && !top->p_right)// Check if the node is a leaf node
            count++;
        if (top->p_right != nullptr)
            s.push(top->p_right);
        if (top->p_left != nullptr)
            s.push(top->p_left);
    }
    return count;
}