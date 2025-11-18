#include <iostream>
#include <iomanip>
#include <time.h>
#include <chrono>

using namespace std;
using namespace chrono;


//Объявление
const int LEN_ARR = 100;
int arr[LEN_ARR];
int arr_sort[LEN_ARR];


//Цвета текста
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"


//Объявление функций
int menu_commands(int choice);


//Сортировки
void bubble_sort(int* arr_sort) {
	for (int i = 0; i < LEN_ARR - 1; ++i) {
		for (int j = 0; j < LEN_ARR - 1 - i; ++j) {
			if (arr_sort[j] > arr_sort[j + 1]) {
				swap(arr_sort[j], arr_sort[j + 1]);
			}
		}
	}
}

void shaker_sort(int* arr_sort) {
	int left = 0, right = LEN_ARR - 1;
	while (left <= right) {
		for (int i = left; i < right; ++i) {
			if (arr_sort[i] > arr_sort[i + 1]) {
				swap(arr_sort[i], arr_sort[i + 1]);
			}
		}
		--right;

		for (int i = right; i > left; --i) {
			if (arr_sort[i] < arr_sort[i - 1]) {
				swap(arr_sort[i], arr_sort[i - 1]);
			}
		}
		++left;
	}

}

void insertion_sort(int* arr_sort) {
	for (int i = 1; i < LEN_ARR; ++i) {
		int j = i - 1;
		int key = arr_sort[i];
		while (j >= 0 && arr_sort[j] > key) {
			arr_sort[j + 1] = arr_sort[j];
			--j;
		}
		arr_sort[j + 1] = key;
	}

}

void selection_sort(int* arr_sort) {
	for (int i = 0; i < LEN_ARR - 1; ++i) {
		int minNum = i;
		for (int j = i + 1; j < LEN_ARR; ++j) {
			if (arr_sort[j] < arr_sort[minNum]) {
				minNum = j;
			}
		}
		swap(arr_sort[i], arr_sort[minNum]);
	}
}

void quick_sort(int* arr_sort, int begin, int end) {
	if (begin >= end) return;

	int left = begin;
	int right = end;
	int mid = arr_sort[(left + right) / 2];

	while (left <= right) {
		while (arr_sort[left] < mid) left++;
		while (arr_sort[right] > mid) right--;

		if (left <= right) {
			std::swap(arr_sort[left], arr_sort[right]);
			left++;
			right--;
		}
	}

	if (begin < right) quick_sort(arr_sort, begin, right);
	if (left < end) quick_sort(arr_sort, left, end);
}


//Другие функции
void separation() {
	cout << "\n";
}

void waiting() {
	separation();
	separation();
	cout << RED << "Нажмите Enter для продолжения..." << RESET << endl;
	cin.ignore();
	cin.get();
}

void clear_screen() {
	system("cls");
}

void clear_all_array() {
	for (int i = 0; i < LEN_ARR; ++i) {
		arr[i] = 0;
		arr_sort[i] = 0;
	}
}

void clear_array_sort() {
	for (int i = 0; i < LEN_ARR; ++i) {
		arr_sort[i] = 0;
	}
}

void clear_array_menu() {
	cout << "Выберите что очистить" << endl;
	cout << GREEN << "1) Все массивы" << RESET << endl;
	cout << GREEN << "2) Только отсортированный массив" << RESET << endl;
	cout << "Выбор: ";
	int clear_array_choice;
	cin >> clear_array_choice;
	switch (clear_array_choice) {
	case 1:
		clear_all_array();
		break;
	case 2:
		clear_array_sort();
		break;
	}
	separation();
	cout << GREEN << "Массив успешно очищен!" << RESET;
}

void random_array() {
	srand(time(NULL));
	for (int i = 0; i < LEN_ARR; ++i) {
		arr[i] = rand() % 199 - 99;
	}
}

