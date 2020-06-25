#include <stdlib.h>
#include <stdio.h>

#include "../Headers/main.h"

link* getHardcoded(savesFile save)
{
	link* hardcodeHead = NULL;
	if (save.storedElements == _placeType)
	{
		link
			* outSidePtr = newLink("readChain/outSide", _placeType, true),
			* storePtr = newLink("readChain/store", _placeType, true),
			* housePtr = newLink("readChain/house", _placeType, true);
		hardcodeHead = outSidePtr;

		//Initialization
		placeType
			outSide =
		{
			.name = "Outside"
		},
			store =
		{
			.name = "Store",
			.marketPlace = true
		},
			house =
		{
			.name = "House",
			.livingPlace = true
		};

		//Chaining
		outSidePtr->nextLinkPtr = storePtr;
		storePtr->nextLinkPtr = housePtr;

		//Pass values
		outSidePtr->elementPtr->placeType_ = outSide;
		storePtr->elementPtr->placeType_ = store;
		housePtr->elementPtr->placeType_ = house;

		//Setting Ids
		setLinkId(outSidePtr, 1);
		setLinkId(storePtr, 2);
		setLinkId(housePtr, 3);
	}
	else if (save.storedElements == _eventType)
	{
		link
			* getOutPtr = newLink("readChain/getOut", _eventType, true),
			* shopPtr = newLink("readChain/shop", _eventType, true),
			* policePtr = newLink("readChain/police", _eventType, true);
		hardcodeHead = getOutPtr;

		//Initialization
		eventType
			getOut =
			{
				.name = "Get out\n",
				.duration_s = 3600,
				.requiredItemTypeId = nullId,
				.requiredPlaceTypeId = 1,	//Outside
				.userSelectable = true,
				.onSuccess =
				{
					.mentalHealth = 30
				}
			},
			shop =
			{
				.name = "Shop",
				.duration_s = 300,
				.requiredItemTypeId = nullId,
				.requiredPlaceTypeId = 2,	//Store
				.userSelectable = true
			},
			police =
			{
				.name = "Police control",
				.duration_s = 300,
				.requiredItemTypeId = 2,	//Exit_certificate
				.requiredPlaceTypeId = nullId,
				.executableOnFailure = true,
				.onSuccess =
				{
					.mentalHealth = 15
				},
				.onFailure =
				{
					.mentalHealth = -40,
					.money = -135.0
				}
			};

		//Chaining
		getOutPtr->nextLinkPtr = shopPtr;
		shopPtr->nextLinkPtr = policePtr;

		//Pass values
		getOutPtr->elementPtr->eventType_ = getOut;
		shopPtr->elementPtr->eventType_ = shop;
		policePtr->elementPtr->eventType_ = police;

		//Setting Ids
		setLinkId(getOutPtr, getOutEventTypeId);
		setLinkId(shopPtr, shopEventTypeId);
		setLinkId(policePtr, policeControlEventTypeId);
	}
	else if (save.storedElements == _itemType)
	{
		link
			* foodPtr = newLink("readChain/food", _itemType, true),
			* certPtr = newLink("readChain/cert", _itemType, true),
			*maskPtr = newLink("readChain/mask", _itemType, true);
		hardcodeHead = foodPtr;

		//Initialization
		itemType
			food =
			{
				.name = "Food",
				.price = 5,
				.usesCount = 1
			},
			cert =
			{
				.name = "Exit certificate",
				.usesCount = 1
			},
			mask =
			{
				.name = "Mask",
				.usesCount = 1
			};

		//Chaining
		foodPtr->nextLinkPtr = certPtr;
		certPtr->nextLinkPtr = maskPtr;

		//Pass values
		foodPtr->elementPtr->itemType_ = food;
		certPtr->elementPtr->itemType_ = cert;
		maskPtr->elementPtr->itemType_ = mask;

		//Setting Ids
		setLinkId(foodPtr, 1);
		setLinkId(certPtr, 2);
		setLinkId(maskPtr, 3);
	}
	else if (save.storedElements == _place)
	{
		link
			* outTherePtr = newLink("readChain/outThere", _place, true),
			* housePtr = newLink("readChain/house", _place, true),
			* storePtr = newLink("readChain/store", _place, true);
		hardcodeHead = outTherePtr;

		//Initialization
		place
			outThere =
			{
				.name = "Out there",
				.placeTypeId = 1	//outSide
			},
			house =
			{
				.name = "Your home",
				.placeTypeId = 3	//House
			},
			store =
			{
				.name = "Some polyvalent store",
				.placeTypeId = 2	//Store
			};

		//Chaining
		outTherePtr->nextLinkPtr = housePtr;
		housePtr->nextLinkPtr = storePtr;

		//Pass values
		outTherePtr->elementPtr->place_ = outThere;
		housePtr->elementPtr->place_ = house;
		storePtr->elementPtr->place_ = store;

		//Setting Ids
		setLinkId(outTherePtr, 1);
		setLinkId(housePtr, 2);
		setLinkId(storePtr, 3);
	}
	else if (save.storedElements == _item)
	{
	link
		*sFoodPtr = newLink("readChain/sFood", _item, true),
		*yCertPtr = newLink("readChain/yCert", _item, true);
		hardcodeHead = sFoodPtr;

		//Initialization
		item
		sFood =
		{
			.itemTypeId = 1,	//Food
			.locationPlaceId = 3,	//In food store
			.proprietaryId = nullId,	//Owned by none
			.locationPersonId = nullId	//Held by none
		},
		yCert =
		{
			.itemTypeId = 2,	//Exit certificate
			.locationPlaceId = nullId,	//Not in a place
			.proprietaryId = playerId,	//Player is proprietary
			.locationPersonId = playerId	//In the player's pocket
		};

		//Chaining
		sFoodPtr->nextLinkPtr = yCertPtr;

		//Pass values
		sFoodPtr->elementPtr->item_ = sFood;
		yCertPtr->elementPtr->item_ = yCert;

		//Setting Ids
		setLinkId(sFoodPtr, 1);
		setLinkId(yCertPtr, 2);
	}

	return hardcodeHead;
}

