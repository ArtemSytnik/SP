#include <stdio.h>
#include <Windows.h>

int main()
{
	HANDLE mutex = CreateMutexA(NULL, FALSE, "MyMutex");

	if (WaitForSingleObject(mutex, 0) == WAIT_OBJECT_0)
	{
		printf("Laboratory work #5\nCompleted by: Sytnik A.V. group 535a\n\n");
		printf("Program is working right now.\nPress any key to stop it.");
		getchar();
		ReleaseMutex(mutex);
	}
	else
	{
		printf("Can't start program!");
		getchar();
	}

	CloseHandle(mutex);
	return 0;
}