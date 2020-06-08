#pragma once

#include <stdbool.h>

//Inheritance structures: Created to be used in other structures
typedef struct location
{
	int x, y;
}location;

typedef struct stats
{
	int health, mentalHealth, hunger, hygiene, stamina, money;
}stats;

//System enum: Created to know structures [CREATE_STRUCTURE]
typedef enum structId
{
	_itemType, _buildingType, _eventType, _simulation, //global structures
	_event, _building, _item, _person, //games structures
	lastStructId
}structId;

//Simulator structures: They are the simulator's core
typedef struct savesFile
{
	structId storedElements;
	char path[70], name[wordLength], file[wordLength];
}savesFile;

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
	bool livingPlace, marketPlace, carePlace;
}buildingType;

typedef struct itemType
{
	unsigned int ID, usesCount;
	char name[wordLength];
}itemType;

typedef struct item
{
	unsigned int 
		ID,
		proprietaryId,
		locationBuildingId,
		itemTypeId,
		usedCount;
	
	location loc;
}item;

typedef enum personParticularity
{
	//[CREATE_PERSON_PARTICULARITY]
	gender, sporty, smoker, remoteWorker, lastPersonParticularityId
}personParticularity;

typedef struct person
{
	char firstName[wordLength], lastName[wordLength];
	unsigned int ID, houseId;
	unsigned short int 
		gender, //0, 1, 2
		sportiness; //0, 1, 2
	
	bool smoker, remoteWorking;
	float salary, money;
	stats stats_;
}person;

typedef struct eventType // <=> action
{
	unsigned int 
		ID,
		requiredItemTypeId,
		requiredBuildingTypeId,
		itemTypeConsumption,
		duration_s;
	char name[wordLength];
	
	//Consequence on stats
	stats 
		onSuccess,
		onFailure;
	
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
	buildingType buildingType_;
	itemType itemType_;
	simulation simulation_;
	
	event event_;
	building building_;
	item item_;
	person person_;
}element;

typedef struct link
{
	long int ID;
	element* elementPtr;
	structId structType;
	
	struct link* nextLinkPtr;
}link;
