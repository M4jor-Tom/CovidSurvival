#pragma once

#include <stdbool.h>

void mainMenu();

void editionMenu();

void elementsMenu(char *optionsLabel);

//Displays a menu
int menu(int menuType, char *optionsLabel);

//Game setup function. Grabs information from player such as chosen simulation or character for new simulations.
link **setupGame();

//One occurence of the simulation returns false when the game ends
bool playGame(link **gameChains);

//Like insertLink from link.h, inserts a link in a chain but only for events.
//Will insert event in the right place so it's time-sorted
link *insertEvent(link *chain, link *eventLinkPtr);