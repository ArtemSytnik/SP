#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <time.h>

#define ARRAY_MAX_SIZE 7

CRITICAL_SECTION critSection;
HANDLE* threads;
int tlsIndex;

//Запуск потоков
void launch_threads(int count);
//Функция потоков
DWORD WINAPI thread_function(LPVOID arr);
//Подсчёт массива
void calculating_array(int* main_array, int* result_array);
//Находим самый большой делитель числа
int find_largest_divisor(int num);
//Находим сумму элементов массива
int sum_of_array_elements(int* array);
//Выводим массив
void print_array(int* arr);

int main()
{
	int count;
	printf("Laboratory work #4\nCompleted by: Sytnik A.V. group 535a\n\n");
	printf("Enter the number of threads :");
	scanf("%i", &count);

	threads = new HANDLE[count];
	srand(time(0));

	InitializeCriticalSection(&critSection);
	launch_threads(count);
	WaitForMultipleObjects(count, threads, TRUE, INFINITE);
	DeleteCriticalSection(&critSection);

	system("pause");
	return 0;
}

void launch_threads(int count)
{
	InitializeCriticalSection(&critSection);
	int** arrays = new int*[count];
	tlsIndex = TlsAlloc();

	for (int i = 0; i < count; i++)
	{
		arrays[i] = new int[ARRAY_MAX_SIZE];
		for (int j = 0; j < ARRAY_MAX_SIZE; j++)
			arrays[i][j] = rand() % 90 + 10;
		threads[i] = CreateThread(NULL, 0, thread_function, arrays[i], NULL, NULL);
	}
}

DWORD WINAPI thread_function(LPVOID param)
{
	EnterCriticalSection(&critSection);
	printf("Thread ID : %u\n", GetCurrentThreadId());
	int* array = (int*)param;
	TlsSetValue(tlsIndex, (LPVOID)(new int[ARRAY_MAX_SIZE]));
	int sum = 0;

	printf("Thread array: ");
	print_array(array);

	calculating_array(array, (int*)TlsGetValue(tlsIndex));

	printf("\nProcessed array: ");
	print_array((int*)TlsGetValue(tlsIndex));

	sum = sum_of_array_elements((int*)TlsGetValue(tlsIndex));
	printf("\nResult sum: %d\n\n", sum);
	LeaveCriticalSection(&critSection);
	return 0;
}

void calculating_array(int* main_array, int* result_array)
{
	for (int i = 0; i < ARRAY_MAX_SIZE; i++)
	{
		result_array[i] = find_largest_divisor(main_array[i]);
	}
}

int find_largest_divisor(int num)
{
	int j = num / 2;
	for (int i = j; i >= 2; i--)
	{
		if (num % i == 0)
			return i;
	}
}

int sum_of_array_elements(int* array)
{
	int result = 0;
	for (int i = 0; i < ARRAY_MAX_SIZE; i++)
	{
		result += array[i];
	}
	return result;
}

void print_array(int* arr)
{
	for (int i = 0; i < ARRAY_MAX_SIZE; i++) {
		printf("%i ", arr[i]);
	}
}