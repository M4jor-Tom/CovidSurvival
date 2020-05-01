#include <time.h>
#include <string.h>
#include <stdio.h>

#include "../Headers/structures.h"
#include "../Headers/generic.h"
#include "../Headers/link.h"
#include "../Headers/filesManagement.h"

void test(bool print);

int main()
{
	srand(time(NULL));
	
	savesFiles *globalSavesFiles = initSavesFiles();
	
	test(false);
	
	int select = 0, editionSelect = 0;
	
	do
	{
		select = menu(1);
		switch(select)
		{
			case 1:
				while(playGame());
				break;
			
			case 2:
				do
				{	
					editionSelect = menu(2);
					switch(editionSelect)
					{
						case 1:
							//Create
							
							break;
							
						case 2:
							//Edit
							
							break;
							
						case 3:
							//Delete
							
							break;
							
						case 4:
							break;
							
						default:
							printf("Select again\n\n");
					}
				}while(editionSelect != 4);
				break;
				
			case 3:
				break;
				
			default:
				printf("Select again\n\n");
		}
	}while(select != 3);
	
	//structId structure = _item;
	//displayChain(readFile("items.dat", _item));
	return 0;
}

void test(bool print)
{
	//Testing link constructor
	int i;
	structId last = lastStructId, structType_ = _eventType;
	for(i = 0; i < last; i++)
	{
		link* linkPtr = newLink("test fails on empty link", structType_, false);
		freeLink(linkPtr);
		
		linkPtr = newLink("test fails on link with element", structType_, true);
		freeLink(linkPtr);
	}
	
	//Testing eventType displaying
	link 
		*linkPtr_ = newLink("second test fails on link with element", structType_, true),
		*eventTypes = linkPtr_;
	linkPtr_ -> structType = structType_;
	
	for(i = 0; i < 5; i++)
	{
		//Next Link
		linkPtr_ -> nextLinkPtr = newLink("second test fails on link with element in loop", structType_, true);
		linkPtr_ = linkPtr_ -> nextLinkPtr;
		linkPtr_ -> elementPtr -> eventType_.ID = i + 1;
	}
	
	if(print)
	{
		printf("Existing eventTypes: \n");
		displayChain(eventTypes);
	}
		
	freeChain(eventTypes);
	
	if(print)
	{
		printf("Deleted eventTypes: \n");
		displayChain(eventTypes);
	}
}















/*
CHOISIR UN TYPE D'ELEMENT
-items <
-immeubles
-
-

*/
