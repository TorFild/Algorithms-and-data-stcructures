#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

// Структура даних учасника олімпіади (Варіант 6)
struct Participant
{
    string passportSeries;
    string surname;
    string school;
    int age;

    void print() const
    {
        cout << left << setw(8) << passportSeries
             << left << setw(15) << surname
             << left << setw(15) << school
             << left << setw(5) << age << endl;
    }
};

// ================= СТЕК (Stack - LIFO) =================
// Вузол для стеку
struct StackNode
{
    Participant data;
    StackNode *next;
};

class Stack
{
private:
    StackNode *topNode; // Вказівник на вершину стеку
public:
    Stack() { topNode = nullptr; }

    // Додавання елемента у вершину стеку
    void push(Participant p)
    {
        StackNode *newNode = new StackNode;
        newNode->data = p;
        newNode->next = topNode;
        topNode = newNode;
        cout << "У стек додано: " << p.surname << endl;
    }

    // Видалення елемента з вершини стеку
    void pop()
    {
        if (topNode == nullptr)
        {
            cout << "Стек порожній! Видалення неможливе." << endl;
            return;
        }
        StackNode *temp = topNode;
        cout << "Зі стеку видалено: " << temp->data.surname << endl;
        topNode = topNode->next;
        delete temp;
    }

    // Виведення вмісту стеку
    void print() const
    {
        if (topNode == nullptr)
        {
            cout << "Стек порожній!" << endl;
            return;
        }
        cout << "\n--- Вміст стеку (зверху вниз) ---" << endl;
        cout << left << setw(8) << "Серія" << setw(15) << "Прізвище" << setw(15) << "Заклад" << setw(5) << "Вік\n";
        cout << "---------------------------------------------\n";
        StackNode *current = topNode;
        while (current != nullptr)
        {
            current->data.print();
            current = current->next;
        }
        cout << "---------------------------------------------\n\n";
    }
};

// ================= ЧЕРГА (Queue - FIFO) =================
// Вузол для черги
struct QueueNode
{
    Participant data;
    QueueNode *next;
};

class Queue
{
private:
    QueueNode *head; // Вказівник на початок черги (звідси видаляємо)
    QueueNode *tail; // Вказівник на кінець черги (сюди додаємо)
public:
    Queue()
    {
        head = nullptr;
        tail = nullptr;
    }

    // Додавання елемента в кінець черги
    void enqueue(Participant p)
    {
        QueueNode *newNode = new QueueNode;
        newNode->data = p;
        newNode->next = nullptr;

        if (head == nullptr)
        { // Якщо черга порожня
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        cout << "У чергу додано: " << p.surname << endl;
    }

    // Видалення елемента з початку черги
    void dequeue()
    {
        if (head == nullptr)
        {
            cout << "Черга порожня! Видалення неможливе." << endl;
            return;
        }
        QueueNode *temp = head;
        cout << "З черги вийшов: " << temp->data.surname << endl;
        head = head->next;

        if (head == nullptr)
        { // Якщо після видалення черга стала порожньою
            tail = nullptr;
        }
        delete temp;
    }

    // Виведення вмісту черги
    void print() const
    {
        if (head == nullptr)
        {
            cout << "Черга порожня!" << endl;
            return;
        }
        cout << "\n--- Вміст черги (від початку до кінця) ---" << endl;
        cout << left << setw(8) << "Серія" << setw(15) << "Прізвище" << setw(15) << "Заклад" << setw(5) << "Вік\n";
        cout << "---------------------------------------------\n";
        QueueNode *current = head;
        while (current != nullptr)
        {
            current->data.print();
            current = current->next;
        }
        cout << "---------------------------------------------\n\n";
    }
};

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    cout << "========== ТЕСТУВАННЯ СТЕКУ (LIFO) ==========" << endl;
    Stack myStack;
    myStack.push({"КВ", "Коваленко", "Ліцей №1", 16});
    myStack.push({"СН", "Шевченко", "Гімназія №2", 15});
    myStack.push({"АВ", "Іваненко", "Ліцей №1", 17});

    myStack.print();

    myStack.pop(); // Має видалити Іваненка (останній доданий)
    myStack.print();

    cout << "========== ТЕСТУВАННЯ ЧЕРГИ (FIFO) ==========" << endl;
    Queue myQueue;
    myQueue.enqueue({"КВ", "Коваленко", "Ліцей №1", 16});
    myQueue.enqueue({"СН", "Шевченко", "Гімназія №2", 15});
    myQueue.enqueue({"АВ", "Іваненко", "Ліцей №1", 17});

    myQueue.print();

    myQueue.dequeue(); // Має видалити Коваленка (перший доданий)
    myQueue.print();

    return 0;
}