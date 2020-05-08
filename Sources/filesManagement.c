#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../Headers/main.h"

//[CREATE_STRUCTURE]
savesFiles
	globalFiles[] = 
	{
		{
			.storedElements = _itemType,
			.name = "Item types",
			.path = "ressources/",
			.file = "itemType.txt"
		},
		{
			.storedElements = _buildingType,
			.name = "Building types",
			.path = "ressources/",
			.file = "buildingType.txt"
		},
		{
			.storedElements = _eventType,
			.name = "Event types",
			.path = "ressources/",
			.file = "eventType.txt"
		},
		{
			.storedElements = _simulation,
			.name = "Simulations",
			.path = "saves/",
			.file = "simulation.txt"
		}
	},
	
	gamesFiles[] = 
	{
		{
			.storedElements = _item,
			.name = "Items",
			.path = "saves/%d/",
			.file = "item.txt"
		},
		{
			.storedElements = _building,
			.name = "Buildings",
			.path = "saves/%d/",
			.file = "building.txt"
		},
		{
			.storedElements = _event,
			.name = "Events",
			.path = "saves/%d/",
			.file = "event.txt"
		},
		{
			.storedElements = _person,
			.name = "Persons",
			.path = "saves/simulation_%d/",
			.file = "person.txt"
		}
	};

bool writeChain(link* chain, savesFiles save)
{
	bool success = false;
	
	#ifdef DEBUG
	if
	(
	#endif
		mkSdir(save.path)
	#ifdef DEBUG
		 == -1
	)
		printf("<writeChain> Warning: Failed to create folder\n")
	#endif
	;
	
	#ifdef DEBUG
	if(chain == NULL)
		printf("<writeChain> Warning: Null chain\n");
		
	else
	#endif
	{
		char baseName[70] = "\0";
		strcpy(baseName, save.path);
		strcat(baseName, save.file);
		
		FILE *filePtr = fopen(baseName, "w");
		
		//FILE *fileTxtPtr = fopen("logs.txt", "ab");
		while(chain != NULL)
		{
			//Saving
			success = (bool)fwrite(chain -> elementPtr, sizeof(element), 1, filePtr);
			//fprintf(fileTxtPtr, "Wrote: Element of ID = %d and type ID = %d in %s;\n", getLinkId(chain), chain -> structType, path);
			
			//Next link
			chain = chain -> nextLinkPtr;
		}
		fclose(filePtr);
		//fclose(fileTxtPtr);
	}
	
	return success;
}

link *readChain(savesFiles save, structId type)
{
	char baseName[70] = "\0";
	strcat(baseName, save.path);
	strcat(baseName, save.file);
	
	FILE* filePtr = fopen(baseName, "r");
	bool keepReading = true;
	
	//Creating empty link
	link *chainHeadPtr = NULL, *linkPtr = NULL;
	element *elementsBufferPtr = NULL;
	link **chain;
	
	if(filePtr == NULL)
	{
		#ifdef DEBUG
		printf("<readFile> Warning: File %s not found\n", baseName);
		#endif
		return NULL;
	}
	else 
	{
		//Analysing file
		fseek(filePtr, 0, SEEK_END);
		unsigned int 
			size = ftell(filePtr),
			elementsCount = size / sizeof(element);
		fseek(filePtr, 0, SEEK_SET);
		
		//Allocating memory
		elementsBufferPtr = safeMalloc(size, "readChain/elementsBuffer");
		chain = safeMalloc(elementsCount * sizeof(link*), "readChain/linksArray");
		
		//Reading
		fread(elementsBufferPtr, 1, size, filePtr);
		
		//Chain structuration
		unsigned int i;
		for(i = 0; i < elementsCount; i++)
		{
			//Creating a new link in the chain, with read element
			chain[i] = newLink("readChain/single link", type, false);
			chain[i] -> elementPtr = &elementsBufferPtr[i];
			
			if(i)
			{
				//Chaining links
				chain[i - 1] -> nextLinkPtr = chain[i];
			}
			else if(i + 1 == elementsCount)
			{
				chain[i] -> nextLinkPtr = NULL;
			}
		}
	}
		
	//Undoing last action in while loop
	//linkPtr = prevLinkPtr;
	//freeLink(linkPtr -> nextLinkPtr);
	
	#ifdef DEBUG
	if(elementsBufferPtr == NULL) 
		printf("<readFile> Warning: Empty file, null return\n");
	#endif
	
	fclose(filePtr);
	
	return chain[0];
}
