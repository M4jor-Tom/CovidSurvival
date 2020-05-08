#pragma once

#include <stdbool.h>


//Writes the elements of a chain's links in a file. Only elements are written
bool writeChain(link* chain, char* path);

//Creates a chain of links and puts an element 
link* readChain(char* path, structId Type);