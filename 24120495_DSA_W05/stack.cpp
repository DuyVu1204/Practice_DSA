#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct NODE
{
    int key;
    NODE* p_next;
};
struct Stack
{
    NODE* top;
};

Stack* initializeStack();
void push(Stack& s, int key);
int pop(Stack& s);
int size(Stack s);
bool isEmpty(Stack s);
void clearStack(Stack& s);//Add stack free function to avoid duplication

Stack* initializeStack()
{
    Stack* s = new Stack();
    s->top = nullptr;
    return s;
}

void push(Stack& s, int key)
{
    NODE* newNode = new NODE();
    newNode->key = key;
    newNode->p_next = nullptr;
    if (s.top == nullptr)
    {
        s.top = newNode;
    }
    else
    {
        newNode->p_next = s.top;
        s.top = newNode;
    }
}

int pop(Stack& s)
{
    if (s.top == nullptr)
    {
        return -1;
    }
    NODE* temp = s.top;
    int x = temp->key;
    s.top = s.top->p_next;
    delete temp;
    return x;
}

int size(Stack s)
{
    if (s.top == nullptr)
        return 0;
    NODE* temp = s.top;
    int count = 0;
    while (temp != nullptr)
    {
        count++;
        temp = temp->p_next;
    }
    return count;
}

bool isEmpty(Stack s)
{
    if (s.top == nullptr)
        return true;
    else
        return false;
}

void disPlay(Stack s)
{
    NODE* temp = s.top;
    while (temp != nullptr)
    {
        cout << temp->key << " ";
        temp = temp->p_next;
    }
}

void clearStack(Stack& s) {
    while (!isEmpty(s))
    {
        pop(s);
    }
}

int main()
{
    Stack* s = nullptr;
    s=initializeStack();
    ifstream file("input.txt");
    if (!file)
    {
        cout << "Error open file!" << endl;
        return 1;
    }
    ofstream outfile("output.txt");
    if (!outfile)
    {
        cout << "Error file!" << endl;
        return 1;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string call;
        ss >> call;
        if (line.compare("init") == 0)
        {
            if (s!=nullptr)
            {
                while (!isEmpty(*s))
                {
                    pop(*s);
                }
                delete s;
            }
            s = initializeStack();
            outfile << "EMPTY" << endl;
        }
        else if (call == "push")
        {
            int x;
            ss >> x;
            push(*s, x);
            Stack* v = nullptr;//create new stack to save the value in reverse and save to output as requested
            v = initializeStack();
            NODE* temp = s->top;
            while (temp != nullptr)
            {
                push(*v, temp->key);
                temp = temp->p_next;
            }
            NODE* reverse = v->top;//put data into output
            while (reverse != nullptr)
            {
                outfile << reverse->key << " ";
                reverse = reverse->p_next;
            }
            outfile << endl;
        }
        else if (call == "pop")
        {
            if (isEmpty(*s))
            {
                outfile << "EMPTY" << endl;
            }
            else
            {
                pop(*s);
                if (isEmpty(*s))
                    outfile << "EMPTY" << endl;
                else
                {
                    Stack* v = nullptr;//create new stack to save the value in reverse and save to output as requested
                    v = initializeStack();
                    NODE* temp = s->top;
                    while (temp != nullptr)
                    {
                        push(*v, temp->key);
                        temp = temp->p_next;
                    }
                    NODE* reverse = v->top;//put data into output
                    while (reverse != nullptr)
                    {
                        outfile << reverse->key << " ";
                        reverse = reverse->p_next;
                    }
                    outfile << endl;
                }
            }
        }
        else if (call == "size")
        {
            outfile << size(*s) << endl;
        }
        else if (call == "isEmpty")
        {
            if (!isEmpty(*s))
                outfile << "FALSE" << endl;
            else 
                outfile << "TRUE" << endl;
        }
    }
    file.close();
    outfile.close();
    if (s != nullptr)//free up memory
    {
        clearStack(*s);
        delete s;
    }
    return 0;
}
