#pragma once

#include <stdbool.h>

#include "structures.h"

bool writeChain(link* chain, char* path);

link* readFile(char* path, structId Type);
