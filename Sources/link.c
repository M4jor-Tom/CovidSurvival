#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

#include "../Headers/main.h"

extern savesFile globalFile[];

link* newLink(char* errorMessage, structId type, bool createElement)
{
	link* ret = (link*)safeMalloc(sizeof(link), errorMessage);
	
	ret -> nextLinkPtr = NULL;
	ret -> ID = nullId;
	
	ret -> structType = type;
	ret -> elementPtr = createElement
		? newElement(errorMessage)
		: NULL;
	return ret;
}

element *newElement(char* errorMessage)
{
	//Memory allocation
	element* elementPtr = (element*)safeMalloc(sizeof(element), errorMessage);
	
	//Memory initialisation
	memset(elementPtr, 0, sizeof(element));
	
	return elementPtr;
}

void freeLink(link **linkPtrPtr)
{
	if(*linkPtrPtr != NULL)
	{
		//printf("link::accessed\n");
		if((*linkPtrPtr) -> elementPtr != NULL)
		{
			//Frees element if exists
			//printf("element::accessed\n");
			memset((*linkPtrPtr) -> elementPtr, 0, sizeof(element));
			//printf("element::memset\n");
			//free((*linkPtrPtr) -> elementPtr);
			//printf("element::processed\n");
			(*linkPtrPtr) -> elementPtr = NULL;
		}
		
		//Frees link if exists
		memset(*linkPtrPtr, 0, sizeof(link));
		free(*linkPtrPtr);
		*linkPtrPtr = NULL;
		//printf("link::processed\n");
	}
}

void freeChain(link **chainPtr, link *Excepted)
{
	if(chainPtr != NULL)
		if(*chainPtr != NULL)
		{
			//printf("chain::accessed\n");
			//Recurses to free next link of the chain
			freeChain(&(*chainPtr) -> nextLinkPtr, Excepted);
			
			//printf("chain::recursed\n");
			if(*chainPtr != Excepted)
				//Ends up freeing this link
				freeLink(chainPtr);
			
			//printf("chain::processed\n");
		}
}

link* lastLink(link* chain)
{
	if(chain != NULL)
	{
		if(chain -> nextLinkPtr == NULL)
			//Last link
			return chain;
			
		else 
			//Recusion/Next link
			return lastLink(chain -> nextLinkPtr);
	}
	else return NULL;
}

link* deleteLink(link *chain, unsigned int Id)
{
	link *previousLinkPtr = NULL, *chainHeaderPtr;
	bool deleted = false;
	chainHeaderPtr = chain;
	
	while(chain != NULL && deleted == false)
	{
		//While chain's running and nothing's deleted
		if(getLinkId(chain) == Id)
		{
			//Must delete
			//Next link for who's deleted becomes it for the previous one
			if(previousLinkPtr != NULL)
				//If it's not the first to delete
				previousLinkPtr -> nextLinkPtr = chain -> nextLinkPtr;
			else
				//If it's the frst to delete, returned header becomes the second one
				chainHeaderPtr = chain -> nextLinkPtr;
			
			//freeLink(chain);
			deleted = true;
		}
		
		//To next link
		previousLinkPtr = chain;
		chain = chain -> nextLinkPtr;
	}
	
	return chainHeaderPtr;
}

link* insertLink(link* headLinkPtr, link* toInsertLinkPtr)
{
	if(headLinkPtr == NULL)
	{
		//Null list
		setLinkId(toInsertLinkPtr, 1);
		return toInsertLinkPtr;
	}
	else
	{
		//Getting last link
		link* lastLinkPtr = lastLink(headLinkPtr);

		//Putting new link
		lastLinkPtr -> nextLinkPtr = toInsertLinkPtr;
		
		//Identifying the link by Id (auto increment)
		setLinkId(toInsertLinkPtr, getLinkId(lastLinkPtr) + 1);
		return headLinkPtr;
	}
}

void setLinkId(link* linkPtr, unsigned int Id)
{
	linkPtr -> ID = Id;
	setElementId(linkPtr -> elementPtr, linkPtr -> structType, Id);
}

