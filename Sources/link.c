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
	//Index of last structure
	structId last = lastStructId;
	
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
	
	cursor = man;
	strcpy(particularityLabels[cursor], "man");
	
	cursor = sporty;
	strcpy(particularityLabels[cursor], "sporty");
	
	cursor = smoker;
	strcpy(particularityLabels[cursor], "smoker");
	
	cursor = remoteWorker;
	strcpy(particularityLabels[cursor], "remoteWorker");
	
	return particularityLabels;
}

void displayStats(stats toDisplay, char* tagging)
{
	bool mustFreeTagging = false;
	if(tagging == NULL)
	{
		strcpy(tagging, "stats");
		mustFreeTagging = true;
	}
	
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
					"[eventType]\n\tID: %d\n\tName: %s\n",
					elementPtr -> eventType_.ID,
					elementPtr -> eventType_.name
				);
				displayStats(elementPtr -> eventType_.consequence, "eventType global consequence");
				
				//[CREATE_PERSON_PARTICULARITY]
				char **particularityLabels = initParticularityLabels();
				personParticularity cursor = 0;
				
				for(cursor = 0; cursor < last; cursor++)
				{
					char tag[50];
					strcpy(tag, "eventType specific consequence for ");
					strcat(tag, particularityLabels[cursor]);
					displayStats(elementPtr -> eventType_.consequenceFor[cursor], tag);
				}
				printf("\n\n");
				break;
				
			case _building:
				break;
				
			case _buildingType:
				break;
				
			case _item:
				break;
				
			case _itemType:
				break;
				
			case _simulation:
				break;
				
			case _person:
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
