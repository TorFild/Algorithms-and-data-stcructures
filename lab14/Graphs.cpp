#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

const int V = 6;

struct Queue
{
    int data[V];
    int front, rear;
    Queue()
    {
        front = 0;
        rear = 0;
    }
    void push(int val) { data[rear++] = val; }
    int pop() { return data[front++]; }
    bool isEmpty() { return front == rear; }
};

char name(int i) { return 'a' + i; }

void BFS(int **matrix, int startNode)
{
    bool visited[V] = {false};
    Queue q;

    visited[startNode] = true;
    q.push(startNode);

    cout << "BFS: ";
    while (!q.isEmpty())
    {
        int curr = q.pop();
        cout << name(curr) << " ";

        for (int i = 0; i < V; i++)
        {
            if (matrix[curr][i] != 0 && !visited[i])
            {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << endl;
}

void DFS_Recursive(int **matrix, int curr, bool visited[])
{
    visited[curr] = true;
    cout << name(curr) << " ";

    for (int i = 0; i < V; i++)
    {
        if (matrix[curr][i] != 0 && !visited[i])
        {
            DFS_Recursive(matrix, i, visited);
        }
    }
}

void DFS(int **matrix, int startNode)
{
    bool visited[V] = {false};
    cout << "DFS: ";
    DFS_Recursive(matrix, startNode, visited);
    cout << endl;
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int **am_undirected = new int *[V];
    int **am_directed = new int *[V];

    int d1[6][6] = {
        {0, 0, 1, 1, 0, 0}, {0, 0, 1, 1, 0, 0}, {1, 1, 0, 0, 1, 1}, {1, 1, 0, 0, 1, 1}, {0, 0, 1, 1, 0, 0}, {0, 0, 1, 1, 0, 0}};
    int d2[6][6] = {
        {0, 1, 1, 1, 0, 1}, {0, 0, 1, 1, 1, 0}, {0, 0, 0, 0, 1, 0}, {0, 0, 1, 0, 0, 1}, {0, 0, 0, 0, 0, 1}, {0, 0, 1, 0, 0, 0}};

    for (int i = 0; i < V; i++)
    {
        am_undirected[i] = new int[V];
        am_directed[i] = new int[V];
        for (int j = 0; j < V; j++)
        {
            am_undirected[i][j] = d1[i][j];
            am_directed[i][j] = d2[i][j];
        }
    }

    cout << "=== НЕОРІЄНТОВАНИЙ ГРАФ ===" << endl;
    BFS(am_undirected, 0);
    DFS(am_undirected, 0);

    cout << "\n=== ОРІЄНТОВАНИЙ ГРАФ ===" << endl;
    BFS(am_directed, 0);
    DFS(am_directed, 0);

    for (int i = 0; i < V; i++)
    {
        delete[] am_undirected[i];
        delete[] am_directed[i];
    }
    delete[] am_undirected;
    delete[] am_directed;

    return 0;
}