#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <chrono>
#include <vector>

using namespace std;

// Sort functions

//Heap Sort
void heapify(int* a, int n, int i)
{
    int max = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left<n && a[left]>a[max])
    {
        max = left;
    }
    if (right<n && a[right]>a[max])
    {
        max = right;
    }
    if (max != i)
    {
        swap(a[i], a[max]);
        heapify(a, n, max);
    }

}
void heapSort(int* a, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(a, n, i);
    }
    for (int i = n - 1; i > 0; i--)
    {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

//Insertion Sort
void insertionSort(int* a, int n) {
    for (int i = 1; i < n; i++)
    {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
    }
}

//Selection Sort
void selectionSort(int* a, int n){
    for (int i=0; i<n-1; i++)
    {
        int min=i;
        for (int j=i+1; j<n; j++)
        {
            if (a[j]<a[min])
            min=j;
        }
        swap(a[i], a[min]);
    }
}

//Bubble Sort
void bubbleSort(int* a, int n){
    for (int i=1; i<n; i++)
    {
        for (int j=n-1; j>=i; j--)
        {
            if (a[j-1]>a[j])
            swap(a[j-1],a[j]);
        }
    }
}

//Merge Sort
void merge(int* a, int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    int* temp = new int[right - left + 1];

    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        }
        else {
            temp[k++] = a[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = a[i++];
    }

    while (j <= right) {  
        temp[k++] = a[j++];
    }

    for (int x = 0; x < k; x++) {
        a[left + x] = temp[x];
    }

    delete[] temp;
}
void mergeSort(int* a, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

//Quick Sort
int partition(int* a, int left, int right) {
    int randomIndex = left + rand() % (right - left + 1);
    swap(a[randomIndex], a[right]); 
    int pivot = a[right];
    int i = left - 1;

    for (int j = left; j < right; j++) 
    {
        if (a[j] < pivot) 
        {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[right]); 
    return i + 1;
}

void quickSort(int* a, int left, int right) {
    if (left < right) {
        int pi = partition(a, left, right); 

        quickSort(a, left, pi - 1); 
        quickSort(a, pi + 1, right);
    }
}

//Shaker Sort
void shakerSort(int* a, int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        for (int i = left; i < right; i++) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
            }
        }
        right--;

        for (int i = right; i > left; i--) {    
            if (a[i] < a[i - 1]) {
                swap(a[i], a[i - 1]);
            }
        }
        left++;
    }
}

//Shell Sort
void shellSort(int* a, int n){
    int i, j, interval, temp;
    for (interval=n/2; interval>0; interval/=2)
    {
        for (i=interval; i<n; i++)
        {
            temp=a[i];
            for (j=i; j>=interval && a[j-interval]>temp; j-=interval)
            {
                a[j]=a[j-interval];
            }
            a[j]=temp;
        }
    }
}

int getmax(int* a, int n){
    return *max_element(a, a+n);
}

//Radix Sort
void countingsort_radix(int* a, int n, int exp){
    int* output; 
    output=new int[n];
    int count[10]={0};
    for (int i=0; i<n; i++)
    count[(a[i]/exp)%10]++;
    for (int i=1; i<10; i++)
    count[i]+=count[i-1];
    for (int i=n-1; i>=0; i--)
    {
        int digit=(a[i]/exp)%10;
        output[count[digit]-1]=a[i];
        count[digit]--;
    }
    for (int i=0; i<n; i++)
    a[i]=output[i];
    delete[]output;
}

void radixSort(int* a, int n){
    int maxNum=getmax(a,n);
    for (int exp=1; maxNum/exp>0; exp*=10)
    countingsort_radix(a, n, exp);
}

//Counting Sort
void countingSort(int* a, int n){
    int maxArr=getmax(a, n);
    int* count=new int[maxArr+1]();
    for (int i=0; i<n; i++)
    count[a[i]]++;
    for (int i=1; i<=maxArr; i++)
    count[i]+=count[i-1];
    int* output=new int[n];
    for (int i=n-1; i>=0; i--)
    {
        output[count[a[i]]-1]=a[i];
        count[a[i]]--;
    }
    for (int i=0; i<n; i++)
    a[i]=output[i];
    delete[]count;
    delete[]output;
}

//Flash Sort
void insertionSort_of_flash_sort(int* a, int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= l && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}


void flashSort(int* a, int n){
    int minVal= *min_element(a, a+n);
    int maxVal= *max_element(a, a+n);

    if (maxVal == minVal) return;  

    int m=int(0.45*n);
    vector<int> L(m,0);

    for (int i=0; i<n; i++)
    {
        int k=(m-1)*(a[i]-minVal)/(maxVal-minVal);
        L[k]++;
    }

    for (int i=1; i<m; i++)
    {
        L[i]+=L[i-1];
    }

    vector<int> temp(n);
    for (int i=n-1; i>=0; i--)
    {
        int k=(m-1)*(a[i]-minVal)/(maxVal-minVal);
        temp[L[k]-1]=a[i];
        L[k]--;
    }
    for (int i=0; i<n; i++)
    {
        a[i]=temp[i];
    }
    int i=0;
    while (i<n)
    {
        int j=i+1;
        while (j<n && a[j]>=a[j-1])
        j++;
        insertionSort_of_flash_sort(a, i, j - 1);
        i=j;
    }
}