void setElementId(element* elementPtr, structId type, unsigned int Id)
{
	structId last = lastStructId;
	unsigned int elementId = nullId;
	
	switch(type)
	{
		//[CREATE_STRUCTURE]
		case _eventType:
			elementPtr -> eventType_.ID = Id;
			break;
			
		case _placeType:
			elementPtr -> placeType_.ID = Id;
			break;
			
		case _itemType:
			elementPtr -> itemType_.ID = Id;
			break;
			
		case _event:
			elementPtr -> event_.ID = Id;
			break;
			
		case _place:
			elementPtr -> place_.ID = Id;
			break;
			
		case _item:
			elementPtr -> item_.ID = Id;
			break;
			
		case _person:
			elementPtr -> person_.ID = Id;
			break;
			
		case _simulation:
			elementPtr -> simulation_.ID = Id;
			break;
			
		#ifdef DEBUG
		default:
			printf("<getElementId> Error: Unknown structure type (%d), should be in [%d;%d]\n", type, 0, last);
		#endif
	}
}

long int getElementId(element* elementPtr, structId type)
{
	structId last = lastStructId;
	unsigned int elementId = nullId;
	switch(type)
	{
		//[CREATE_STRUCTURE] [CREATE_GLOBAL_STRUCTURE]
		case _itemType:
			elementId = elementPtr -> itemType_.ID;
			break;
			
		case _placeType:
			elementId = elementPtr -> placeType_.ID;
			break;
			
		case _eventType:
			elementId = elementPtr -> eventType_.ID;
			break;
			
		case _simulation:
			elementId = elementPtr -> simulation_.ID;
			break;
			
		//[CREATE_GAME_STRUCTURE]
		case _event:
			elementId = elementPtr -> event_.ID;
			break;
			
		case _place:
			elementId = elementPtr -> place_.ID;
			break;
			
		case _item:
			elementId = elementPtr -> item_.ID;
			break;
			
		case _person:
			elementId = elementPtr -> person_.ID;
			break;
			
		#ifdef DEBUG
		default:
			printf("<getElementId> Error: Unknown structure type (%d), should be in [%d;%d]\n", type, 0, last);
		#endif
	}
	return elementId;
}

long int getLinkId(link* linkPtr)
{
	if (linkPtr != NULL)
	{
		if(linkPtr -> ID == nullId)
			linkPtr -> ID = getElementId(linkPtr -> elementPtr, linkPtr -> structType);
		return linkPtr -> ID;
	}
	else
	{
		#ifdef DEBUG
			printf("<getLinkPtr> Notice: NULL link ptr, returning 0\n");
		#endif

		return 0;
	}
}

link *getLinkById(structId _structId, long int Id, link *currentSimPtr)
{
	if(Id != nullId)
	{
		//Fetches for link
		savesFile *dataFile = setGameFiles(currentSimPtr);
		link 
			*chain = readChain(dataFile[_structId]),
			*ret = chain_search(chain, (unsigned int)Id);
		
		return ret;
	}
	else return NULL;
}

link *higherId(link *chain)
{
	if (chain != NULL)
	{
		link* remainingChainHiestId = higherId(chain->nextLinkPtr);

		if (remainingChainHiestId == NULL)
			return chain;
		else
			return getLinkId(remainingChainHiestId) > getLinkId(chain)
				? remainingChainHiestId
				: chain;
	}
	else return NULL;
}

link *chain_search(link* chain, unsigned int ID)
{
	while(chain != NULL)
	{
		if(getLinkId(chain) == (long int)ID)
			//If found
			return chain;
			
		//Next
		chain = chain -> nextLinkPtr;
	}
	
	//Not found
	return NULL;
}

long int grabId(structId retStructId, link *currentSimPtr, bool allowNullId)
{
	long int joinId = nullId;
	link
		*displayedChain = NULL,
		*ret = NULL;
	
	//If joining needed on game files
	savesFile *dataFile = NULL;
	if(currentSimPtr != NULL)
		dataFile = setGameFiles(currentSimPtr);
	
	//Get available save
	dataFile = dataFile == NULL
		? globalFile
		: dataFile;
	
	//Display choices
	displayedChain = readChain(dataFile[retStructId]);
	
	//HMI
	printf("Select among one of those:\n");
	displayChain(displayedChain, currentSimPtr);
	scanf("%ld", &joinId);
	getchar();
	
	//End
	freeChain(&displayedChain, NULL);
	
	if(joinId != nullId || allowNullId)
		return joinId;
	else return grabId(retStructId, currentSimPtr, allowNullId);
}

