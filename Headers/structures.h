#pragma once

#include <stdbool.h>

#include "generic.h"

#define MAN false
#define WOMAN true

//Needs files conversion if changes
//[CREATE_PERSON_PARTICULARITY]
#define personParticularitiesCount 4
#define wordLength 40
#define smallWordLength 20

//Inheritance structures: Created to be used in other structures
typedef struct location
{
	int x, y;
}location;

typedef struct stats
{
	int health, mentalHealth, hunger, hygiene, stamina;
}stats;

//System enum: Created to know structures [CREATE_STRUCTURE]
typedef enum structId
{
	_eventType, _event, _building, _buildingType, _simulation, _itemType, _item, _person, lastStructId
}structId;

//Simulator structures: They are the simulator's core
typedef struct savesFiles
{
	structId storedElements;
	char name[wordLength];
}savesFiles;

typedef struct building
{
	unsigned int ID, typeId;
	char name[wordLength];
	location loc;
}building;

typedef struct buildingType
{
	unsigned int ID;
	char name[wordLength];
}buildingType;

typedef struct itemType
{
	unsigned int ID;
	char name[wordLength];
}itemType;

typedef struct item
{
	unsigned int ID, itemTypeId;
	int proprietaryId;
	char name[wordLength];
}item;

typedef enum personParticularity
{
	//[CREATE_PERSON_PARTICULARITY]
	man, sporty, smoker, remoteWorker, lastPersonParticularityId
}personParticularity;

typedef struct person
{
	char firstName[wordLength], lastName[wordLength];
	unsigned int ID, houseId;
	unsigned short int sportiness;
	
	bool gender, smoker, remoteWorking;
	float salary, money;
	stats stats_;
}person;

typedef struct eventType // <=> action
{
	unsigned int ID;
	char name[wordLength];
	
	//Consequence on stats
	stats consequence;
	
	//Consequence on stats for specific personParticularities (sum with consequence ?)
	stats consequenceFor[personParticularitiesCount/* <=> personParticularity :: lastParticularityId*/];
}eventType;

typedef struct event
{
	unsigned int ID,
		transmitterId,
		receiverId,
		eventTypeId,
		eventTime;
	
	//Comment ?
}event;

typedef struct simulation
{
	unsigned int ID;
	unsigned long int simuledTime;
}simulation;

typedef union element
{
	//[CREATE_STRUCTURE]
	eventType eventType_;
	event event_;
	building building_;
	buildingType buildingType_;
	itemType itemType_;
	item item_;
	person person_;
	simulation simulation_;
}element;

typedef struct link
{
	long int ID;
	element* elementPtr;
	structId structType;
	
	struct link* nextLinkPtr;
}link;
