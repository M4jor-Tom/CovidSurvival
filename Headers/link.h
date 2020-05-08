#pragma once

#include <stdbool.h>

// --- Memory functions ---

//Creates a link pointing to an element of the [type] structure. Writes [errorMessage] if can't
link *newLink(char *errorMessage, structId type, bool createElement);

//Creates an element to put in a link. newLink Calls this function
element *newElement(char *errorMessage);

//Frees a link as well as its element if it exists
void freeLink(link* linkPtr);

//Frees a chain as well as its elements if they exist
void freeChain(link* chain);


// --- Chaining functions ---

//Get to last link from a link's pointer
link* lastLink(link* currentLinkPtr);

//Inserts a created link et the end of a chain
link* insertLink(link* headLinkPtr, link *toInsertLinkPtr);

//Gets a link's element Id from the link's pointer
long int getLinkId(link* linkPtr);

//Gets a link's element Id from the element's pointer and type
long int getElementId(element* elementPtr, structId type);

link *chain_search(link *linkPtr, unsigned int ID);


// --- Human/Program interface functions ---

//Creates an array of character strings for each personnality a person can have (in the structure)
char **initParticularityLabels();

//Returns a link scanf'd by the user
link grabLink(structId structType);

//Launches grabLink() as long as the user wants it
link* grabChain(structId structType);


//Displays a link
void displayLink(link toDisplay);

//Launches displayLink as long as there are links to display in the chain
void displayChain(link *toDisplayPtr);