#include <time.h>
#include <string.h>
#include <stdio.h>

#include "../Headers/structures.h"
#include "../Headers/generic.h"
#include "../Headers/link.h"
#include "../Headers/filesManagement.h"
#include "../Headers/game.h"

void test(bool print);

int main()
{
	srand(time(NULL));
	
	savesFiles *globalSavesFiles = initSavesFiles();
	
	test(false);
	
	int select = 0, editionSelect = 0, elementSelect = 0;
	
	do
	{
		select = menu(start);
		simulation sim;
		switch(select)
		{
			case 1:
				while(playGame(sim));
				break;
			
			case 2:
				do
				{	
					editionSelect = menu(edition);
					switch(editionSelect)
					{
						case 1:
							//Create
						case 2:
							//Edit
						case 3:
							//Delete
							do
							{
								elementSelect = menu(elements);
								switch(elementSelect)
								{
									case 4:
										break;
									
									default:
										printf("Select again\n\n");
								}
							}while(elementSelect != 4);
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
	structId last = lastStructId, structType_ = 0;
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
		*chain = linkPtr_;
	
	for(structType_ = 0; structType_ < last; structType_++)
	{
		for(i = 0; i < 3; i++)
		{
			//Next Link
			linkPtr_ -> nextLinkPtr = newLink("second test fails on link with element in loop", structType_, true);
			linkPtr_ = linkPtr_ -> nextLinkPtr;
			linkPtr_ -> elementPtr -> eventType_.ID = i + 1;
		}
		linkPtr_ -> structType = structType_;
	}
	
	if(print)
	{
		printf("Existing structures: \n");
		displayChain(chain);
	}
		
	freeChain(chain);
	
	if(print)
	{
		printf("Deleted structures: \n");
		displayChain(chain);
	}
}