void hand_array() {
	cout << RED << "Введите 100 чисел (от -99 до 99) по одному или одной строкой:\n" << RESET;
	for (int i = 0; i < LEN_ARR; ++i) {
		int temp_element;
		cout << BLUE << i + 1 << " элемент: " << RESET;
		cin >> temp_element;
		if (-99 <= temp_element && temp_element <= 99) {
			arr[i] = temp_element;
		}
		else {
			cout << RED << "Введённое число не подходит (только числа от -99 до 99)!" << endl;
			cout << "Введите другое число." << RESET << endl;
			--i;
		}
	}
}

void input_array() {
	cout << "Выберите способ заполнения массива:" << endl;
	cout << GREEN << "1) Заполнение случайными числами" << RESET << endl;
	cout << GREEN << "2) Заполнение вручную" << RESET << endl;
	cout << "Способ: ";
	int input_array_choice;
	cin >> input_array_choice;
	separation();
	switch (input_array_choice) {
	case 1:
		random_array();
		break;
	case 2:
		hand_array();
		break;
	}
	cout << GREEN << "Массив успешно создан!" << RESET;
}

void output_array() {
	cout << GREEN << "Текущий неотсортированный массив:\n" << RESET;
	cout << "{ ";
	for (int i = 0; i < LEN_ARR; ++i) {
		cout << arr[i] << " ";
	}
	cout << "}";
}

void output_array_sort() {
	cout << GREEN << "Текущий отсортированный массив:\n" << RESET;
	cout << "{ ";
	for (int i = 0; i < LEN_ARR; ++i) {
		cout << arr_sort[i] << " ";
	}
	cout << "}";
}

void command_choice() {
	cout << GREEN << "Введите номер команды: " << RESET;
	int user_choice;
	cin >> user_choice;
	separation();
	menu_commands(user_choice);
}

void array_copy(int* arr, int* arr_sort) {
	for (int i = 0; i < LEN_ARR; ++i) {
		arr_sort[i] = arr[i];
	}
}

void sort_menu() {
	cout << "Выберите способ сортировки:" << endl;
	cout << GREEN << "1) Bubble sort" << RESET << endl;
	cout << GREEN << "2) Shaker sort" << RESET << endl;
	cout << GREEN << "3) Insertion sort" << RESET << endl;
	cout << GREEN << "4) Selection sort" << RESET << endl;
	cout << GREEN << "5) Quick sort" << RESET << endl;
	cout << "Способ: ";
	int input_sort_choice;
	cin >> input_sort_choice;
	array_copy(arr, arr_sort);
	separation();
	nanoseconds result;
	switch (input_sort_choice) {
	case 1: {
		auto start = steady_clock::now();
		bubble_sort(arr_sort);
		auto end = steady_clock::now();
		result = duration_cast<nanoseconds>(end - start);
		break;
	}
	case 2: {
		auto start = steady_clock::now();
		shaker_sort(arr_sort);
		auto end = steady_clock::now();
		result = duration_cast<nanoseconds>(end - start);
		break;
	}
	case 3: {
		auto start = steady_clock::now();
		insertion_sort(arr_sort);
		auto end = steady_clock::now();
		result = duration_cast<nanoseconds>(end - start);
		break;
	}
	case 4: {
		auto start = steady_clock::now();
		selection_sort(arr_sort);
		auto end = steady_clock::now();
		result = duration_cast<nanoseconds>(end - start);
		break;
	}
	case 5:
	{
		auto start = steady_clock::now();
		quick_sort(arr_sort, 0, LEN_ARR - 1);
		auto end = steady_clock::now();
		result = duration_cast<nanoseconds>(end - start);
		break;
	}
	}
	cout << GREEN << "Массив успешно отсортирован за " << result.count() << " нс" << RESET;
}

void max_min_array(int* arr, int& max_array, int& min_array) {
	max_array = min_array = arr[0];
	for (int i = 0; i < LEN_ARR - 1; ++i) {
		if (max_array < arr[i + 1]) {
			max_array = arr[i + 1];
		}
		if (min_array > arr[i + 1]) {
			min_array = arr[i + 1];
		}
	}
}

