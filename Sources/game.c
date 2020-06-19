#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>

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

link **setupGame()
{
	//Getting simulations list and choice's recipient
	link 
		**gameChains = safeMalloc(sizeof(link *) * lastStructId, "setupGame/gameChains init"),
		*simulations = readChain(globalFile[_simulation]),
		*currentSimPtr = NULL;
	int i;
	char choice[] = "\0";
	bool createSim = false;
	
	//Set each ptr of lists of data to NULL
	memset(gameChains, 0, sizeof(link *) * lastStructId);
	
	if(simulations != NULL)
	{
		printf("Create a new simulation ? (y/other)\n");
		scanf("%s", choice);
	}
	
	if(simulations == NULL || !strcmp(choice, "y"))
	{
		//Creating a game
		currentSimPtr = newLink("setupGame/no simulation found/create simulation", _simulation, true);
		
		//Getting the new simulations list
		simulations = insertLink(simulations, currentSimPtr);
		
		createSim = true;
	}
	else
	{
		currentSimPtr = selectLink(simulations);
		
		//Freeing selection, ommiting choice
		freeChain(&simulations, currentSimPtr);
	}
	
	//Creating game files from the source code's template
	savesFile *gameFile = setGameFiles(currentSimPtr);
	
	if(simulations == NULL)
		for(i = _event; i < lastStructId; i++)
			//Creating the directory for wanted file
			mkSdir(gameFile[i].path);
	
	//Get selected simulation
	gameChains[_simulation] = currentSimPtr;
	
	if(createSim)
	{
		//Creating a character
		printf("Design your character:\n");
		gameChains[_person] = newLink("setupGame/no simulation found/create character", _person, true);
		*gameChains[_person] = grabLink(_person, NULL);
		setLinkId(gameChains[_person], 1);
		
		//Save created character
		writeChain(gameChains[_person], gameFile[_person]);
	}
	
	//Rewriteing simulations in case a new's here
	writeChain(simulations, gameFile[_simulation]);
	
	for(i = 0; i < lastStructId; i++)
		if(gameChains[i] == NULL)
			//Load chain
			gameChains[i] = readChain(gameFile[i]);
	
	return gameChains;
}

bool playGame(link **gameChains)
{
	bool keepPlaying = true;
	
	link *newEvent = newLink("newEvent", _event, false);
	*newEvent = grabLink(_event, gameChains[_simulation]);
	gameChains[_event] = insertEvent(gameChains[_event], newEvent);
	
	system("cls");
	printf("Game data:\n");
	int i;
	savesFile *gameFile = setGameFiles(gameChains[_simulation]);
	for (i = 0; i < lastStructId; i++)
	{
		displayChain(gameChains[i], gameChains[_simulation]);
		if (&gameFile[i] != NULL)
			writeChain(gameChains[i], gameFile[i]);

		#ifdef DEBUG
			else printf("<playGame> Warning: Can't save structId %d\n", i);
		#endif
	}

	free(gameFile);
	
	getch();
	return keepPlaying;
}

void timeSet(link **gameChains, unsigned long int time)
{
	gameChains[_simulation] -> elementPtr -> simulation_.simuledTime = time;
}

void happen(link **gameChains)
{
	unsigned long int time = gameChains[_simulation] -> elementPtr -> simulation_.simuledTime;
}

link* insertEvent(link* chain, link* eventLinkPtr)
{
	if(eventLinkPtr != NULL && eventLinkPtr -> structType == _event)
	{
		setLinkId(eventLinkPtr, getLinkId(higherId(chain)) + 1);

		link
			*nextFromNewLinkPtr = chain,
			*previousLinkPtr = NULL,
			*ret = NULL;
		while (
			nextFromNewLinkPtr != NULL
			&&
			eventLinkPtr->elementPtr->event_.eventTime >
			nextFromNewLinkPtr->elementPtr->event_.eventTime
		)
		{
			//While the current eventTime is bigger than the selected one and as long te selected one exists

			//The ptr that could've been next is a past one
			previousLinkPtr = nextFromNewLinkPtr;

			//Go to the next one
			nextFromNewLinkPtr = nextFromNewLinkPtr -> nextLinkPtr;
		}

		//Now, eventLink's eventTime is greater than nextFromNewLink's one, or there's no more nextFromNewLink.
		//The new eventLink must be added after nextFromNewLinkPtr.

		if(previousLinkPtr == NULL)
		{
			//If the new event must be first
			ret = eventLinkPtr;

			if (chain != NULL)
				//... and not the last
				ret -> nextLinkPtr = chain;
		}
		else
		{
			//If the new event must be in the middle or in last

			//Chain header returned
			ret = chain;

			//eventLinkPtr insertion in the middle
			previousLinkPtr -> nextLinkPtr = eventLinkPtr;
			eventLinkPtr -> nextLinkPtr = nextFromNewLinkPtr;
		}
		return ret;
	}
	else
	{
		#ifdef DEBUG
			//Error return and printing
			printf("<insertEvent> Error: eventLinkPtr = %d", eventLinkPtr);
			if (eventLinkPtr != NULL)
				printf(", eventLinkPtr -> structType = %d", eventLinkPtr->structType);

			printf("\n");
		#endif

		return NULL;
	}
}