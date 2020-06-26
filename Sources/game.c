#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
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

		setLinkId(currentSimPtr, highestId(simulations) + 1);
		
		//Getting the new simulations list
		currentSimPtr -> nextLinkPtr = simulations;
		simulations = currentSimPtr;
		
		createSim = true;
	}
	else
	{
		currentSimPtr = selectLink(simulations, true, NULL, (element){0});
		if(currentSimPtr == NULL)
			return NULL;

		simulations = makeFirstLink(getLinkId(currentSimPtr), simulations);

		//Freeing selection, ommiting choice
		//freeChain(&simulations, currentSimPtr);
	}
	
	//Creating game files from the source code's template
	savesFile *gameFile = setGameFiles(currentSimPtr);
	
	if(simulations == NULL)
		for(i = _event; i < lastStructId; i++)
			//Creating the directory for wanted file
			mkSdir(gameFile[i].path);
	
	//Get selected simulation
	gameChains[_simulation] = simulations;
	
	if(createSim)
	{
		//Creating a character
		printf("Design your character:\n");
		gameChains[_person] = newLink("setupGame/no simulation found/create character", _person, true);
		*gameChains[_person] = grabLink(_person, NULL);
		gameChains[_person] -> elementPtr -> person_.houseId = 2;
		gameChains[_person]->elementPtr->person_.placeId = 2;
		setLinkId(gameChains[_person], hardcodedMaxId + 1);
		
		//Save created character
		writeChain(gameChains[_person], gameFile[_person]);
	}
	
	//Rewriteing simulations in case a new's here
	writeChain(simulations, gameFile[_simulation]);
	
	for(i = 0; i < lastStructId; i++)
		if(gameChains[i] == NULL)
		{
			//Load chain
			gameChains[i] = readChain(gameFile[i]);
		}
	
	return gameChains;
}

void inGameActions(link** gameChains, bool *keepPlaying)
{
	system("cls");
	printf("Simulation %ld, ", getLinkId(gameChains[_simulation])); printf("["); displayTime(getTime(gameChains)); printf("]\n");
	printf("\n\tWhat do ?\n");
	printf("\n\tWait-----------------1");
	printf("\n\tDo actions-----------2");
	printf("\n\tWatch informations---3\n");
	printf("\n\tLeave simulation-----4\n\n");
	int select = 0;
	do
	{
		if (select == 0)
			printf("\rSelect one of those: ");
		else
			printf("\rSelect one existing of those: ");


		select = getche();
	}while(select != '1' && select != '2' && select != '3' &&select != '4' && select != '&' && select != 'é' && select != '"' && select != '\'');

	link
		*eventChoice = NULL,
		*newEvent = NULL,
		*filteredChain = NULL;
	element filter;
	structId chainType;
	bool couldInsert = false;

	switch (select)
	{
		case '1':
		case '&':
			run(gameChains, grabDateTime("\nTill when do you want to wait ?"), true);
			break;

		case '2':
		case 'é':
			newEvent = newLink("inGameActionsMenu/newEvent malloc", _event, false);
			*newEvent = grabLink(_event, gameChains[_simulation]);
			gameChains[_event] = insertEvent(gameChains, gameChains[_event], newEvent, &couldInsert);
			printf("[i]Event %s\n\n->\n", couldInsert ? "scheduled" : "unschedulable");
			getch();

			break;

		case '3':
		case '"':
			printf("\nWich information type do you want to watch ?\n1.Inventory\n2.Schedulements\n3.Inmates\n");
			do
			{
				if (select == 0)
					printf("\rSelect one of those: ");
				else
					printf("\rSelect one existing of those: ");

				select = getche();
				printf("\n");
			}while(select != '1' && select != '2' && select != '3' && select != '&' && select != 'é' && select != '"');

			switch (select)
			{
				case '1':
				case '&':
					chainType = _item;
					filter = (element)
					{
						.item_.locationPersonId = playerId
					};
					break;

				case '2':
				case 'é':
					chainType = _event;
					filter = (element)
					{
						.event_.transmitterId = playerId,
						.event_.receiverId = playerId
					};
					break;

				case '3':
				case '"':
					chainType = _person;
					filter = (element)
					{
						.person_.houseId = 2 // Your house
					};
					break;
			}

			filteredChain = filterChainBy(gameChains[chainType], filter);
			displayChain(filteredChain, gameChains[_simulation]);
			freeChain(&filteredChain, NULL);

			printf("Delete an event ? (y/else)\n");
			if (getche() == 'y')
			{
				system("cls");
				link *toDelete = selectLink(
					gameChains[_event],
					true,
					gameChains[_simulation],
					(element) {.event_.receiverId = playerId, .event_.transmitterId = playerId}
				);
				gameChains[_event] = deleteLink(gameChains[_event], getLinkId(toDelete));
			}

			printf("\n->\n");
			getch();
			break;
		case '4':
		case '\'':
			*keepPlaying = false;
			break;
	}
}

