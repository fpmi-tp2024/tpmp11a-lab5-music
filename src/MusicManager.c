#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../sqlite/sqlite3.h"

const char* adminPassword = "123456";
sqlite3* d;

struct tm number_to_date(long int number) {
	struct tm tm;
	time_t t = (time_t)number;
	tm = *gmtime(&t);
	return tm;
}

long int date_to_number(int day, int month, int year) {
	struct tm tm;
	tm.tm_mday = day;
	tm.tm_mon = month - 1; // Ìåñÿöû â tm íà÷èíàþòñÿ ñ 0
	tm.tm_year = year - 1900; // Ãîäû â tm íà÷èíàþòñÿ ñ 1900
	tm.tm_hour = 0;
	tm.tm_min = 0;
	tm.tm_sec = 0;
	tm.tm_isdst = -1;
	return mktime(&tm);
}

void printCommands(const char* comand[], int size) {
	for (int i = 0; i < size; i++)
		printf("%d - \t\t%s\n\n", i + 1, comand[i]);
	printf("0 - Exit\n");
}

int Authorization(sqlite3** db) {
	char userName[51], password[51];
	d = *db;
	printf("Enter your name: ");
	scanf("%s", userName);
	userName[50] = '\0';
	printf("Enter password: ");
	scanf("%s", password);
	password[50] = '\0';
	int isAdmin = !strcmp(password, adminPassword);
	char* rights = isAdmin ? "admin" : "user";
	printf("Hello \'%s\' (rights - %s )\nWellcome to database Music-Salon!\n", userName, rights);
	return isAdmin;
}

static void restrictions_callback(sqlite3_context* context, int argc, sqlite3_value** argv) {
	int total_received = 0;
	int total_sold = 0;
	int compact_disk_id = atoi(sqlite3_value_text(argv[4]));

	sqlite3_stmt* stmt;
	const char* sql = "SELECT SUM(count) FROM Compact_Sale_Info WHERE Compact_Disk_info_ID = ? AND codeOfOperation = 1";
	sqlite3_prepare_v2(d, sql, -1, &stmt, 0);
	sqlite3_bind_int(stmt, 1, compact_disk_id);
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		total_received = sqlite3_column_int(stmt, 0);
	}
	sqlite3_finalize(stmt);

	sqlite3_prepare_v2(d, sql, -1, &stmt, 0);
	sqlite3_bind_int(stmt, 1, compact_disk_id);
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		total_sold = sqlite3_column_int(stmt, 0);
	}
	sqlite3_finalize(stmt);

	if (total_sold > total_received) {
		fprintf(stderr, "Error: Cannot insert new record into Compact_Sale_Info table. The total number of sold compact disks exceeds the total number of received compact disks.\n");
		sqlite3_exec(d, "ROLLBACK", 0, 0, 0);
	}
	else
	{
		printf("Evetything is ok\n");
	}
}

static int callback(void* tmp, int argc, char* argv[], char* colName[]) {
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(colName[i], "dateOfOperation") == 0 || strcmp(colName[i], "dateOfCreate") == 0)
		{
			char* endptr;
			long int number = strtol(argv[i], &endptr, 10);
			struct tm tm = number_to_date(number);

			printf(" %s = %d-%d-%d\n", colName[i], tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
		}
		else
		{
			printf(" %s = %s\n", colName[i], argv[i] ? argv[i] : "NULL");
		}
	}
	printf("\n");
	return 0;
}

