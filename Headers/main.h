#pragma once

#ifdef _MSC_VER

	#define getch() _getch()
	#define getche() _getche()

#endif


#define DEBUG

#define nullId -1

#define SECONDS_PER_MINUTE 60
#define SECONDS_PER_HOUR 3600
#define SECONDS_PER_DAY 86400
#define SECONDS_PER_WEEK 604800


//Needs files conversion if changes
//[CREATE_PERSON_PARTICULARITY]
#define personParticularitiesCount 4
#define globalStructuresCount 4
#define structuresCount 8

#define wordLength 40
#define smallWordLength 20

#define MAN 0
#define WOMAN 1
#define OTHER 2

#define start 1
#define edition 2
#define elements 3


#include "dirent.h"
#include "generic.h"
#include "structures.h"
#include "link.h"
#include "filesManagement.h"
#include "game.h"