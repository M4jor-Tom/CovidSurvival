#pragma once

#include <stdbool.h>

void mainMenu();

void editionMenu();

void elementsMenu(char *optionsLabel);

//Displays a menu
int menu(int menuType, char *optionsLabel);

//Game setup function. Grabs information from player such as chosen simulation or character for new simulations.
link **setupGame();

//Runs the simulation till expected. Will go to the end of events if running till then.
void run(link** gameChains, unsigned long long int nextTime, bool forward);

//One occurence of the simulation returns false when the game ends
bool playGame(link **gameChains);

//Gets simulation time
unsigned long long int getTime(link** gameChains);


bool eventApply(link** gameChains, link* eventLinkPtr, bool forward);

//Like insertLink from link.h, inserts a link in a chain but only for events.
//Will insert event in the right place so it's time-sorted
link* insertEvent(link** gameChains, link* chain, link* eventLinkPtr, bool* couldInsert);

//Returns the player's ptr
person* getPlayerPtr(link* personsChain);