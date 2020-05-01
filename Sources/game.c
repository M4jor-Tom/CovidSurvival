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
	//[EDITION_MENU_OPTIONS]
	printf("\t-----\tEdition menu\t-----\t\n\n");
	printf("\t   Add Elements-------------1\n");
	printf("\t   Edit Elements------------2\n");
	printf("\t   Delete Elements----------3\n");
	printf("\t   Back to the main menu----4\n");
	printf("\n\t  Please make a choice\n");
}

void elementsMenu()
{
	//[ELEMENTS_MENU_OPTIONS]
	printf("\t-----\tElements menu\t-----\t\n\n");
	printf("\t   Back to the edition menu----4\n");
	printf("\n\t  Please make a choice\n");
}

int menu(int menuType)
{
	
	int select = 0;
	
	switch(menuType)
	{
		case start:
			mainMenu();
			break;
			
		case edition:
			editionMenu();
			break;
			
		case elements:
			elementsMenu();
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
	bool keepPlaying = true;
	
	return keepPlaying;
}
