#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#define SIZE 9

using namespace std;

void bubbleSort(int a[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {

        for (int j = size - 1; j > i; j--)
        {
            if (a[j] < a[j - 1])
            {
                int temp = a[j - 1];
                a[j - 1] = a[j];
                a[j] = temp;
            }
        }

        cout << i + 1 << "-й прохід:\t";
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

    bubbleSort(arr, SIZE);

    cout << "--------------------------------------------------------------------------\n";
    cout << "Відсортований:\t";
    for (int i = 0; i < SIZE; i++)
    {
        cout << arr[i] << "\t";
    }
    cout << endl;

    return 0;
}