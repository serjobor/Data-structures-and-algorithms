// ЛБ-3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// М011 ЛБ-3 Боривов С. И. Вариант 4. 
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

struct task 
{
	string name;

	int proceed_time;

	int needed_time;

	int input_time;

	int priority;
};

struct stack_element 
{
	struct task* value;

	struct stack_element* next;
};

struct processor 
{
	struct task* task;

	struct stack_element* stack;
};

struct queue_element
{
	struct task* task;

	struct queue_element* last;
};

struct task_queue
{
	struct queue_element* queue0;
	struct queue_element* queue1;
	struct queue_element* queue2;
};

string task_to_string(struct task* task) 
{
	string name_pre("\tИмя: ");
	string proceed_pre("\n\tВремя  выполнения задачи: ");
	string priority_pre("\n\tПриоритет: ");
	string input_pre("\n\t Время поступления: ");
	string needed_pre("\n\tНеобходимое время: ");

	return name_pre + task->name + proceed_pre
		+ to_string(task->proceed_time) 
		+ needed_pre + to_string(task->needed_time) 
		+ priority_pre + to_string(task->priority)
		+ input_pre + to_string(task->input_time) + "\n";

}

int get_queue_length(struct queue_element* queue) // п длина очереди
{
	struct queue_element* ptr = queue;

	int i = 0;
	if (queue == 0)

		return 0;

	while (ptr != NULL) 
	{
		i++;
		ptr = ptr->last;
	}

	return i;
}

struct task* generate_task(string name, int needed_time, int input_time, int priority) 
{
	struct task* ret = new struct task;

	ret->name = name;
	ret->needed_time = needed_time;
	ret->input_time = input_time;
	ret->priority = priority;
	ret->proceed_time = 0;

	return ret;
}

struct task* generate_random(int time) 
{
	string name;

	cout << "Введите имя: ";
	cin >> name;

	return generate_task(name, rand() % 10 + 1, time, rand() % 3);
}

struct stack_element* push_stack(struct stack_element* stack, struct task* task)
{
	struct stack_element* new_element = new struct stack_element;

	new_element->next = stack;
	new_element->value = task;

	return new_element;
}

struct stack_element* pop_stack(struct stack_element* stack, struct task* task) 
{
	*task = *(stack->value);

	return stack->next;
}

void push_task_queue(struct task_queue* queue, struct task* task) 
{
	struct queue_element* ptr;

	struct queue_element* new_element = new struct queue_element;

	new_element->task = task;

	new_element->last = 0;

	switch (task->priority) 
	{
	case 0:

		if (queue->queue0 == 0)
		{
			queue->queue0 = new_element;

			cout << "Задача добавлена: \n" << task_to_string(new_element->task) << endl;

			return;
		}

		ptr = queue->queue0;

		while (ptr->last != NULL)

			ptr = ptr->last;

		ptr->last = new_element;

		break;

	case 1:

		if (queue->queue1 == 0) 
		{
			queue->queue1 = new_element;

			cout << "Задача добавлена: \n" << task_to_string(new_element->task) << endl;

			return;

		}
		ptr = queue->queue1;

		while (ptr->last != NULL)

			ptr = ptr->last;

		ptr->last = new_element;

		break;

	case 2:

		if (queue->queue2 == 0) 
		{
			queue->queue2 = new_element;

			cout << "Задача добавлена: \n" << task_to_string(new_element->task) << endl;

			return;

		}
		ptr = queue->queue2;

		while (ptr->last != NULL)

			ptr = ptr->last;

		ptr->last = new_element;

		break;
	}
	cout << "Задача добавлена: \n" << task_to_string(new_element->task) << endl;

	return;
}

struct task* pop_task_queue(struct task_queue* queue)
{
	struct queue_element* ret;

	if (get_queue_length(queue->queue0) != 0) 
	{
		ret = queue->queue0;

		queue->queue0 = queue->queue0->last;

		return ret->task;
	}

	if (get_queue_length(queue->queue1) != 0) 
	{
		ret = queue->queue1;

		queue->queue1 = queue->queue1->last;

		return ret->task;
	}

	if (get_queue_length(queue->queue2) != 0) 
	{
		ret = queue->queue2;

		queue->queue2 = queue->queue2->last;

		return ret->task;
	}

	return 0;
}

