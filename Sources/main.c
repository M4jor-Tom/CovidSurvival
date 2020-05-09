#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
		elementType = 0,
		idChoice = 0;
		
	structId elementChoice = lastStructId;
		
	link 
		*existingChain = NULL, 
		*newLinkPtr = NULL,
		*selectedLinkPtr = NULL,
		*selectedLinkNextPtr = NULL;
	
	char editionLabel[15] = "\0";
	
	do
	{
		mainSelect = menu(start, NULL);
		simulation sim = setupGame();
		switch(mainSelect)
		{
			case 1:
				while(playGame(sim));
				break;
			
			case 2:
				do
				{	
					editionSelect = menu(edition, NULL);
					switch(editionSelect)
					{
						case 1:
							//Create
							if(!strcmp(editionLabel, "\0"))
								strcpy(editionLabel, "Create");
						case 2:
							//Edit
							if(!strcmp(editionLabel, "\0"))
								strcpy(editionLabel, "Edit");
						case 3:
							//Delete
							if(!strcmp(editionLabel, "\0"))
								strcpy(editionLabel, "Delete");
							do
							{
								elementSelect = menu(elements, editionLabel);
								switch(elementSelect)
								{
									case 1:
										//itemType
										if(elementChoice == lastStructId)
											elementChoice = _itemType;
									case 2:
										//buildingType
										if(elementChoice == lastStructId)
											elementChoice = _buildingType;
									case 3:
										//eventType
										if(elementChoice == lastStructId)
											elementChoice = _eventType;
									case 4:
										//simulation
										if(elementChoice == lastStructId)
											elementChoice = _simulation;
										
										//freeChain(existingChain);
										existingChain = readChain(globalFiles[elementChoice], elementChoice);
										switch(editionSelect)
										{
											case 1:
												//Create
												//freeLink(newLinkPtr);
												newLinkPtr = newLink("main/create element", elementChoice, false);
												*newLinkPtr = grabLink(elementChoice);
												
												existingChain = insertLink(existingChain, newLinkPtr);
												writeChain(existingChain, globalFiles[elementChoice]);
												break;
												
											case 2:
												//Edit
											case 3:
												//Delete
												
												//Display chain so user can see before choosing
												displayChain(existingChain);
												
												//User selection
												printf("Select %s of Id: ", globalFiles[elementChoice].name);
												scanf("%d", &idChoice);
												getchar();
												
												//Fetching
												selectedLinkPtr = chain_search(existingChain, idChoice);
												if(selectedLinkPtr != NULL && editionSelect == 2)
												{
													//If Id exists in chain AND is edited
													
													//Save a way to the rest of the chain
													selectedLinkNextPtr = selectedLinkPtr -> nextLinkPtr;
													
													//elementPtr is going to be re-malloc'd by grabLink
													//free(selectedLinkPtr -> elementPtr);
													
													//Give new data to this link
													*selectedLinkPtr = grabLink(elementChoice);
													
													//Give back Id and nextLinkPtr to selectedLink
													setLinkId(selectedLinkPtr, idChoice);
													selectedLinkPtr -> nextLinkPtr = selectedLinkNextPtr;
												}
												else if(selectedLinkPtr != NULL && editionSelect == 3)
												{
													//If Id exists in chain AND is deleted
													existingChain = deleteLink(existingChain, idChoice);
												}
												else
												{
													//Null result
													printf("Unknown %s Id: %d\n", globalFiles[elementChoice].name, idChoice);
												}
												writeChain(existingChain, globalFiles[elementChoice]);
										}
										break;
										
									case 5:
										//Leave
										strcpy(editionLabel, "\0");
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
