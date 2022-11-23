// ЛБ-6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// Борисов С.И. ЛБ-6 Вариант 10.

#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

int tabs = 0;

struct Node // структура для представления узлов дерева
{
    string FIO;
    unsigned char height;
    Node* left;
    Node* right;
    Node(string k) { FIO = k; left = right = 0; height = 1; }
};

int height(Node* p) // высота
{
    return p ? p->height : 0;
}

int bfactor(Node* p)  //разность высот левого и правого поддеревьев
{
    return height(p->right) - height(p->left);
}

void fixheight(Node* p) // восстановка корректного поля высоты заданного узла
{
    int hl = height(p->left);
    int hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

Node* rotate_right(Node* p) // правый поворот вокруг p
{
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

Node* rotate_left(Node* q) // левый поворот вокруг q
{
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

Node* balance(Node* p) // балансировка
{
    fixheight(p);
    if (bfactor(p) == 2)
    {
        if (bfactor(p->right) < 0)
            p->right = rotate_right(p->right);
        return rotate_left(p);
    }
    if (bfactor(p) == -2)
    {
        if (bfactor(p->left) > 0)
            p->left = rotate_left(p->left);
        return rotate_right(p);
    }
    return p;
}

Node* insert(Node* p, string k) // вставка ключа k в дерево с корнем p
{
    if (p == NULL) return new Node(k);
    if (k < p->FIO)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

Node* find_min(Node* p) // поиск узла с минимальным ключом в дереве p 
{
    return p->left ? find_min(p->left) : p;
}

Node* remove_min(Node* p) // удаление узла с минимальным ключом из дерева p
{
    if (p->left == 0)
        return p->right;
    p->left = remove_min(p->left);
    return balance(p);
}

Node* remove(Node* p, string k) // удаление ключа k из дерева p
{
    if (!p) return 0;
    if (k < p->FIO)
        p->left = remove(p->left, k);
    else if (k > p->FIO)
        p->right = remove(p->right, k);
    else  
    {
        Node* q = p->left;
        Node* r = p->right;
        delete p;
        if (!r) return q;
        Node* min = find_min(r);
        min->right = remove_min(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

void tree_print(Node* p)
{
    if (p != NULL) 
    {
        tree_print(p->left);
        cout << p->FIO << endl;
        tree_print(p->right);
    }
}

void tree_print_beautiful(Node* p)
{
    if (p != NULL)
    {
        tabs += 5;        
        tree_print_beautiful(p->left);
        for (int i = 0; i < tabs; i++) cout << " ";
        cout << p->FIO << endl;
        tree_print_beautiful(p->right);
        tabs -= 5;
    }
}

////Node* treeabs(Node* p) 
////{
////    if (p != NULL) 
////    {
////        treeabs(p->left);
////        treeabs(p->right);
////        p->FIO = abs(p->FIO);        
////        return balance(p);
////    }
////}
////
////Node* tree4(Node* p)
////{
////    if (p != NULL) 
////    {
////        if (p->FIO % 4 == 0)
////        {
////            p->FIO /= 2;
////        }
////        tree4(p->left);
////        tree4(p->right);
////        return balance(p);
////    }
////}
//
////struct Node_list
////{
////    Node* val;
////    Node_list* pnext;
////    Node_list(Node* v, Node_list* n) 
////    {
////        val = v;
////        pnext = n;
////    }
////};
//
////struct List
////{
////    Node_list* first = NULL;
////    Node_list* tail = NULL;
////    bool is_empty() 
////    {
////        return first ? 0 : 1;
////    };
////    void add(Node* v) 
////    {
////        Node_list* new_elem = new Node_list(v, NULL);
////        if (is_empty()) 
////        {
////            first = new_elem;
////            tail = new_elem;
////        }
////        else
////        {
////            tail->pnext = new_elem;
////            tail = new_elem;
////        }
////    }
////    void minus() 
////    {
////        Node_list* tmp1 = first;
////        Node_list* tmp2 = first->pnext;
////        do 
////        {
////            tmp2->val->FIO -= tmp1->val->FIO;
////            tmp1 = tmp1->pnext;
////            tmp2 = tmp2->pnext;
////        } while (tmp2 != NULL);
////    }
////};
//
////Node* trees(Node* p, List* n) 
////{
////    if (p != NULL)
////    {
////        trees(p->left, n);
////        trees(p->right, n);
////        n->add(p);
////        return balance(p);
////    }
////}

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("color 0F");

    Node* p = NULL;
    char x[100];
    int choice = -1;

    while (choice != 0) 
    {
        cout << "________________________________________________________________________\n";
        cout << "|1. Показать дерево.                                                   |\n";
        cout << "|2. Добавить вершину.                                                  |\n";
        cout << "|3. Удалить вершину.                                                   |\n";
       // cout << "|4. Заменить отриц на полож и делящиеся на 4 без остатка уменьшить в 2.|\n";
       // cout << "|5. От текущей вершины отнять предыдущую.                              |\n";
        cout << "|6. Красивое дерево.                                                   |\n";
        cout << "|0. Выход.                                                             |\n";
        cout << "|______________________________________________________________________|\n";
        cout << "Введите пункт меню: ";
        do 
        {
            cin >> x;
        } while (!isdigit(x[0]));
        choice = atof(x);
        cin.get();
       
        switch (choice)
        {
        case 1:
        {
            tree_print(p);
            break;
        }
        case 2:
        {
            cout << "Введите значение: ";
            string elem;
            getline(cin, elem);
            p = insert(p, elem);
            break;
        }
        case 3:
        {           
            cout << "Введите значение: ";
            string elem;
            getline(cin, elem);
            p = remove(p, elem);
            break;
        }
        case 4:
        {
            /*treeabs(p);
            tree4(p);
            cout << "Новое дерево: \n";
            tree_print(p);*/
            break;
        }
        case 5:
        {
           /* List* n = new List;
            trees(p, n);
            n->minus();
            cout << "Новое дерево: \n";
            tree_print(p);*/
            break;
        }
        case 6:
        {
            tree_print_beautiful(p);
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


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
