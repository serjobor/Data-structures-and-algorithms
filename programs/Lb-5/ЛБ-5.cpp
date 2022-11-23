// ЛБ-5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// Борисов С.И. ЛБ-5 Вариант 15.
#include<iostream>
#include<ctime>

using namespace std;

void add_to_array(int* A, int value, int n)
{
	int* arr = new int[n + 1];
	arr = A;
	arr[n] = value;
	A = arr;
}
//ф-ция "шейкер"-сортировки
void ShakerSort(int* A, int& n)
{
	int numOfCompare = 0;  //кол-во сравнений
	int numOfReshuffle = 0; // кол-во перестановок

	//while (true)
	//{
		int leftMark = 1;
		int rightMark = n - 1;

		while (leftMark <= rightMark)
		{
			
			for (int i = rightMark; i >=leftMark; i--)
			{
				numOfCompare++;
				if (A[i - 1] > A[i])
				{
					swap(A[i - 1], A[i]);
					//
					numOfReshuffle++;
				}
			}			
			leftMark++;		

			for (int i = leftMark; i <= rightMark; i++)
			{
				numOfCompare++;
				if (A[i - 1] > A[i])
				{
					swap(A[i - 1], A[i]);
					//
					numOfReshuffle++;
				}
			}		
			rightMark--;			
	//	}

	//	break;
	}
	cout << "Кол-во операций сравнения: " << numOfCompare << "\n";
	cout << "Кол-во операций перестановки: " << numOfReshuffle << "\n";
}

void delete_by_index(int*& A, int& n, int index)
{
	int* arr = new int[n - 1];

	if (index == (n - 1))
	{
		for (int i = 0; i < index; i++)
		{
			arr[i] = A[i];
		}
		delete[] A;
		A = arr;
	}
	else
	{
		for (int i = index; i < n; i++)
		{
			A[i] = A[i + 1];
		}
	}
}

void print_array(int* A, int& n)
{
	for (int i = 0; i < n; i++)
	{
		cout << " " << A[i];
	}
	cout << endl;
}

void count_repeated(int* A, int& n)
{
	ShakerSort(A, n);
	print_array(A, n);

	int k = 0;
	int ret = 0;

	for (int i = 0; i < n; i++)
	{
		if (A[i] == A[i + 1])
			ret++;
		else
		{
			if (ret >= 1)
				k++;
			ret = 0;
		}
	}
	cout << "Кол-во повторяющихся чисел: " << k << "\n";
}

int main()
{
	setlocale(LC_ALL, "russian");
	srand(time(0));

	int n;
	cout << "Введите размер массива: ";
	cin >> n;

	int* A = new int[n];
	cout << "Исходный массив:\n";

	
	/*	
	for (int k = 0; k < n; k++)///////////////////////
	{
		A[k] = n - k; // запись значений по убыванию
		cout << A[k] << "[" << k << "]" "\t";
	}
	cout << endl;
	//*/

	///*
	for (int i = 0; i < n; i++)
	{
		A[i] = rand() % 10;
		cout << " " << A[i];
	}
	cout << endl;
	//*/

	int Key_board = 0;
	char x[100];

	while (Key_board != 7)
	{
		cout << "_______________________________________________________" << endl;
		cout << "|Нажмите 1 для добавления элемента.                    |\n";
		cout << "|Нажмите 2 для удаления элемента.                      |\n";
		cout << "|Нажмите 3 чтобы вывести количество повторяющихся чисел|\n";
		cout << "|Нажмите 4 чтобы найти элемент по индексу              |\n";
		cout << "|Нажмите 5 чтобы найти элемент по значению             |\n";
		cout << "|Нажмите 6 для сортировки                              |\n";
		cout << "|Нажмите 7 для выхода из программы                     |\n";
		cout << "|______________________________________________________|" << endl;

		do
		{
			cout << "Выберите пункт: ";
			cin >> x;
		} while (!isdigit(x[0]));

		Key_board = atof(x);

		switch (Key_board)
		{
		case 1:
		{
			int value;

			cout << "Введите значение элемента: ";
			cin >> value;

			add_to_array(A, value, n);
			n++;

			ShakerSort(A, n);

			cout << "Отсортированный массив: ";
			print_array(A, n);

			break;
		}
		case 2:
		{
			int index;

			cout << "Введите индекс элемента: ";
			cin >> index;

			delete_by_index(A, n, index);
			n--;

			ShakerSort(A, n);

			cout << "Отсортированный массив: ";
			print_array(A, n);

			break;
		}
		case 3:
		{
			count_repeated(A, n);
			break;
		}
		case 4:
		{
			int index;

			cout << "Введите индекс элемента: ";
			cin >> index;
			cout << "Найденный элемент: " << A[index] << ": [" << index << "]" << endl;

			break;
		}
		case 5:
		{
			int value;

			cout << "Введите значение элемента: ";
			cin >> value;

			for (int i = 0; i < n; i++)
			{
				if (A[i] == value)
				{
					cout << "Найденный элемент: " << A[i] << ": [" << i << "]" << endl;
				}
			}
			break;
		}
		case 6:
		{
			ShakerSort(A, n);
			cout << "Отсортированный массив: ";
			print_array(A, n);

			break;
		}
		case 7: { return 0; break; }

		default: {cout << "Ошибка ввода.\n"; break; }

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
