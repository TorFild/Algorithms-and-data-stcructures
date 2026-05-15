#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

struct Edge
{
    int src;
    int dest;
};

struct AdjNode
{
    int dest;
    AdjNode *next;
};

char getNodeName(int index)
{
    return 'a' + index;
}

Edge *am_to_el(int **am, int V, bool isDirected, int &edgeCount)
{

    edgeCount = 0;
    for (int i = 0; i < V; i++)
    {
        for (int j = (isDirected ? 0 : i); j < V; j++)
        {
            if (am[i][j] == 1)
                edgeCount++;
        }
    }

    Edge *el = new Edge[edgeCount];
    int currentEdge = 0;
    for (int i = 0; i < V; i++)
    {
        for (int j = (isDirected ? 0 : i); j < V; j++)
        {
            if (am[i][j] == 1)
            {
                el[currentEdge].src = i;
                el[currentEdge].dest = j;
                currentEdge++;
            }
        }
    }
    return el;
}

int **am_to_im(int **am, int V, bool isDirected, int &E)
{
    Edge *el = am_to_el(am, V, isDirected, E);

    int **im = new int *[V];
    for (int i = 0; i < V; i++)
    {
        im[i] = new int[E];
        for (int j = 0; j < E; j++)
            im[i][j] = 0;
    }

    for (int e = 0; e < E; e++)
    {
        int u = el[e].src;
        int v = el[e].dest;

        if (isDirected)
        {
            im[u][e] = 1;
            im[v][e] = -1;
        }
        else
        {
            im[u][e] = 1;
            im[v][e] = 1;
        }
    }
    delete[] el;
    return im;
}

Edge *im_to_el(int **im, int V, int E, bool isDirected)
{
    Edge *el = new Edge[E];

    for (int e = 0; e < E; e++)
    {
        int src = -1, dest = -1;
        if (isDirected)
        {
            for (int v = 0; v < V; v++)
            {
                if (im[v][e] == 1)
                    src = v;
                if (im[v][e] == -1)
                    dest = v;
            }
            if (src != -1 && dest != -1)
            {
                el[e].src = src;
                el[e].dest = dest;
            }
        }
        else
        {
            for (int v = 0; v < V; v++)
            {
                if (im[v][e] == 1)
                {
                    if (src == -1)
                        src = v;
                    else
                        dest = v;
                }
            }
            if (dest == -1)
                dest = src;
            if (src != -1)
            {
                el[e].src = src;
                el[e].dest = dest;
            }
        }
    }
    return el;
}

int **im_to_am(int **im, int V, int E, bool isDirected)
{

    int **am = new int *[V];
    for (int i = 0; i < V; i++)
    {
        am[i] = new int[V];
        for (int j = 0; j < V; j++)
            am[i][j] = 0;
    }

    Edge *el = im_to_el(im, V, E, isDirected);
    for (int e = 0; e < E; e++)
    {
        int u = el[e].src;
        int v = el[e].dest;
        am[u][v] = 1;
        if (!isDirected)
        {
            am[v][u] = 1;
        }
    }
    delete[] el;
    return am;
}

AdjNode **am_to_al(int **am, int V)
{
    AdjNode **al = new AdjNode *[V];
    for (int i = 0; i < V; i++)
        al[i] = nullptr;

    for (int i = 0; i < V; i++)
    {
        AdjNode *tail = nullptr;
        for (int j = 0; j < V; j++)
        {
            if (am[i][j] == 1)
            {
                AdjNode *newNode = new AdjNode{j, nullptr};
                if (al[i] == nullptr)
                {
                    al[i] = newNode;
                    tail = newNode;
                }
                else
                {
                    tail->next = newNode;
                    tail = newNode;
                }
            }
        }
    }
    return al;
}

AdjNode **im_to_al(int **im, int V, int E, bool isDirected)
{
    int **tempAM = im_to_am(im, V, E, isDirected);
    AdjNode **al = am_to_al(tempAM, V);

    for (int i = 0; i < V; i++)
        delete[] tempAM[i];
    delete[] tempAM;

    return al;
}

void printAM(int **am, int V)
{
    cout << "   a  b  c  d  e  f\n";
    for (int i = 0; i < V; i++)
    {
        cout << getNodeName(i) << " ";
        for (int j = 0; j < V; j++)
        {
            cout << setw(2) << am[i][j] << " ";
        }
        cout << endl;
    }
}

