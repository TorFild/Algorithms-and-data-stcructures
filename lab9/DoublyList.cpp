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

struct Node
{
    Participant data;
    Node *next;
    Node *prev;
};

class DoublyLinkedList
{
public:
    Node *head;
    Node *tail;
    int size;

    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    int getSize() const
    {
        return size;
    }

    void clear()
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~DoublyLinkedList()
    {
        clear();
    }

    void printList() const
    {
        if (head == nullptr)
        {
            cout << "Список порожній!" << endl;
            return;
        }
        cout << left << setw(8) << "Серія" << setw(15) << "Прізвище" << setw(15) << "Заклад" << setw(5) << "Вік\n";
        cout << "---------------------------------------------\n";
        Node *current = head;
        while (current != nullptr)
        {
            current->data.print();
            current = current->next;
        }
        cout << "---------------------------------------------\n";
    }

    void push_back(Participant p)
    {
        Node *newNode = new Node{p, nullptr, nullptr};
        if (head == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    Node *get(int k) const
    {
        if (k < 1 || k > size)
            return nullptr;
        Node *current = head;
        for (int i = 1; i < k; i++)
        {
            current = current->next;
        }
        return current;
    }

    void remove(int k)
    {
        Node *target = get(k);
        if (target == nullptr)
            return;

        if (target->prev != nullptr)
        {
            target->prev->next = target->next;
        }
        else
        {
            head = target->next;
        }

        if (target->next != nullptr)
        {
            target->next->prev = target->prev;
        }
        else
        {
            tail = target->prev;
        }

        delete target;
        size--;
    }

    void swapAfter(int p)
    {
        Node *node1 = get(p + 1);
        Node *node2 = get(p + 2);

        if (node1 == nullptr || node2 == nullptr || node1->next != node2)
        {
            cout << "Недостатньо елементів для обміну після позиції " << p << endl;
            return;
        }

        Node *prevNode = node1->prev;
        Node *nextNode = node2->next;

        if (prevNode != nullptr)
            prevNode->next = node2;
        else
            head = node2;

        if (nextNode != nullptr)
            nextNode->prev = node1;
        else
            tail = node1;

        node2->prev = prevNode;
        node2->next = node1;

        node1->prev = node2;
        node1->next = nextNode;
    }

    void insertBefore(int k, Participant p)
    {
        if (k == 1 || head == nullptr)
        {
            Node *newNode = new Node{p, head, nullptr};
            if (head != nullptr)
                head->prev = newNode;
            head = newNode;
            if (tail == nullptr)
                tail = newNode;
            size++;
            return;
        }

        Node *target = get(k);
        if (target == nullptr)
            return;

        Node *newNode = new Node{p, target, target->prev};
        target->prev->next = newNode;
        target->prev = newNode;
        size++;
    }

    DoublyLinkedList *copy() const
    {
        DoublyLinkedList *newList = new DoublyLinkedList();
        Node *current = head;
        while (current != nullptr)
        {
            newList->push_back(current->data);
            current = current->next;
        }
        return newList;
    }

    DoublyLinkedList *split(int k)
    {
        DoublyLinkedList *newList = new DoublyLinkedList();
        if (k < 1 || k >= size)
            return newList;

        Node *splitNode = get(k);
        Node *startOfNew = splitNode->next;

        newList->head = startOfNew;
        newList->tail = this->tail;
        newList->size = this->size - k;
        startOfNew->prev = nullptr;

        this->tail = splitNode;
        splitNode->next = nullptr;
        this->size = k;

        return newList;
    }

    void merge(DoublyLinkedList *otherList)
    {
        if (otherList == nullptr || otherList->head == nullptr)
            return;

        if (this->head == nullptr)
        {
            this->head = otherList->head;
            this->tail = otherList->tail;
        }
        else
        {
            this->tail->next = otherList->head;
            otherList->head->prev = this->tail;
            this->tail = otherList->tail;
        }
        this->size += otherList->size;

        otherList->head = nullptr;
        otherList->tail = nullptr;
        otherList->size = 0;
    }

    int findBySurname(string surname) const
    {
        Node *current = head;
        int index = 1;
        while (current != nullptr)
        {
            if (current->data.surname == surname)
            {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1;
    }
};

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    DoublyLinkedList list;
    cout << "=== 1. Додавання елементів ===" << endl;
    list.push_back({"КВ", "Коваленко", "Ліцей №1", 16});
    list.push_back({"СН", "Шевченко", "Гімназія №2", 15});
    list.push_back({"АВ", "Іваненко", "Ліцей №1", 17});
    list.push_back({"КВ", "Бойко", "СЗШ №5", 14});
    list.printList();
    cout << "Кількість елементів у списку: " << list.getSize() << endl;

    cout << "\n=== 2. Включення перед 2-им вузлом ===" << endl;
    list.insertBefore(2, {"АА", "Ткаченко", "Ліцей №3", 15});
    list.printList();

    cout << "\n=== 3. Вилучення 3-го елемента ===" << endl;
    list.remove(3);
    list.printList();

    cout << "\n=== 4. Пошук за прізвищем 'Бойко' ===" << endl;
    int pos = list.findBySurname("Бойко");
    if (pos != -1)
        cout << "Учасник 'Бойко' знайдений на позиції: " << pos << endl;
    else
        cout << "Учасника не знайдено" << endl;

    cout << "\n=== 5. Обмін сусідніх елементів після 1-ї позиції (зміна вказівників 2 і 3) ===" << endl;
    list.swapAfter(1);
    list.printList();

    cout << "\n=== 6. Копіювання списку ===" << endl;
    DoublyLinkedList *copiedList = list.copy();
    cout << "Створено незалежну копію:" << endl;
    copiedList->printList();

    cout << "\n=== 7. Розбиття копії на два списки (по 2-му елементу) ===" << endl;
    DoublyLinkedList *secondPart = copiedList->split(2);
    cout << "Перша частина (залишок):" << endl;
    copiedList->printList();
    cout << "Друга частина (відщеплена):" << endl;
    secondPart->printList();

    cout << "\n=== 8. Злиття розбитих списків назад ===" << endl;
    copiedList->merge(secondPart);
    copiedList->printList();

    cout << "\n=== 9. Очищення списку ===" << endl;
    list.clear();
    list.printList();

    delete copiedList;
    delete secondPart;
    return 0;
}