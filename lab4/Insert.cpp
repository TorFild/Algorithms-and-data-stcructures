#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#define SIZE 9

using namespace std;

void insertSort(int a[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int x = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > x)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = x;

        cout << i << "-й прохід:\t";
        for (int k = 0; k < size; k++)
        {
            cout << a[k] << "\t";
        }
        cout << endl;
    }
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int arr[SIZE];
    srand(time(NULL));

    cout << "Вихідний масив:\t";
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = rand() % (120 - (-120) + 1) + (-120);
        cout << arr[i] << "\t";
    }
    cout << "\n--------------------------------------------------------------------------\n";

    insertSort(arr, SIZE);

    cout << "--------------------------------------------------------------------------\n";
    cout << "Відсортований:\t";
    for (int i = 0; i < SIZE; i++)
    {
        cout << arr[i] << "\t";
    }
    cout << endl;

    return 0;
}