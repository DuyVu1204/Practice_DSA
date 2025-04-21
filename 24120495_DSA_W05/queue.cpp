#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

struct NODE {
    int key;
    NODE* p_next;
};

struct Queue {
    NODE* head;
    NODE* tail;
};

Queue* initializeQueue();
void enqueue(Queue& q, int key);
int dequeue(Queue& q);
int size(Queue q);
bool isEmpty(Queue q);
void clearQueue(Queue& q);//Add queue free function to avoid duplication

Queue* initializeQueue() {
    Queue* q = new Queue;
    q->head = nullptr;
    q->tail = nullptr;
    return q;
}

void enqueue(Queue& q, int key) {
    NODE* newNode = new NODE();
    newNode->key = key;
    newNode->p_next = nullptr;
    if (q.head == nullptr)
    {
        q.head = newNode;
        q.tail = newNode;
    }
    else
    {
        q.tail->p_next = newNode;
        q.tail = newNode;
    }
}

int dequeue(Queue& q) {
    if (q.head == nullptr)
        return -1;
    int x;
    NODE* temp = q.head;
    x = temp->key;
    if (q.head == q.tail)
    {
        q.head = nullptr;
        q.tail = nullptr;
    }
    else
    {
        q.head = q.head->p_next;
    }
    delete temp;
    return x;
}

int size(Queue q) {
    if (q.head == nullptr)
        return 0;
    NODE* temp = q.head;
    int count = 0;
    while (temp != nullptr)
    {
        count++;
        temp = temp->p_next;
    }
    return count;
}

bool isEmpty(Queue q) {
    if (q.head == nullptr)
        return true;
    else
        return false;
}

void clearQueue(Queue& q) {
     while (!isEmpty(q))
     {
        dequeue(q);
     }
}


int main() {
    Queue* q = nullptr;
    q = initializeQueue();
    ifstream file("input.txt");
    if (!file)
    {
        cout << "Error open file" << endl;
        return 1;
    }
    ofstream outfile("output.txt");
    if (!outfile)
    {
        cout << "Error open file" << endl;
        return 1;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string call;
        ss >> call;
        if (call == "init")
        {
            if (q != nullptr)
            {
                while (!isEmpty(*q))
                {
                    dequeue(*q);
                }
                delete q;
            }
            q = initializeQueue();

            outfile << "EMPTY" << endl;
        }
        else if (call == "enqueue")
        {
            int x;
            ss >> x;
            enqueue(*q, x);
            NODE* temp = q->head;
            while (temp != nullptr)
            {
                outfile << temp->key << " ";
                temp = temp->p_next;
            }
            outfile << endl;
        }
        else if (call == "dequeue")
        {
            if (isEmpty(*q))
            {
                outfile << "EMPTY" << endl;
            }
            else
            {
                dequeue(*q);
                if (isEmpty(*q))
                {
                    outfile << "EMPTY" << endl;
                }
                else
                {
                    NODE* temp = q->head;
                    while (temp != nullptr)
                    {
                        outfile << temp->key << " ";
                        temp = temp->p_next;
                    }
                    outfile << endl;
                }
            }
        }
        else if (call == "size")
        {
            outfile << size(*q) << endl;
        }
        else if (call == "isEmpty")
        {

            if (!isEmpty(*q))
                outfile << "FALSE" << endl;
            else
                outfile << "TRUE" << endl;
        }
    }
    file.close();
    outfile.close();
    if (q != nullptr)//free up memory
    {
        clearQueue(*q);
        delete q;
    }
    return 0;
}
