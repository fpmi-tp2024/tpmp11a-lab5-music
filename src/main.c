#include <string.h>
#include <stdio.h>
#include <locale.h>
#include "../include/MusicManager.h"
#include "../sqlite/sqlite3.h"

void (*Admin_functions[ADMIN_FUN_COUNT])(sqlite3 *db) = {
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
void (*User_functions[USER_FUN_COUNT])(sqlite3* db) = {
	CountAndName_ByMostPopularSigner,
	AllCd_ByMaxSold,
	Info_ByDate,
};
void (**Function[2])(sqlite3* db) = {
		User_functions,
		Admin_functions
};

int main() {
	setlocale(LC_ALL, "rus");
    	if (sqlite3_open("../doc/DB_Source/Music_Salon_DB.db", &db)) {
       		 printf("Cant open db!\n");
       		 return -1;
   	}
	int isAdmin = Authorization(&db);


	if (isAdmin)
	{
		do {
			int choise;
			printf("\nChoose Command\n");

			printCommands(adminCommands, ADMIN_FUN_COUNT);

			scanf("%d", &choise);

			if (choise == EXIT_CHOISE)
				break;
			if (choise > ADMIN_FUN_COUNT) {
				printf("Invalid Comand");
				continue;
			}

			Function[1][choise - 1](db);
		} while (1);
	}
	else
	{
		do {
			int choise;
			printf("\nChoose Command\n");

			printCommands(userCommands, USER_FUN_COUNT);

			scanf("%d", &choise);

			if (choise == EXIT_CHOISE)
				break;
			if (1 && choise > USER_FUN_COUNT) {
				printf("Invalid Comand");
				continue;
			}

			Function[0][choise - 1](db);
		} while (1);
	}



	printf("Exit...\n");
	return 1;
}
