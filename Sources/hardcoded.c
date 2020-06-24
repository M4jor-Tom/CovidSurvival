#include <stdlib.h>

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
			.name = "Outside\n"
		},
			store =
		{
			.name = "Store\n",
			.marketPlace = true
		},
			house =
		{
			.name = "House\n",
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
				.requiredPlaceTypeId = 1	//Outside
			},
			shop =
			{
				.name = "Shop\n",
				.duration_s = 300,
				.requiredItemTypeId = nullId,
				.requiredPlaceTypeId = 2	//Store
			},
			police =
			{
				.name = "Police control\n",
				.duration_s = 300,
				.requiredItemTypeId = 2,	//Exit_certificate
				.requiredPlaceTypeId = nullId,
				.selectableOnFailure = true
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
			* certPtr = newLink("readChain/cert", _itemType, true);
		hardcodeHead = foodPtr;

		//Initialization
		itemType
			food =
			{
				.name = "Food\n",
				.price = 5,
				.usesCount = 1
			},
			cert =
			{
				.name = "Exit certificate\n",
				.usesCount = 1
			};

		//Chaining
		foodPtr->nextLinkPtr = certPtr;

		//Pass values
		foodPtr->elementPtr->itemType_ = food;
		certPtr->elementPtr->itemType_ = cert;

		//Setting Ids
		setLinkId(foodPtr, 1);
		setLinkId(certPtr, 2);
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
				.name = "Out there\n",
				.placeTypeId = 1	//outSide
			},
			house =
			{
				.name = "Your home\n",
				.placeTypeId = 3	//House
			},
			store =
			{
				.name = "Some polyvalent store\n",
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

bool shop(link** gameChains, unsigned long int shopId)
{
	bool bought = false;
	if (gameChains != NULL && gameChains[_placeType] != NULL && gameChains[_place] != NULL)
	{
		//Get all game itemTypes
		link* buyableItems = gameChains[_itemType];

		//Get only items located at the store
		/*element itemsFilter =
		{
			.itemType_
		};*/

		//[perf-flag] (Getting Id of bought item) Copy chain to filtered, choose within filtered, free filtered
		//buyableItems = filterChainBy(gameChains, _item, itemsFilter);
		link* selectedItemType = selectLink(buyableItems);
		unsigned long int selectedItemTypeId = getLinkId(selectedItemType);
		//freeChain(&buyableItems, NULL);


		//Getting data about bougt item and player's money
		//link *chosenItem = getLinkById(_item, chosenId, gameChains[_simulation]);
		//link *chosenItemType = getJoinedLink(chosenItem, _itemType, gameChains[_simulation], 1);
		person* playerPtr = &getLinkById(_person, playerId, gameChains[_simulation]) -> elementPtr -> person_;
		float
			money = playerPtr->stats_.money,
			price = selectedItemType->elementPtr->itemType_.price;
		//freeLink(&chosenItemType);

		if(price < money)
		{
			//The player buys the item
			//chosenItem->elementPtr->item_.proprietaryId = playerId;	//Because he bought it
			//chosenItem->elementPtr->item_.locationPersonId = playerId;	//And he took it on himself

			//Creating the item corresponding to the player's expectations
			link* createdItem = newLink("shop/item creation", _item, true);
			createdItem -> elementPtr -> item_.itemTypeId = selectedItemTypeId;
			createdItem -> elementPtr -> item_.proprietaryId = playerId;
			createdItem -> elementPtr -> item_.locationPersonId = playerId;
			createdItem -> elementPtr -> item_.locationPlaceId = nullId;
			gameChains[_item] = insertLink(gameChains[_item], createdItem);

			playerPtr->stats_.money = money - price;

			bought = true;
		}
	}
	return bought;
}