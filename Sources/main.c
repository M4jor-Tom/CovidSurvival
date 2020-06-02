#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../Headers/main.h"

void test(bool file, bool print);

int main()
{
	system("color F0");
	srand(time(NULL));
	test(false, false);
	
	extern savesFile globalFile[];
	
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
		simulation *sim;
		switch(mainSelect)
		{
			case 1:
				sim = setupGame();
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
						case 4:
							//Watch
							if(!strcmp(editionLabel, "\0"))
								strcpy(editionLabel, "Watch");
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
										
										//freeChain(existingChain, NULL);
										existingChain = readChain(globalFile[elementChoice]);
										switch(editionSelect)
										{
											case 1:
												//Create
												//freeLink(newLinkPtr);
												newLinkPtr = newLink("main/create element", elementChoice, false);
												*newLinkPtr = grabLink(elementChoice);
												
												existingChain = insertLink(existingChain, newLinkPtr);
												writeChain(existingChain, globalFile[elementChoice]);
												
												//If user wants to do things with another element
												printf("->");
												getch();
												system("cls");
												elementChoice = lastStructId;
												break;
												
											case 2:
												//Edit
											case 3:
												//Delete
											case 4:
												//Watch
												
												//Display chain so user can see (before choosing ?)
												displayChain(existingChain);
												if(editionSelect == 4)
												{
													//Watch
													/*printf("\nHit any key to go\n");
													getch();*/
												}
												else
												{
													//If the point is not just to watch
													//User selection
													printf("Select %s of Id: ", globalFile[elementChoice].name);
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
														printf("Unknown %s Id: %d\n", globalFile[elementChoice].name, idChoice);
													}
													writeChain(existingChain, globalFile[elementChoice]);
												}
												
												//If user wants to do things with another element
												printf("->");
												getch();
												system("cls");
												elementChoice = lastStructId;
										}
										break;
										
									case 5:
										//Leave
										//Maybe user will want to select another type of element after
										strcpy(editionLabel, "\0");
										break;
									
									default:
										printf("Select again\n\n");
								}
								
							}while(elementSelect != globalStructuresCount + 1);
							break;
							
						case 5:
							//Leave
							break;
							
						default:
							printf("Select again\n\n");
					}
				}while(editionSelect != 5);
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
		freeChain(chain, NULL);
	
	if(print)
	{
		/*printf("Deleted structures: \n");
		displayChain(chain);*/
		//printf("Read structures: \n");
		
	}
}
