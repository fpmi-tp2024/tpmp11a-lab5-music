#include "../sqlite/sqlite3.h"

sqlite3* db;

const char* adminCommands[] = {
	"For all compacts - information on the number of sold and remaining compacts of the same type in descending order of difference.",

	"For the specified compact - information on the number and value of compacts sold during the specified period.",

	"For a compact purchased the maximum number of times - give all information about it and music works.",

	"For the most popular artist - information on the number of sold CDs with his works.",

	"For each author - information about the number of sold CDs with his records and the amount of money received.",

	"Prohibit putting comp sales information in the table if the total number of comps sold exceeds the total number of comps received.",

	"For the specified period, determines the number of compacts received and sold for each type of compact.",

	"Outputs information about the results of its sale for the specified period by the given compact code.",

	"Insert",
	"Update",
	"Delete",
};
const char* userCommands[] = {
	"For the most popular artist - information on the number of sold CDs with his works.",

	"For a compact purchased the maximum number of times - give all information about it and music works.",

	"Outputs information about the results of its sale for the specified period by the given compact code."
};
#define ADMIN_FUN_COUNT 11
#define USER_FUN_COUNT 3
#define EXIT_CHOISE 0

void printCommands(const char* comand[], int size);
int Authorization();

void CountOfSoldAndRemainingCD_Ordered(sqlite3 *db);
void CountAndCostCD_ByDate(sqlite3 *db);
void AllCd_ByMaxSold(sqlite3 *db);
void CountAndName_ByMostPopularSigner(sqlite3 *db);
void SalaryAndSoldCount_ByAuthor(sqlite3 *db);
void Restrictions(sqlite3 *db);
void InfoCD_ByDate(sqlite3 *db);
void Info_ByDate(sqlite3 *db);
void Insert(sqlite3 *db);
void UpDate(sqlite3 *db);
void Delete(sqlite3 *db);

const void (*Admin_functions[ADMIN_FUN_COUNT])(sqlite3 *db) = {
	CountOfSoldAndRemainingCD_Ordered,
	CountAndCostCD_ByDate,
	AllCd_ByMaxSold,
	CountAndName_ByMostPopularSigner,
	SalaryAndSoldCount_ByAuthor,
	Restrictions,
	InfoCD_ByDate,
	Info_ByDate,
	Insert,
	UpDate,
	Delete,
};
const void (*User_functions[USER_FUN_COUNT])(sqlite3* db) = {
	CountAndName_ByMostPopularSigner,
	AllCd_ByMaxSold,
	Info_ByDate,
};
const void (**Function[2])(sqlite3* db) = {
		User_functions,
		Admin_functions
};
