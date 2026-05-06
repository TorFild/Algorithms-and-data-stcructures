#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

void downHeap(int a[], int k, int size)
{
    int child;
    int tmp = a[k];
    while (2 * k + 1 < size)
    {
        child = 2 * k + 1;
        if ((child < size - 1) && (a[child] < a[child + 1]))
            child++;
        if (tmp >= a[child])
            break;
        a[k] = a[child];
        k = child;
    }
    a[k] = tmp;
}

void heapSort(int a[], int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
        downHeap(a, i, size);
    for (int i = size - 1; i > 0; i--)
    {
        int last = a[i];
        a[i] = a[0];
        a[0] = last;
        downHeap(a, 0, i);
    }
}

void quickSort(int a[], long N)
{
    long i = 0, j = N;
    int temp, p;
    p = a[N >> 1];

    do
    {
        while (a[i] < p)
            i++;
        while (a[j] > p)
            j--;

        if (i <= j)
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0)
        quickSort(a, j);
    if (N > i)
        quickSort(a + i, N - i);
}

void merge(int a[], long left, long split, long right)
{
    long pos1 = left;
    long pos2 = split + 1;
    long pos3 = 0;
    int *temp = new int[right - left + 1];

    while (pos1 <= split && pos2 <= right)
    {
        if (a[pos1] < a[pos2])
        {
            temp[pos3++] = a[pos1++];
        }
        else
        {
            temp[pos3++] = a[pos2++];
        }
    }

    while (pos1 <= split)
    {
        temp[pos3++] = a[pos1++];
    }
    while (pos2 <= right)
    {
        temp[pos3++] = a[pos2++];
    }

    for (pos3 = 0; pos3 < right - left + 1; pos3++)
    {
        a[left + pos3] = temp[pos3];
    }
    delete[] temp;
}

void mergeSort(int a[], long left, long right)
{
    long split;
    if (left < right)
    {
        split = (left + right) / 2;
        mergeSort(a, left, split);
        mergeSort(a, split + 1, right);
        merge(a, left, split, right);
    }
}

void fillArray(int a[], long size)
{
    for (long i = 0; i < size; i++)
    {
        a[i] = rand() % (120 - (-20) + 1) + (-20);
    }
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    srand(time(NULL));

    long sizes[] = {600, 6000, 60000};

    for (int s = 0; s < 3; s++)
    {
        long currentSize = sizes[s];
        int *arr = new int[currentSize];
        cout << "\n=== Тестування для " << currentSize << " елементів ===\n";

        fillArray(arr, currentSize);
        unsigned int start = clock();
        heapSort(arr, currentSize);
        unsigned int end = clock();
        cout << "Пірамідальне:\t" << end - start << " мс\n";

        fillArray(arr, currentSize);
        start = clock();
        quickSort(arr, currentSize - 1);
        end = clock();
        cout << "Швидке:\t\t" << end - start << " мс\n";

        fillArray(arr, currentSize);
        start = clock();
        mergeSort(arr, 0, currentSize - 1);
        end = clock();
        cout << "Злиттям:\t" << end - start << " мс\n";

        delete[] arr;
    }

    return 0;
}