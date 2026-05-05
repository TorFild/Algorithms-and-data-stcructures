#include <iostream>
#include <iomanip>
#include "TablePrinter.h"

using namespace std;

// Визначення функції виведення таблиці
void printTable(double start, double end, double step, MathFunc f)
{
    cout << "------------------------\n";
    cout << setw(10) << "x" << " | " << setw(10) << "y = f(x)" << "\n";
    cout << "------------------------\n";

    for (double x = start; x <= end + 1e-9; x += step)
    {
        // Виклик функції за допомогою вказівника
        cout << setw(10) << x << " | " << setw(10) << f(x) << "\n";
    }
    cout << "------------------------\n\n";
}