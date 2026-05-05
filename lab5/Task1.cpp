#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

void shakerSortSteps(int a[], long size)
{
    long j, k = size - 1;
    long lb = 1, ub = size - 1;
    int x;
    int pass = 1;

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

        cout << pass++ << "-й прохід (вгору):\t";
        for (int i = 0; i < size; i++)
            cout << a[i] << "\t";
        cout << endl;

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

        if (lb < ub)
        {
            cout << pass++ << "-й прохід (вниз):\t";
            for (int i = 0; i < size; i++)
                cout << a[i] << "\t";
            cout << endl;
        }

    } while (lb < ub);
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int arr[10];
    srand(time(NULL));

    cout << "Вихідний масив:\t\t";
    for (int i = 0; i < 10; i++)
    {
        arr[i] = rand() % (120 - 20 + 1) + 20;
        cout << arr[i] << "\t";
    }
    cout << "\n--------------------------------------------------------------------------------------\n";

    shakerSortSteps(arr, 10);

    return 0;
}
