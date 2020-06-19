#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../Headers/main.h"

//[CREATE_STRUCTURE]
savesFile
	globalFile[structuresCount] = 
	{
		{
			.storedElements = _itemType,
			.name = "Item type",
			.path = "ressources/",
			.file = "itemType.covid"
		},
		{
			.storedElements = _placeType,
			.name = "Place type",
			.path = "ressources/",
			.file = "placeType.covid"
		},
		{
			.storedElements = _eventType,
			.name = "Event type",
			.path = "ressources/",
			.file = "eventType.covid"
		},
		{
			.storedElements = _simulation,
			.name = "Simulation",
			.path = "saves/",
			.file = "simulation.covid"
		},
		{
			//gameFile template
			.storedElements = _event,
			.name = "Event",
			.path = "saves/simulation_%u/",
			.file = "event.surviver"
		},
		{
			//gameFile template
			.storedElements = _place,
			.name = "Place",
			.path = "saves/simulation_%u/",
			.file = "place.surviver"
		},
		{
			//gameFile template
			.storedElements = _item,
			.name = "Item",
			.path = "saves/simulation_%u/",
			.file = "item.surviver"
		},
		{
			//gameFile template
			.storedElements = _person,
			.name = "Person",
			.path = "saves/simulation_%u/",
			.file = "person.surviver"
		}
	};

link *ommitHardcoded(link *chain, savesFile save)
{
	if (save.storedElements == _placeType)
	{
		//Outside
		chain = deleteLink(chain, 1);

		//Market
		chain = deleteLink(chain, 2);
	}
	else if (save.storedElements == _eventType)
	{
		//Get out
		chain = deleteLink(chain, 1);

		//Shop
		chain = deleteLink(chain, 2);

		//Police control
		chain = deleteLink(chain, 3);
	}
	else if (save.storedElements == _itemType)
	{
		//food
		chain = deleteLink(chain, 1);

		//Certificate
		chain = deleteLink(chain, 2);
	}

	return chain;
}

link *getHardcoded(savesFile save)
{
	link *hardcodeHead = NULL;
	if (save.storedElements == _placeType)
	{
		link* outSide = newLink("readChain/outSide", _placeType, true);
		hardcodeHead = outSide;
		setLinkId(outSide, 1);

		//[EDIT_STRUCTURE]
		strcpy(outSide->elementPtr->placeType_.name, "Outside");
	}
	else if (save.storedElements == _eventType)
	{
		link
			* getOutPtr = newLink("readChain/getOut", _eventType, true),
			* shopPtr = newLink("readChain/shop", _eventType, true),
			* policePtr = newLink("readChain/police", _eventType, true);
		hardcodeHead = getOutPtr;

		//Initialization
		eventType getOut, shop, police;

		//Chaining
		getOutPtr->nextLinkPtr = shopPtr;
		shopPtr->nextLinkPtr = policePtr;

		//Given values
		getOut = (eventType)
		{
			.name = "Get out",
			.requiredItemTypeId = nullId,
			.requiredPlaceTypeId = nullId
		};

		shop = (eventType)
		{
			.name = "Shop",
			.requiredItemTypeId = nullId,
			.requiredPlaceTypeId = nullId
		};

		police = (eventType)
		{
			.name = "Police_control",
			.requiredItemTypeId = 2,	//Exit_certificate
			.requiredPlaceTypeId = nullId,
			.selectableOnFailure = true
		};

		//Pass values
		getOutPtr->elementPtr->eventType_ = getOut;
		shopPtr->elementPtr->eventType_ = shop;
		policePtr->elementPtr->eventType_ = police;

		//Setting Ids
		setLinkId(getOutPtr, 1);
		setLinkId(shopPtr, 2);
		setLinkId(policePtr, 3);
	}
	else if (save.storedElements == _itemType)
	{
		link
			* foodPtr = newLink("readChain/food", _itemType, true),
			* certPtr = newLink("readChain/cert", _itemType, true);
		hardcodeHead = foodPtr;

		//Initialization
		itemType food, cert;

		//Chaining
		foodPtr->nextLinkPtr = certPtr;

		//Given values
		food = (itemType)
		{
			.name = "Food",
			.price = 5,
			.usesCount = 1
		};

		cert = (itemType)
		{
			.name = "Exit certificate",
			.usesCount = 1
		};

		//Pass values
		foodPtr->elementPtr->itemType_ = food;
		certPtr->elementPtr->itemType_ = cert;

		//Setting Ids
		setLinkId(foodPtr, 1);
		setLinkId(certPtr, 2);
	}

	return hardcodeHead;
}

