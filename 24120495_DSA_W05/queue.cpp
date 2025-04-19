#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

struct NODE{
    int key;
    NODE* p_next;
};

struct Queue{
    NODE* head;
    NODE* tail;
};

Queue* initializeQueue();
void enqueue(Queue &q, int key);
int dequeue(Queue &q);
int size(Queue q);
bool isEmpty(Queue q);

Queue* initializeQueue(){
    Queue* q=new Queue;
    q->head=nullptr;
    q->tail=nullptr;
    return q;
}

void enqueue(Queue &q, int key){
    NODE* newNode=new NODE();
    newNode->key=key;
    newNode->p_next=nullptr;
    if (q.head==nullptr)
    {
        q.head=newNode;
        q.tail=newNode;
    }
    else
    {
        q.tail->p_next=newNode;
        q.tail=newNode;
    }
}

int dequeue(Queue &q){
    int x;
    if (q.head==nullptr)
    return -1;
        NODE* temp=q.head;
        x=temp->key;
        if (q.head==q.tail)
        {
            q.head=nullptr;
            q.tail=nullptr;
        }
        else
        {
            q.head=q.head->p_next;
        }
        delete temp;
    return x;
}

int size(Queue q){
    if (q.head==nullptr)
    return 0;
    NODE* temp=q.head;
    int count=0;
    while (temp!=nullptr)
    {
        count++;
        temp=temp->p_next;
    }
    return count;
}

bool isEmpty(Queue q){
    if (q.head==nullptr)
    return true;
    else
    return false;
}

int main(){
    Queue* q;
    ifstream file("input.txt");
    if (!file)
    cout<<"Error file"<<endl;
    ofstream outfile("output.txt");
    if (!outfile)
    cout<<"Error file"<<endl;
    string line;
    while (getline(file,line))
    {
        stringstream ss(line);
        string call;
        ss>>call;
        if (call=="init")
        {
            q=initializeQueue();
            outfile<<"EMPTY"<<endl;
        }
        else if(call=="enqueue")
        {
            int x;
            ss>>x;
            enqueue(*q,x);
            NODE* temp=q->head;
            while (temp!=nullptr)
            {
                outfile<<temp->key<<" ";
                temp=temp->p_next;
            }
            outfile<<endl;
        }
        else if (call=="dequeue")
        {
            if (q->head==nullptr)
            {
                outfile<<"EMPTY"<<endl;
            }
            else
            {
                dequeue(*q);
                if (q->head==nullptr)
                {
                    outfile<<"EMPTY"<<endl;
                }
                else
                {
                    NODE* temp=q->head;
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
            outfile<<size(*q)<<endl;
        }
        else if (call=="isEmpty")
        {
            if (isEmpty(*q))
            outfile<<"TRUE"<<endl;
            else 
            outfile<<"FALSE"<<endl;
        }
    }
    file.close();
    outfile.close();
    return 0;
}