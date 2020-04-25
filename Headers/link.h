#pragma once

#include "structures.h"

//malloc functions

//Creates a link pointing to an element of the [type] structure. Writes [errorMessage] if can't
link* newLink(char* errorMessage, structId type);

//Creates an element to put in a link. newLink Calls this function
element *newElement(structId type, char* errorMessage);

//Get to last link from a link's pointer
link* lastLink(link* currentLinkPtr);

//Inserts a created link et the end of a chain
link* insertLink(link* headLinkPtr, link* toInsertLinkPtr);

//Gets a link's element Id from the link's pointer
long int getLinkId(link* linkPtr);

//Gets a link's element Id from the element's pointer and type
long int getElementId(element* elementPtr, structId type);

link* chain_search(link* linkPtr, unsigned int ID);



void displayLink(link toDisplay);

void displayChain(link* toDisplayPtr);
