#pragma once

//Generates a bunch of essential data for the game
link* getHardcoded(savesFile save);

//Gets rid of hardcoded data loaded within the RAM
link* ommitHardcoded(link* chain, savesFile save);

void getOut(link **gameChains);

void shop(link **gameChains, unsigned long int shopId);

void policeControl(link **gameChains);