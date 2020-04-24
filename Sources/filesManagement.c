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
	link* recipientHeadListPtr = NULL;
	element* elementPtr = NULL;
	
	if(filePtr == NULL)
	{
		#ifdef DEBUG
		printf("<readFile> Warning: File not found\n");
		#endif
		return NULL;
	}
	else while(fread(elementPtr, sizeof(element), 1, filePtr))
	{
		recipientHeadListPtr = newLink("readFile/else/while", type);
	}
	
	#ifdef DEBUG
	if(recipientHeadListPtr == NULL) 
		printf("<readFile> Warning: NULL return\n");
	#endif
	
	fclose(filePtr);
	
	return recipientHeadListPtr;
}
