#include <stdio.h>
#include <Windows.h>
#include <locale.h>
#include <limits.h>
#include <float.h>
int main() {
	printf("Laboratory work #1\nCompleted by: Sytnik A.V. group 535a\n\n");
	//Вывод типов данных
	printf("char\t\t\tSIZE: %iB\tMIN: %i\t\t\tMAX: %i\n", sizeof(char), CHAR_MIN, CHAR_MAX);
	printf("signed char\t\tSIZE: %iB\tMIN: %i\t\t\tMAX: %i\n", sizeof(signed char), SCHAR_MIN, SCHAR_MAX);
	printf("unsigned char\t\tSIZE: %iB\tMIN: %i\t\t\t\tMAX: %i\n", sizeof(unsigned char), 0, UCHAR_MAX);
	printf("short\t\t\tSIZE: %iB\tMIN: %hi\t\t\tMAX: %hi\n", sizeof(short), SHRT_MIN, SHRT_MAX);
	printf("unsigned short\t\tSIZE: %iB\tMIN: %hu\t\t\t\tMAX: %hu\n", sizeof(unsigned short), 0, USHRT_MAX);
	printf("int\t\t\tSIZE: %iB\tMIN: %i\t\tMAX: %i\n", sizeof(int), INT_MIN, INT_MAX);
	printf("unsigned int\t\tSIZE: %iB\tMIN: %u\t\t\t\tMAX: %u\n", sizeof(unsigned int), 0, UINT_MAX);
	printf("long\t\t\tSIZE: %iB\tMIN: %li\t\tMAX: %li\n", sizeof(long), LONG_MIN, LONG_MAX);
	printf("unsigned long\t\tSIZE: %iB\tMIN: %lu\t\t\t\tMAX: %lu\n", sizeof(unsigned long), 0, ULONG_MAX);
	printf("long long\t\tSIZE: %iB\tMIN: %lli\tMAX: %lli\n", sizeof(long long), LLONG_MIN, LLONG_MAX);
	printf("unsigned long long\tSIZE: %iB\tMIN: %i\t\t\t\tMAX: %llu\n", sizeof(unsigned long long), 0, ULLONG_MAX);
	printf("float\t\t\tSIZE: %iB\tMIN: %e\t\tMAX: %e\n", sizeof(float), FLT_MIN, FLT_MAX);
	printf("double\t\t\tSIZE: %iB\tMIN: %le\t\tMAX: %le\n", sizeof(double), DBL_MIN, DBL_MAX);
	printf("long double\t\tSIZE: %iB\tMIN: %Le\t\tMAX: %Le\n", sizeof(double), LDBL_MIN, LDBL_MAX);
	system("pause");
	return 0;
}