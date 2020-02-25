#include <stdio.h>
#include <Windows.h>
#include <locale.h>
#include <tchar.h>
void ErrorGenerate();
void InfoOutput();

int main(int argc, char *argv[]) {
	setlocale(LC_CTYPE, "rus");
	if(argv[1] != NULL){
		if (strcmp(argv[1], "-e") == 0) {
			ErrorGenerate();
		}
		else if (strcmp(argv[1], "-s") == 0) {
			InfoOutput();
		}
		else {
			printf("Неверный ключ!\n");
		}
	}
	else {
		printf("Отсутствует ключ!\n");
	}
	system("pause");
	return 0;
}

void ErrorGenerate(){
	MEMORYSTATUS lpBuffer;
	GlobalMemoryStatus(&lpBuffer);

	LPTSTR pszBuf = NULL;

	pszBuf = (LPTSTR)LocalAlloc(
		LPTR, lpBuffer.dwTotalVirtual * 2);

	LPVOID lpMsgBuf;
	DWORD dw = GetLastError();
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);
	wprintf(L"%s", lpMsgBuf);
	LocalFree(lpMsgBuf);
}

void InfoOutput(){
	SYSTEM_INFO s_info;

	GetNativeSystemInfo(
		(LPSYSTEM_INFO)&s_info
	);

	printf("System information: \n");
	printf("OEM ID: %u\n", s_info.dwOemId);
	printf("Processor Architecture: %u\n", s_info.wProcessorArchitecture);
	printf("Reserved: %u\n", s_info.wReserved);
	printf("Page size: %u\n", s_info.dwPageSize);
	printf("Minimum application address: %lx\n", s_info.lpMinimumApplicationAddress);
	printf("Maximum application address: %lx\n", s_info.lpMaximumApplicationAddress);
	printf("Active processor mask: %u\n", s_info.dwActiveProcessorMask);
	printf("Number of processors: %u\n", s_info.dwNumberOfProcessors);
	printf("Processor type: %u\n", s_info.dwProcessorType);
	printf("Allocation granularity: %u\n", s_info.dwAllocationGranularity);
	printf("Processor level: %u\n", s_info.wProcessorLevel);
	printf("Processor revision: %u\n", s_info.wProcessorRevision);
}