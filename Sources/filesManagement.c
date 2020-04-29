#define wordSize 40

#include <stdio.h>

#include "../Headers/filesManagement.h"

bool writeChain(link* chain, char *path)
{
	bool success = false;
	
	#ifdef DEBUG
	if(chain == NULL)
		printf("<writeChain> Warning: Null chain\n");
	#endif
	
	else
	{
		FILE* filePtr = fopen(path, "w+");
		while(chain != NULL)
		{
			//Saving
			success = (bool)fwrite(chain, sizeof(element), 1, filePtr);
			
			//Next link
			chain = chain -> nextLinkPtr;
		}
		fclose(filePtr);
	}
	
	return success;
}

link* readFile(char* path, structId type)
{
	FILE* filePtr = fopen(path, "r+");
	
	//Creating empty link
	link* linkPtr = newLink("readFile/else/while", type, false);
	element* tempElementPtr;
	
	if(filePtr == NULL)
	{
		#ifdef DEBUG
		printf("<readFile> Warning: File not found\n");
		#endif
		return NULL;
	}
	else while(fread(tempElementPtr, sizeof(element), 1, filePtr))
		if(tempElementPtr != NULL)
		{
			//Read element writting
			linkPtr -> elementPtr = tempElementPtr;
			
			//Creating next link
			linkPtr -> nextLinkPtr = newLink("readFile/else/while", type, false);
			
			//Going to the next one
			linkPtr = linkPtr -> nextLinkPtr;
		}
	
	#ifdef DEBUG
	if(tempElementPtr == NULL) 
		printf("<readFile> Warning: Empty file, null return\n");
	#endif
	
	fclose(filePtr);
	
	return linkPtr;
}
