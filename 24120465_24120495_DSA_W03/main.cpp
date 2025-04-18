#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <chrono>
#include <vector>
#include "sort.h"

using namespace std;

//read input file into array data
void read_input_file(int* &a, int &n,const char *name){
    FILE* f;
    fopen_s(&f, name, "r");
    if (f!=NULL)
    {
        fscanf_s(f, "%d", &n);
        a=new int[n];
        for (int i=0; i<n; i++)
        fscanf_s(f,"%d", &a[i]);
    }
    else
    {
        cout<<"Not open file input.txt\n";
    }
    fclose(f);
}

//Write sorted data to output
void write_output_file(int* a, int n,const char* name){
    FILE* f;
    fopen_s(&f, name, "w");
    if (f!=NULL)
    {
        fprintf(f,"%d\n", n);
        for (int i=0; i<n; i++)
        fprintf(f,"%d ", a[i]);
    }
    else
    {
        cout<<"Not open file output.txt"<<endl;
    }
    fclose(f);
}

//process the command line arguments you want to enter
void parse_arguments(int argc, char* argv[], char*& algorithm, char*& input_file, char*& output_file) {
    for (int i = 1; i < argc; i++) {
        char* arg = argv[i];

        if (strcmp(arg, "-a") == 0 && i + 1 < argc) {
            algorithm = argv[++i];
        } else if (strcmp(arg, "-i") == 0 && i + 1 < argc) {
            input_file = argv[++i];
        } else if (strcmp(arg, "-o") == 0 && i + 1 < argc) {
            output_file = argv[++i];
        }
    }
}

//main
int main(int argc, char* argv[]){
    int* a, n;

    char* algorithm = nullptr;
    char* input_file = nullptr;
    char* output_file = nullptr;

    parse_arguments(argc, argv, algorithm, input_file, output_file);

    read_input_file(a, n, "input.txt");
    if (algorithm != NULL && strcmp(algorithm, "selection-sort") == 0) 
    {
        selectionSort(a, n);
    } 
        else if (algorithm!=NULL && strcmp(algorithm, "bubble-sort")==0)
    {
        bubbleSort(a, n);
    }
        else if (algorithm!=NULL && strcmp(algorithm, "shell-sort")==0)
    {
        shellSort(a, n);
    }
        else if (algorithm!=NULL && strcmp(algorithm, "shaker-sort")==0)
    {
        shakerSort(a, n);
    }
        else if (algorithm!=NULL && strcmp(algorithm, "insertion-sort")==0)
    {
        insertionSort(a, n);
    }
        else if (algorithm!=NULL && strcmp(algorithm, "heap-sort")==0)
    {
        heapSort(a, n);
    }
        else if (algorithm!=NULL && strcmp(algorithm, "merge-sort")==0)
    {
        mergeSort(a,0, n-1);
    }
        else if (algorithm!=NULL && strcmp(algorithm, "quick-sort")==0)
    {
        quickSort(a,0, n-1);
    }   
        else if (algorithm!=NULL && strcmp(algorithm, "radix-sort")==0)
    {
        radixSort(a, n);
    }   
        else if (algorithm!=NULL && strcmp(algorithm, "counting-sort")==0)
    {
        countingSort(a, n);
    }   
        else if (algorithm!=NULL && strcmp(algorithm, "flash-sort")==0)
    {
        flashSort(a, n);
    }
    else
    {
        cout << "Algorithm not specified or not recognized!" << endl;  
    }
    write_output_file(a, n, "output.txt");
    delete[]a;
    return 0;
}