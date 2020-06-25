#pragma once

//Generates a bunch of essential data for the game
link* getHardcoded(savesFile save);

//Gets rid of hardcoded data loaded within the RAM
link* ommitHardcoded(link* chain, savesFile save);

void getOut(link **gameChains, bool forward);

bool shop(link** gameChains, bool forward);

void idle(link** gameChains, unsigned long long int time, bool forward);

bool policeControl(link **gameChains);