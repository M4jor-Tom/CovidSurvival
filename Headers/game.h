#pragma once

#include <stdbool.h>

void mainMenu();

void editionMenu();

void elementsMenu(char *optionsLabel);

int menu(int menuType, char *optionsLabel);

link **setupGame();

bool playGame(link **gameChains);