stats getPlayerStats(link** gameChains)
{
	return getLinkById(_person, playerId, gameChains[_simulation])->elementPtr->person_.stats_;
}

bool deadEnd(stats analyse)
{
	char deathMessage[150] = "\0";
	bool dead = false;
	if (analyse.health == 0)
	{
		strcat(deathMessage, "You die.\n");
		dead = true;
	}
	if (analyse.hunger == 0)
	{
		strcat(deathMessage, "Yes, eating was important.\n");
		dead = true;
	}
	if (analyse.hygiene == 0)
	{
		strcat(deathMessage, "You stinked to death.\n");
		dead = true;
	}
	if (analyse.mentalHealth == 0)
	{
		strcat(deathMessage, "You suddunly bought a knife, threatened people in the street, and got caught.\n");
		dead = true;
	}
	if (dead)
	{
		printf("Death reason: %s", deathMessage);
		getch();
	}
	return dead;
}

bool playGame(link **gameChains)
{
	bool keepPlaying = false;
	bool dead = false;
	if (gameChains != NULL)
	{
		keepPlaying = true;
		inGameActions(gameChains, &keepPlaying);

		dead = deadEnd(getLinkById(_person, playerId, gameChains[_simulation]) -> elementPtr -> person_.stats_);
		keepPlaying = !dead && keepPlaying;

		int i;
		savesFile* gameFile = setGameFiles(gameChains[_simulation]);

		for (i = 0; i < lastStructId; i++)
		{
			if (&gameFile[i] != NULL)
				if(i != _simulation || !dead)
					writeChain(/*dead ? NULL :*/ gameChains[i], gameFile[i]);

			if (dead)
			{
				//gameChains[_simulation] = gameChains[_simulation]->nextLinkPtr;
			}

			#ifdef DEBUG
				else printf("<playGame> Warning: Can't save structId %d\n", i);
			#endif
		}

		free(gameFile);
	}
	
	return keepPlaying;
}

void setTime(link **gameChains, unsigned long long int time)
{
	gameChains[_simulation] -> elementPtr -> simulation_.simuledTime = time;
}

unsigned long long int getTime(link **gameChains)
{
	return gameChains[_simulation]->elementPtr->simulation_.simuledTime;;
}

unsigned long long int getEventTime(link* event)
{
	return event -> elementPtr -> event_.eventTime;
}

link *getIncomingEvent(link **gameChains)
{
	if(gameChains != NULL && gameChains[_event] != NULL)
	{
		unsigned long long int simTime = getTime(gameChains);
		link
			* eventsCursor = gameChains[_event];
		while(eventsCursor != NULL)
		{
			if(eventsCursor->elementPtr->event_.eventTime > simTime)
				//Found an event that's in the future
				return eventsCursor;

			eventsCursor = eventsCursor -> nextLinkPtr;
		}
		return NULL;
	}
	else
	{
		return NULL;
	}
}

unsigned long long int getEventDuration(link *event, link **gameChains)
{
	if (gameChains != NULL)
	{
		//[JOIN] event-eventType
		link* eventType_ = getJoinedLink(event, _eventType, gameChains[_simulation], 1);
		unsigned long long int duration = eventType_->elementPtr->eventType_.duration_s;
		freeLink(&eventType_);
		return duration;
	}
	else
	{
		return 0;
	}
}

unsigned long long int getEventEnd(link *event, link **gameChains)
{
	return event -> elementPtr -> event_.eventTime + getEventDuration(event, gameChains);
}

link *getHappeningEvent(link **gameChains)
{
	if(gameChains != NULL && gameChains[_event] != NULL)
	{
		unsigned long long int simTime = getTime(gameChains);
		link *eventsCursor = gameChains[_event];

		while(
			eventsCursor != NULL 
			&& 
			getEventEnd(eventsCursor, gameChains) < simTime
		)
		{
			//While the event is in the past, pass it
			eventsCursor = eventsCursor -> nextLinkPtr;
		}

		//Now eventsCursor points to an event that is ended in the future
		//Les's know if it began

		if(eventsCursor != NULL && eventsCursor -> elementPtr -> event_.eventTime < simTime)
			return eventsCursor;
	}
	return NULL;
}

