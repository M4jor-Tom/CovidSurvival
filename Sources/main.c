#include <time.h>
#include <string.h>

#include "../Headers/structures.h"
#include "../Headers/generic.h"
#include "../Headers/link.h"
#include "../Headers/filesManagement.h"

savesFiles *initGlobalSavesFiles();

int main()
{
	srand(time(NULL));
	
	savesFiles *globalSavesFiles = initGlobalSavesFiles();
	
	//Testing link constructor
	int i;
	structId last = lastStructId;
	for(i = 0; i < last; i++)
	{
		link* linkPtr = newLink("test fail", i, true);
		freeLink(linkPtr);
	}

	switch(mainMenu())
	{
		//case
	}
	//structId structure = _item;
	//displayChain(readFile("items.dat", _item));
	return 0;
}

savesFiles *initGlobalSavesFiles()
{
	savesFiles *globalSavesFiles = safeMalloc(sizeof(savesFiles) * lastStructId, "globalSavesFiles initialisation");
	
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