void max_min_array_sort(int* arr_sort, int& max_array, int& min_array) {
	min_array = arr_sort[0];
	max_array = arr_sort[LEN_ARR - 1];
}

void max_min_output() {
	int max_array;
	int min_array;

	auto start1 = steady_clock::now();
	max_min_array(arr, max_array, min_array);
	auto end1 = steady_clock::now();
	auto result1 = duration_cast<nanoseconds>(end1 - start1);

	cout << GREEN << "Максимальный элемент массива: " << RESET << max_array << endl;
	cout << GREEN << "Минимальный элемент массива: " << RESET << min_array << endl;

	auto start2 = steady_clock::now();
	max_min_array_sort(arr_sort, max_array, min_array);
	auto end2 = steady_clock::now();
	auto result2 = duration_cast<nanoseconds>(end2 - start2);

	separation();
	cout << GREEN << "Время поиска в неотсортированном массиве: " << RESET << result1.count() << endl;
	cout << GREEN << "Время поиска в отсортированном массиве: " << RESET << result2.count() << endl;
}

void elements_finding_array(int* arr, int& average_max_min) {
	int count_elements = 0;
	cout << GREEN << "Индексы элементов, равных среднему значению max и min: " << RESET;
	for (int i = 0; i < LEN_ARR; ++i) {
		if (arr[i] == average_max_min) {
			cout << i << " ";
			++count_elements;
		}
	}
	separation();
	cout << GREEN << "Количество элементов: " << RESET << count_elements << endl;
}

void elements_finding_array_sort(int* arr, int& average_max_min) {
	int count_elements = 0;
	cout << GREEN << "Индексы элементов, равных среднему значению max и min: " << RESET;
	for (int i = 0; i < LEN_ARR; ++i) {
		if (arr[i] == average_max_min) {
			cout << i << " ";
			++count_elements;
		}
		else {
			if (arr[i] > average_max_min) {
				break;
			}
		}
	}
	separation();
	cout << GREEN << "Количество элементов: " << RESET << count_elements << endl;
}

void average_max_min() {
	int max_array;
	int min_array;

	cout << RED << "Неотсортированный массив:" << RESET << endl;
	auto start1 = steady_clock::now();
	max_min_array(arr, max_array, min_array);
	int average_max_min = (max_array + min_array) / 2;
	elements_finding_array(arr, average_max_min);
	auto end1 = steady_clock::now();
	auto result1 = duration_cast<nanoseconds>(end1 - start1);
	cout << GREEN << "Поиск в неотсортированном массиве выполнен за  " << RESET << result1.count() << "нс" << endl;
	cout << GREEN << "Среднее значение max и min элемента массива: " << RESET << average_max_min << endl;
	separation();

	cout << RED << "Отсортированный массив:" << RESET << endl;
	auto start2 = steady_clock::now();
	max_min_array_sort(arr_sort, max_array, min_array);
	int average_max_min_sort = (max_array + min_array) / 2;
	elements_finding_array_sort(arr_sort, average_max_min_sort);
	auto end2 = steady_clock::now();
	auto result2 = duration_cast<nanoseconds>(end2 - start2);
	cout << GREEN << "Поиск в отсортированном массиве выполнен за  " << RESET << result2.count() << "нс" << endl;
	cout << GREEN << "Среднее значение max и min элемента массива: " << RESET << average_max_min_sort << endl;
}

void elements_less_a(int* arr_sort) {
	int number_a;
	cout << RED << "Введите число a: " << RESET;
	cin >> number_a;
	int count_elements = 0;
	cout << GREEN << "Элементы меньше a: " << RESET;
	for (int i = 0; i < LEN_ARR; ++i) {
		if (arr_sort[i] < number_a) {
			cout << arr_sort[i] << " ";
			++count_elements;
		}
		else {
			break;
		}
	}
	separation();
	cout << GREEN << "Количество элементов меньше a: " << RESET << count_elements << endl;
}

