#pragma once

#define start 1
#define edition 2
#define elements 3

#include <stdbool.h>

#include "generic.h"
#include "structures.h"
#include "link.h"

void mainMenu();

void editionMenu();

int menu(int menuType);

bool playGame(simulation game);