void CountOfSoldAndRemainingCD_Ordered(sqlite3 *db) {
	char requestBuffer[500];
	char* errorMsg = 0;

	sprintf(requestBuffer,
		"SELECT cdi.ID, cdi.producerName, IFNULL(SUM(csi.count * (csi.codeOfOperation = 1)), 0) AS sold_count, IFNULL(SUM(csi.count * (csi.codeOfOperation = 0)), 0) AS remaining_count, ABS(IFNULL(SUM(csi.count * (csi.codeOfOperation = 1)), 0) - IFNULL(SUM(csi.count * (csi.codeOfOperation = 0)), 0)) AS difference "
		"FROM Compact_Disk_info cdi "
		"LEFT JOIN Compact_Sale_Info csi "
		"ON cdi.ID = csi.Compact_Disk_info_ID "
		"GROUP BY cdi.ID, cdi.producerName, cdi.price "
		"ORDER BY difference DESC;"
	);
	if (sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg))
		printf("%s", errorMsg);
}
void CountAndCostCD_ByDate(sqlite3 *db){
	char requestBuffer[255];
	char* errorMsg = 0;
	int id;
	printf("Enter id: ");
	scanf("%d", &id);


	int startDay, startMonth, startYear;

	printf("Enter start day: ");
	scanf("%d", &startDay);
	printf("Enter start month: ");
	scanf("%d", &startMonth);
	printf("Enter start year: ");
	scanf("%d", &startYear);
	long int startDate = date_to_number(startDay, startMonth, startYear);


	int endDay, endMonth, endYear;

	printf("Enter end day: ");
	scanf("%d", &endDay);
	printf("Enter end month: ");
	scanf("%d", &endMonth);
	printf("Enter end year: ");
	scanf("%d", &endYear);
	long int endDate = date_to_number(endDay, endMonth, endYear);

	sprintf(requestBuffer,
		"SELECT Compact_Sale_Info.count, Compact_Disk_info.price "
		"FROM Compact_Sale_Info "
		"JOIN Compact_Disk_info "
		"USING(id) "
		"WHERE Compact_Sale_Info.dateOfOperation "
		"BETWEEN %ld and %ld and Compact_Disk_info.id = %d;"
		, startDate, endDate, id);
	if (sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg))
		printf("%s", errorMsg);
}
void AllCd_ByMaxSold(sqlite3 *db){
	char requestBuffer[500];
	char* errorMsg = 0;
	sprintf(requestBuffer,
		"SELECT d.ID, d.dateOfCreate, d.producerName, d.price, p.author, p.signer, p.name, MAX(s.count) as max_count "
		"FROM Compact_Disk_info d "
		"JOIN producer_info p ON d.ID = p.Compact_Disk_info_ID "
		"JOIN Compact_Sale_Info s ON d.ID = s.Compact_Disk_info_ID "
		"GROUP BY d.ID, d.dateOfCreate, d.producerName, d.price, p.author, p.signer, p.name "
		"HAVING MAX(s.count) = (SELECT max(count) FROM Compact_Sale_Info);"
	);

	if (sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg))
		printf("%s", errorMsg);
}
void CountAndName_ByMostPopularSigner(sqlite3 *db){
	char requestBuffer[255];
	char* errorMsg = 0;
	sprintf(requestBuffer,
		"SELECT p.name, p.signer, s.count "
		"FROM producer_info p "
		"JOIN Compact_Sale_Info s "
		"ON p.Compact_Disk_info_ID = s.ID "
		"WHERE s.count = (SELECT max(count) FROM Compact_Sale_Info);"
	);
	if (sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg))
		printf("%s", errorMsg);
}
void SalaryAndSoldCount_ByAuthor(sqlite3 *db){
	char requestBuffer[255];
	char* errorMsg = 0;
	sprintf(requestBuffer,
		"SELECT p.signer, p.name, sum(d.price * s.count) maxsum "
		"FROM producer_info p "
		"JOIN Compact_Sale_Info s "
		"ON p.Compact_Disk_info_ID = s.ID "
		"JOIN Compact_Disk_info d "
		"ON p.Compact_Disk_info_ID = d.ID "
		"GROUP by p.signer;"
	);
	if (sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg))
		printf("%s", errorMsg);
}
void Insert(sqlite3 *db){
	char requestBuffer[255];
	char* errorMsg = 0;
	int choice;
	printf("If you want to INSERT in Producer Info Table type 1\n");
	printf("If you want to INSERT in Compact Disk Info Table type 2\n");
	printf("If you want to INSERT in Compact Sale Info Table type 3\n");

	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
	{
		char author[51], signer[51], name[51];
		int Compact_Disk_info_ID;
		printf("Enter author: ");
		scanf("%s", author);
		author[50] = '\0';
		printf("Enter signer: ");
		scanf("%s", signer);
		signer[50] = '\0';
		printf("Enter name: ");
		scanf("%s", name);
		name[50] = '\0';
		printf("Enter Compact_Disk_info_ID: ");
		scanf("%d", &Compact_Disk_info_ID);

		sprintf(requestBuffer, "INSERT INTO producer_info (author, signer, name, Compact_Disk_info_ID) "
			"VALUES (null, '%s', '%s', '%s', '%d');", author, signer, name, Compact_Disk_info_ID);
		break;
	}
	case 2:
	{
		char producerName[51];
		int price;

		int createDay, createMonth, createYear;

		printf("Enter create day: ");
		scanf("%d", &createDay);
		printf("Enter create month: ");
		scanf("%d", &createMonth);
		printf("Enter create year: ");
		scanf("%d", &createYear);
		long int dateOfCreate = date_to_number(createDay, createMonth, createYear);


		printf("Enter Producer Name: ");
		scanf("%s", producerName);
		producerName[50] = '\0';
		printf("Enter price: ");
		scanf("%d", &price);

		sprintf(requestBuffer, "INSERT INTO Compact_Disk_info (ID, dateOfCreate, producerName, price) "
			"VALUES (null, %ld, '%s', '%d');", dateOfCreate, producerName, price);
		break;
	}
	case 3:
	{
		char producerName[51];
		int Compact_Disk_info_ID, count, codeOfOperation;
		printf("Enter count: ");
		scanf("%d", &count);


		int operationDay, operationMonth, operationYear;

		printf("Enter start day: ");
		scanf("%d", &operationDay);
		printf("Enter start month: ");
		scanf("%d", &operationMonth);
		printf("Enter start year: ");
		scanf("%d", &operationYear);
		long int dateOfOperation = date_to_number(operationDay, operationMonth, operationYear);

		printf("Enter Code of Operation (0 or 1): ");
		scanf("%d", &codeOfOperation);

		if (codeOfOperation != 0 && codeOfOperation != 1)
		{
			printf("Wrong codeOfOperation\n");
			return;
		}

		printf("Enter Compact_Disk_info_ID: ");
		scanf("%d", &Compact_Disk_info_ID);

		sprintf(requestBuffer, "INSERT INTO Compact_Sale_Info (ID, count, dateOfOperation, codeOfOperation, Compact_Disk_info_ID) "
			"VALUES (null, '%d', %ld, %d, %d);", count, dateOfOperation, producerName, Compact_Disk_info_ID);
		break;
	}
	default:
		printf("Wrong choice!\n");
		return;
	}

	if (sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg))
		printf("%s", errorMsg);
}
void UpDate(sqlite3 *db){
	char requestBuffer[255];
	char* errorMsg = 0;

	int choice;
	printf("If you want to UPDATE Producer Info Table type 1\n");
	printf("If you want to UPDATE Compact Disk Info Table type 2\n");
	printf("If you want to UPDATE Compact Sale Info Table type 3\n");

	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
	{
		int id;
		printf("Enter id to update: ");
		scanf("%d", &id);
		char author[51], singer[51], name[51];
		int Compact_Disk_info_ID;
		printf("Enter author: ");
		scanf("%s", author);
		author[50] = '\0';
		printf("Enter signer: ");
		scanf("%s", singer);
		singer[50] = '\0';
		printf("Enter name: ");
		scanf("%s", name);
		name[50] = '\0';
		printf("Enter Compact_Disk_info_ID: ");
		scanf("%d", &Compact_Disk_info_ID);

		sprintf(requestBuffer, "UPDATE producer_info SET name='%s', author='%s', signer='%s' WHERE id=%d;", name, author, singer, id);
		break;
	}
	case 2:
	{
		int id;
		printf("Enter id to update: ");
		scanf("%d", &id);
		char producerName[51];
		int price;

		int createDay, createMonth, createYear;

		printf("Enter create day: ");
		scanf("%d", &createDay);
		printf("Enter create month: ");
		scanf("%d", &createMonth);
		printf("Enter create year: ");
		scanf("%d", &createYear);
		long int dateOfCreate = date_to_number(createDay, createMonth, createYear);

		printf("Enter Producer Name: ");
		scanf("%s", producerName);
		producerName[50] = '\0';
		printf("Enter price: ");
		scanf("%d", &price);

		sprintf(requestBuffer, "UPDATE Compact_Disk_info SET dateOfCreate=%ld, producerName='%s', price='%d' WHERE id=%d;", dateOfCreate, producerName, price, id);
		break;
	}
	case 3:
	{
		int id;
		printf("Enter id to update: ");
		scanf("%d", &id);
		char producerName[51];
		int Compact_Disk_info_ID, count, codeOfOperation;
		printf("Enter count: ");
		scanf("%d", &count);


		int operationDay, operationMonth, operationYear;

		printf("Enter start day: ");
		scanf("%d", &operationDay);
		printf("Enter start month: ");
		scanf("%d", &operationMonth);
		printf("Enter start year: ");
		scanf("%d", &operationYear);
		long int dateOfOperation = date_to_number(operationDay, operationMonth, operationYear);

		printf("Enter Code of Operation (0 or 1): ");
		scanf("%d", &codeOfOperation);

		if (codeOfOperation != 0 && codeOfOperation != 1)
		{
			printf("Wrong codeOfOperation\n");
			return;
		}

		printf("Enter Compact_Disk_info_ID: ");
		scanf("%d", &Compact_Disk_info_ID);


		sprintf(requestBuffer, "UPDATE Compact_Sale_Info SET count='%d', dateOfOperation=%ld, codeOfOperation='%d', Compact_Disk_info_ID='%d' WHERE id=%d;", count, dateOfOperation, codeOfOperation, Compact_Disk_info_ID, id);
		break;
	}
	default:
		printf("Wrong choice!\n");
		return;
	}

	if (sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg))
		printf("%s", errorMsg);
}
void Delete(sqlite3 *db){
	char requestBuffer[255];
	char* errorMsg = 0;
	int choice;
	printf("If you want to Delete from Producer Info Table type 1\n");
	printf("If you want to Delete from Compact Disk Info Table type 2\n");
	printf("If you want to Delete from Compact Sale Info Table type 3\n");

	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
	{
		int id;
		printf("Enter id to delete: ");
		scanf("%d", &id);

		sprintf(requestBuffer, "DELETE FROM producer_info WHERE ID = '%d';", id);
		break;
	}
	case 2:
	{
		int id;
		printf("Enter id to delete: ");
		scanf("%d", &id);

		sprintf(requestBuffer, "DELETE FROM Compact_Disk_info WHERE ID = '%d';", id);
		break;
	}
	case 3:
	{
		int id;
		printf("Enter id to delete: ");
		scanf("%d", &id);

		sprintf(requestBuffer, "DELETE FROM Compact_Sale_Info WHERE ID = '%d';", id);
		break;
	}
	default:
		printf("Wrong choice!\n");
		return;
	}

	if (sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg))
		printf("%s", errorMsg);
}
void Restrictions(sqlite3 *db) {
	sqlite3_create_function(db, "restrictions_callback", 0, SQLITE_UTF8, 0, &restrictions_callback, 0, 0);
    const char *sql = "CREATE TRIGGER IF NOT EXISTS check_compact_disk_sales BEFORE INSERT ON Compact_Sale_Info FOR EACH ROW BEGIN SELECT restrictions_callback(); END;";
    sqlite3_exec(db, sql, 0, 0, 0);
}
void InfoCD_ByDate(sqlite3 *db){
	char requestBuffer[500];
	char* errorMsg = 0;

	int startDay, startMonth, startYear;

	printf("Enter start day: ");
	scanf("%d", &startDay);
	printf("Enter start month: ");
	scanf("%d", &startMonth);
	printf("Enter start year: ");
	scanf("%d", &startYear);
	long int startDate = date_to_number(startDay, startMonth, startYear);


	int endDay, endMonth, endYear;

	printf("Enter end day: ");
	scanf("%d", &endDay);
	printf("Enter end month: ");
	scanf("%d", &endMonth);
	printf("Enter end year: ");
	scanf("%d", &endYear);
	long int endDate = date_to_number(endDay, endMonth, endYear);


	sprintf(requestBuffer,
		"INSERT INTO Compact_Disk_Sales_Summary (ProducerName, CountReceived, CountSold) "
		"SELECT cdi.producerName, COUNT(cdi.ID), COALESCE(SUM(csi.count), 0) "
		"FROM Compact_Disk_info cdi "
		"JOIN producer_info p "
		"ON cdi.ID = p.Compact_Disk_info_ID "
		"LEFT JOIN Compact_Sale_Info csi "
		"ON cdi.ID = csi.Compact_Disk_info_ID "
		"WHERE cdi.dateOfCreate BETWEEN %ld AND %ld "
		"AND csi.dateOfOperation BETWEEN %ld AND %ld "
		"GROUP BY cdi.producerName;", startDate, endDate, startDate, endDate);
	if (sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg))
		printf("%s", errorMsg);
}


