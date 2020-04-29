#pragma once

#include <stdbool.h>

#include "generic.h"

#define MAN false
#define WOMAN true

//Needs files conversion if changes
//[CREATE_PERSON_PARTICULARITY]
#define personParticularitiesCount 4
#define wordLength 40

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
	//[CREATE_STRUCTURE]
	_eventType, _event, _building, _buildingType, _simulation, _itemType, _item, _person, lastStructId
}structId;

//Simulator structures: They are the simulator's core
typedef struct savesFiles
{
	structId storedElements;
	char name[wordLength];
}savesFiles;


/*typedef enum eventTypeId
{
	working, walking, running, shopping, eating, sleeping, lastActionId
}eventTypeId;*/

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
	man, sporty, smoker, remoteWorker, lastParticularityId
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

typedef struct eventType
{
	unsigned int ID;
	char name[wordLength];
	stats consequence;
	stats consequenceFor[personParticularitiesCount];
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
}element;

typedef struct link
{
	element* elementPtr;
	structId structType;
	
	struct link* nextLinkPtr;
}link;

typedef struct simulation
{
	unsigned int ID;
	unsigned long int simuledTime;
	
	savesFiles simulationData;
	
	//Array containing link headers adress to each element type
	link** dataStructures;
}simulation;
