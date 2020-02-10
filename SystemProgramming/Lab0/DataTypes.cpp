#include <stdio.h>
#include <Windows.h>
#include <locale.h>
int main() {
	setlocale(LC_CTYPE, "rus");
	printf("Лабораторная работа №0\nВыполнил: Сытник А.В. группа 535а\n\n");
	printf("SHORT\t\tSIZE: %iB\tMIN: %i\t\tMAX: %i\n", sizeof(SHORT), -32768, 32767);
	printf("WORD\t\tSIZE: %iB\tMIN: %i\t\t\tMAX: %i\n", sizeof(WORD), 0, 65535);
	printf("INT\t\tSIZE: %iB\tMIN: %i\tMAX: %i\n", sizeof(INT), -2147483647 - 1, 2147483647);
	printf("UINT\t\tSIZE: %iB\tMIN: %u\t\t\tMAX: %u\n", sizeof(UINT), 0, 4294967295);
	printf("DWORD\t\tSIZE: %iB\tMIN: %u\t\t\tMAX: %u\n", sizeof(DWORD), 0, 4294967295);
	printf("BYTE\t\tSIZE: %iB\tMIN: %i\t\t\tMAX: %i\n", sizeof(BYTE), 0, 255);
	printf("BOOL\t\tSIZE: %iB\tMIN: %i\t\t\tMAX: %i\n", sizeof(BOOL), FALSE, TRUE);
	printf("BOOLEAN\t\tSIZE: %iB\tMIN: %i\t\t\tMAX: %i\n", sizeof(BOOLEAN), FALSE, TRUE);
	printf("CHAR\t\tSIZE: %iB\tMIN: %i\t\tMAX: %i\n", sizeof(CHAR), -128, 127);
	printf("WCHAR\t\tSIZE: %iB\tMIN: %i\t\t\tMAX: %i\n", sizeof(WCHAR), 0, 65535);
	printf("TCHAR\t\tSIZE: %iB\tMIN: %i\t\t\tMAX: %i\n", sizeof(TCHAR), 0, 65535);
	printf("DOUBLE\t\tSIZE: %iB\tMIN: %e\tMAX: %e\n", sizeof(DOUBLE), 1.7E-308, 1.7E+308);
	printf("FLOAT\t\tSIZE: %iB\tMIN: %e\tMAX: %e\n", sizeof(FLOAT), 3.4E-38, 3.4E+38);
	printf("LPSTR\t\tSIZE: %iB\tMIN: %u\t\t\tMAX: %u\n", sizeof(LPSTR), 0, 4294967295);
	printf("LPCSTR\t\tSIZE: %iB\tMIN: %u\t\t\tMAX: %u\n", sizeof(LPCSTR), 0, 4294967295);
	printf("LPWSTR\t\tSIZE: %iB\tMIN: %u\t\t\tMAX: %u\n", sizeof(LPWSTR), 0, 4294967295);
	printf("LPCWSTR\t\tSIZE: %iB\tMIN: %u\t\t\tMAX: %u\n", sizeof(LPCWSTR), 0, 4294967295);
	printf("LPTSTR\t\tSIZE: %iB\tMIN: %u\t\t\tMAX: %u\n", sizeof(LPTSTR), 0, 4294967295);
	printf("LPCTSTR\t\tSIZE: %iB\tMIN: %u\t\t\tMAX: %u\n", sizeof(LPCTSTR), 0, 4294967295);
	system("pause");
	return 0;
}