#pragma once

#include "structures.h"

//malloc functions

//Creates a link pointing to an element of the [type] structure. Writes [errorMessage] if can't
link* newLink(char* errorMessage, structId type);

//Creates an element to put in a link. newLink Calls this function
element *newElement(structId type, char* errorMessage);


link* lastLink(link* currentLinkPtr);

link* insertLink(link* headLinkPtr, link* toInsertLinkPtr);

int list_search(link* linksList, element* _elementPtr);



void displayLink(link toDisplay);

void displayChain(link* toDisplayPtr);