int get_queue_priority(struct task_queue* queue) 
{
	if (get_queue_length(queue->queue0) == 0)
	{
		if (get_queue_length(queue->queue1) == 0)
		{
			if (get_queue_length(queue->queue2) == 0) 
			{
				return 3;
			} 
			return 2;
		}
		else 
			return 1;
	}

	else return 0;
}

void add_random(struct task_queue* queue, int time) 
{
	push_task_queue(queue, generate_random(time));
}

string queues_to_string(struct task_queue* queue) 
{
	string ret("");

	struct queue_element* ptr = queue->queue0;

	ret += "\nОчередь 0:";

	while (ptr != 0) 
	{
		ret += "\n" + task_to_string(ptr->task);
		ptr = ptr->last;
	}

	ptr = queue->queue1;
	ret += "\n\nОчередь 1:";

	while (ptr != 0) 
	{
		ret += "\n" + task_to_string(ptr->task);
		ptr = ptr->last;
	}

	ptr = queue->queue2;
	ret += "\n\nОчередь 2:";

	while (ptr != 0) 
	{
		ret += "\n" + task_to_string(ptr->task);

		ptr = ptr->last;
	}
	return ret;
}

string stack_to_string(struct stack_element* stack) 
{
	string ret("");

	struct stack_element* ptr = stack;

	ret += "\nСтек:";

	while (ptr != 0) 
	{
		ret += "\n" + task_to_string(ptr->value);

		ptr = ptr->next;
	}

	return ret;
}

void add_element(struct task_queue* queue, int time)
{
	
	int needed;
	int priority;
	string name;

	cout << "Введите имя: ";
	cin >> name;
	cout << "\nВведите необходимое время: ";
	cin >> needed;
	cout << "\nВведите приоритет: ";
	cin >> priority;
	push_task_queue(queue, generate_task(name, needed, time, priority));
}

void iterate(struct task_queue* queue, struct processor* processor, int* time) 
{
	if (processor->task != 0)
	{
		int new_priority;
		new_priority = get_queue_priority(queue);

		if (new_priority < processor->task->priority)
		{
			processor->stack = push_stack(processor->stack, processor->task);
			processor->task = pop_task_queue(queue);
		}

	}

	else 
	{
		if (processor->stack != 0) 
		{
			if (processor->stack->value->priority <= get_queue_priority(queue)) 
			{
				struct task* new_task = new struct task;
				processor->stack = pop_stack(processor->stack, new_task);
				processor->task = new_task;
			}
		}
		else

			if ((processor->task = pop_task_queue(queue)) == 0) 
			{
				cout << "Нет задачи" << endl;
				return;
			}
	}
	(*time)++;

	processor->task->proceed_time += 1;

	cout << "Все время процесса: " << (*time) << endl;

	if (processor->task->proceed_time >= processor->task->needed_time) 
	{
		cout << "Задача выполнена: \n" << task_to_string(processor->task) << endl;
		processor->task = 0;
	}
	else
	cout << "В процессор: \n" << task_to_string(processor->task) << endl;
	cout << queues_to_string(queue) << endl;
	cout << stack_to_string(processor->stack) << endl;
}

void iterate_multiple(struct task_queue* queue, struct processor* processor, int* time) 
{
	int count;
	cout << "Введите n: ";
	cin >> count;

	for (int i = 0; i < count; i++) 
	{
		iterate(queue, processor, time);
	}

}

int main() 
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));

	struct task_queue* queue = new struct task_queue;

	queue->queue0 = 0;
	queue->queue1 = 0;
	queue->queue2 = 0;

	struct processor* processor = new struct processor;

	processor->task = 0;
	processor->stack = 0;

	int sys_time = 0;

	while (true) 
	{
		cout << "________________________________\n";
		cout << "|1| Одна итерация.             |\n";
		cout << "|2| Итерация n кол-во раз.     |\n";
		cout << "|3| Рандомная задача.          |\n";
		cout << "|4| Самостоятельный ввод задачи|\n";
		cout << "|0| Выход.                     |\n";
		cout << "|______________________________|"<< endl;
		cout << "Ввод: ";

		int choice;
		cin >> choice;

		switch (choice)
		{
		case 1:
			iterate(queue, processor, &sys_time);

			break;
		case 2:
			iterate_multiple(queue, processor, &sys_time);

			break;
		case 3:
			add_random(queue, sys_time);

			break;
		case 4:
			add_element(queue, sys_time);

			break;
		case 0:
			return 0;
		default:
			cout << "Ошибка ввода\n";
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
