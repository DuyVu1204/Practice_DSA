#include <iostream>
#include "sort.h"

using namespace std;

void selectionsort(int* a, int n){
    for (int i=0; i<n-1; i++)
    {
        int min=i;
        for (int j=i+1; j<n; j++)
        {
            if (a[j]<a[min])
            min=j;
        }
        swap(a[min], a[i]);
    }
}