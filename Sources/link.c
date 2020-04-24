#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/structures.h"
#include "../Headers/link.h"

link* newLink(char* errorMessage, structId type)
{
	link* ret = (link*)safeMalloc(sizeof(link), errorMessage);
	ret -> elementPtr = NULL;
	ret -> nextLinkPtr = NULL;
	ret -> elementPtr = newElement(type, errorMessage);
	return ret;
}

element *newElement(structId type, char* errorMessage)
{
	structId last = lastStructId;
	element* elementPtr = (element*)safeMalloc(sizeof(element), errorMessage);
			
	switch(type)
	{
		//[CREATE_STRUCTURE]
		case _event:
			strcpy(elementPtr -> event_.name, "\0");
			break;
			
		case _building:
			break;
			
		case _buildingType:
			break;
			
		case _item:
			break;
			
		case _person:
			break;
			
		default:
			printf("<newElement> Error: Unknown structure type (%d), should be in [%d;%d]\n", type, 0, last);
	}
	return elementPtr;
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

int list_search(link* linksList, element* _elementPtr)
{
	int i = 0;
	while(linksList != NULL)
	{
		if(linksList -> elementPtr == _elementPtr)
			return i;
		i++;
		linksList = linksList -> nextLinkPtr;
	}
	return - 1;
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