link *getJoinedLink(link *mainLink, structId selectedStruct, link *currentSimPtr, unsigned short int joinIndex)
{
	long int joinId = nullId;
	link *ret = NULL;
	
	//If joining needed on game files
	savesFile *dataFile = NULL;
	if(currentSimPtr != NULL)
		dataFile = setGameFiles(currentSimPtr);
	
	element *elementPtr = mainLink -> elementPtr;
	
	//Getting the Id from the current element and the targetted element
	if(mainLink != NULL)
	{
		switch(mainLink -> structType)
		{
			//[CREATE_STRUCTURE] [EDIT_STRUCTURE] [JOIN_STRUCTURE]
			case _eventType:
				switch(selectedStruct)
				{
					case _itemType:
						joinId = elementPtr -> eventType_.requiredItemTypeId;
						break;
						
					case _placeType:
						joinId = elementPtr -> eventType_.requiredPlaceTypeId;
						break;
				}
				break;
				
			case _event:
				switch(selectedStruct)
				{
					case _itemType:
						joinId = elementPtr -> event_.itemId;
						break;
						
					case _placeType:
						joinId = elementPtr -> event_.placeId;
						break;
					
					case _eventType:
						joinId = elementPtr -> event_.eventTypeId;
						break;
					
					case _person:
						if(joinIndex <= 1)
							joinId = elementPtr -> event_.transmitterId;
						else
							joinId = elementPtr -> event_.receiverId;
						break;
				}
				break;
				
			case _place:
				switch(selectedStruct)
				{
					case _placeType:
						joinId = elementPtr -> place_.placeTypeId;
						break;
				}
				break;
				
			case _item:
				switch(selectedStruct)
				{
					case _itemType:
						joinId = elementPtr -> item_.itemTypeId;
						break;
						
					case _person:
						joinId = elementPtr -> item_.proprietaryId;
						break;
						
					case _place:
						joinId = elementPtr -> item_.locationPlaceId;
						break;
				}
				break;
				
			case _person:
				switch(selectedStruct)
				{
					case _place:
						joinId = elementPtr -> person_.houseId;
						break;
				}
				break;
				
			default:
				printf("<getJoinedLink> Warning: Un-handled structure type: %u\n", mainLink -> structType);
		}
	}
	
	//Operating
	if(joinId != nullId)
	{
		//Choosing an file environment to join in
		dataFile = dataFile == NULL
			? globalFile
			: dataFile;
		
		//Making a 'sql like' join
		link 
			*joiningChain = readChain(dataFile[selectedStruct]),
			*joinedLinkPtr = chain_search(joiningChain, joinId);
		
		if(joinedLinkPtr != NULL)
			ret = joinedLinkPtr;
		else
			printf("Warning: None of %s has ID = %d\n", dataFile[selectedStruct].name, joinId);
		
		freeChain(&joiningChain, joinedLinkPtr);
	}
	return ret;
}



char **initParticularityLabels()
{
	personParticularity last = lastPersonParticularityId, cursor = 0;
	char **particularityLabels = safeMalloc(sizeof(char*) * last, "initParticularityLabels wordsList");
	
	int i;
	for(i = 0; i < last; i++)
		particularityLabels[i] = safeMalloc(sizeof(char) * wordLength, "initParticularityLabels word");
	
	
	//[CREATE_PERSON_PARTICULARITY]
	
	cursor = gender;
	strcpy(particularityLabels[cursor], "man");
	
	cursor = sporty;
	strcpy(particularityLabels[cursor], "sporty");
	
	cursor = smoker;
	strcpy(particularityLabels[cursor], "smoker");
	
	cursor = remoteWorker;
	strcpy(particularityLabels[cursor], "remoteWorker");
	
	return particularityLabels;
}


long long int grabInt(char *instructions)
{
	int ret = 0;
	
	if(instructions != NULL)
		printf(instructions);
		
	scanf("%d", &ret);
	getchar();
	
	return ret;
}

float grabFloat(char *instructions)
{
	float ret = 0;
	
	if(instructions != NULL)
		printf(instructions);
		
	scanf("%f", &ret);
	getchar();
	
	return ret;
}

stats grabStats(char *instructions)
{
	stats recipient;
	memset(&recipient, 0, sizeof(recipient));
	
	if(instructions != NULL)
		printf(instructions);
	
	//[CREATE_STATS]
	recipient.health = grabInt("health: ");
	recipient.hunger = grabInt("hunger: ");
	recipient.hygiene = grabInt("hygiene: ");
	recipient.mentalHealth = grabInt("mentalHealth: ");
	recipient.stamina = grabInt("stamina: ");
	recipient.karma = grabInt("karma: ");
	recipient.money = grabFloat("money: ");

	printf("CoronaVirus (y/else): ");
	recipient.coronaVirus = getch() == 'y'
		? true
		: false;
	
	return recipient;
}

