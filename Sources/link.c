#define nullId -1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../Headers/structures.h"
#include "../Headers/link.h"

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

void freeLink(link* linkPtr)
{
	if(linkPtr != NULL)
	{
		if(linkPtr -> elementPtr)
		{
			//Frees element ifexists
			memset(linkPtr -> elementPtr, 0, sizeof(element));
			free(linkPtr -> elementPtr);
		}
		
		//Frees link if exists
		memset(linkPtr, 0, sizeof(link));
		free(linkPtr);
	}
}

void freeChain(link* chain)
{
	if(chain != NULL)
	{
		//Recurses to free next link of the chain
		freeChain(chain -> nextLinkPtr);
		
		//Ends up freeing this link
		freeLink(chain);
	}
}

link* lastLink(link* currentLinkPtr)
{
	if(currentLinkPtr != NULL)
	{
		if(currentLinkPtr -> nextLinkPtr == NULL)
			//Last link
			return currentLinkPtr;
			
		else 
			//Recusion/Next link
			return lastLink(currentLinkPtr -> nextLinkPtr);
	}
	else return NULL;
}

link* insertLink(link* headLinkPtr, link* toInsertLinkPtr)
{
	if(headLinkPtr == NULL)
	{
		//Null list
		toInsertLinkPtr -> nextLinkPtr = NULL;
		return toInsertLinkPtr;
	}
	else
	{
		//Getting last link
		link* lastLinkPtr = lastLink(headLinkPtr);

		//Putting new link
		lastLinkPtr -> nextLinkPtr = toInsertLinkPtr;
		return headLinkPtr;
	}
}

long int getElementId(element* elementPtr, structId type)
{
	structId last = lastStructId;
	unsigned int elementId = - 1;
	switch(type)
	{
		//[CREATE_STRUCTURE]
		case _event:
			elementId = elementPtr -> event_.ID;
			break;
			
		case _eventType:
			elementId = elementPtr -> eventType_.ID;
			break;
			
		case _building:
			elementId = elementPtr -> building_.ID;
			break;
			
		case _buildingType:
			elementId = elementPtr -> buildingType_.ID;
			break;
			
		case _item:
			elementId = elementPtr -> item_.ID;
			break;
			
		case _itemType:
			elementId = elementPtr -> itemType_.ID;
			break;
			
		case _person:
			elementId = elementPtr -> person_.ID;
			break;
			
		case _simulation:
			elementId = elementPtr -> simulation_.ID;
			break;
			
		default:
			printf("<newElement> Error: Unknown structure type (%d), should be in [%d;%d]\n", type, 0, last);
	}
	return elementId;
}

long int getLinkId(link* linkPtr)
{
	if(linkPtr -> ID == nullId)
		linkPtr -> ID = getElementId(linkPtr -> elementPtr, linkPtr -> structType);
	return linkPtr -> ID;
}


link* chain_search(link* linkPtr, unsigned int ID)
{
	while(linkPtr != NULL)
	{
		if(getLinkId(linkPtr) == (long int)ID)
			//If found
			return linkPtr;
			
		//Next
		linkPtr = linkPtr -> nextLinkPtr;
	}
	
	//Not found
	return NULL;
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



link grabLink(structId structType)
{
	switch(structType)
	{
		//[CREATE_STRUCTURE]
		
	}
}

link* grabChain(structId structType)
{
	int keepGrabbing = 1;
	while(keepGrabbing)
	{
		//Operate
		grabLink(structType);
		
		//Restart ?
		printf("\nKeep grabbing ? 1/0\n");
		
		scanf("%d", &keepGrabbing);
		getchar();
		
		system("cls");
	}
	
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
		"[%s]\n\tHealth: %d\n\tHunger: %d\n\tHygiene: %d\n\tmentalHealth: %d\n\tStamina: %d\n",
		tagging,
		toDisplay.health,
		toDisplay.hunger,
		toDisplay.hygiene,
		toDisplay.mentalHealth,
		toDisplay.stamina
	);
	
	if(mustFreeTagging)
		free(tagging);
}

