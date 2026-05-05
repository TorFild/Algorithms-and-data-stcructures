#include <iostream>
#include <cmath>
#include <windows.h>
#include "TablePrinter.h" // Підключаємо наш заголовний файл

using namespace std;

// Функція 1: З першої лабораторної роботи (Варіант 6)
double funcLab1(double x)
{
    int n = 2; // Фіксуємо параметр n для побудови таблиці
    if (x <= 0)
    {
        double sum = 0;
        for (int i = 1; i <= n; i++)
            sum += (x - i) * (x - i);
        return sum;
    }
    else
    {
        double prod = 1;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n - 1; j++)
                prod *= (x - i - 2.0 * j);
        return prod;
    }
}

// Функція 2: Будь-яка інша математична функція (наприклад, x^2 + 1)
double customMathFunc(double x)
{
    return x * x + 1.0;
}

int main()
{
    SetConsoleOutputCP(65001);

    double start, end, step;

    cout << "=== Тестування функції з Лабораторної №1 ===\n";
    cout << "Введіть початок інтервалу: ";
    cin >> start;
    cout << "Введіть кінець інтервалу: ";
    cin >> end;
    cout << "Введіть крок: ";
    cin >> step;

    // Передаємо функцію funcLab1 як аргумент
    printTable(start, end, step, funcLab1);

    cout << "=== Тестування вбудованої функції cos(x) ===\n";
    // Можна передавати вбудовані функції з <cmath>!
    printTable(0, 3.14, 0.5, cos);

    cout << "=== Тестування власної функції x^2 + 1 ===\n";
    printTable(-2, 2, 1, customMathFunc);

    return 0;
}