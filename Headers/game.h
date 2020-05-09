#pragma once

#include <stdbool.h>

void mainMenu();

void editionMenu();

void elementsMenu(char *optionsLabel);

int menu(int menuType, char *optionsLabel);

simulation setupGame();

bool playGame(simulation game);
