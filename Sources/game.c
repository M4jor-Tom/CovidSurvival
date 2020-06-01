#include <stdio.h>

#include "../Headers/main.h"

extern savesFile globalFile[];

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
	printf("\t   Watch Elements-----------4\n");
	printf("\t   Back to the main menu----5\n");
	printf("\n\t  Please make a choice\n");
}

void elementsMenu(char *optionsLabel)
{
	//[ELEMENTS_MENU_OPTIONS]
	//[CREATE_STRUCTURE]
	printf("\t-----\tElements menu\t-----\t\n\n");
	int i, j;
	for(i = 1, j = 0; j < globalStructuresCount; i++, j++)
		printf("\t   %s %s----%d\n", optionsLabel, globalFile[j].name, i);
	
	printf("\t   Back to the edition menu----%d\n", globalStructuresCount + 1);
	printf("\n\t  Please make a choice\n");
}

int menu(int menuType, char *optionsLabel)
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
			elementsMenu(optionsLabel);
			break;
	}
		
	//User selection
	scanf("%d", &select);
	getchar();
		
	system("cls");
	return select;
}


link *setupGame()
{
	//Getting simulations list and choice's recipient
	link *simulations = readChain(globalFile[_simulation], _simulation);
	link *currentSimPtr = NULL;
	
	if(simulations != NULL)
	{
		int idChoice = 0;
		
		do
		{
			//Displaying simulations
			displayChain(simulations);
			printf("Select a simulation Id: ");
			
			//Selecting a game
			scanf("%u", &idChoice);
			getchar();
			
			//Fetching for the game
			currentSimPtr = chain_search(simulations, idChoice);
			
			//Freeing selection, ommiting choice
			freeChain(simulations, currentSimPtr);
		}while(currentSimPtr == NULL);
	}
	else
	{
		//Creating a game
		currentSimPtr = newLink("setupGame/no simulation found/create simulation", _simulation, true);
		setLinkId(currentSimPtr, 1);
		if(!writeChain(currentSimPtr, globalFile[_simulation]))
			printf("<setupGame> Error: writeChain failed");
		
		//Creating a character
		printf("Design your character:\n");
		link *personPtr = newLink("setupGame/no simulation found/create character", _person, true);
		*personPtr = grabLink(_person);
		
		//Creating game files from the source code's template
		savesFile *gameFile = setGameFiles(currentSimPtr);
		
		int i;
		for(i = 0; i < lastStructId; i++)
			//Creating the directory for wanted file
			mkSdir(gameFile[i].path);
			
		//
		writeChain(personPtr, gameFile[_person]);
	}
	
	return currentSimPtr;
}

bool playGame(simulation *game)
{
	bool keepPlaying = true;
	
	return keepPlaying;
}