void elements_greater_b(int* arr_sort) {
	int number_b;
	cout << RED << "Введите число b: " << RESET;
	cin >> number_b;
	int count_elements = 0;
	cout << GREEN << "Элементы больше b: " << RESET;
	for (int i = LEN_ARR - 1; i >= 0; --i) {
		if (arr_sort[i] > number_b) {
			cout << arr_sort[i] << " ";
			++count_elements;
		}
		else {
			break;
		}
	}
	separation();
	cout << GREEN << "Количество элементов больше b: " << RESET << count_elements << endl;
}

bool element_find_default(int* arr_sort, int& element_find) {
	for (int i = 0; i < LEN_ARR; ++i) {
		if (arr_sort[i] == element_find) {
			return true;
		}
	}
	return false;
}

bool element_find_binary(int* arr_sort, int& element_find, int start, int end) {
	if (end >= start) {
		int middle = start + (end - start) / 2;

		if (arr_sort[middle] == element_find) {
			return true;
		}

		if (arr_sort[middle] > element_find) {
			return element_find_binary(arr_sort, element_find, start, middle - 1);
		}

		return element_find_binary(arr_sort, element_find, middle + 1, end);
	}

	return false;
}

void element_find_output() {
	int element_find;
	cout << RED << "Введите число для поиска: " << RESET;
	cin >> element_find;
	separation();

	cout << RED << "Метод перебора: " << RESET << endl;
	auto start1 = steady_clock::now();
	bool flag1 = element_find_default(arr_sort, element_find);
	auto end1 = steady_clock::now();
	auto result1 = duration_cast<nanoseconds>(end1 - start1);
	if (flag1) {
		cout << GREEN << "Элемент " << RESET << element_find << GREEN << " найден в массиве!" << RESET << endl;
	}
	else {
		cout << RED << "Элемент " << RESET << element_find << RED << " не найден в массиве!" << RESET << endl;
	}
	cout << GREEN << "Время выполнения: " << result1.count() << "нс" << RESET << endl;
	separation();

	cout << RED << "Метод бинарного поиска: " << RESET << endl;
	auto start2 = steady_clock::now();
	bool flag2 = element_find_binary(arr_sort, element_find, 0, LEN_ARR - 1);
	auto end2 = steady_clock::now();
	auto result2 = duration_cast<nanoseconds>(end2 - start2);
	if (flag2) {
		cout << GREEN << "Элемент " << RESET << element_find << GREEN << " найден в массиве!" << RESET << endl;
	}
	else {
		cout << RED << "Элемент " << RESET << element_find << RED << " не найден в массиве!" << RESET << endl;
	}
	cout << GREEN << "Время выполнения: " << result2.count() << "нс" << RESET << endl;
}

void swap_elements_array(int* arr_sort, int& index1, int& index2) {
	swap(arr_sort[index1], arr_sort[index2]);
}

void swap_elements_array_output() {
	output_array_sort();
	separation();
	int index1;
	int index2;
	cout << RED << "Введите индексы двух элементов для обмена местами (от 0 до 99)." << RESET << endl;
	cout << BLUE << "Первый индекс: " << RESET;
	cin >> index1;
	cout << BLUE << "Второй индекс: " << RESET;
	cin >> index2;
	separation();
	auto start1 = steady_clock::now();
	swap_elements_array(arr_sort, index1, index2);
	auto end1 = steady_clock::now();
	auto result1 = duration_cast<nanoseconds>(end1 - start1);
	output_array_sort();
	separation();
	cout << GREEN << "Элементы успешно обменяны местами за " << RESET << result1.count() << "нс";
}

