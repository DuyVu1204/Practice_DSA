#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#define p 31
#define m 2000

using namespace std;

struct Company;
struct Node;
struct HashTable;
vector<Company> readCompanyList(string file_name);// read list MST
long long hashString(string company_name);// Hash function
HashTable* createHashTable(vector<Company> list_company);// create hash table
void insert(HashTable* hash_table, Company company);// add element
Company* search(HashTable* hash_table, string company_name);// element search
void deleteHashTable(HashTable* hash_table);// free up memory

struct Company{
    string name;
    string profit_tax;
    string address;
};

struct Node{
    Company data;
    Node* next;
};

// hashtable by vector combined with linked list
struct HashTable{
    vector<Node*> bucket;
};

// read list from file MST to vector Company
vector<Company> readCompanyList(string file_name){
    vector<Company> company_list;
    ifstream in;
    in.open(file_name);//open file
    if (!in)
    {
        cout<<"Failed open file input"<<endl;
        return company_list;// return vector null
    }
    string line;// read each line of the file
    getline(in, line);// ignore the first line because it is the title

    while (getline(in, line))
    {
        Company new_company;
        stringstream ss(line);
        getline(ss, new_company.name, '|');// add name
        getline(ss, new_company.profit_tax, '|');// add profit_tax
        getline(ss, new_company.address);// add address
        company_list.push_back(new_company);// add new company to vector
    }
    in.close();// close file
    return company_list;// return vector after add
}

long long hashString(string company_name){
    long long n=company_name.size();// size of vector
    long long hash=0;
    long long power=1;
    if (n>20)
    {
        company_name=company_name.substr(n-20);
    }
    for (char c: company_name)
    {
        hash=(hash+(c*power)%m)%m;//Quick formula to avoid memory overflow
        power=(power*p)%m;// p^i mod m, because hash mod m too
    }
    return hash;// return value hash done
}

HashTable* createHashTable(vector<Company> list_company){
    HashTable* hash_table=new HashTable();// creative new hash table 
    hash_table->bucket.resize(m, nullptr);// create hash table with given size m
    return hash_table;// return hash table
}

void insert(HashTable* hash_table, Company company){
    Node* new_company=new Node();// new company to add hash table
    new_company->data=company;// data new company
    new_company->next=nullptr;// new company pointer nullptr
    long long hash=hashString(company.name);// value hash
    if (hash_table->bucket[hash]!=nullptr) // check hash location has company
    {
        new_company->next=hash_table->bucket[hash];// add head 
        hash_table->bucket[hash]=new_company;// update head
    }
    else
        hash_table->bucket[hash]=new_company;// add it now
}

Company* search(HashTable* hash_table, string company_name){
    long long hash=hashString(company_name);// value hash
    Node* temp=hash_table->bucket[hash];// temporary variable
    while (temp!=nullptr)
    {
        if (temp->data.name==company_name)// check name company
        {
            return &temp->data;// return company this now
        }
        temp=temp->next;// pointer next company
    }
    return nullptr;// if the company does not exist, return nullptr
}

void deleteHashTable(HashTable* hash_table) {
    for (Node* &head : hash_table->bucket) // Browse each position of the hash function
    {
        while (head != nullptr)// if there are many nodes delete them all
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    delete hash_table;// delete hash table
}

int main(int argc, char *argv[]){
    if (argc<4)
    {
        cout<<"Incorrect command"<<endl;
        cout << "Usage Example: ./main ./MST.txt ./input.txt ./output.txt" << endl;
        return 1;
    }
    string mst_file=argv[1];// MST.txt
    string input=argv[2];// input.txt
    string output=argv[3];// output.txt
    vector<Company> company_list=readCompanyList(mst_file);// creative vector list company
    ifstream in;
    in.open(input);// open input
    ofstream out;
    out.open(output);// open output
    if (!in || !out)// check open file
    {
        cout<<"Open file error"<<endl;
        return 1;
    }
    HashTable* new_hashtable=createHashTable(company_list);// creative new hash table
    for (long long i=0; i<company_list.size(); i++)
    {
        insert(new_hashtable, company_list[i]);// add each company to the hash table
    }
    string line;// read each line of the file input need search
    while (getline(in, line))
    {
        Company* result_search;// create temporary variable to contain the company to search
        result_search=search(new_hashtable, line);
        if (result_search!=nullptr)// check if that company exists in the hash table
        out<<result_search->name<<'|'<<result_search->profit_tax<<'|'<<result_search->address<<endl;// add file output
    }
    in.close();//close file input
    out.close();//close file output
    deleteHashTable(new_hashtable);
    return 0;
}