bool inChain(link *chain, link *linkPtr)
{
	bool found = false;
	while(chain != NULL && found == false)
	{
		found = linkPtr == chain;

		chain = chain -> nextLinkPtr;
	}
	return found;
}

stats operateStats(stats base, stats consequence)
{
	//[EDIT_STATS]
	return (stats)
	{
		.health = returnInRange(0, base.health + consequence.health, 100),
		.hunger = returnInRange(0, base.hunger + consequence.hunger, 100),
		.hygiene = returnInRange(0, base.hygiene + consequence.hygiene, 100),
		.karma = returnInRange(0, base.karma + consequence.karma, 100),
		.mentalHealth = returnInRange(0, base.mentalHealth + consequence.mentalHealth, 100),
		.money = (float)returnInRange(0, (int)base.money + (int)consequence.money, 100),
		.stamina = returnInRange(0, base.stamina + consequence.stamina, 100),
		.coronaVirus = base.coronaVirus | consequence.coronaVirus
	};
}

void consumeItem(link** gameChains, link* consumedLinkPtr, unsigned int amount)
{
	item consumed = consumedLinkPtr->elementPtr->item_;
	itemType consumedType = getLinkById(_itemType, consumed.itemTypeId, gameChains[_simulation])->elementPtr->itemType_;
	consumedLinkPtr->elementPtr->item_.usedCount = consumed.usedCount + amount;
	if (consumedLinkPtr->elementPtr->item_.usedCount >= consumedType.usesCount)
	{
		//Person's item broke
		gameChains[_item] = deleteLink(gameChains[_item], getLinkId(consumedLinkPtr));
	}
}

bool eventApply(link** gameChains, link* eventLinkPtr, bool forward)
{
	//Wich event ?
	event happening = eventLinkPtr -> elementPtr -> event_;
	link* happeningTypeLinkPtr = getLinkById(_eventType, happening.eventTypeId, gameChains[_simulation]);
	eventType happeningType = happeningTypeLinkPtr != NULL ? happeningTypeLinkPtr->elementPtr->eventType_ : (eventType) { 0 };

	//Risk to et controlled and contamined
	risk(gameChains, happeningTypeLinkPtr, forward);

	//Wich item consummed ?
	link* consumedLinkPtr = getLinkById(_item, happening.itemId, gameChains[_simulation]);

	//Who is targetted ?
	link* receiverLinkPtr = getLinkById(_person, happening.receiverId, gameChains[_simulation]);
	person receiver = receiverLinkPtr->elementPtr->person_;

	//Where is the event/receiver
	link
		* whereEventPtr = getLinkById(_place, happening.placeId, gameChains[_place]),
		* wherePersonPtr = getLinkById(_place, receiver.placeId, gameChains[_simulation]);

	if((consumedLinkPtr != NULL || happening.itemId == nullId) && (whereEventPtr == wherePersonPtr || happening.placeId == nullId))
	{
		//Success
		receiverLinkPtr->elementPtr->person_.stats_ = operateStats(receiver.stats_, happeningType.onSuccess);

		if (consumedLinkPtr != NULL)
		{
			consumeItem(gameChains, consumedLinkPtr, happeningType.itemTypeConsumption);
		}
	}
	else if(happeningType.executableOnFailure)
	{
		//Failure
		receiverLinkPtr->elementPtr->person_.stats_ = operateStats(receiver.stats_, happeningType.onFailure);
	}
	else 
		//Cannot happen
		return false;

	//Add consequences for particular cases
	personParticularity cursor;
	for(cursor = 0; cursor < lastPersonParticularityId; cursor++)
		receiverLinkPtr->elementPtr->person_.stats_ = operateStats(receiver.stats_, happeningType.consequenceFor[cursor]);

	//Could happen
	return true;
}

void happenEvent(link **gameChains, link *eventLinkPtr, bool forward)
{
	if(gameChains != NULL && gameChains[_event] != NULL && eventLinkPtr != NULL)
	{
		link *eventTypePtr = getJoinedLink(eventLinkPtr, _eventType, gameChains[_simulation], 1);

		//Process event's consequences
		switch(getLinkId(eventTypePtr))
		{
			case getOutEventTypeId:
				getOut(gameChains, forward);
				break;

			case shopEventTypeId:
				shop(gameChains, forward);
				break;

			default:
				if (eventApply(gameChains, eventLinkPtr, forward))
				{
					printf("\nEvent done !\n");
					getch();
				}
				else
				{
					printf("\nEvent cancelled...\n");
					getch();
				}
				break;
		}

		//Set time to event's end
		setTime(gameChains, getEventEnd(eventLinkPtr, gameChains));
	}
}

