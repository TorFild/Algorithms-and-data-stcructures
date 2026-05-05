#ifndef TABLE_PRINTER_H
#define TABLE_PRINTER_H

// Створюємо синонім типу: вказівник на функцію,
// яка приймає double і повертає double
typedef double (*MathFunc)(double);

// Прототип функції виведення таблиці значень
void printTable(double start, double end, double step, MathFunc f);

#endif