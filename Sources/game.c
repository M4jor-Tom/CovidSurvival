#include <stdio.h>

#include "../Headers/game.h"

int mainMenu()
{
	char select[2];
	int intSelect;
	do
	{
		//[MENU_OPTIONS]
		printf("\t-----\tMain menu\t-----\t\n\n");
		printf("1.Play\n");
		printf("2.Edit game data\n");
		printf("3.Leave\n");
		
		//Value conversion
		scanf("%s", select);
		intSelect = atoi(select);
		
		system("cls");
	}while(intSelect > 3);
	return intSelect;
}

bool playGame(simulation game)
{
	
}
