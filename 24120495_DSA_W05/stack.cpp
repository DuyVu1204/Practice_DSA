#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct NODE
{
    int key;
    NODE *p_next;
};
struct Stack
{
    NODE *top;
};

Stack *initializeStack();
void push(Stack &s, int key);
int pop(Stack &s);
int size(Stack s);
bool isEmpty(Stack s);

Stack *initializeStack()
{
    Stack *s = new Stack();
    s->top = nullptr;
    return s;
}

void push(Stack &s, int key)
{
    NODE *newNode = new NODE();
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

int pop(Stack &s)
{
    if (s.top==nullptr)
    {
        return -1;
    }
    NODE *temp = s.top;
    int x = temp->key;
    s.top = s.top->p_next;
    delete temp;
    return x;
}

int size(Stack s)
{
    if (s.top == nullptr)
        return 0;
    NODE *temp = s.top;
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
    NODE* temp=s.top;
    while (temp != nullptr)
    {
        cout << temp->key << " ";   
        temp=temp->p_next;
    }
}


int main()
{
    Stack *s;
    ifstream file("input.txt");
        if (!file)
        cout<<"Error file!"<<endl;
    ofstream outfile("output.txt"); 
        if(!outfile)
        cout<<"Error file!"<<endl;
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string call;
        ss>>call;
        if (line.compare("init")==0)
        {
            s=initializeStack();
            outfile<<"EMPTY"<<endl;
        }
        else if (call=="push")
        {
            int x;
            ss>>x;
            push(*s, x);
            Stack* v=nullptr;
            v=initializeStack();
            NODE* temp=s->top;
                    while (temp!=nullptr)
                    {
                      push(*v,temp->key);
                      temp=temp->p_next;
                    }
            NODE* reverse=v->top;
                   while (reverse!=nullptr)
                   {
                      outfile<<reverse->key<<" ";
                      reverse=reverse->p_next;
                   }
                   outfile<<endl;
        }
        else if (call=="pop")
        {
            if (isEmpty(*s))
            {
                outfile<<"EMPTY"<<endl;             
            }
            else
            {
                pop(*s);
                if (isEmpty(*s))
                outfile<<"EMPTY"<<endl;
                else
                {
                    NODE* temp=s->top;
                    while (temp!=nullptr)
                    {
                      outfile<<temp->key<<" ";
                      temp=temp->p_next;
                    }
                    outfile<<endl;
                }
            }
        }
        else if (call=="size")
        {
            cout<<size(*s)<<endl;
        }
        else if (call=="isEmpty")
        {
            if (isEmpty(*s))
            outfile<<"True"<<endl;
            else outfile<<"False"<<endl;
        }
    }
    file.close();
    outfile.close();
    return 0;
}