void printIM(int **im, int V, int E)
{
    if (E == 0)
        return;
    cout << "   e1 e2 e3 ... (ребра)\n";
    for (int i = 0; i < V; i++)
    {
        cout << getNodeName(i) << " ";
        for (int j = 0; j < E; j++)
        {
            cout << setw(2) << im[i][j] << " ";
        }
        cout << endl;
    }
}

void printEL(Edge *el, int E)
{
    cout << "{ ";
    for (int i = 0; i < E; i++)
    {
        cout << "(" << getNodeName(el[i].src) << "," << getNodeName(el[i].dest) << ") ";
    }
    cout << "}\n";
}

void printAL(AdjNode **al, int V)
{
    for (int i = 0; i < V; i++)
    {
        cout << getNodeName(i) << " -> ";
        AdjNode *current = al[i];
        while (current != nullptr)
        {
            cout << getNodeName(current->dest) << " ";
            current = current->next;
        }
        cout << endl;
    }
}

void freeMatrix(int **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
        delete[] matrix[i];
    delete[] matrix;
}

void freeAL(AdjNode **al, int V)
{
    for (int i = 0; i < V; i++)
    {
        AdjNode *current = al[i];
        while (current != nullptr)
        {
            AdjNode *temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] al;
}

void processGraph(int **am, int V, string graphName, bool isDirected)
{
    cout << "\n======================================================\n";
    cout << "        АНАЛІЗ ГРАФА: " << graphName << endl;
    cout << "======================================================\n";

    cout << "\n--- Вихідна Матриця Суміжності (AM) ---\n";
    printAM(am, V);

    int E = 0;
    cout << "\n1. За заданою AM побудувати Матрицю Інцидентності (IM):\n";
    int **im = am_to_im(am, V, isDirected, E);
    printIM(im, V, E);

    cout << "\n2. За заданою IM побудувати Список Ребер (EL):\n";
    Edge *el_from_im = im_to_el(im, V, E, isDirected);
    printEL(el_from_im, E);

    cout << "\n3. За заданою AM побудувати Список Суміжності (AL):\n";
    AdjNode **al_from_am = am_to_al(am, V);
    printAL(al_from_am, V);

    cout << "\n4. За заданою IM побудувати Матрицю Суміжності (AM):\n";
    int **am_from_im = im_to_am(im, V, E, isDirected);
    printAM(am_from_im, V);

    cout << "\n5. За заданою AM побудувати Список Ребер (EL):\n";
    Edge *el_from_am = am_to_el(am, V, isDirected, E);
    printEL(el_from_am, E);

    cout << "\n6. За заданою IM побудувати Список Суміжності (AL):\n";
    AdjNode **al_from_im = im_to_al(im, V, E, isDirected);
    printAL(al_from_im, V);

    freeMatrix(im, V);
    freeMatrix(am_from_im, V);
    delete[] el_from_im;
    delete[] el_from_am;
    freeAL(al_from_am, V);
    freeAL(al_from_im, V);
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    int V = 6;

    int **am_undirected = new int *[V];
    int data1[6][6] = {
        {1, 0, 1, 1, 0, 0},
        {0, 1, 1, 1, 0, 0},
        {1, 1, 1, 0, 1, 1},
        {1, 1, 0, 1, 1, 1},
        {0, 0, 1, 1, 1, 0},
        {0, 0, 1, 1, 0, 1}};
    for (int i = 0; i < V; i++)
    {
        am_undirected[i] = new int[V];
        for (int j = 0; j < V; j++)
            am_undirected[i][j] = data1[i][j];
    }

    int **am_directed = new int *[V];
    int data2[6][6] = {
        {0, 1, 1, 1, 0, 1},
        {0, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0, 1},
        {0, 0, 0, 0, 0, 1},
        {0, 0, 1, 0, 0, 0}};
    for (int i = 0; i < V; i++)
    {
        am_directed[i] = new int[V];
        for (int j = 0; j < V; j++)
            am_directed[i][j] = data2[i][j];
    }

    processGraph(am_undirected, V, "Неорієнтований граф ", false);
    processGraph(am_directed, V, "Орієнтований граф ", true);

    freeMatrix(am_undirected, V);
    freeMatrix(am_directed, V);

    return 0;
}