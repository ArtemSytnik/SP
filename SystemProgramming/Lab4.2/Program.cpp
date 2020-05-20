#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <time.h>

HANDLE semaphore;

int get_randomised_integer(int minimum, int maximum);
DWORD WINAPI thread_function(LPVOID param);

int main()
{
	// Количество указателей
	int maximum_handles;
	// Количество потоков
	int maximum_threads;
	srand(time(NULL));
	printf("Laboratory work #5\nCompleted by: Sytnik A.V. group 535a\n\n");
	printf("Please input max number of handles : ");
	scanf("%i", &maximum_handles);

	printf("Please input max number of threads : ");
	scanf("%i", &maximum_threads);

	//Создание семафора
	HANDLE* threads = new HANDLE[maximum_threads];
	semaphore = CreateSemaphoreA(NULL, maximum_handles, maximum_handles, "MySemaphore");
	if (semaphore == NULL) {
		printf("* An error occurred while creating the semaphore *");
		system("pause");
		return 1;
	}
		
	//Создание файла
	HANDLE file = CreateFileA("work_result.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == INVALID_HANDLE_VALUE)
	{
		CloseHandle(file);
		return 1;
	}
	CloseHandle(file);

	for (int i = 0; i < maximum_threads; i++)
	{
		int* params = new int[2];
		params[0] = i; //Количество потоков
		params[1] = get_randomised_integer(1, 5); //Время сна.
									  
		threads[i] = CreateThread(
			NULL, // дескриптор защиты
			0, // начальный размер стека
			thread_function, // функция потока
			(LPVOID)params, // параметры потока
			NULL, // опции создания
			NULL);// идентификатор потока
	}
	WaitForMultipleObjects(maximum_threads, threads, TRUE, INFINITE);
	return 0;
}

DWORD WINAPI thread_function(LPVOID param)
{
	int* params = (int*)param;
	clock_t start = clock();
	int thread_number = params[0];
	LPSTR str = new CHAR[128];

	DWORD result = WaitForSingleObject(semaphore, 500);
	while (result != WAIT_OBJECT_0)
	{
		result = WaitForSingleObject(semaphore, 1000);
		printf("Thread number %i waiting for semaphore\n", thread_number);
	}

	printf("Thread number %i decrement semaphore. Going to sleep\n", thread_number);

	Sleep(params[1] * 1000);

	HANDLE file = CreateFileA("work_result.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == INVALID_HANDLE_VALUE)
	{
		ReleaseSemaphore(semaphore, 1, NULL);
		return 0;
	}
	SetFilePointer(file, 0, NULL, FILE_END);

	clock_t finish = clock();
	float time_elapsed = (finish - start) / CLK_TCK;

	sprintf(str, "Thread number %i made his work in %f seconds\n\0", thread_number, time_elapsed);
	WriteFile(file, str, strlen(str), NULL, NULL);
	CloseHandle(file);

	printf("Thread number %i released semaphore.\n", thread_number);
	ReleaseSemaphore(semaphore, 1, NULL);
	return 0;
}

int get_randomised_integer(int minimum, int maximum)
{
	return minimum + rand() % (maximum + 1 - minimum);
}
