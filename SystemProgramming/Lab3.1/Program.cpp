#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
using namespace std;

#define PACK_COMMAND 1
#define UNPACK_COMMAND 2

//Разархивация
bool archive_unpacking(LPSTR object, LPSTR result);
//Архивация
bool archive_packing(LPSTR packedArchive, LPSTR result);
//Запуска дочернего процесса
bool start_process(LPSTR control_string);
//Вывод ошибки
void print_error();

int main()
{
	int choose;
	for (;;)
	{
		system("cls");
		printf("Laboratory work #4\nCompleted by: Sytnik A.V. group 535a\n\n");
		printf("Menu:\n");
		printf("1)Archive packing \n");
		printf("2)Archive unpacking \n");
		printf("Choose menu item : ");
		scanf("%i", &choose);

		switch (choose)
		{
		case PACK_COMMAND:
		{
			LPSTR object = new CHAR[MAX_PATH];
			LPSTR result = new CHAR[MAX_PATH];

			printf("The path to the object (file or directory): ");
			scanf("%s", object);
			printf("Archive result: ");
			scanf("%s", result);
			if (archive_packing(object, result))
			{
				printf("Archive packing was successful\n");
			}
			break;
		}
		case UNPACK_COMMAND:
		{
			LPSTR packedArchive = new CHAR[MAX_PATH];
			LPSTR result = new CHAR[MAX_PATH];

			printf("The path to the archive:");
			scanf("%s", packedArchive);
			printf("Archive unpacking path:");
			scanf("%s", result);
			if (archive_unpacking(packedArchive, result))
			{
				printf("Archive unpacking was successful\n");
			}
			break;
		}
		default:printf("*Incorrect menu item! PLease try again!*\n");
		}
		system("pause");
		system("cls");
	}
}

bool archive_unpacking(LPSTR packedArchive, LPSTR result)
{
	LPSTR control_string = new CHAR[MAX_PATH];
	ZeroMemory(control_string, MAX_PATH);

	// Установка пути к 7z and и объкта архивирования .zip
	strncpy(control_string, "C:\\Program Files\\7-Zip\\7z.exe e", MAX_PATH - strlen(control_string));
	strncat(control_string, packedArchive, MAX_PATH - strlen(control_string));

	// -o set установка директории для распаковки
	strncat(control_string, " -o", MAX_PATH - strlen(control_string));
	strncat(control_string, result, MAX_PATH - strlen(control_string));

	// -y Авто-ответ на все вопросы которые может спросить система да
	strncat(control_string, " -y", MAX_PATH - strlen(control_string));
	return start_process(control_string);
}

bool archive_packing(LPSTR object, LPSTR result)
{
	LPSTR control_string = new CHAR[MAX_PATH];
	ZeroMemory(control_string, MAX_PATH);

	strncpy(control_string, "C:\\Program Files\\7-Zip\\7z.exe a -tzip ", MAX_PATH - strlen(control_string));
	strncat(control_string, result, MAX_PATH - strlen(control_string));
	strncat(control_string, " ", MAX_PATH - strlen(control_string));
	strncat(control_string, object, MAX_PATH - strlen(control_string));
	return start_process(control_string);
}

bool start_process(LPSTR control_string) 
{
	HANDLE pipe_reader;
	HANDLE pipe_writer;

	SECURITY_ATTRIBUTES security_attributes;
	security_attributes.nLength = sizeof(SECURITY_ATTRIBUTES);
	security_attributes.bInheritHandle = TRUE;
	security_attributes.lpSecurityDescriptor = NULL;

	CreatePipe(&pipe_reader, &pipe_writer, &security_attributes, 0);
	if (pipe_reader == INVALID_HANDLE_VALUE || pipe_writer == INVALID_HANDLE_VALUE)
	{
		print_error();
		return false;
	}

	if (!SetHandleInformation(pipe_reader, HANDLE_FLAG_INHERIT, 0))
	{
		print_error();
		return false;
	}

	STARTUPINFOA startup_info;
	ZeroMemory(&startup_info, sizeof(STARTUPINFOA));
	startup_info.cb = sizeof(startup_info);
	startup_info.hStdError = pipe_writer;
	startup_info.dwFlags |= STARTF_USESTDHANDLES;

	PROCESS_INFORMATION process_info;
	ZeroMemory(&process_info, sizeof(process_info));

	if (!CreateProcessA(NULL, control_string, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startup_info, &process_info)) 
	{
		print_error();
		return false;
	}
	WaitForSingleObject(process_info.hProcess, INFINITE);
	DWORD readed = 0;
	LPSTR result = new CHAR[1024];
	ZeroMemory(result, 1024);
	OVERLAPPED overlapped;
	while (ReadFile(pipe_reader, result, 1024, &readed, &overlapped))
	{
		printf("%s", result);
	}
	CloseHandle(pipe_reader);
	CloseHandle(pipe_writer);
	CloseHandle(process_info.hProcess);
	CloseHandle(process_info.hThread);
	return true;
}

void print_error()
{
	printf("\n*Error!*\n ERROR MASSAGE:");
	void* error;
	FormatMessage
	(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&error,
		0,
		NULL
	);
	PTCHAR res((char*)error);
	printf("%s", res);
}