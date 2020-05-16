#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <locale.h>

#define AmountOfBytesToRead 2048
//Перекодировка из Unicode в ASCII
void Unicode_to_Ascii(char*);
//Перекодировка из ASCII в Unicode
void Ascii_to_Unicode(char*);
//Создание файла результата, и открытие исходного текста.
bool GetFiles(char*, HANDLE*, HANDLE*);

int main(int argc, char* argv[]) {
	if (argv[1] != NULL && argv[2] != NULL) {
		if (strcmp(argv[1], "-u") == 0) {
			Unicode_to_Ascii(argv[2]);
		}
		else if (strcmp(argv[1], "-a") == 0) {
			Ascii_to_Unicode(argv[2]);
		}
		else {
			printf("Invalid parameters!");
		}
	}
	else {
		printf("Enter the parameters and try again!\n");
	}
	system("pause");
	return 0;
}

void Ascii_to_Unicode(char* path) {
	HANDLE FileToRead;
	HANDLE FileToWrite;

	if (GetFiles(path, &FileToRead, &FileToWrite)) {


		BYTE buff[AmountOfBytesToRead];
		DWORD dwBytes;

		while (ReadFile(FileToRead, buff, AmountOfBytesToRead, (LPDWORD)&dwBytes, NULL))
		{
			if (dwBytes == 0) break;
			//Получаем размер строки в Unicode
			int u_length = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)buff, dwBytes, NULL, 0);
			wchar_t* u_str = new wchar_t[u_length];
			//Перекодировка
			MultiByteToWideChar(CP_UTF8, 0, (LPCCH)buff, dwBytes, u_str, u_length);
			if (!WriteFile(FileToWrite, u_str, u_length * sizeof(wchar_t), (LPDWORD)&dwBytes, NULL)) {
				printf("Write error!");
				break;
			}
		}
		CloseHandle(FileToRead);
		CloseHandle(FileToWrite);
	}
	return;
}

void Unicode_to_Ascii(char* path) {
	HANDLE FileToRead;
	HANDLE FileToWrite;

	if (GetFiles(path, &FileToRead, &FileToWrite)) {
		BYTE buff[AmountOfBytesToRead];
		DWORD dwBytes;
		while (ReadFile(FileToRead, buff, AmountOfBytesToRead, (LPDWORD)&dwBytes, NULL))
		{
			if (dwBytes == 0) break;
			//Получаем размер строки в юникоде
			int u_length = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)buff, dwBytes, NULL, 0);
			//указатель на буфер со строкой которую необходимо конвертировать
			wchar_t* u_str = new wchar_t[u_length];
			MultiByteToWideChar(CP_UTF8, 0, (LPCCH)buff, dwBytes, u_str, u_length);
			//Получаем размер строки в ANSI
			int a_length = WideCharToMultiByte(CP_ACP, 0, u_str, u_length, NULL, 0, NULL, NULL);
			//Указатель на буфер с преобразованной строкой.
			char* a_str = new char[a_length];
			//Перекодировка
			WideCharToMultiByte(CP_ACP, 0, u_str, u_length, a_str, a_length, NULL, NULL);

			if (!WriteFile(FileToWrite, a_str, a_length * sizeof(char), &dwBytes, NULL)) {
				printf("Write error!");
				break;
			}
		}
		CloseHandle(FileToRead);
		CloseHandle(FileToWrite);
	}
	return;
}

bool GetFiles(char* path, HANDLE* readFile, HANDLE* writeFile) {
	bool result = true;
	*readFile = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	*writeFile = CreateFileA("C:\\Users\\Home\\Desktop\\SP\\SystemProgramming\\result.txt", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (*readFile == INVALID_HANDLE_VALUE || *writeFile == INVALID_HANDLE_VALUE) result = false;
	return result;
}