void pass_find_output() {
	cout << RED << "Введите размер последовательности (N) (не больше 1000): " << RESET;
	int n;
	cin >> n;
	const int MAX_SIZE = 1000;
	int sequence[MAX_SIZE];

	cout << RED << "Введите " << n - 1 << " чисел из последовательности 0 до " << n - 1 << " c пропущенным числом и одинаковым шагом:" << RESET << endl;
	for (int i = 0; i < n - 1; ++i) {
		cout << BLUE << i + 1 << " число: " << RESET;
		cin >> sequence[i];
	}

	int current_sum_elements = 0;
	int final_sum_elements = n * (n - 1) / 2;
	for (int i = 0; i < n - 1; ++i) {
		current_sum_elements += sequence[i];
	}

	for (int i = 0; i < n - 2; ++i) {
		for (int j = 0; j < n - 2 - i; ++j) {
			if (sequence[j] > sequence[j + 1]) {
				swap(sequence[j], sequence[j + 1]);
			}
		}
	}

	int step = sequence[1] - sequence[0];
	for (int i = 2; i < n - 1; ++i) {
		int current_step = sequence[i] - sequence[i - 1];
		if (current_step < step) {
			step = current_step;
		}
	}

	int missing_number = 0;
	for (int i = 1; i < n - 1; ++i) {
		if (sequence[i] - sequence[i - 1] != step) {
			missing_number = sequence[i - 1] + step;
			break;
		}
	}
	cout << GREEN << "Пропущенное число: " << RESET << missing_number << endl;
	separation();
}

int menu_commands(int choice) {
	switch (choice) {
	case 1:
		input_array();
		waiting();
		return 0;
		break;
	case 2:
		sort_menu();
		waiting();
		return 0;
		break;
	case 3:
		max_min_output();
		waiting();
		return 0;
		break;
	case 4:
		average_max_min();
		waiting();
		return 0;
		break;
	case 5:
		elements_less_a(arr_sort);
		waiting();
		return 0;
		break;
	case 6:
		elements_greater_b(arr_sort);
		waiting();
		return 0;
		break;
	case 7:
		element_find_output();
		waiting();
		return 0;
		break;
	case 8:
		swap_elements_array_output();
		waiting();
		return 0;
		break;
	case 9:
		pass_find_output();
		waiting();
		return 0;
		break;
	case 10:
		output_array();
		separation();
		separation();
		output_array_sort();
		waiting();
		return 0;
		break;
	case 11:
		clear_array_menu();
		waiting();
		return 0;
		break;
	default:
		cout << RED << "Ошибка! Введите номер команды от 1 до 11\n" << RESET << endl;
		command_choice();
		break;

	}
}

void menu() {
	setlocale(0, "");
	cout << "|=======================================================|" << endl;
	cout << "|                 " << BLUE << "Лабораторная работа 2" << RESET << "                 |" << endl;
	cout << "|=======================================================|" << endl;
	cout << "| " << GREEN << "1) Создать целочисленный массив" << RESET << "                       |" << endl;
	cout << "| " << GREEN << "2) Отсортировать массив по возрастанию" << RESET << "                |" << endl;
	cout << "| " << GREEN << "3) Найти max и min элемент массива" << RESET << "                    |" << endl;
	cout << "| " << GREEN << "4) Найти среднее значение max и min значения массива" << RESET << "  |" << endl;
	cout << "| " << GREEN << "5) Количество элементов, меньших числа a" << RESET << "              |" << endl;
	cout << "| " << GREEN << "6) Количество элементов, больших числа b" << RESET << "              |" << endl;
	cout << "| " << GREEN << "7) Поиск числа в массиве" << RESET << "                              |" << endl;
	cout << "| " << GREEN << "8) Поменять местами элементы массива" << RESET << "                  |" << endl;
	cout << "| " << GREEN << "9) Найти пропущенное число в последовательности (ИДЗ)" << RESET << " |" << endl;
	cout << "|                                                       |" << endl;
	cout << "| " << RED << "10) Вывести текущий массив" << RESET << "                            |" << endl;
	cout << "| " << RED << "11) Очистить массив" << RESET << "                                   |" << endl;
	cout << "|=======================================================|" << endl;
	cout << "|                 " << BLUE << "Лабораторная работа 2" << RESET << "                 |" << endl;
	cout << "|=======================================================|" << endl;
	cout << endl;
}

//Главная функция
int main() {
	while (true) {
		menu();
		command_choice();
		clear_screen();
	}
	return 0;
}
