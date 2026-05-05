#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

void selectSort(int a[], long size)
{
    for (long i = 0; i < size - 1; i++)
    {
        long k = i;
        int x = a[i];
        for (long j = i + 1; j < size; j++)
        {
            if (a[j] < x)
            {
                k = j;
                x = a[j];
            }
        }
        a[k] = a[i];
        a[i] = x;
    }
}

void bubbleSort(int a[], long size)
{
    for (long i = 0; i < size - 1; i++)
    {
        for (long j = size - 1; j > i; j--)
        {
            if (a[j] < a[j - 1])
            {
                int temp = a[j - 1];
                a[j - 1] = a[j];
                a[j] = temp;
            }
        }
    }
}

void shakerSort(int a[], long size)
{
    long j, k = size - 1;
    long lb = 1, ub = size - 1;
    int x;
    do
    {
        for (j = ub; j > 0; j--)
        {
            if (a[j - 1] > a[j])
            {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
                k = j;
            }
        }
        lb = k + 1;
        for (j = 1; j <= ub; j++)
        {
            if (a[j - 1] > a[j])
            {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
                k = j;
            }
        }
        ub = k - 1;
    } while (lb < ub);
}

void insertSort(int a[], long size)
{
    for (long i = 1; i < size; i++)
    {
        int x = a[i];
        long j = i - 1;
        while (j >= 0 && a[j] > x)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = x;
    }
}

void fillArray(int a[], long size)
{
    for (long i = 0; i < size; i++)
    {
        a[i] = rand() % (120 - (-120) + 1) + (-120);
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
        selectSort(arr, currentSize);
        unsigned int end = clock();
        cout << "Вибір:\t\t" << end - start << " мс\n";

        fillArray(arr, currentSize);
        start = clock();
        bubbleSort(arr, currentSize);
        end = clock();
        cout << "Бульбашка:\t" << end - start << " мс\n";

        fillArray(arr, currentSize);
        start = clock();
        shakerSort(arr, currentSize);
        end = clock();
        cout << "Шейкер:\t\t" << end - start << " мс\n";

        fillArray(arr, currentSize);
        start = clock();
        insertSort(arr, currentSize);
        end = clock();
        cout << "Вставка:\t" << end - start << " мс\n";

        delete[] arr;
    }

    return 0;
}
