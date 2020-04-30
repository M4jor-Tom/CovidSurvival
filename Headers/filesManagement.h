#pragma once

#include <stdbool.h>

#include "structures.h"

bool writeChain(link* chain, char* path);

link* readChain(char* path, structId Type);

savesFiles *initSavesFiles();