link grabLink(structId structType, link *currentSimPtr)
{
	link 
		link_,
		*displayedChain = NULL,
		*chosenLinkPtr = NULL,
		*joinedLinkPtr = NULL,
		*joinedLinkPtr2 = NULL;
	memset(&link_, 0, sizeof(link));
	link_.structType = structType;
	link_.elementPtr = newElement("grabLink");
	
	element *recipient = link_.elementPtr;
	memset(recipient, 0, sizeof(element));
	structId lastStructId_ = lastStructId;
	
	long int idChoice;
	
	//Only for eventTypes
	personParticularity lastPersonParticularityId_ = lastPersonParticularityId;
	char 
		choice[2] = "\0",
		*instructions = safeMalloc(sizeof(char) * 60, "grabLink/instruction"),
		**particularityLabels = initParticularityLabels();
	personParticularity cursor = 0;
	
	switch(structType)
	{
		//[CREATE_STRUCTURE] [EDIT_STRUCTURE]
		case _person:
			printf("[person]\n\tLast name: ");
			scanf("%s", recipient -> person_.lastName);
			
			printf("\tFirst name: ");
			scanf("%s", recipient -> person_.firstName);
			
			recipient -> person_.stats_ = grabStats("person's stats\n");
			
			recipient -> person_.houseId = nullId;
			break;
			
		case _event:
			//On part du principe que le joueur à un Id de 1
			recipient -> event_.transmitterId = 1;
			
			//eventType
			printf("\n[event]Event type: ");
			recipient -> event_.eventTypeId = grabId(_eventType, currentSimPtr, false);
			
			//person
			printf("\n\tReceiver: ");
			recipient -> event_.receiverId = grabId(_person, currentSimPtr, false);
			
			//#TODO wtf I'm gettin tired joinedLinkPtr = getJoinedLink(getLinkById(_item, ))
			//Does a joined structure (eventType) has a non-nullId value for join to itemType ? (means if I need an item of this event)
			
			//Fetch an item ptr from event
			joinedLinkPtr = getLinkById(_eventType, recipient -> event_.eventTypeId, currentSimPtr);
			if(joinedLinkPtr -> elementPtr -> eventType_.requiredItemTypeId != nullId)
			{
				joinedLinkPtr2 = getLinkById(_itemType, joinedLinkPtr -> elementPtr -> eventType_.requiredItemTypeId, currentSimPtr);
				recipient -> event_.itemId = grabId(_item, currentSimPtr, false);
			}
			
			//Fetch a place ptr from event
			joinedLinkPtr = getLinkById(_eventType, recipient -> event_.eventTypeId, currentSimPtr);
			if(joinedLinkPtr -> elementPtr -> eventType_.requiredPlaceTypeId != nullId)
			{
				joinedLinkPtr2 = getLinkById(_placeType, joinedLinkPtr -> elementPtr -> eventType_.requiredPlaceTypeId, currentSimPtr);
				recipient -> event_.placeId = grabId(_place, currentSimPtr, false);
			}

			recipient -> event_.eventTime = (unsigned long int)grabInt("Happening time: ");
			
			break;
		
		case _eventType:
			printf("[event type]\n\tName: ");
			scanf("%s", recipient -> eventType_.name);
			
			printf("\tDuration: ");
			scanf("%u", &recipient -> eventType_.duration_s);
			
			//Item consumed on eventing
			idChoice = nullId;
			printf("Require item type ? (y/any)\n");
			scanf("%s", &choice);
			
			//Ask to the user a choice to make for an itemType's Id
			if(!strcmp(choice, "y"))
			{
				//Empty choice
				strcpy(choice, "\0");
				
				//Getting choices to display
				displayedChain = readChain(globalFile[_itemType]);
				
				//Choosing a link, getting its Id
				chosenLinkPtr = selectLink(displayedChain);
				
				if(chosenLinkPtr != NULL)
					idChoice = chosenLinkPtr -> ID;
				
				//Getting itemType consumption
				printf(
					"%s consumption (?/%u) ",
					chosenLinkPtr -> elementPtr -> itemType_.name,
					chosenLinkPtr -> elementPtr -> itemType_.usesCount
				);
				
				scanf("%u", &recipient -> eventType_.itemTypeConsumption);
				getchar();
				
				//Freeing this chain done for pure display
				freeChain(&displayedChain, NULL);
			}
			
			//Binding the chosen itemType to the eventType
			recipient -> eventType_.requiredItemTypeId = idChoice;
			
			//Item consumed on eventing
			idChoice = nullId;
			printf("Require place type ? (y/any)\n");
			scanf("%s", &choice);
			
			//Ask to the user a choice to make for an itemType's Id
			if(!strcmp(choice, "y"))
			{
				//Empty choice
				strcpy(choice, "\0");
				
				//Getting choices to display
				displayedChain = readChain(globalFile[_placeType]);
				
				//Choosing a link, getting its Id
				chosenLinkPtr = selectLink(displayedChain);
				
				if(chosenLinkPtr != NULL)
					idChoice = chosenLinkPtr -> ID;
				
				//Freeing this chain done for pure display
				freeChain(&displayedChain, NULL);
			}
			
			//Binding the chosen placeType to the eventType
			recipient -> eventType_.requiredPlaceTypeId = idChoice;
			
			//Success case consequences
			recipient -> eventType_.onSuccess = grabStats("\tStats added to receiver's on success:\n");
			
			//Failure case consequences
			if(recipient -> eventType_.requiredItemTypeId != nullId || recipient -> eventType_.requiredPlaceTypeId != nullId)
				recipient -> eventType_.onFailure = grabStats("\tStats added to receiver's on failure:\n");
			
			printf("Make option selectable on failure ? (y/any)\n");
			recipient -> eventType_.selectableOnFailure = getche() == 'y';
			
			//Particular cases consequences
			printf("Create particular cases ? (y/any)\n");
			scanf("%s", &choice);
			
			if(!strcmp(choice, "y"))
			{
				//Empty choice
				strcpy(choice, "\0");
				for(cursor = 0; cursor < lastPersonParticularityId_; cursor++)
				{
					//Particular case consequences
					printf("\tCreate a particular case for %s ? (y/any)\n", particularityLabels[cursor]);
					scanf("%s", &choice);
					
					if(!strcmp(choice, "y"))
					{
						//Particularities for each ones
						strcpy(instructions, "\tStats added to user's in addition for ");
						strcat(instructions, particularityLabels[cursor]);
						strcat(instructions, "\n");
						
						recipient -> eventType_.consequenceFor[cursor] = grabStats(instructions);
					}
					else
						memset(&recipient -> eventType_.consequenceFor[cursor], 0, sizeof(stats));
				}
			}
			
			//Empty choice
			strcpy(choice, "\0");
			break;
			
		case _placeType:
			printf("[place type]\n\tName: ");
			scanf("%s", recipient -> placeType_.name);
			printf("\tCan be a living place (y/else):");
			recipient -> placeType_.livingPlace = 'y' == getche();
			printf("\n\tCan be a market place (y/else):");
			recipient -> placeType_.marketPlace = 'y' == getche();
			printf("\n\tCan be a care place (y/else):");
			recipient -> placeType_.carePlace = 'y' == getche();
			printf("\n\n");
			break;
			
		case _itemType:
			printf("[item type]\n\tName: ");
			scanf("%s", recipient -> itemType_.name);
			
			printf("\tPrice: ");
			scanf("%u", &recipient -> itemType_.price);
			
			printf("\tUses count: ");
			scanf("%u", &recipient -> itemType_.usesCount);
			break;
			
		case _simulation:
			printf("[simulation]\nSimuled time: ");
			scanf("%u", &recipient -> simulation_.simuledTime);
			break;
			
		#ifdef DEBUG
		default:
			printf("<grabLink> Error: Unknown structure type (%d), should be in [%d;%d]\n", structType, 0, lastStructId_);
		#endif
	}
	
	//For eventTypes only
	free(instructions);
	freeMatress((void**)particularityLabels, lastPersonParticularityId_);
	
	return link_;
}

