#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

// Кількість учасників згідно з варіантом 6
const int T = 10;

// Оголошення структури
struct Participant
{
    string passportSeries;
    string surname;
    string school;
    int age;

    // Метод для зручного виведення одного запису
    void print()
    {
        cout << passportSeries << "\t" << surname << "\t" << school << "\t\t" << age << endl;
    }
};

// 1. Стійкий алгоритм (Вставка) для сортування за віком
void insertSortByAge(Participant a[], int size)
{
    for (int i = 1; i < size; i++)
    {
        Participant x = a[i];
        int j = i - 1;
        // Порівнюємо за ключем "вік"
        while (j >= 0 && a[j].age > x.age)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = x;
    }
}

// 2. Нестійкий алгоритм (Вибір) для сортування за серією паспорта
void selectSortByPassport(Participant a[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < size; j++)
        {
            // Порівнюємо за ключем "серія паспорта" (лексикографічно)
            if (a[j].passportSeries < a[k].passportSeries)
            {
                k = j;
            }
        }
        // Обмін структурами цілком
        Participant temp = a[k];
        a[k] = a[i];
        a[i] = temp;
    }
}

// Функція для виведення масиву структур на екран
void printArray(Participant a[], int size)
{
    cout << "Серія\tПрізвище\tЗаклад\t\tВік\n";
    cout << "--------------------------------------------------\n";
    for (int i = 0; i < size; i++)
    {
        a[i].print();
    }
    cout << "--------------------------------------------------\n";
}

// Допоміжна функція для копіювання масиву (щоб зберегти оригінал)
void copyArray(Participant src[], Participant dest[], int size)
{
    for (int i = 0; i < size; i++)
    {
        dest[i] = src[i];
    }
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // Ініціалізація даних 10 учасників
    Participant original[T] = {
        {"КВ", "Коваленко", "Ліцей №1", 16},
        {"СН", "Шевченко", "Гімназія №2", 15},
        {"АВ", "Іваненко", "Ліцей №1", 17},
        {"КВ", "Бойко", "СЗШ №5", 15},
        {"АА", "Ткаченко", "Ліцей №3", 16},
        {"СН", "Кравченко", "Гімназія №2", 14},
        {"ВВ", "Олійник", "СЗШ №10", 17},
        {"КВ", "Мельник", "Ліцей №1", 15},
        {"АА", "Волошин", "СЗШ №5", 16},
        {"ВВ", "Григоренко", "Ліцей №3", 15}};

    Participant current[T];
    int choice;

    do
    {
        cout << "\nОберіть дію:\n";
        cout << "0 - Вивести дані в початковому порядку\n";
        cout << "1 - Відсортувати за серією паспорта (нестійкий)\n";
        cout << "2 - Відсортувати за віком (стійкий)\n";
        cout << "3 - Вийти з програми\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        // Щоразу працюємо з копією оригінальних даних
        copyArray(original, current, T);

        switch (choice)
        {
        case 0:
            cout << "\nДані у вихідному порядку:\n";
            printArray(current, T);
            break;
        case 1:
            cout << "\nДані, відсортовані за серією паспорта:\n";
            selectSortByPassport(current, T);
            printArray(current, T);
            break;
        case 2:
            cout << "\nДані, відсортовані за віком:\n";
            insertSortByAge(current, T);
            printArray(current, T);
            break;
        case 3:
            cout << "Завершення роботи...\n";
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != 3);

    return 0;
}