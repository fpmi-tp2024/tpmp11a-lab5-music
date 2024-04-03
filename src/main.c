#include <string.h>
#include <stdio.h>
#include <locale.h>
#include "../include/MusicManager.h"
#include "../sqlite/sqlite3.h"

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
