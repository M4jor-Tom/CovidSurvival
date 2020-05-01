#include <stdio.h>

#include "../Headers/game.h"

void mainMenu()
{
	//[MAIN_MENU_OPTIONS]
	printf("\t-----\tMain menu\t-----\t\n\n");
	printf("\t   Play-------------1\n");
	printf("\t   Edit game data---2\n");
	printf("\t   Leave------------3\n");
	printf("\n\t  Please make a choice\n");
}

void editionMenu()
{
	//[EDIT_MENU_OPTIONS]
	printf("\t-----\tEdition menu\t-----\t\n\n");
	printf("\t   Add Elements-------------1\n");
	printf("\t   Edit Elements------------2\n");
	printf("\t   Delete Elements----------3\n");
	printf("\t   Back to the main menu----4\n");
	printf("\n\t  Please make a choice\n");
}

int menu(int menuType)
{
	
	int select = 0;
	
	switch(menuType)
	{
		case 1:
			mainMenu();
			break;
			
		case 2:
			editionMenu();
			break;
	}
		
	//Value conversion
	scanf("%d", &select);
	getchar();
		
	system("cls");
	return select;
}


bool playGame(simulation game)
{
	
}