link* ommitHardcoded(link* chain, savesFile save)
{
	int i;
	for (i = 0; i < hardcodedMaxId; i++)
		chain = deleteLink(chain, i);
	return chain;
}

void getOut(link** gameChains, bool forward)
{
	if (random(0, 100) < copsProba)
	{
		policeControl(gameChains);
		printf("\nCops controlled you\n");
		getch();
	}
}

bool shop(link** gameChains, bool forward)
{
	bool bought = false;
	if (gameChains != NULL && gameChains[_placeType] != NULL && gameChains[_place] != NULL)
	{
		//Get all game itemTypes
		link* selectedItemType = selectLink(gameChains[_itemType], true, NULL, (element){NULL});
		if(selectedItemType == NULL)
			return false;

		unsigned long int selectedItemTypeId = getLinkId(selectedItemType);


		//Getting data about bougt item and player's money
		person* playerPtr = &getLinkById(_person, playerId, gameChains[_simulation]) -> elementPtr -> person_;
		float
			money = playerPtr->stats_.money,
			price = selectedItemType->elementPtr->itemType_.price;

		if(price < money)
		{
			//The player buys the item
			//Creating the item corresponding to the player's expectations
			link* createdItem = newLink("shop/item creation", _item, true);
			createdItem -> elementPtr -> item_.itemTypeId = selectedItemTypeId;
			createdItem -> elementPtr -> item_.proprietaryId = playerId;
			createdItem -> elementPtr -> item_.locationPersonId = playerId;
			createdItem -> elementPtr -> item_.locationPlaceId = nullId;
			gameChains[_item] = insertLink(gameChains[_item], createdItem);

			gameChains[_person]->elementPtr->person_.stats_.money = money - price;

			bought = true;
		}
	}
	return bought;
}

void move(link** gameChains, bool forward)
{
	//Instruction
	printf("\nYou choose to move around !\n");

	//Data grab
	long int placeId = grabId(_place, gameChains[_simulation], true, (element){NULL});
	if (placeId != nullId)
	{
		//Go somewhere
		getLinkById(_person, playerId, gameChains[_simulation]) -> elementPtr ->person_.placeId = placeId;
	}
	else printf("\nWell, you stay where you are...\n");
}

void idle(link** gameChains, unsigned long long int time, bool forward)
{
	if (gameChains != NULL)
	{
		link* personsChain = gameChains[_person];
		int i, j = 0;
		while (personsChain != NULL)
		{
			for (i = 0, j = 0; i < time; i = i + timeForConsequence, j++)
			{
				gameChains[_person]->elementPtr->person_.stats_ =
					operateStats(
						gameChains[_person]->elementPtr->person_.stats_,
						(stats)
						{
							.hunger = -1,
							.hygiene = -1,
							.mentalHealth = -1,
							.stamina = 1
						}
					);
			}
			personsChain = personsChain -> nextLinkPtr;
		}
		printf("You idled enought to loose %d hunger, hygiene, and mentalhealth, and won %d stamina", j, j);
		setTime(gameChains, getTime(gameChains) + time);
	}
}


bool policeControl(link** gameChains)
{
	bool playerIsRegular = true;
	if(gameChains)
	{
		link
			*inventory = filterChainBy(gameChains[_item], (element){.item_.locationPersonId = playerId}),
			*ownedInventory = filterChainBy(inventory, (element) {.item_.proprietaryId = playerId}),
			*exitCertificate = filterChainBy(ownedInventory, (element){.item_.itemTypeId = 2});

		playerIsRegular = exitCertificate != NULL;

		freeChain(&exitCertificate, NULL);
		freeChain(&ownedInventory, NULL);
		freeChain(&inventory, NULL);

		link* playerLinkPtr = getLinkById(_person, playerId, gameChains[_simulation]);
		eventType policeControl = getLinkById(_eventType, policeControlEventTypeId, gameChains[_simulation])->elementPtr->eventType_;
		person player = playerLinkPtr->elementPtr->person_;

		playerLinkPtr->elementPtr->person_.stats_ = 
			operateStats(
				player.stats_,
				playerIsRegular 
					? policeControl.onSuccess 
					: policeControl.onFailure
			);

	}
	return playerIsRegular;
}