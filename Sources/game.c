#include <stdio.h>

#include "../Headers/main.h"

extern savesFiles globalFiles[];
extern savesFiles gameFiles[];

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

void elementsMenu(char *optionsLabel)
{
	//[ELEMENTS_MENU_OPTIONS]
	//[CREATE_STRUCTURE]
	printf("\t-----\tElements menu\t-----\t\n\n");
	int i, j;
	for(i = 1, j = 0; j < globalStructuresCount; i++, j++)
		printf("\t   %s %s----%d\n", optionsLabel, globalFiles[j].name, i);
	
	printf("\t   Back to the edition menu----%d\n", globalStructuresCount + 1);
	printf("\n\t  Please make a choice\n");
}

int menu(int menuType, char *optionsLabel)
{
	int select;
	
	switch(menuType)
	{
		case start:
			mainMenu();
			break;
			
		case edition:
			editionMenu();
			break;
			
		case elements:
			elementsMenu(optionsLabel);
			break;
	}
		
	//Value conversion
	scanf("%d", &select);
	getchar();
		
	system("cls");
	return select;
}


simulation setupGame()
{
	simulation sim;
	return sim;
}

bool playGame(simulation game)
{
	bool keepPlaying = true;
	
	return keepPlaying;
}
