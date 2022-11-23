// ЛБ-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
// М011 ЛБ-2 Боривов С. И. Вариант 14. 

#include <iostream>
#include<cmath>
using namespace std;

struct Node // ячейка списка
{
	int val;
	Node* next;
	Node(int x, Node* t)
	{
		val = x;
		next = t;
	}
};

struct cycle_sp
{
	Node* first = new Node(NULL, NULL);
	Node* now = new Node(NULL, first);

	bool is_empty()
	{
		if (first->next == NULL)
			return 0;
		else
			return 1;
	}

	void input(int value)
	{
		Node* new_elem = new Node(value, first);
		if (!is_empty())
		{
			first = new_elem;
			now = new_elem;
			now->next = first;
		}
		else
		{
			now->next = new_elem;
			now = new_elem;
		}
	}

	void erase_first() // удаление элемента с начала
	{
		Node* erased = first;
		first = first->next;
		now->next = first;
		delete erased;
	}

	void erase_elem(int elem)
	{
		if (is_empty() == 0)
			return;
		else
			if (first->val == elem)
			{
				erase_first();
				return;
			}
			else
			{
				if (now->val == elem) // удаление эл в конце
				{
					if (now == first)
					{
						erase_first();
						return;
					}
					Node* erased = first;
					while (erased->next != now)
						erased = erased->next;
					erased->next = first;
					delete now;
					now = erased;
				}
				else
				{
					Node* one = first; // удаление элемента в середине
					Node* second = first->next;
					while (second->next != first && second->val != elem)
					{
						second = second->next;
						one = one->next;
					}
					if (second->next == first && second->val != elem)
					{
						cout << "данного элемента нет в списке.";
						return;
					}
					one->next = second->next;
					delete second;
				}
			}
	}

	void print_sp()
	{
		if (is_empty() == 0)
		{
			return;
		}
		else
		{
			Node* tmp = first;

			while (tmp->next != first)
			{
				cout << tmp->val << ' ';
				tmp = tmp->next;
			}
			cout << tmp->val << ' ';
			tmp = tmp->next;
			cout << endl << endl;
		}
	}

	void zadanie_1(cycle_sp sp)
	{
		Node* tmp = first;

		if (tmp->val % 3 == 0)
			sp.input(tmp->val);
		tmp = tmp->next;

		while (tmp != first)
		{
			if (tmp->val % 3 == 0)
				sp.input(tmp->val);
			tmp = tmp->next;
		}

		cout << "первый список: ";
		sp.print_sp();
		cout << endl;
	}

	void zadanie_2(cycle_sp sp)
	{
		Node* tmp = first;

		if (tmp->val % 2 == 0)
			sp.input(tmp->val);
		tmp = tmp->next;

		while (tmp != first)
		{
			if (tmp->val % 2 == 0)
				sp.input(tmp->val);
			tmp = tmp->next;
		}

		cout << "второй список: ";
		sp.print_sp();
		cout << endl;
	}

	void zadanie_3(cycle_sp sp)
	{
		Node* tmp = first;

		if (((tmp->val % 3 == 0) || (tmp->val % 2 == 0)) && !((tmp->val % 2 == 0) && (tmp->val % 3 == 0)))
			sp.input(tmp->val);
		tmp = tmp->next;

		while (tmp != first)
		{
			if (((tmp->val % 3 == 0) || (tmp->val % 2 == 0)) && !((tmp->val % 2 == 0) && (tmp->val % 3 == 0)))
				sp.input(tmp->val);
			tmp = tmp->next;
		}

		cout << "третий список: ";
		sp.print_sp();
		cout << endl;
	}
};


int main()
{
	setlocale(LC_ALL, "Russian");

	int n, elem;

	cout << "Введите количество элементов исходной последовательности: ";
	cin >> n;

	if (n < 2)
	{
		cout << "Число элементов списка слишком мало." << endl;
		system("pause");
		return 0;
	}
	cout << endl << endl;

	cycle_sp list;
	for (int i = 0; i < n; i++)
	{
		cin >> elem;
		list.input(elem);
	}
	cout << "изначальный список: ";
	list.print_sp();

	cycle_sp list_1;
	cycle_sp list_2;
	cycle_sp list_3;

	list.zadanie_1(list_1);
	list.zadanie_2(list_2);
	list.zadanie_3(list_3);

	cout << endl << endl << "введите удаляемое число: ";
	cin >> elem;
	list.erase_elem(elem);

	cout << "результат после удаления элемента из 1-го списка: ";
	list.print_sp();

	system("pause");
	return 0;
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