bool writeChain(link* chain, savesFile save)
{
	bool success = false;
	
	//Delete hard data before save (wich is hardcoded) to avoid dobloons
	chain = ommitHardcoded(chain, save);
	
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
	
	
	char baseName[70] = "\0";
	strcpy(baseName, save.path);
	strcat(baseName, save.file);
	
	FILE *filePtr = fopen(baseName, "w");
	
	//FILE *fileTxtPtr = fopen("logs.txt", "ab");
	if(chain == NULL)
	{
		//Null chain, delete file
		#ifdef DEBUG
		printf("<writeChain> Notice: Null chain, deleting file %s\n", baseName);
		#endif
		if(filePtr != NULL)
			fclose(filePtr);

		if(remove(baseName) == 0)
		{
			#ifdef DEBUG
			printf("<writeChain> file %s deleted\n", baseName);
			#endif
		}
	}
	else while(chain != NULL)
	{
		//Saving
		success = (bool)fwrite(chain -> elementPtr, sizeof(element), 1, filePtr);
		//fprintf(fileTxtPtr, "Wrote: Element of ID = %d and type ID = %d in %s;\n", getLinkId(chain), chain -> structType, path);
		
		//Next link
		chain = chain -> nextLinkPtr;
	}
	
	fclose(filePtr);
	//fclose(fileTxtPtr);
	
	return success;
}

link *readChain(savesFile save)
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
		#ifdef DEBUG_NOTICE
		printf("<readChain> Notice: File %s not found\n", baseName);
		#endif
		chain = NULL;
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
		//Chain structuration
		if(fread(elementsBufferPtr, 1, size, filePtr))
		{
			unsigned int i;
			for(i = 0; i < elementsCount; i++)
			{
				//Creating a new link in the chain, with read element
				chain[i] = newLink("readChain/single link", save.storedElements, false);
				chain[i] -> elementPtr = &elementsBufferPtr[i];
				chain[i] -> ID = getElementId(chain[i] -> elementPtr, save.storedElements);
				
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
		else
		{
			#ifdef DEBUG
			if(elementsBufferPtr == NULL) 
				printf("<readChain> Notice: %s is empty, deleting...\n", baseName);
			#endif
			fclose(filePtr);
			if(remove(baseName) == 0)
			{
				#ifdef DEBUG
				if(elementsBufferPtr == NULL) 
					printf("<readChain> %s deleted\n", baseName);
				#endif
			}
		}
	}
	
	if(filePtr != NULL)
		fclose(filePtr);
	
	//Add a constant data in the beginning of the chain
	link *hardcodeHead = getHardcoded(save);

	if(hardcodeHead != NULL)
	{
		if (chain != NULL)
			//First link is alone
			lastLink(hardcodeHead) -> nextLinkPtr = chain[0];
		else
			chain = safeMalloc(sizeof(link**), "readChain/hardcoded data");
		chain[0] = hardcodeHead;
	}
	
	if(chain != NULL)
		return chain[0];
	else return NULL;
}

savesFile *setGameFiles(link *simulationLinkPtr)
{
	//Create game files
	savesFile *gameFilePtr = safeMalloc(sizeof(savesFile) * structuresCount, "setGameFiles/gameFile");
	int i;
	for(i = 0; i < lastStructId; i++)
	{
		//For each global file
		//Decide whether the file's wideness is
		if(!strstr(gameFilePtr[i].path, "%u"))
			//GameWide file
			sprintf(gameFilePtr[i].path, globalFile[i].path, simulationLinkPtr -> ID);
		else
			//Global file
			strcpy(gameFilePtr[i].path, globalFile[i].path);
		
		strcpy(gameFilePtr[i].file, globalFile[i].file);
		strcpy(gameFilePtr[i].name, globalFile[i].name);
		gameFilePtr[i].storedElements = globalFile[i].storedElements;
	}
	return gameFilePtr;
}

void displayFile(savesFile toDisplay)
{
	printf(
		"<displayFile>\n\tStored element: %u\n\tName: %s\n\tBase name: %s%s",
		toDisplay.storedElements,
		toDisplay.name,
		toDisplay.path,
		toDisplay.file
	);
}

char *baseName(savesFile saves)
{
	//Creating return variable
	char *baseName = safeMalloc(sizeof(char) * 70, "baseName");
	baseName[0] = '\0';
	
	strcat(baseName, saves.path);
	strcat(baseName, saves.file);
	
	return baseName;
}
