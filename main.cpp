#include <iostream>
#include <chrono>
#include <ctime>
#include <algorithm>

#define SIZE_SMALL 100
#define SIZE_LARGE 10000

using namespace std;

void insertionSort(int theArray[], int n)
{
    for (int i = 1; i < n; ++i)
    {
        int key = theArray[i];
        int j = i - 1;

        while (j >= 0 && theArray[j] > key)
        {
            theArray[j + 1] = theArray[j];
            --j;
        }

        theArray[j + 1] = key;
    }
}

void merge(int theArray[], int first, int mid, int last)
{
    int temp[last - first + 1];
    int i = first, j = mid + 1, k = 0;

    while (i <= mid && j <= last)
    {
        if (theArray[i] <= theArray[j])
        {
            temp[k] = theArray[i];
            ++i;
        }
        else
        {
            temp[k] = theArray[j];
            ++j;
        }
        ++k;
    }

    while (i <= mid)
    {
        temp[k] = theArray[i];
        ++i;
        ++k;
    }

    while (j <= last)
    {
        temp[k] = theArray[j];
        ++j;
        ++k;
    }

    for (int i = first; i <= last; ++i)
    {
        theArray[i] = temp[i - first];
    }
}

void mergeSort(int theArray[], int first, int last)
{
    if (first < last)
    {
        int mid = (first + last) / 2;

        mergeSort(theArray, first, mid);
        mergeSort(theArray, mid + 1, last);
        merge(theArray, first, mid, last);
    }
}

void timeSort(int theArray[], int n)
{
    // measure time for system sort
    auto start = chrono::steady_clock::now();
    sort(theArray, theArray + n);
    auto end = chrono::steady_clock::now();
    cout << "System Sort - Elapsed time in nanoseconds for 100 elements: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;
    cout << "System Sort - Elapsed time in nanoseconds for 10000 elements: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;

    // measure time for insertion sort
    start = chrono::steady_clock::now();
    insertionSort(theArray, n);
    end = chrono::steady_clock::now();
    cout << "Insertion sort - Elapsed time in nanoseconds for 100 elements: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;
    cout << "Insertion sort - Elapsed time in nanoseconds for 10000 elements: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;

    // measure time for merge sort
    start = chrono::steady_clock::now();
    mergeSort(theArray, 0, n - 1);
    end = chrono::steady_clock::now();
    cout << "Merge sort - Elapsed time in nanoseconds for 100 elements: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;
    cout << "Merge sort - Elapsed time in nanoseconds for 10000 elements: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;

}

int main()
{
    int small[SIZE_SMALL];
    int large[SIZE_LARGE];

    // fill array with random values
    srand(time(nullptr));
    for (int i = 0; i < SIZE_SMALL; ++i)
    {
        small[i] = rand() % 100;
    }

    timeSort(small, SIZE_SMALL);

    // fill large array with random values
    for (int i = 0; i < SIZE_LARGE; ++i)
    {
        large[i] = rand() % 100;
    }


    return 0;
}
