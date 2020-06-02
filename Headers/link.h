#pragma once

#include <stdbool.h>

// --- Memory functions ---

//Creates a link pointing to an element of the [type] structure. Writes [errorMessage] if can't
link *newLink(char *errorMessage, structId type, bool createElement);

//Creates an element to put in a link. newLink Calls this function
element *newElement(char *errorMessage);

//Frees a link as well as its element if it exists
void freeLink(link *linkPtr);

//Frees a chain as well as its elements if they exist
void freeChain(link *chain, link *Excepted);


// --- Chaining functions ---

//Get to last link from a link's pointer
link* lastLink(link* currentLinkPtr);

//Deletes a link by Id and returns the list head (which can be different if the first link is the one deleted)
link* deleteLink(link *chain, unsigned int Id);

//Inserts a created link et the end of a chain
link* insertLink(link *headLinkPtr, link *toInsertLinkPtr);

//Gives an Id to both link and corresponding element
void setLinkId(link *linkPtr, unsigned int Id);

//Gives an Id to the corresponding element
void setElementId(element *elementPtr, structId type, unsigned int Id);

//Gets a link's element Id from the link's pointer
long int getLinkId(link *linkPtr);

//Gets a link's element Id from the element's pointer and type
long int getElementId(element *elementPtr, structId type);

//Returns a link's ptr from a chain within wich an Id's one has been searched. Returns NULL if Id doesn't exists
link *chain_search(link *chain, unsigned int ID);


// --- Human/Program interface functions ---

//Creates an array of character strings for each personnality a person can have (in the structure)
char **initParticularityLabels();

//Returns a link scanf'd by the user
link grabLink(structId structType);

//Launches grabLink() as long as the user wants it
link *grabChain(structId structType);

//Gets a link's ptr out of a chain by user choice
link *selectLink(link *chain);


//Displays a link
void displayLink(link toDisplay);

//Launches displayLink as long as there are links to display in the chain
void displayChain(link *toDisplayPtr);