link* grabChain(structId structType, link *currentSimPtr)
{
	int keepGrabbing = 1;
	link
		*chain = safeMalloc(sizeof(link), "grabChain init"), 
		*linkPtr = chain;
	
	while(keepGrabbing)
	{
		//Operate
		*linkPtr = grabLink(structType, currentSimPtr);
		
		//Restart ?
		printf("\nKeep grabbing ? y/any\n");
		
		keepGrabbing = getche() == 'y';
		
		system("cls");
		
		if(keepGrabbing)
		{
			linkPtr -> nextLinkPtr = safeMalloc(sizeof(link), "grabChain next");
			linkPtr = linkPtr -> nextLinkPtr;
		}
	}
	
	return chain;
}

link *selectLink(link *chain)
{
	link *chosenLinkPtr = NULL;
	int idChoice = nullId;
	
	if(chain != NULL)
	{
		//User query + choices display
		printf("Please select among %ss: (Enter %d to escape)\n", globalFile[chain -> structType].name, nullId);
		displayChain(chain, NULL);
		do
		{
			//Getting choice's link ptr from Id
			scanf("%d", &idChoice);
			getchar();
			
			chosenLinkPtr = chain_search(chain, (unsigned int)idChoice);
		}while(chosenLinkPtr == NULL || idChoice == nullId);
	}
	else 
	{
		printf("<selectLink> Notice: Empty chain given to choose in, returning NULL\n");
	}
	
	return chosenLinkPtr;
}

