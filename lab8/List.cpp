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

    void print()
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
};

class LinkedList
{
public:
    Node *head;

    LinkedList() { head = nullptr; }

    void add(Participant p)
    {
        Node *newNode = new Node{p, nullptr};
        if (head == nullptr)
        {
            head = newNode;
            return;
        }
        Node *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void printList()
    {
        if (head == nullptr)
        {
            cout << "Список порожній!\n";
            return;
        }
        cout << left << setw(8) << "Серія" << setw(15) << "Прізвище" << setw(15) << "Заклад" << setw(5) << "Вік\n";
        cout << "---------------------------------------------\n";
        Node *temp = head;
        while (temp != nullptr)
        {
            temp->data.print();
            temp = temp->next;
        }
        cout << "---------------------------------------------\n";
    }

    int findPosition(string searchSurname)
    {
        Node *temp = head;
        int pos = 1;
        while (temp != nullptr)
        {
            if (temp->data.surname == searchSurname)
                return pos;
            temp = temp->next;
            pos++;
        }
        return -1;
    }

    Participant getElement(int pos)
    {
        Node *temp = head;
        for (int i = 1; temp != nullptr && i < pos; i++)
        {
            temp = temp->next;
        }
        if (temp != nullptr)
            return temp->data;
        return {"", "Не знайдено", "", 0};
    }

    void remove(int pos)
    {
        if (head == nullptr)
            return;
        if (pos == 1)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node *temp = head;
        for (int i = 1; temp != nullptr && i < pos - 1; i++)
        {
            temp = temp->next;
        }
        if (temp == nullptr || temp->next == nullptr)
            return;

        Node *nextNode = temp->next->next;
        delete temp->next;
        temp->next = nextNode;
    }

    void swapElements(int pos1, int pos2)
    {
        if (pos1 == pos2)
            return;
        Node *node1 = head;
        Node *node2 = head;
        for (int i = 1; node1 != nullptr && i < pos1; i++)
            node1 = node1->next;
        for (int i = 1; node2 != nullptr && i < pos2; i++)
            node2 = node2->next;

        if (node1 != nullptr && node2 != nullptr)
        {
            Participant temp = node1->data;
            node1->data = node2->data;
            node2->data = temp;
        }
    }

    void sortByAge()
    {
        if (!head)
            return;
        bool swapped;
        Node *ptr1;
        Node *lptr = nullptr;

        do
        {
            swapped = false;
            ptr1 = head;

            while (ptr1->next != lptr)
            {
                if (ptr1->data.age > ptr1->next->data.age)
                {
                    Participant temp = ptr1->data;
                    ptr1->data = ptr1->next->data;
                    ptr1->next->data = temp;
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }
};

LinkedList mergeSortedLists(LinkedList &list1, LinkedList &list2)
{
    LinkedList mergedList;
    Node *p1 = list1.head;
    Node *p2 = list2.head;

    while (p1 != nullptr && p2 != nullptr)
    {
        if (p1->data.age <= p2->data.age)
        {
            mergedList.add(p1->data);
            p1 = p1->next;
        }
        else
        {
            mergedList.add(p2->data);
            p2 = p2->next;
        }
    }
    while (p1 != nullptr)
    {
        mergedList.add(p1->data);
        p1 = p1->next;
    }
    while (p2 != nullptr)
    {
        mergedList.add(p2->data);
        p2 = p2->next;
    }
    return mergedList;
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    LinkedList list1;
    list1.add({"КВ ", "Коваленко", "Ліцей №1", 16});
    list1.add({"СН", "Шевченко", "Гімназія №2", 15});
    list1.add({"АВ", "Іваненко", "Ліцей №1", 17});

    cout << "=== Початковий Список 1 ===\n";
    list1.printList();

    cout << "\n=== Тестування функцій ===\n";
    int pos = list1.findPosition("Шевченко");
    cout << "Позиція 'Шевченко' у списку: " << pos << endl;

    Participant nextPart = list1.getElement(pos + 1);
    cout << "Наступний за ним учасник: " << nextPart.surname << endl;

    cout << "\nМіняємо місцями 1-го і 3-го учасника:\n";
    list1.swapElements(1, 3);
    list1.printList();

    cout << "\nВилучаємо 2-го учасника:\n";
    list1.remove(2);
    list1.printList();

    cout << "\n=== Сортування Списку 1 за віком ===\n";
    list1.sortByAge();
    list1.printList();

    cout << "\n=== Створюємо і сортуємо Список 2 ===\n";
    LinkedList list2;
    list2.add({"КВ", "Бойко", "СЗШ №5", 14});
    list2.add({"АА", "Ткаченко", "Ліцей №3", 18});
    list2.sortByAge();
    list2.printList();

    cout << "\n=== ОБ'ЄДНАННЯ ДВОХ ВІДСОРТОВАНИХ СПИСКІВ ===\n";
    LinkedList merged = mergeSortedLists(list1, list2);
    merged.printList();

    return 0;
}