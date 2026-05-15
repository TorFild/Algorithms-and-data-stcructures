#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

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

struct DequeNode
{
    Participant data;
    DequeNode *next;
    DequeNode *prev;
};

class Deque
{
private:
    DequeNode *head;
    DequeNode *tail;

public:
    Deque() { head = tail = nullptr; }

    void push_front(Participant p)
    {
        DequeNode *newNode = new DequeNode{p, head, nullptr};
        if (head)
            head->prev = newNode;
        head = newNode;
        if (!tail)
            tail = newNode;
        cout << "У дек (на початок) додано: " << p.surname << endl;
    }

    void push_back(Participant p)
    {
        DequeNode *newNode = new DequeNode{p, nullptr, tail};
        if (tail)
            tail->next = newNode;
        tail = newNode;
        if (!head)
            head = newNode;
        cout << "У дек (в кінець) додано: " << p.surname << endl;
    }

    void pop_front()
    {
        if (!head)
        {
            cout << "Дек порожній!" << endl;
            return;
        }
        DequeNode *temp = head;
        cout << "З деку (з початку) видалено: " << temp->data.surname << endl;
        head = head->next;
        if (head)
            head->prev = nullptr;
        else
            tail = nullptr;
        delete temp;
    }

    void pop_back()
    {
        if (!tail)
        {
            cout << "Дек порожній!" << endl;
            return;
        }
        DequeNode *temp = tail;
        cout << "З деку (з кінця) видалено: " << temp->data.surname << endl;
        tail = tail->prev;
        if (tail)
            tail->next = nullptr;
        else
            head = nullptr;
        delete temp;
    }

    void print() const
    {
        if (!head)
        {
            cout << "Дек порожній!" << endl;
            return;
        }
        cout << "\n--- Вміст деку (від початку до кінця) ---" << endl;
        cout << left << setw(8) << "Серія" << setw(15) << "Прізвище" << setw(15) << "Заклад" << setw(5) << "Вік\n";
        cout << "---------------------------------------------\n";
        DequeNode *current = head;
        while (current)
        {
            current->data.print();
            current = current->next;
        }
        cout << "---------------------------------------------\n\n";
    }
};

struct PriorityQueueNode
{
    Participant data;
    PriorityQueueNode *next;
};

class PriorityQueue
{
private:
    PriorityQueueNode *head;

public:
    PriorityQueue() { head = nullptr; }

    void enqueue(Participant p)
    {
        PriorityQueueNode *newNode = new PriorityQueueNode{p, nullptr};
        cout << "У пріоритетну чергу додаємо: " << p.surname << " (Вік: " << p.age << ")" << endl;

        if (!head || p.age < head->data.age)
        {
            newNode->next = head;
            head = newNode;
            return;
        }

        PriorityQueueNode *current = head;
        while (current->next && current->next->data.age <= p.age)
        {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    void dequeue()
    {
        if (!head)
        {
            cout << "Черга порожня!" << endl;
            return;
        }
        PriorityQueueNode *temp = head;
        cout << "З пріоритетної черги вийшов: " << temp->data.surname << " (Вік: " << temp->data.age << ")" << endl;
        head = head->next;
        delete temp;
    }

    void print() const
    {
        if (!head)
        {
            cout << "Черга порожня!" << endl;
            return;
        }
        cout << "\n--- Вміст пріоритетної черги ---" << endl;
        cout << left << setw(8) << "Серія" << setw(15) << "Прізвище" << setw(15) << "Заклад" << setw(5) << "Вік\n";
        cout << "---------------------------------------------\n";
        PriorityQueueNode *current = head;
        while (current)
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

    cout << "========== ТЕСТУВАННЯ ДЕКУ ==========" << endl;
    Deque myDeque;
    myDeque.push_back({"КВ", "Коваленко", "Ліцей №1", 16});
    myDeque.push_front({"СН", "Шевченко", "Гімназія №2", 15});
    myDeque.push_back({"АВ", "Іваненко", "Ліцей №1", 17});
    myDeque.print();

    myDeque.pop_front();
    myDeque.pop_back();
    myDeque.print();

    cout << "========== ТЕСТУВАННЯ ПРІОРИТЕТНОЇ ЧЕРГИ ==========" << endl;
    PriorityQueue pq;

    pq.enqueue({"КВ", "Бойко", "СЗШ №5", 17});
    pq.enqueue({"АА", "Ткаченко", "Ліцей №3", 14});
    pq.enqueue({"ВВ", "Олійник", "СЗШ №10", 16});
    pq.enqueue({"СН", "Мельник", "Гімназія №2", 14});

    pq.print();

    pq.dequeue();
    pq.print();

    return 0;
}