void displayLocation(location toDisplay, char *tagging)
{
	bool mustFreeTagging = false;
	if(tagging == NULL)
	{
		strcpy(tagging, "location");
		mustFreeTagging = true;
	}
	printf("[%s]\n\tx: %d\n\ty: %d\n", tagging, toDisplay.x, toDisplay.y);
	
	
	if(mustFreeTagging)
		free(tagging);
}

void displayStats(stats toDisplay, char *tagging)
{
	bool mustFreeTagging = false;
	if(tagging == NULL)
	{
		strcpy(tagging, "stats");
		mustFreeTagging = true;
	}
	
	//[CREATE_STATS]
	printf
	(
		"[%s]\n\tHealth: %d\n\tHunger: %d\n\tHygiene: %d\n\tmentalHealth: %d\n\tStamina: %d\n\tmoney: %.2f\n\tKarma: %d%s\n",
		tagging,
		toDisplay.health,
		toDisplay.hunger,
		toDisplay.hygiene,
		toDisplay.mentalHealth,
		toDisplay.stamina,
		toDisplay.money,
		toDisplay.karma,
		toDisplay.coronaVirus
			? "\n\tCoronavirus"
			: ""
	);
	
	if(mustFreeTagging)
		free(tagging);
}

void displayLink(link toDisplay, link *currentSimPtr)
{
	if(toDisplay.elementPtr != NULL)
	{
		//Ease writting
		element *elementPtr = toDisplay.elementPtr;
		personParticularity last = lastPersonParticularityId;
		
		//If joining needed
		link 
			*joinedLinkPtr = NULL,
			*joinedLinkPtr2 = NULL;

		unsigned int time = 0;
		
		//[PERSON_PARTICULARITY]
		char
			genderToString[6] = "\0",
			smokerString[4] = "\0",
			remoteWorkingString[4] = "\0",
			weekDay[10] = "\0";
		
		//What to display ?
		switch(toDisplay.structType)
		{
			//[CREATE_STRUCTURE] [EDIT_STRUCTURE]
			case _event:
				printf
				(
					"[event]\n\tID: %u",
					elementPtr -> event_.ID
				);
				
				//[JOIN] event-eventType
				joinedLinkPtr = getJoinedLink(&toDisplay, _eventType, currentSimPtr, 1);
				if(joinedLinkPtr != NULL)
				{
					printf(
						"\n\tEvent type: %s",
						joinedLinkPtr -> elementPtr -> eventType_.name
					);
				}

				time = elementPtr->event_.eventTime;
				switch(secondsTo("day", time))
				{
					case 0:
						strcpy(weekDay, "monday");
						break;

					case 1:
						strcpy(weekDay, "tuesday");
						break;

					case 2:
						strcpy(weekDay, "wednesday");
						break;

					case 3:
						strcpy(weekDay, "thursday");
						break;

					case 4:
						strcpy(weekDay, "friday");
						break;

					case 5:
						strcpy(weekDay, "saturday");
						break;

					case 6:
						strcpy(weekDay, "sunday");
						break;

					default:
						strcpy(weekDay, "unknown");
				}

				printf(
					"\n\tHappens on: Week %u, %s, at %u:%u:%u",
					secondsTo("week", time),
					weekDay,
					secondsTo("hour", time),
					secondsTo("minute", time),
					secondsTo("second", time)
				);
				
				//[JOIN] event-person
				joinedLinkPtr = getJoinedLink(&toDisplay, _person, currentSimPtr, 1);
				if(joinedLinkPtr != NULL)
				{
					printf(
						"\n\tTransmitter: %s %s",
						joinedLinkPtr -> elementPtr -> person_.firstName,
						joinedLinkPtr -> elementPtr -> person_.lastName
					);
				}
				
				//[JOIN] event-person
				joinedLinkPtr = getJoinedLink(&toDisplay, _person, currentSimPtr, 2);
				if(joinedLinkPtr != NULL)
				{
					printf(
						"\n\tReceiver: %s %s\n\n",
						joinedLinkPtr -> elementPtr -> person_.firstName,
						joinedLinkPtr -> elementPtr -> person_.lastName
					);
				}
				
				//[JOIN] event-item
				joinedLinkPtr = getJoinedLink(&toDisplay, _item, currentSimPtr, 1);
				if(joinedLinkPtr != NULL)
				{
					//[JOIN] event-item-itemType
					joinedLinkPtr2 = getJoinedLink(joinedLinkPtr, _itemType, currentSimPtr, 1);
					printf(
						"\n\tItem: %s (%u uses out of %u)",
						joinedLinkPtr2 -> elementPtr -> itemType_.name,
						joinedLinkPtr -> elementPtr -> item_.usedCount,
						joinedLinkPtr2 -> elementPtr -> itemType_.usesCount
					);
				}
				
				//[JOIN] event-place
				joinedLinkPtr = getJoinedLink(&toDisplay, _place, currentSimPtr, 1);
				if(joinedLinkPtr != NULL)
				{
					//[JOIN] event-place-placeType
					joinedLinkPtr2 = getJoinedLink(joinedLinkPtr, _placeType, currentSimPtr, 1);
					printf(
						"\n\tLocation: %s (%s)",
						joinedLinkPtr -> elementPtr -> place_.name,
						joinedLinkPtr2 -> elementPtr -> placeType_.name
					);
					displayLocation(joinedLinkPtr -> elementPtr -> place_.loc, "place's location");
				}
				break;
				
			case _eventType:
				printf
				(
					"[event type]\n\tID: %u\n\tName: %s\n\tDuration: %u days, %u hours, %u minutes and %u seconds\n",
					elementPtr -> eventType_.ID,
					elementPtr -> eventType_.name,
					secondsTo("days", elementPtr -> eventType_.duration_s),
					secondsTo("hours", elementPtr -> eventType_.duration_s),
					secondsTo("minutes", elementPtr -> eventType_.duration_s),
					secondsTo("seconds", elementPtr -> eventType_.duration_s)
				);
				displayStats(elementPtr -> eventType_.onSuccess, "event type success consequence");
				displayStats(elementPtr -> eventType_.onFailure, "event type failure consequence");
				
				
				char **particularityLabels = initParticularityLabels();
				personParticularity cursor = 0;
				
				//Prepare an empty stats variable to compare with
				stats emptyStatsBuffer;
				memset(&emptyStatsBuffer, 0, sizeof(stats));
				
				for(cursor = 0; cursor < last; cursor++)
					if(memcmp(&elementPtr -> eventType_.consequenceFor[cursor], &emptyStatsBuffer, sizeof(stats)))
					{
						//Display non-empty particulary case stats
						char tag[50];
						strcpy(tag, "event type specific consequence for ");
						strcat(tag, particularityLabels[cursor]);
						displayStats(elementPtr -> eventType_.consequenceFor[cursor], tag);
					}
				
				//[JOIN] itemType
				joinedLinkPtr = getJoinedLink(&toDisplay, _itemType, currentSimPtr, 1);
				if(joinedLinkPtr != NULL)
					printf(
						"\t-> Used item type: %s, consumes %u times (%u in total)\n",
						joinedLinkPtr -> elementPtr -> itemType_.name,
						elementPtr -> eventType_.itemTypeConsumption,
						joinedLinkPtr -> elementPtr -> itemType_.usesCount
					);
				
				//[JOIN] placeType
				joinedLinkPtr = getJoinedLink(&toDisplay, _placeType, currentSimPtr, 1);
				if(joinedLinkPtr != NULL)
					printf(
						"\t-> Necessary place type: %s\n",
						joinedLinkPtr -> elementPtr -> placeType_.name
					);
				
				printf(
					"\t-%selectable on failure",
					toDisplay.elementPtr -> eventType_.selectableOnFailure
						? "S"
						: "Not s"
				);
				
				printf("\n\n");
				break;
				
			case _place:
				printf
				(
					"[place]\n\tID: %u\n\tName: %s",
					elementPtr -> place_.ID,
					elementPtr -> place_.name
				);
				
				//[JOIN] placeType
				joinedLinkPtr = getJoinedLink(&toDisplay, _placeType, currentSimPtr, 1);
				if(joinedLinkPtr != NULL)
				{
					printf(
						"\n\tType: %s",
						joinedLinkPtr -> elementPtr -> placeType_.name
					);
				}
				
				displayLocation(elementPtr -> place_.loc, "place location");
				printf("\n\n");
				break;
				
			case _placeType:
				printf
				(
					"[place type]\n\tID: %u\n\tName: %s\n",
					elementPtr -> placeType_.ID,
					elementPtr -> placeType_.name
				);
				if(elementPtr -> placeType_.livingPlace)
					printf("\tLiving place\n");
				if(elementPtr -> placeType_.marketPlace)
					printf("\tMarket place\n");
				if(elementPtr -> placeType_.carePlace)
					printf("\tCare place\n");
				break;
				
			case _item:
				if(currentSimPtr != NULL)
				{
					printf
					(
						"[item]\n\tID: %u\n",
						elementPtr -> item_.ID
					);
					
					//[JOIN] itemType
					joinedLinkPtr = getJoinedLink(&toDisplay, _itemType, currentSimPtr, 1);
					if(joinedLinkPtr != NULL)
						printf
						(
							"\tType: %s\n",
							joinedLinkPtr -> elementPtr -> itemType_.name
						);
					
					//[JOIN] person
					joinedLinkPtr = getJoinedLink(&toDisplay, _person, currentSimPtr, 1);
					if(joinedLinkPtr != NULL)
						printf
						(
							"\tProprietary: %s %s\n",
							joinedLinkPtr -> elementPtr -> person_.firstName,
							joinedLinkPtr -> elementPtr -> person_.lastName
						);
					
					//[JOIN] place
					joinedLinkPtr = getJoinedLink(&toDisplay, _place, currentSimPtr, 1);
					if(joinedLinkPtr != NULL)
					{
						printf
						(
							"\tLocation: %s\n",
							joinedLinkPtr -> elementPtr -> place_.name
						);
						displayLocation(joinedLinkPtr -> elementPtr -> place_.loc, "location ");
					}
					else
						displayLocation(elementPtr -> item_.loc, "location ");
					
					printf
					(
						"tTimes used: %u\n\n",
						elementPtr -> item_.usedCount
					);
				}
				break;
				
			case _itemType:
				printf
				(
					"[item type]\n\tID: %u\n\tName: %s\n\tPrice: %u\n\tUses count: %u\n\n",
					elementPtr -> itemType_.ID,
					elementPtr -> itemType_.name,
					elementPtr -> itemType_.price,
					elementPtr -> itemType_.usesCount
				);
				break;
				
			case _simulation:
				printf
				(
					"[simulation]\n\tID: %u\n\tSimuled time: %u\n\n",
					elementPtr -> simulation_.ID,
					elementPtr -> simulation_.simuledTime
				);
				break;
				
			case _person:
				if(currentSimPtr != NULL)
				{
					//particularities
					if(elementPtr -> person_.gender == MAN)
						strcpy(genderToString, "man");
					else if(elementPtr -> person_.gender == WOMAN)
						strcpy(genderToString, "woman");
					else
						strcpy(genderToString, "other");
					
					if(elementPtr -> person_.smoker)
						strcpy(smokerString, "yes");
					else strcpy(smokerString, "no");
					
					if(elementPtr -> person_.remoteWorking)
						strcpy(remoteWorkingString, "yes");
					else strcpy(remoteWorkingString, "no");
					
					//[CREATE_PERSON_PARTICULARITY]
					printf
					(
						"[person]\n\tID: %d\n\tFirst Name: %s\n\tLast Name: %s\n",
						elementPtr -> person_.ID,
						elementPtr -> person_.firstName,
						elementPtr -> person_.lastName
					);
					
					//[JOIN] place (house)
					joinedLinkPtr = getJoinedLink(&toDisplay, _place, currentSimPtr, 1);
					if(joinedLinkPtr != NULL)
					{
						//[JOIN] placeType (house type (= house ?))
						joinedLinkPtr2 = getJoinedLink(joinedLinkPtr, _placeType, currentSimPtr, 1);
						printf(
							"\n\tLiving: %s (%s)",
							joinedLinkPtr -> elementPtr -> place_.name,
							joinedLinkPtr2 -> elementPtr -> placeType_.name
						);
					}
					
					printf(
						"\n\tSportiness level: %d/2\n\tGender: %s\n\tSmoker: %s\n\tRemote worker: %s\n\tSalary: %.2f\n",
						elementPtr -> person_.sportiness,
						genderToString,
						smokerString,
						remoteWorkingString,
						elementPtr -> person_.salary
					);
					
					displayStats(elementPtr -> person_.stats_, "person stats");
					printf("\n\n");
				}
				break;
				
			#ifdef DEBUG
			default:
				printf("<displayLink> Error: invalid structId: %d\n", toDisplay.structType);
			#endif
		}
	}
}

void displayChain(link* toDisplayPtr, link *currentSimPtr)
{
	if(toDisplayPtr != NULL)
	{
		//Process
		displayLink(*toDisplayPtr, currentSimPtr);
		
		//Recursion
		displayChain(toDisplayPtr -> nextLinkPtr, currentSimPtr);
	}
}
