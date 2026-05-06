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
        {
            child++;
        }

        if (tmp >= a[child])
        {
            break;
        }

        a[k] = a[child];
        k = child;
    }
    a[k] = tmp;
}

void heapSort(int a[], int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        downHeap(a, i, size);
    }

    cout << "Сформована піраміда:\t";
    for (int i = 0; i < size; i++)
        cout << a[i] << "\t";
    cout << "\n\nПочинаємо сортування:\n";

    for (int i = size - 1; i > 0; i--)
    {
        int last = a[i];
        a[i] = a[0];
        a[0] = last;

        downHeap(a, 0, i);

        cout << size - i << "-й крок:\t\t";
        for (int k = 0; k < size; k++)
            cout << a[k] << "\t";
        cout << endl;
    }
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    srand(time(NULL));

    int arr[10];
    cout << "Вихідний масив:\t\t";
    for (int i = 0; i < 10; i++)
    {
        arr[i] = rand() % (120 - (-20) + 1) + (-20);
        cout << arr[i] << "\t";
    }
    cout << "\n--------------------------------------------------------------------------------------\n";

    heapSort(arr, 10);

    return 0;
}