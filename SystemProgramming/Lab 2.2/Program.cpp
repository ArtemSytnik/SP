#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>;
#include <iostream>
#include <locale.h>
using namespace std;
// Выбор директории
void Set_directory(TCHAR *buffer);
// Вывод файлов выбранной директории
void Print_directory(TCHAR *buffer);
// Копирование файла
void Cope_file(TCHAR *buffer);
// Создание директории
void Make_directory(TCHAR *buffer);
// Подробная информация о файле
void Get_fileInfo(TCHAR *buffer);
// Удаление файла или пустой директории
void Delete_object(TCHAR *buffer);
int main() {
	setlocale(LC_ALL, "rus");
	int choose;
	for (;;) {
		TCHAR buffer[MAX_PATH];
		GetCurrentDirectory(sizeof(buffer), buffer);

		system("cls");
		printf("Laboratory work #2\nCompleted by: Sytnik A.V. group 535a\n\n");
		printf("Current directory:%s\n", buffer);
		printf("Menu:\n");
		printf("1)Directory Selection\n");
		printf("2)Print files of the selected directory\n");
		printf("3)Copy file\n");
		printf("4)Directory creation\n");
		printf("5)Get file information\n");
		printf("6)Delete a file or empty directory\n");
		printf("7)Exit\n");
		printf("Enter the menu item:");
		scanf("%i", &choose);
		system("cls");

		switch (choose) {
		case 1: Set_directory(buffer); break;
		case 2: Print_directory(buffer); break;
		case 3: Cope_file(buffer); break;
		case 4:	Make_directory(buffer); break;
		case 5: Get_fileInfo(buffer); break;
		case 6: Delete_object(buffer); break;
		case 7: return 0; break;
		default:printf("Please try again! You selected wrong menu item.\n");
		}
		system("pause");
		system("cls");
	}
}

void Set_directory(TCHAR *buffer) {
	for (;;) {
		printf("Enter the full path to the directory\n");
		printf("Example: D://folder\n>>");

		TCHAR way[MAX_PATH];
		getchar();
		fgets(way, MAX_PATH - 1, stdin);
		way[strlen(way) - 1] = '\0';

		if (!SetCurrentDirectory(way))
			printf("\nError! Invalid directory path!\n");
		else {
			GetCurrentDirectory(sizeof(way), way);
			printf("Your current directory: %s\n", way);
			strcpy(buffer, way);
			return;
		}
		system("pause");
	}
}
void Print_directory(TCHAR *buffer) {
	printf("Files in the current directory: \n");

	WIN32_FIND_DATA FindFileData;
	TCHAR find[MAX_PATH];
	strcpy(find, buffer);
	strcat(find, "\\*");
	HANDLE hFile = FindFirstFile(find, &FindFileData);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		do {
			SYSTEMTIME systemT;
			FILETIME fileT;
			FileTimeToLocalFileTime(&FindFileData.ftCreationTime, &fileT);
			FileTimeToSystemTime(&fileT, &systemT);
			LONGLONG size = (FindFileData.nFileSizeHigh * (MAXDWORD + 1)) + FindFileData.nFileSizeLow;

			printf("%-40s %20lu bytes ", FindFileData.cFileName, size);
			printf("%2u.%u.%u %u:%u\n", systemT.wDay, systemT.wMonth, systemT.wYear, systemT.wHour, systemT.wMinute);

		} while (FindNextFile(hFile, &FindFileData) != 0);
		FindClose(hFile);
	}
}
void Cope_file(TCHAR *buffer) {
	for (;;) {
		printf("Enter a file name in the current directory. Example: lab1.txt\n>>");

		TCHAR find[MAX_PATH], s[MAX_PATH], newDirectory[MAX_PATH];
		strcpy(find, buffer);
		getchar();
		fgets(s, MAX_PATH - 1, stdin);
		s[strlen(s) - 1] = '\0';
		strcat(find, "\\");
		strcat(find, s);
		printf("\nEnter the path where you want to copy the file. Example: D:// \n>>");

		fgets(newDirectory, MAX_PATH - 1, stdin);
		newDirectory[strlen(newDirectory) - 1] = '\0';
		strcat(newDirectory, "\\");
		strcat(newDirectory, s);

		if (CopyFile(find, newDirectory, false)) return;
		else cout << "Error! Invalid path or file name!\n";
	}
}
void Make_directory(TCHAR *buffer) {
	TCHAR directoryName[MAX_PATH], way[MAX_PATH];
	printf("\nEnter the name of the new directory\n>>");
	getchar();
	fgets(directoryName, MAX_PATH - 1, stdin);
	directoryName[strlen(directoryName) - 1] = '\0';
	strcpy(way, buffer);
	strcat(way, "\\");
	strcat(way, directoryName);
	if (CreateDirectory(way, NULL))
		printf("Directory successfully created\n");
	else
		printf("Error! Failed to create directory!\n");
}
void Get_fileInfo(TCHAR *buffer) {
	TCHAR fileName[MAX_PATH], way[MAX_PATH];
	printf("Enter the file name:\n>>");
	getchar();
	fgets(fileName, MAX_PATH - 1, stdin);
	fileName[strlen(fileName) - 1] = '\0';
	strcpy(way, buffer);
	strcat(way, "\\");
	strcat(way, fileName);
	HANDLE hFile = CreateFile(way, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	BY_HANDLE_FILE_INFORMATION info;
	BOOL f = GetFileInformationByHandle(hFile, &info);
	CloseHandle(hFile);
	if (!f) {
		printf("Error! Incorrect File Name!\n");
	}
	else {
		if ((info.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0)
			printf("Hidden ");
		if ((info.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) != 0)
			printf("System ");
		if ((info.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) != 0)
			printf("Archive ");
		if ((info.dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED) != 0)
			printf("Compressed ");
		if ((info.dwFileAttributes & FILE_ATTRIBUTE_NORMAL) != 0)
			printf("Normal ");
		printf("file\n");

		SYSTEMTIME systemT;
		FILETIME fileT;

		FileTimeToLocalFileTime(&info.ftCreationTime, &fileT);
		FileTimeToSystemTime(&fileT, &systemT);
		printf("Creation time - %2u.%u.%u %u:%u\n", systemT.wDay, systemT.wMonth, systemT.wYear, systemT.wHour, systemT.wMinute);

		FileTimeToLocalFileTime(&info.ftLastWriteTime, &fileT);
		FileTimeToSystemTime(&fileT, &systemT);
		printf("Change time - %2u.%u.%u %u:%u\n", systemT.wDay, systemT.wMonth, systemT.wYear, systemT.wHour, systemT.wMinute);
	}
}
void Delete_object(TCHAR *buffer) {
	TCHAR fileName[MAX_PATH], way[MAX_PATH];
	printf("Enter the name of the file or directory you want to delete!\n>>");
	getchar();

	fgets(fileName, MAX_PATH - 1, stdin);
	fileName[strlen(fileName) - 1] = '\0';
	strcpy(way, buffer);
	strcat(way, "\\");
	strcat(way, fileName);

	BOOL deleteSuccess = DeleteFile(way), removeSuccess;
	if (!deleteSuccess) {
		removeSuccess = RemoveDirectory(way);
	}
	if (!deleteSuccess && !removeSuccess) {
		DWORD lastErrorCode = GetLastError();
		void* cstr; //В эту переменную будет записано сообщение
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&cstr,
			0,
			NULL
		);
		// Преобразование сообщения в читабельный вид
		PTCHAR result((char*)cstr);
		printf("%s", result);
	}
}

