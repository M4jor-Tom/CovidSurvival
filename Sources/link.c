#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../Headers/structures.h"
#include "../Headers/link.h"

link* newLink(char* errorMessage, structId type, bool createElement)
{
	link* ret = (link*)safeMalloc(sizeof(link), errorMessage);
	ret -> elementPtr = NULL;
	ret -> nextLinkPtr = NULL;
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
	if(linkPtr -> elementPtr)
		free(linkPtr -> elementPtr);
	
	free(linkPtr);
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
	switch(type)
	{
		//[CREATE_STRUCTURE]
		case _event:
			return elementPtr -> event_.ID;
			break;
			
		case _building:
			return elementPtr -> building_.ID;
			break;
			
		case _buildingType:
			return elementPtr -> buildingType_.ID;
			break;
			
		case _item:
			return elementPtr -> item_.ID;
			break;
			
		case _person:
			return elementPtr -> person_.ID;
			break;
			
		default:
			printf("<newElement> Error: Unknown structure type (%d), should be in [%d;%d]\n", type, 0, last);
	}
	return - 1;
}

long int getLinkId(link* linkPtr)
{
	return getElementId(linkPtr -> elementPtr, linkPtr -> structType);
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

void displayLink(link toDisplay)
{
	switch(toDisplay.structType)
	{
		//[CREATE_STRUCTURE]
		case _event:
			//printf("[event] \n", toDisplay.elementPtr -> );
			break;
			
		case _building:
			break;
			
		case _buildingType:
			break;
			
		case _simulation:
			break;
			
		case _item:
			break;
			
		case _person:
			break;
			
		default:
			printf("<displayLink> Error: invalid data\n");
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
