#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

struct Participant
{
    string surname;
    int age;
    int score;
};

struct Node
{
    Participant data;
    Node *left;
    Node *right;
};

void addBySurname(Participant p, Node *&node)
{
    if (node == nullptr)
    {
        node = new Node{p, nullptr, nullptr};
        return;
    }
    if (p.surname < node->data.surname)
    {
        addBySurname(p, node->left);
    }
    else
    {
        addBySurname(p, node->right);
    }
}

void addByAge(Participant p, Node *&node)
{
    if (node == nullptr)
    {
        node = new Node{p, nullptr, nullptr};
        return;
    }
    if (p.age < node->data.age)
    {
        addByAge(p, node->left);
    }
    else
    {
        addByAge(p, node->right);
    }
}

void printTree(Node *node)
{
    if (node != nullptr)
    {
        printTree(node->left);
        cout << left << setw(15) << node->data.surname
             << left << setw(10) << node->data.age
             << left << setw(10) << node->data.score << endl;
        printTree(node->right);
    }
}

void getAgeSumAndCount(Node *node, int &sum, int &count)
{
    if (node != nullptr)
    {
        getAgeSumAndCount(node->left, sum, count);
        sum += node->data.age;
        count++;
        getAgeSumAndCount(node->right, sum, count);
    }
}

void deleteTree(Node *&node)
{
    if (node != nullptr)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
        node = nullptr;
    }
}

void transferData(Node *source, Node *&destRoot)
{
    if (source != nullptr)
    {
        transferData(source->left, destRoot);
        addByAge(source->data, destRoot);
        transferData(source->right, destRoot);
    }
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Node *treeBySurname = nullptr;
    Node *treeByAge = nullptr;

    cout << "Введіть кількість учасників: ";
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        Participant p;
        cout << "\nУчасник " << i + 1 << ":" << endl;
        cout << "Прізвище: ";
        cin >> p.surname;
        cout << "Вік: ";
        cin >> p.age;
        cout << "Бали: ";
        cin >> p.score;
        addBySurname(p, treeBySurname);
    }

    cout << "\n=== Дерево 1 (впорядковане за ПРІЗВИЩЕМ) ===" << endl;
    cout << left << setw(15) << "Прізвище" << setw(10) << "Вік" << setw(10) << "Бали\n";
    cout << "-----------------------------------" << endl;
    printTree(treeBySurname);

    int sumAge = 0, count = 0;
    getAgeSumAndCount(treeBySurname, sumAge, count);
    if (count > 0)
    {
        cout << "\nСередній вік учасників: " << (double)sumAge / count << " років." << endl;
    }

    cout << "\nПересипаємо дані у Дерево 2 (за віком) та видаляємо Дерево 1..." << endl;
    transferData(treeBySurname, treeByAge);
    deleteTree(treeBySurname);

    cout << "\n=== Дерево 2 (впорядковане за ВІКОМ) ===" << endl;
    cout << left << setw(15) << "Прізвище" << setw(10) << "Вік" << setw(10) << "Бали\n";
    cout << "-----------------------------------" << endl;
    printTree(treeByAge);

    cout << "\nОчищення пам'яті..." << endl;
    deleteTree(treeByAge);
    cout << "Програму завершено." << endl;

    return 0;
}