void Info_ByDate(sqlite3 *db){
	char requestBuffer[800];
	char* errorMsg = 0;
	int id;

	printf("Enter id: ");
	scanf("%d", &id);

	int startDay, startMonth, startYear;

	printf("Enter start day: ");
	scanf("%d", &startDay);
	printf("Enter start month: ");
	scanf("%d", &startMonth);
	printf("Enter start year: ");
	scanf("%d", &startYear);
	long int startDate = date_to_number(startDay, startMonth, startYear);


	int endDay, endMonth, endYear;

	printf("Enter end day: ");
	scanf("%d", &endDay);
	printf("Enter end month: ");
	scanf("%d", &endMonth);
	printf("Enter end year: ");
	scanf("%d", &endYear);
	long int endDate = date_to_number(endDay, endMonth, endYear);


	sprintf(requestBuffer,
		"SELECT cdi.ID, cdi.producerName, IFNULL(SUM(csi.count * (csi.codeOfOperation = 1)), 0) AS sold_count, csi.dateOfOperation, "
		"IFNULL(SUM(csi.count * (csi.codeOfOperation = 0)), 0) AS remaining_count, "
		"ABS(IFNULL(SUM(csi.count * (csi.codeOfOperation = 1)), 0) - IFNULL(SUM(csi.count * (csi.codeOfOperation = 0)), 0)) AS difference "
		"FROM Compact_Disk_info cdi "
		"LEFT JOIN Compact_Sale_Info csi "
		"ON cdi.ID = csi.Compact_Disk_info_ID "
		"WHERE cdi.ID = %d AND csi.dateOfOperation BETWEEN %ld AND %ld "
		"GROUP BY cdi.ID, cdi.producerName, cdi.price;",
		id, startDate, endDate);

	if (sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg))
		printf("%s", errorMsg);
}
