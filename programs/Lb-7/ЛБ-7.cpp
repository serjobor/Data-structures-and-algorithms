// ЛБ-7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
// Борисов С.И. ЛБ-7 Вариант 7.
#include <iostream>
using namespace std;

struct Node
{
    int inf;
    Node* next;
};

int check(int A) //проверка корректности ввода
{
    while (cin.fail() || cin.rdbuf()->in_avail() > 1 || A < 0) //проверка корректности ввода
    {
        cout << "Введено недопустимое значение переменной. Пожалуйста, повторите попытку: ";
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        cin >> A;
    }
    return A;
}


void push(Node*& st, int dat) // Загрузка числа в стек
{
    Node* el = new Node;
    el->inf = dat;
    el->next = st;
    st = el;
}

int pop(Node*& st) // Извлечение из стека
{   
    int value = st->inf;
    Node* temp = st;
    st = st->next;
    delete temp;

    return value;
}

int peek(Node* st)// Получение числа без его извлечения
{     
    return st->inf;
}

Node** graph;   // Массив списков смежности

void add(Node*& list, int data) //Добавление смежной вершины
{  
    if (!list) { list = new Node; list->inf = data; list->next = 0; return; }

    Node* temp = list;
    while (temp->next)temp = temp->next;
    Node* elem = new Node;
    elem->inf = data;
    elem->next = NULL;
    temp->next = elem;
}

void del(Node*& l, int key) // Удаление вершины key из списка
{ 
    if (l->inf == key) { Node* tmp = l; l = l->next; delete tmp; }
    else
    {
        Node* tmp = l;
        while (tmp)
        {
            if (tmp->next) // есть следующая вершина
                if (tmp->next->inf == key)// и если она искомая
                {  
                    Node* tmp2 = tmp->next;
                    tmp->next = tmp->next->next;
                    delete tmp2;
                }
            tmp = tmp->next;
        }
    }
}

int eiler(Node** gr, int num) // Определение эйлеровости графа
{
    int count;
    for (int i = 0; i < num; i++) //проход по всем вершинам
    {  
        count = 0;
        Node* tmp = gr[i];
        while (tmp) // считаем степень
        { 
            count++; 
            tmp = tmp->next;
        }
        if (count % 2 == 1)return 0; // степень нечетная
    }
    return 1;   // все степени четные
}

