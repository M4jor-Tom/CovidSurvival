#include <time.h>
#include <string.h>
#include <stdio.h>

#include "../Headers/main.h"

void test(bool file, bool print);

int main()
{
	srand(time(NULL));
	
	test(false, false);
	
	extern savesFiles globalFiles[];
	extern savesFiles gameFiles[];
	
	int 
		mainSelect = 0,
		editionSelect = 0,
		elementSelect = 0,
		elementType = 0;
		
	link *existingChain = NULL, *newLinkPtr = NULL;
	
	do
	{
		mainSelect = menu(start);
		simulation sim;
		switch(mainSelect)
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
									case 1:
										//itemType
									case 2:
										//buildingType
									case 3:
										//eventType
									case 4:
										//simulation
										
										elementType = elementSelect - 1;
										existingChain = readChain(globalFiles[elementType], elementType);
										switch(editionSelect)
										{
											case 1:
												//Create
												newLinkPtr = newLink("main/create element", elementType, false);
												*newLinkPtr = grabLink(elementType);
												
												existingChain = insertLink(existingChain, newLinkPtr);
												writeChain(existingChain, globalFiles[elementType]);
												break;
											case 2:
												//Edit
											case 3:
												//Delete
												displayChain(existingChain);
										}
										break;
										
									case 5:
										//Leave
										break;
									
									default:
										printf("Select again\n\n");
								}
							}while(elementSelect != globalStructuresCount + 1);
							break;
							
						case 4:
							//Leave
							break;
							
						default:
							printf("Select again\n\n");
					}
				}while(editionSelect != 4);
				break;
				
			case 3:
				//Leave
				break;
				
			default:
				printf("Select again\n\n");
		}
	}while(mainSelect != 3);
	
	//freeChain(existingChain);
	freeLink(newLinkPtr);
	
	return 0;
}

void test(bool file, bool print)
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
	
	//Testing displaying
	link 
		*linkPtr_ = newLink("second test fails on link with element", structType_, true),
		*chain = linkPtr_;
	
	//Creating a chain of 3 links of each type of element
	for(i = 0; i < 20; i++)
	{
		//Next Link
		linkPtr_ -> nextLinkPtr = newLink("second test fails on link with element in loop", 0/*structType_*/, true);
		linkPtr_ = linkPtr_ -> nextLinkPtr;
		linkPtr_ -> elementPtr -> eventType_.ID = i + 1;
	}
	linkPtr_ -> structType = structType_;
	
	if(print)
	{
		printf("Existing structures: \n");
		displayChain(chain);
	}
	
	if(file)
		//writeChain(chain, "test/test.test");
	freeChain(chain);
	
	if(print)
	{
		/*printf("Deleted structures: \n");
		displayChain(chain);*/
		//printf("Read structures: \n");
		//displayChain(readChain("test.test", 0));
		
	}
}