void run(link **gameChains, unsigned long long int nextTime, bool forward)
{
	link *nextEvent = getIncomingEvent(gameChains);

	printf("\nWait from "); displayTime(getTime(gameChains)); printf(" to "); displayTime(nextTime); printf(".");

	if (nextEvent == NULL || getEventTime(nextEvent) > nextTime)
	{
		//Set requested time (nothing happend since time has gone)
		idle(gameChains, nextTime - getTime(gameChains), forward);
	}
	else while(getIncomingEvent(gameChains) != NULL && getEventTime(getIncomingEvent(gameChains)) < nextTime)
	{
		nextEvent = getIncomingEvent(gameChains);
		printf("\nBeeep-beeep-beeep ! A schedule alert rings on your phone: ");
		displayTime(getEventTime(nextEvent)); 
		getch();
		printf("\n");
		unsigned long long int nE = getEventTime(nextEvent);
		//Skip time till it's next event
		idle(gameChains, nE - getTime(gameChains), forward);

		//Happen event (time will go to event's end)
		happenEvent(gameChains, nextEvent, forward);
	}
}

link* insertEvent(link **gameChains, link* chain, link* eventLinkPtr, bool *couldInsert)
{
	if(couldInsert != NULL)
		*couldInsert = false;

	if(gameChains != NULL && eventLinkPtr != NULL && eventLinkPtr -> structType == _event)
	{
		//Get/Setting Id for new
		long int
			lastId = highestId(chain),
			newId = lastId > hardcodedMaxId
				? lastId
				: hardcodedMaxId;
		
		setLinkId(eventLinkPtr, newId + 1);

		link
			*nextFromNewLinkPtr = chain,
			*previousLinkPtr = NULL,
			*filtered = NULL,
			*ret = NULL;

		//Getting user's events
		//filtered = filterChainBy(gameChains[_event], (element){.event_.transmitterId = playerId, .event_.receiverId = playerId});

		//Skipping past
		while(
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

		//Inserting event
		if(previousLinkPtr == NULL)
		{
			//If the new event must be first
			if (chain == NULL)
			{
				ret = eventLinkPtr;

				if (couldInsert != NULL)
					*couldInsert = true;
			}
			else if(getEventEnd(eventLinkPtr, gameChains) < getEventTime(chain))
			{
				//[SCHEDULABLE]If the end of the event we want to schedule is BEFORE the begining of the next one, insert.
				ret = eventLinkPtr;
				
				if (chain != NULL)
					//... and not the last
					ret->nextLinkPtr = chain;

				if(couldInsert != NULL)
					*couldInsert = true;
			}
			else
			{
				//[UNSCHEDULABLE]If the event we want to schedule ends after the next one begins, don't insert
				freeLink(&eventLinkPtr);
				ret = chain;
			}
		}
		else
		{
			//If the new event must be in the middle or in last

			//Chain header returned
			ret = chain;

			if(
				getEventEnd(previousLinkPtr, gameChains) < getEventTime(eventLinkPtr) 
				&& 
				(
					previousLinkPtr->nextLinkPtr == NULL || 
					getEventEnd(previousLinkPtr, gameChains) < getEventTime(previousLinkPtr->nextLinkPtr)
				)
			)
			{
				//eventLinkPtr insertion in the middle
				previousLinkPtr -> nextLinkPtr = eventLinkPtr;
				eventLinkPtr -> nextLinkPtr = nextFromNewLinkPtr;

				if(couldInsert != NULL)
					*couldInsert = true;
			}
			else 
			{
				freeLink(&eventLinkPtr);
				if (couldInsert != NULL)
					*couldInsert = false;
			}

		}
		return ret;
	}
	else
	{
		#ifdef DEBUG
			//Error return and printing
			printf("<insertEvent> Error: gameChains = %llu, eventLinkPtr = %llu", (unsigned long long)gameChains, (unsigned long long)eventLinkPtr);
			if (eventLinkPtr != NULL)
				printf(", eventLinkPtr -> structType = %d", eventLinkPtr->structType);

			printf("\n");
		#endif

		return NULL;
	}
}