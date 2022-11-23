// ЛБ-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// М011 ЛБ-1 Боривов С. И. Вариант 10. 

#include <iostream>
using namespace std;
void NOT_Chet(int x);
int Minus_summ(int* c, int y);

void NOT_Chet(int x) // Функция которая выводит кол-во нечетных элементов в массиве.
{
    cout << endl << "Кол-во нечетных элементов в массиве :" << x << "\n";
}

int Minus_summ(int* c, int y) //  Функция считающая cумму отрицательных элементов в массиве.
{
    int minusSumm = 0; 

    for (int i = 0; i < y; i++)
    {
        if (c[i] < 0) // если элемент массива меньше 0, то сумма отриц увеличивается.
            minusSumm += c[i];
    }
    cout << endl << "Сумма отрицательных элементов в массиве :" << minusSumm << "\n";
    return 0;
}

int main()
{
    setlocale(LC_ALL, "rus");
    
    int n;
    cout << "Введите размер массива: ";
    cin >> n;

    int *randomDigits =new int [n]; // создание динамического массива.
    cout << "Заполнение массива случайными цифрами: \n";
    srand(time(NULL));

    for (int i = 0; i < n; i++) // заполнение массива случайными числами.
    {
        randomDigits[i] = -((n / 2) - 1) + rand() % (n-1);
    }
    cout << endl << "Массив c цифрами: " << "\n";
    for (int i = 0; i < n; i++)
    {
        cout << randomDigits[i] << "  ";
    }

    int Key_board = 0; 
    while (Key_board == 0) 
    {
        cout << endl << "Меню: \n";
        cout << "Введите 1, если хотите подсчитать кол-во нечетных элементов в массиве. \n";
        cout << "Введите 2, если хотите подсчитать сумму отрицательных элементов в массиве. \n";
        cout << "Введите 3, если хотите выйти из программы. \n";
        cout << "Ввод: ";
        cin >> Key_board;

        switch (Key_board) 
        {
        case 1:
        {
            // NOT_Chet(randomDigits, n);

            int not_chet_summ = 0;

            for (int i = 0; i < n; i++)
            {
                if ((randomDigits[i] % 2) != 0) // Если остаток от деления на 2 не равен 0, то сумма нечетных увеличиваеться на 1
                    not_chet_summ += 1;
            }

            NOT_Chet(not_chet_summ);
            

            int Key_board_2 = 0;
            cout << "Введите 1, если хотите вернуться в меню \n";
            cout << "Введите 2, если хотите выйти из программы. \n";
            cout << "Ввод: ";
            while (Key_board_2 == 0)
            {
                cin >> Key_board_2;
                switch (Key_board_2)
                {
                case 1:
                {
                    Key_board = 0;
                    break;
                }
                case 2:
                {
                    cout << "Осуществляеться выход из программы..." << endl;
                    exit(EXIT_SUCCESS);
                    break;
                }
                default:
                {
                    cout << "Ошибка! Запрос введен некоректно!";
                    cout << "Повторите ввод: ";
                    Key_board_2 = 0;
                    break;
                }
                }
            }
            break;
        }
        case 2:
        {
            Minus_summ(randomDigits, n);
            int Key_board_3 = 0;
            cout << "Введите 1, если хотите вернуться в меню \n";
            cout << "Введите 2, если хотите выйти из программы. \n";
            cout << "Ввод: ";
            while (Key_board_3 == 0)
            {
                cin >> Key_board_3;
                switch (Key_board_3)
                {
                case 1:
                {
                    Key_board = 0;
                    break;
                }
                case 2:
                {
                    cout << "Осуществляеться выход из программы..." << endl;
                    exit(EXIT_SUCCESS);
                    break;
                }
                default:
                {
                    cout << "Ошибка! Запрос введен некоректно!";
                    cout << "Повторите ввод: ";
                    Key_board_3 = 0;
                    break;
                }
                }
            }
            break;
        }
        case 3:
        {
            cout << "Осуществляеться выход из программы..." << endl;
            exit(EXIT_SUCCESS);
            break;
        }
        default:
        {
            cout << "Ошибка! Запрос введен некоректно!";
            cout << "Повторите ввод: ";
            Key_board = 0;
            break;
        }
        }
    }
    delete[]randomDigits;
   
 return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

/*
int NOT_Chet(int* b, int x) // Функция считающая кол-во нечетных элементов в массиве.
{
    int not_chet_summ = 0;

    for (int i = 0; i < x; i++)
    {
        if ((b[i] % 2) != 0) // Если остаток от деления на 2 не равен 0, то сумма нечетных увеличиваеться на 1
            not_chet_summ += 1;
    }
    cout << endl << "Кол-во нечетных элементов в массиве :" << not_chet_summ << "\n" ;
    return not_chet_summ;
}
*/

/*
#include <numeric>
#include <stdlib.h>
#include <ctime>
NOT_Chet(randomDigits, n);
Minus_summ(randomDigits, n);
*/
// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
