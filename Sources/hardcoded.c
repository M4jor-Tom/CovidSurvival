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
			* housePtr = newLink("readChain/store", _placeType, true);
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
			.name = "Get out",
			.requiredItemTypeId = nullId,
			.requiredPlaceTypeId = 1	//Outside
		},
			shop =
		{
			.name = "Shop",
			.requiredItemTypeId = nullId,
			.requiredPlaceTypeId = 2	//Store
		},
			police =
		{
			.name = "Police control",
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
		setLinkId(getOutPtr, 1);
		setLinkId(shopPtr, 2);
		setLinkId(policePtr, 3);
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
			.name = "Food",
			.price = 5,
			.usesCount = 1
		},
			cert =
		{
			.name = "Exit certificate",
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
			* outTherePtr = newLink("readChain/house", _place, true),
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
			.name = "A store",
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

	return hardcodeHead;
}

link* ommitHardcoded(link* chain, savesFile save)
{
	int i;
	for (i = 0; i < hardcodedMaxId; i++)
		chain = deleteLink(chain, i);
	return chain;
}