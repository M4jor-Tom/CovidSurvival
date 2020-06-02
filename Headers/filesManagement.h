#pragma once

#include <stdbool.h>


//Writes the elements of a chain's links in a file. Only elements are written
bool writeChain(link* chain, savesFile save);

//Creates a chain of links and puts an element 
link* readChain(savesFile save);

//Creates gameFiles from globalFiles' templates of gameFiles
savesFile *setGameFiles(link *simulationLinkPtr);

//Displays data about a file
void displayFile(savesFile toDisplay);

//Gets baseName from a savesFile
char *baseName(savesFile saves);
