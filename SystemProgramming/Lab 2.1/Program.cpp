#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <vector>
#include <locale.h>
using namespace std;
const char fileName[] = "records_list.txt";
struct Record {
	UINT number;
	FILETIME time;
	TCHAR data[81];
	UINT changesNumber;
};
struct Header {
	UINT dataRecordsNumber;
	UINT fileSize;
};
//Получение структуры header из файла
Header Read_header();
//Cчитываем записи после структуры header
vector<Record> Read_records();
//Вывод всех записей
void Show_records();
//Добавление записи в конец
void Add_record();
//Изменение записи по номеру
void Change_record();
//Удаление записи по номеру
void Remove_record();
//Сохранение записей
void Save_records(Header headerInfo, vector <Record> records);
int main()
{
	int choice;
	for (;;) {
		printf("Laboratory work #2\nCompleted by: Sytnik A.V. group 535a\n\n");
		printf("Menu items:\n");
		printf("1)View All Records\n");
		printf("2)Add Records\n");
		printf("3)Change record\n");
		printf("4)Delete record\n");
		printf("5)Exit\n");
		printf("Enter the menu item:");
		scanf("%i", &choice);
		system("cls");

		switch (choice) {
		case 1: Show_records(); break;
		case 2: Add_record(); break;
		case 3: Change_record(); break;
		case 4:	Remove_record(); break;
		case 5: return 0; break;
		default:printf("You selected wrong menu item. Please try again!");
		}
		system("pause");
		system("cls");
	}
}

Header Read_header() {
	Header header;
	DWORD readedBytes;
	HANDLE file = CreateFile(fileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	SetFilePointer(file, NULL, NULL, FILE_BEGIN);
	ReadFile(file, &header, sizeof(Header), &readedBytes, NULL);

	if (readedBytes == 0) {
		header.dataRecordsNumber = 0;
		header.fileSize = 0;
	}
	CloseHandle(file);
	return header;
}

vector<Record> Read_records() {
	HANDLE file = CreateFile(fileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	SetFilePointer(file, sizeof(Header), NULL, FILE_BEGIN);
	vector<Record> records(0);
	Record i;
	DWORD readedBytes = 0;
	for (;;) {
		bool k = ReadFile(file, &i, sizeof(Record), &readedBytes, NULL);
		if (readedBytes == 0) break;
		records.push_back(i);
	}
	CloseHandle(file);
	return records;
}

void Show_records() {
	SYSTEMTIME systemTime;
	vector <Record> records = Read_records();
	Header header = Read_header();
	printf("File size: %u bytes\nAmount of non-empty records: %u\n", header.fileSize, header.dataRecordsNumber);

	for (int i = 0; i < records.size(); i++) {
		FileTimeToSystemTime(&records[i].time, &systemTime);
		printf("#%i    ", records[i].number);
		printf("%2u.%2u.%u %2u:%u ", systemTime.wDay, systemTime.wMonth, systemTime.wYear, systemTime.wHour, systemTime.wMinute);
		printf(" modified:%2u ", records[i].changesNumber);
		printf("%s;\n", records[i].data);
	}
}

void Add_record() {
	Header header = Read_header();
	vector <Record> records = Read_records();
	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);
	FILETIME fileTime;
	Record record;
	SystemTimeToFileTime(&systemTime, &fileTime);

	printf("Enter data without using a space. Maximum - 80 characters.\nTo create an empty record, enter '-':\n");
	scanf("%s", record.data);
	if (strcmp(record.data, "-") == 0) {
		record.number = records.size();
		record.time = fileTime;
		strcpy(record.data, "");
		record.changesNumber = 0;
	}
	else {
		record.number = records.size();
		record.time = fileTime;
		record.changesNumber = 0;
		header.dataRecordsNumber++;
	}
	records.push_back(record);
	header.fileSize = sizeof(header) + sizeof(Record)*records.size();
	Save_records(header, records);
}

void Change_record() {
	SYSTEMTIME systemTime;
	Header header = Read_header();
	vector <Record> records = Read_records();
	UINT recordNumber;

	printf("Enter the number of the record you want to change:");
	scanf("%u", &recordNumber);
	try {
		FileTimeToSystemTime(&records.at(recordNumber).time, &systemTime);
		printf("Record number: %u\n", records[recordNumber].number);
		printf("Record creation time: %u.%u.%u %u:%u\n", systemTime.wDay, systemTime.wMonth, systemTime.wYear, systemTime.wHour, systemTime.wMinute);
		printf("Number of changes of record: %u\n", records[recordNumber].changesNumber);
		printf("Record Data: %s\n", records[recordNumber].data);
		printf("\nEnter new data without using a space. Maximum - 80 characters.\nTo make this record empty, enter '-':\nInput:");

		TCHAR str[81];
		strcpy(str, records[recordNumber].data);
		scanf("%s", records[recordNumber].data);
		if (strcmp(records[recordNumber].data, "-") == 0) strcpy(records[recordNumber].data, "");
		if (strcmp(str, "") == 0 && strcmp(records[recordNumber].data, "") != 0) header.dataRecordsNumber++;
		if (strcmp(str, "") != 0 && strcmp(records[recordNumber].data, "") == 0) header.dataRecordsNumber--;
		records[recordNumber].changesNumber++;
	}
	catch (const std::out_of_range& e)
	{
		printf("Error changing record\n");
	}
	Save_records(header, records);
}

void Remove_record() {
	Header header = Read_header();
	vector <Record> records = Read_records();
	try {
		int i;
		printf("Enter the number of the record you want to delete:");
		scanf("%i", &i);

		if (strcmp(records.at(i).data, "") != 0) header.dataRecordsNumber--;
		records.erase(records.begin() + i);

		vector<Record>(records).swap(records);
		for (int k = 0; k < records.size(); k++) {
			records[k].number = k;
		}
	}
	catch (const std::out_of_range& e)
	{
		printf("\nError deleting record!");
	}
	Save_records(header, records);
}

void Save_records(Header headerInfo, vector <Record> records)
{
	HANDLE changeFile = CreateFile(fileName, GENERIC_WRITE, NULL, NULL, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	SetFilePointer(changeFile, NULL, NULL, FILE_BEGIN);
	WriteFile(changeFile, &headerInfo, sizeof(Header), NULL, NULL);
	SetFilePointer(changeFile, NULL, NULL, FILE_END);

	for (int i = 0; i < records.size(); i++) 
		WriteFile(changeFile, &records[i], sizeof(Record), NULL, NULL);
	CloseHandle(changeFile);
}