#define wordSize 40

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

link* readChain(char* path, structId type)
{
	FILE* filePtr = fopen(path, "r+");
	bool keepReading = true;
	
	//Creating empty link
	link *chainHeadPtr = NULL, *linkPtr = NULL;
	element* tempElementPtr;
	
	if(filePtr == NULL)
	{
		#ifdef DEBUG
		printf("<readFile> Warning: File not found\n");
		#endif
		return NULL;
	}
	else if(fread(tempElementPtr, sizeof(element), 1, filePtr))
	{
		//Reading first element only
		//Creating first recipient link
		linkPtr = newLink("readFile/firstLink", type, false);
		
		//Keeping an eye to the first link pointer to return it as a chain header
		chainHeadPtr = linkPtr;
		
		//New element writting
		linkPtr -> elementPtr = tempElementPtr;
		
		while(fread(tempElementPtr, sizeof(element), 1, filePtr))
		{
			//Reading from second element to end
			//Creating new recipient link
			linkPtr -> nextLinkPtr = newLink("readFile/chain", type, false);
			
			//Going to next link
			linkPtr = linkPtr -> nextLinkPtr;
			
			//New element writting
			linkPtr -> elementPtr = tempElementPtr;
		}
	}
		
	//Undoing last action in while loop
	//linkPtr = prevLinkPtr;
	//freeLink(linkPtr -> nextLinkPtr);
	
	#ifdef DEBUG
	if(chainHeadPtr == NULL) 
		printf("<readFile> Warning: Empty file, null return\n");
	#endif
	
	fclose(filePtr);
	
	return chainHeadPtr;
}


savesFiles *initSavesFiles()
{
	savesFiles *globalSavesFiles = safeMalloc(sizeof(savesFiles) * lastStructId, "savesFiles initialisation");
	
	int structId_;
	for(structId_ = 0; structId_ < lastStructId; structId_++)
	{
		//Unexisting files
		strcpy(globalSavesFiles[structId_].name, "\0");
		globalSavesFiles[structId_].storedElements = structId_;
	}
	
	//Existing files
	strcpy(globalSavesFiles[_eventType].name, "eventTypes.dat");
	strcpy(globalSavesFiles[_buildingType].name, "buildingTypes.dat");
	strcpy(globalSavesFiles[_itemType].name, "itemTypes.dat");
	
	return globalSavesFiles;
}