void eiler_path(Node** gr, int vertex)//Построение цикла
{ 
    Node* S = NULL; // Стек для  пройденных вершин
    int v = vertex - 1; // 1я вершина (произвольная)
    int u;

    push(S, v); //сохраняем ее в стек
    while (S) //пока стек не пуст
    {  
        v = peek(S); // текущая вершина
        if (!gr[v])// если нет инцидентных ребер
        { 
            v = pop(S); cout << v + 1 << "   "; //выводим вершину  (у нас отсчет от 1, поэтому +1)
        }
        else
        {
            u = gr[v]->inf; push(S, u);  //проходим в следующую вершину
            del(gr[v], u); del(gr[u], v); //удаляем пройденное ребро
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Количество вершин:  "; int n; cin >> n; // Количество вершин
    n = check(n);
    int zn; // Текущее значение
    int vertex;

    graph = new Node * [n];
    for (int i = 0; i < n; i++)graph[i] = NULL;
    for (int i = 0; i < n; i++)   // заполняем массив списков
        for (int j = 0; j < n; j++)
        {
            cin >> zn;
            if (zn) add(graph[i], j);
        }
    cout << "Выберети вершину, из которой начнётся поиск Эйлерова пути: ";
    do
    {
        cin >> vertex;
        vertex = check(vertex);
    } while (vertex > n);
    cout << "\n\nРезультат пути:  ";

    if (eiler(graph, n))eiler_path(graph, vertex);
    else cout << "Граф не является эйлеровым.";

    cout << endl;
    return(0);
}





























/*
#include <iostream>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include<vector>
#include<string>
using namespace std;

void show(vector<vector<int>>matrix);
int Search1(vector<vector<int>> matrix, int location, int const node2, vector<bool> UsedTemp, vector <bool>& Used, vector <int> Way, bool& T, int kol = 0);
int Search2(vector<vector<int>> matrix, int location, int const node2, vector<bool> UsedTemp, vector <bool>& Used, vector <int> Way, bool& T, int kol = 0);

int main() 
{
    setlocale(LC_ALL, "Russian");
    vector <int> Way;

    int N; int M; 
    int location; //
    int node1; // начальная вершина
    int node2; // конечная вершина
    bool t1 = false;
    bool t2 = false;
    int temp;
    
    setlocale(LC_ALL, "Russian");
    cout << "Введите количество вершин орграфа N="; cin >> N; cout << endl;

    cout << "Введите количество ребер орграфа, оно не должно превышать " << (N * (N - 1)) / 2 << " , M="; cin >> M; cout << endl;
    vector<vector<int> > matrix(N);
    vector <bool> UsedEdges(M); // использ ребра
    vector <bool> UsedNodes(N); // использ узлы 

    for (int i = 0; i < N; i++) // Заполнение матрицы вершинами
        matrix[i].resize(M);    // Заполнит матрицу вершинами и скорректирует размер под кол-во ребер если их больше

    for (int j = 0; j < M; j++)  //Заполнение матрицы ребрами
    {                                  
        t1 = t2 = false;
        cout << "Введите связи для " << j + 1 << " - ого ребра!" << endl;
        for (int i = 0; i < N; i++)
        {
            cout << "(Вершина  " << i + 1 << ") ";
            if (t1 && t2) 
            {
                cout << "0" << endl;
                continue;
            }
            cin >> temp;

            if (temp < -1 || temp >1) 
            {
                cout << "Неверный ввод!" << endl;
                return 0;
            }
            else if (temp == -1 && t2) 
            {
                cout << "Неверный ввод!" << endl;
                return 0;
            }
            else if (temp == 1 && !t1)
                t1 = true;
            else if (temp == -1 || temp == 1)
                t2 = true;

            matrix[i][j] = temp;
        }
    }

    bool T = false;
    show(matrix);
    cout << "Введите номер начальной вершины: "; cin >> node1; node1--;
    cout << "Введите номер конечной вершины: "; cin >> node2; node2--;
    cout << endl;

    char x[100];
    int choice = -1;
    while (choice != 0)
    {
        cout << "Найти все пути не пересекающиеся по ребрам - 1 \n";
        cout << "Найти все пути не пересекающиеся по вершинам - 2 \n";
        cout << "Выход из программы - 0 \n";
        cout << "Введите выбранный пункт: ";
        do
        {
            cin >> x;
        } while (!isdigit(x[0]));
        choice = atof(x);
        cout << "\n";

        switch (choice)
        {
        case 1:
        {
            Search1(matrix, node1, node2, UsedEdges, UsedEdges, Way, T);
            break;
        }
        case 2:
        {
            Search2(matrix, node1, node2, UsedNodes, UsedNodes, Way, T);
            break;
        }
        case 0:
        {
            return 0;
            break;
        }
        }        
    }
}

void show(vector<vector<int>> matrix)  // демонстрация матрицы
{
    for (int i = 0; i < matrix.size(); i++) 
    {
        for (int j = 0; j < matrix[i].size(); j++) 
        {
            cout << setw(3) << matrix[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

int Search1(vector<vector<int>> matrix, int location, int const node2, vector<bool> UsedTemp, vector <bool>& Used, vector <int> Way, bool& T, int kol)
{                           // матрица  вершина начала  вершина конца   вектор с ребрами      вектор с ребрами       вектор пути   логическая Т; 
    Way.push_back(location + 1);
    if (location == node2)
    {
        T = true;
        for (int i = 0; i < matrix[0].size(); i++) 
        {
            if (UsedTemp[i] == true) 
            {
                Used[i] = true;
            }
        }

        for (vector<int>::iterator it = Way.begin(); it != Way.end(); ++it)
            cout << *it;
        cout << endl;
        return 1;
    }

    for (int i = kol % matrix[0].size();; i = (i + 1))
    {
        T = false;
        if (kol == 0 && i == matrix[0].size()) 
        {
            break;
        }
        i = i % matrix[0].size();
        if (kol != 0 && i == kol - 1) 
        {
            break;
        }

        if (matrix[location][i] == 1 && Used[i] == false && UsedTemp[i] == false) ////////
        {

            UsedTemp[i] = true;
            for (int j = 0; j < matrix.size(); j++) 
            {
                if (matrix[j][i] == -1 || matrix[j][i] == 1 && j != location) 
                {
                    Search1(matrix, j, node2, UsedTemp, Used, Way, T, i + 1);
                    break;
                }//////////
            }
            if (location > 0 && T) 
            {
                break;
            }
        }
    }
}

int Search2(vector<vector<int>> matrix, int location, int const node2, vector<bool> UsedTemp, vector <bool>& Used, vector <int> Way, bool& T, int kol)
{
    Way.push_back(location + 1);
    if (location == node2)
    {
        T = true;
        for (int i = 0; i < matrix.size(); i++)
        {
            if (UsedTemp[i] == true)
            {
                Used[i] = true;
            }
        }
        Used[node2] = false;
        for (vector<int>::iterator it = Way.begin(); it != Way.end(); ++it)
            cout << *it;
        cout << endl;
        return 1;
    }

    for (int i = kol % matrix[0].size();; i = (i + 1)) 
    {
        T = false;
        if (kol == 0 && i == matrix[0].size()) 
        {
            break;
        }
        i = i % matrix[0].size();
        if (kol != 0 && i == kol - 1) 
        {
            break;
        }

        if (matrix[location][i] == 1) ///////////////////////////////////////////
        {
            for (int j = 0; j < matrix.size(); j++) 
            {
                if (matrix[j][i] == -1 || matrix[j][i] == 1 && j != location)
                {
                    if (UsedTemp[j] == false && Used[j] == false) 
                    {
                        UsedTemp[j] = true;
                        Search2(matrix, j, node2, UsedTemp, Used, Way, T, i + 1);
                    }
                    break;
                }////////////////////////////////////////////
            }
            if (location > 0 && T)
            {
                break;
            }
        }
    }
}
*/
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
