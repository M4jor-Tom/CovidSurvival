#pragma once

#include <stdbool.h>

#include "generic.h"

#define man 0
#define woman 1

#define wordLength 40

//Inheritance structures: Created to be used in other structures
typedef struct location
{
	int x, y;
}location;

typedef struct stats
{
	int health, mentalHealth, hunger, hygiene;
}stats;

//System enum: Created to know structures [CREATE_STRUCTURE]
typedef enum structId
{
	_event, _building, _buildingType, _simulation, _item, _person, lastStructId
}structId;

//Simulator structures: They are the simulator's core
typedef enum actionId
{
	working, walking, running, shopping, eating, sleeping, lastActionId
}actionId;

typedef struct action
{
	unsigned int ID;
	stats consequence;
}action;

typedef struct event
{
	unsigned int transmitterId,
		receiverId,
		actionId,
		eventTime;
	
	//Comment ?
}event;

typedef struct building
{
	unsigned int ID, typeId;
	location loc;
}building;

typedef struct buildingType
{
	
}buildingType;

typedef struct item
{
	unsigned int ID;
	int proprietaryId;
	char name[wordLength];
}item;

typedef enum no_choice_yes
{
	no, choice, yes
}no_choice_yes;

typedef struct person
{
	char name[wordLength];
	unsigned int ID, houseId;
	unsigned short int sportiness;
	no_choice_yes remoteWorking;
	
	bool gender, smoker;
	float salary, money;
	stats stats_;
}person;

typedef union element
{
	event event_;
	building building_;
	buildingType buildingType_;
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
	unsigned long int time;
	link* buildings, persons, items;
}simulation;