void displayLink(link toDisplay)
{
	if(toDisplay.elementPtr != NULL)
	{
		//Ease writting
		element *elementPtr = toDisplay.elementPtr;
		personParticularity last = lastPersonParticularityId;
		
		char manWoman[6] = "\0", smokerString[4] = "\0", remoteWorkingString[4] = "\0";
		
		//What to display ?
		switch(toDisplay.structType)
		{
			//[CREATE_STRUCTURE]
			case _event:
				printf
				(
					"[event]\n\tID: %d\n\tType ID: %d\n\treveiver ID: %d\n\tTransmitter ID: %d\n\n",
					elementPtr -> event_.ID,
					elementPtr -> event_.eventTypeId,
					elementPtr -> event_.receiverId,
					elementPtr -> event_.transmitterId
				);
				break;
				
			case _eventType:
				printf
				(
					"[event type]\n\tID: %d\n\tName: %s\n",
					elementPtr -> eventType_.ID,
					elementPtr -> eventType_.name
				);
				displayStats(elementPtr -> eventType_.consequence, "event type global consequence");
				
				
				char **particularityLabels = initParticularityLabels();
				personParticularity cursor = 0;
				
				for(cursor = 0; cursor < last; cursor++)
				{
					char tag[50];
					strcpy(tag, "event type specific consequence for ");
					strcat(tag, particularityLabels[cursor]);
					displayStats(elementPtr -> eventType_.consequenceFor[cursor], tag);
				}
				printf("\n\n");
				break;
				
			case _building:
				printf
				(
					"[building]\n\tID: %d\n\tName: %s\n\tType ID: %d\n",
					elementPtr -> building_.ID,
					elementPtr -> building_.name,
					elementPtr -> building_.typeId
				);
				displayLocation(elementPtr -> building_.loc, "building location");
				printf("\n\n");
				break;
				
			case _buildingType:
				printf
				(
					"[building type]\n\tID: %d\n\tName: %s\n\n",
					elementPtr -> buildingType_.ID,
					elementPtr -> buildingType_.name
				);
				break;
				
			case _item:
				printf
				(
					"[item]\n\tID: %d\n\tProprietary ID: %d\n\tName: %s\n\n",
					elementPtr -> item_.ID,
					elementPtr -> item_.proprietaryId,
					elementPtr -> item_.name
				);
				break;
				
			case _itemType:
				printf
				(
					"[item type]\n\tID: %d\n\tName: %s\n\n",
					elementPtr -> itemType_.ID,
					elementPtr -> itemType_.name
				);
				break;
				
			case _simulation:
				printf
				(
					"[simulation]\n\tID: %d\n\tSimuled time: %\n\n",
					elementPtr -> simulation_.ID
				);
				break;
				
			case _person:
				if(elementPtr -> person_.gender = MAN)
					strcpy(manWoman, "man");
				else strcpy(manWoman, "woman");
				
				if(elementPtr -> person_.smoker)
					strcpy(smokerString, "yes");
				else strcpy(smokerString, "no");
				
				if(elementPtr -> person_.remoteWorking)
					strcpy(remoteWorkingString, "yes");
				else strcpy(remoteWorkingString, "no");
				
				//[CREATE_PERSON_PARTICULARITY]
				printf
				(
					"[person]\n\tID: %d\n\tFirst Name: %s\n\tLast Name: %s\n\tHouse ID: %d\n\tSportiness level: %d/2\n\tGender: %s\n\tSmoker: %s\n\tRemote worker: %s\n\tSalary: %.2f\n\tMoney: %.2f\n",
					elementPtr -> person_.ID,
					elementPtr -> person_.firstName,
					elementPtr -> person_.lastName,
					elementPtr -> person_.houseId,
					elementPtr -> person_.sportiness,
					manWoman,
					smokerString,
					remoteWorkingString,
					elementPtr -> person_.salary,
					elementPtr -> person_.money
				);
				
				displayStats(elementPtr -> person_.stats_, "person stats");
				printf("\n\n");
				break;
				
			default:
				printf("<displayLink> Error: invalid data\n");
		}
	}
}

void displayChain(link* toDisplayPtr)
{
	if(toDisplayPtr != NULL)
	{
		//Process
		displayLink(*toDisplayPtr);
		
		//Recursion
		displayChain(toDisplayPtr -> nextLinkPtr);
	}
}
